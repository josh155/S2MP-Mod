#include "pch.h"
#include "DemoUI.hpp"
#include "Console.hpp"
#include "GameUtil.hpp"
#include "Hook.hpp"
#include "structs.h"

#include <d3d11.h>
#include <dxgi.h>
#include <filesystem>
#include <vector>
#include <string>
#include <atomic>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// ImGui's Win32 backend message handler (defined in imgui_impl_win32.cpp).
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace
{
	// --- swapchain Present / ResizeBuffers originals ---
	using Present_t = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
	using ResizeBuffers_t = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
	Present_t oPresent = nullptr;
	ResizeBuffers_t oResizeBuffers = nullptr;

	// --- D3D / window state ---
	bool g_initialized = false;
	std::atomic<bool> g_visible{ false };
	ID3D11Device* g_device = nullptr;
	ID3D11DeviceContext* g_context = nullptr;
	ID3D11RenderTargetView* g_rtv = nullptr;
	HWND g_window = nullptr;
	WNDPROC g_origWndProc = nullptr;

	// --- demo list ---
	std::vector<std::string> g_demos;
	int g_selected = 0;

	void refresh_demos()
	{
		g_demos.clear();
		std::error_code ec;
		if (std::filesystem::exists("demos", ec))
		{
			for (const auto& entry : std::filesystem::directory_iterator("demos", ec))
			{
				if (entry.is_regular_file(ec) && entry.path().extension() == ".demo")
				{
					g_demos.push_back(entry.path().filename().string());
				}
			}
		}
		if (g_selected >= static_cast<int>(g_demos.size()))
		{
			g_selected = 0;
		}
	}

	void create_render_target(IDXGISwapChain* swapchain)
	{
		ID3D11Texture2D* backbuffer = nullptr;
		if (SUCCEEDED(swapchain->GetBuffer(0, IID_PPV_ARGS(&backbuffer))) && backbuffer)
		{
			g_device->CreateRenderTargetView(backbuffer, nullptr, &g_rtv);
			backbuffer->Release();
		}
	}

	LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (g_visible.load())
		{
			ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);

			// Swallow input while the menu is open so the game doesn't react to it.
			switch (msg)
			{
			case WM_LBUTTONDOWN: case WM_LBUTTONUP: case WM_LBUTTONDBLCLK:
			case WM_RBUTTONDOWN: case WM_RBUTTONUP: case WM_RBUTTONDBLCLK:
			case WM_MBUTTONDOWN: case WM_MBUTTONUP: case WM_MBUTTONDBLCLK:
			case WM_MOUSEWHEEL: case WM_MOUSEMOVE:
			case WM_KEYDOWN: case WM_KEYUP: case WM_CHAR:
			case WM_SYSKEYDOWN: case WM_SYSKEYUP:
				return TRUE;
			default:
				break;
			}
		}

		return CallWindowProc(g_origWndProc, hwnd, msg, wparam, lparam);
	}

	void draw_window()
	{
		ImGui::SetNextWindowSize(ImVec2(380.0f, 150.0f), ImGuiCond_Always);
		bool open = g_visible.load();
		ImGui::Begin("S2MP Demo Player", &open,
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

		if (g_demos.empty())
		{
			ImGui::TextUnformatted("No demos found in demos/");
		}
		else
		{
			ImGui::SetNextItemWidth(-1.0f);
			const char* preview = g_demos[g_selected].c_str();
			if (ImGui::BeginCombo("##demo", preview))
			{
				for (int i = 0; i < static_cast<int>(g_demos.size()); ++i)
				{
					const bool selected = (i == g_selected);
					if (ImGui::Selectable(g_demos[i].c_str(), selected))
					{
						g_selected = i;
					}
					if (selected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::Spacing();

			if (ImGui::Button("Play", ImVec2(110.0f, 0.0f)))
			{
				GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "demo_play " + g_demos[g_selected] + "\n");
			}
			ImGui::SameLine();
			if (ImGui::Button("Stop", ImVec2(110.0f, 0.0f)))
			{
				GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "demo_stop\n");
			}
		}

		ImGui::Spacing();
		if (ImGui::Button("Refresh"))
		{
			refresh_demos();
		}

		ImGui::End();
		g_visible.store(open);
	}

	void init_imgui(IDXGISwapChain* swapchain)
	{
		swapchain->GetDevice(IID_PPV_ARGS(&g_device));
		if (!g_device)
		{
			return;
		}
		g_device->GetImmediateContext(&g_context);

		DXGI_SWAP_CHAIN_DESC desc{};
		swapchain->GetDesc(&desc);
		g_window = desc.OutputWindow;

		create_render_target(swapchain);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::GetIO().IniFilename = nullptr; // don't write imgui.ini next to the game
		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(g_window);
		ImGui_ImplDX11_Init(g_device, g_context);

		g_origWndProc = reinterpret_cast<WNDPROC>(
			SetWindowLongPtr(g_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wnd_proc)));

		refresh_demos();
		g_initialized = true;
		Console::printf("[demo] ImGui demo menu ready (press INSERT)");
	}

	HRESULT __stdcall present_hook(IDXGISwapChain* swapchain, UINT sync_interval, UINT flags)
	{
		if (!g_initialized)
		{
			init_imgui(swapchain);
		}

		// INSERT toggles the menu.
		static bool prev_key = false;
		const bool key = (GetAsyncKeyState(VK_INSERT) & 0x8000) != 0;
		if (key && !prev_key)
		{
			g_visible.store(!g_visible.load());
		}
		prev_key = key;

		if (g_initialized && g_visible.load() && g_rtv)
		{
			ImGui::GetIO().MouseDrawCursor = true; // game hides the OS cursor; draw our own

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			draw_window();

			ImGui::Render();
			g_context->OMSetRenderTargets(1, &g_rtv, nullptr);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}

		return oPresent(swapchain, sync_interval, flags);
	}

	HRESULT __stdcall resize_buffers_hook(IDXGISwapChain* swapchain, UINT buffer_count, UINT width,
		UINT height, DXGI_FORMAT format, UINT flags)
	{
		if (g_rtv)
		{
			g_rtv->Release();
			g_rtv = nullptr;
		}

		const HRESULT hr = oResizeBuffers(swapchain, buffer_count, width, height, format, flags);
		create_render_target(swapchain);
		return hr;
	}

	// Build a throwaway device+swapchain so we can read the IDXGISwapChain vtable
	// (Present is slot 8, ResizeBuffers is slot 13) and hook the game's real ones.
	bool hook_swapchain()
	{
		WNDCLASSEXA wc{};
		wc.cbSize = sizeof(wc);
		wc.lpfnWndProc = DefWindowProcA;
		wc.hInstance = GetModuleHandleA(nullptr);
		wc.lpszClassName = "S2MPDemoUIDummy";
		RegisterClassExA(&wc);

		HWND dummy = CreateWindowA(wc.lpszClassName, "dummy", WS_OVERLAPPEDWINDOW,
			0, 0, 64, 64, nullptr, nullptr, wc.hInstance, nullptr);
		if (!dummy)
		{
			UnregisterClassA(wc.lpszClassName, wc.hInstance);
			return false;
		}

		DXGI_SWAP_CHAIN_DESC sd{};
		sd.BufferCount = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = dummy;
		sd.SampleDesc.Count = 1;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		const D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
		IDXGISwapChain* swapchain = nullptr;
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		D3D_FEATURE_LEVEL got{};

		HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
			levels, 1, D3D11_SDK_VERSION, &sd, &swapchain, &device, &got, &context);
		if (FAILED(hr))
		{
			hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0,
				levels, 1, D3D11_SDK_VERSION, &sd, &swapchain, &device, &got, &context);
		}

		bool ok = false;
		if (SUCCEEDED(hr) && swapchain)
		{
			void** vtable = *reinterpret_cast<void***>(swapchain);
			void* present_addr = vtable[8];
			void* resize_addr = vtable[13];

			ok = Hook::create("IDXGISwapChain::Present", present_addr,
				reinterpret_cast<void*>(&present_hook), reinterpret_cast<void**>(&oPresent));
			Hook::create("IDXGISwapChain::ResizeBuffers", resize_addr,
				reinterpret_cast<void*>(&resize_buffers_hook), reinterpret_cast<void**>(&oResizeBuffers));
		}

		if (swapchain) swapchain->Release();
		if (context) context->Release();
		if (device) device->Release();
		DestroyWindow(dummy);
		UnregisterClassA(wc.lpszClassName, wc.hInstance);

		return ok;
	}
}

namespace DemoUI
{
	void toggle()
	{
		g_visible.store(!g_visible.load());
	}

	void init()
	{
		if (!hook_swapchain())
		{
			Console::printf("[demo] failed to hook swapchain; ImGui demo menu unavailable");
			return;
		}
		GameUtil::addCommand("demo_menu", &DemoUI::toggle);
	}
}
