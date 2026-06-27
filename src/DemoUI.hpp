#pragma once

// Simple in-game ImGui overlay: a non-resizable window with a dropdown of the
// demos in demos/ and a Play button. Toggle with the INSERT key (or the
// "demo_menu" command). Renders via a hooked IDXGISwapChain::Present.
namespace DemoUI
{
	void init();
	void toggle();
}
