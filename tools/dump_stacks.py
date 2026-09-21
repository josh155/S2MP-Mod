"""Scan every thread's stack in s2_mp64_ship.exe for module return addresses.

Use when the game is HALTED (e.g. sitting on a Fatal Error dialog) and you need
the call chain of whatever raised it. Arxan hides the direct references, but the
return addresses are still sitting on the stack.

Addresses are printed as IDA addresses:
    IDA = runtime_VA - module_base
(game.cpp: base = GetModuleHandle(NULL) + 0x1000, _b(v) = base + v, and every
literal in demo_game.hpp is IDA - 0x1000, so the +0x1000 cancels out.)

    python tools/dump_stacks.py [--depth 4096] [--all]

By default only threads whose stack contains module addresses are printed.
"""

from __future__ import annotations

import argparse
import ctypes
import ctypes.wintypes as w
import sys

kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)

TH32CS_SNAPTHREAD = 0x04
TH32CS_SNAPMODULE = 0x08
TH32CS_SNAPMODULE32 = 0x10
TH32CS_SNAPPROCESS = 0x02

PROCESS_ALL = 0x1F0FFF
THREAD_ALL = 0x1F03FF

CONTEXT_AMD64 = 0x100000
CONTEXT_CONTROL = CONTEXT_AMD64 | 0x1
CONTEXT_INTEGER = CONTEXT_AMD64 | 0x2
CONTEXT_FULL = CONTEXT_CONTROL | CONTEXT_INTEGER | (CONTEXT_AMD64 | 0x8)

CONTEXT_SIZE = 1232
OFF_RSP = 0x98
OFF_RIP = 0xF8


class THREADENTRY32(ctypes.Structure):
    _fields_ = [("dwSize", w.DWORD), ("cntUsage", w.DWORD),
                ("th32ThreadID", w.DWORD), ("th32OwnerProcessID", w.DWORD),
                ("tpBasePri", w.LONG), ("tpDeltaPri", w.LONG),
                ("dwFlags", w.DWORD)]


class PROCESSENTRY32W(ctypes.Structure):
    _fields_ = [("dwSize", w.DWORD), ("cntUsage", w.DWORD),
                ("th32ProcessID", w.DWORD), ("th32DefaultHeapID", ctypes.c_void_p),
                ("th32ModuleID", w.DWORD), ("cntThreads", w.DWORD),
                ("th32ParentProcessID", w.DWORD), ("pcPriClassBase", w.LONG),
                ("dwFlags", w.DWORD), ("szExeFile", w.WCHAR * 260)]


class MODULEENTRY32W(ctypes.Structure):
    _fields_ = [("dwSize", w.DWORD), ("th32ModuleID", w.DWORD),
                ("th32ProcessID", w.DWORD), ("GlblcntUsage", w.DWORD),
                ("ProccntUsage", w.DWORD), ("modBaseAddr", ctypes.POINTER(ctypes.c_byte)),
                ("modBaseSize", w.DWORD), ("hModule", w.HMODULE),
                ("szModule", w.WCHAR * 256), ("szExePath", w.WCHAR * 260)]


def find_process(name: str) -> int:
    snap = kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
    entry = PROCESSENTRY32W()
    entry.dwSize = ctypes.sizeof(entry)
    ok = kernel32.Process32FirstW(snap, ctypes.byref(entry))
    while ok:
        if entry.szExeFile.lower() == name.lower():
            kernel32.CloseHandle(snap)
            return entry.th32ProcessID
        ok = kernel32.Process32NextW(snap, ctypes.byref(entry))
    kernel32.CloseHandle(snap)
    return 0


def main_module(pid: int):
    snap = kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid)
    entry = MODULEENTRY32W()
    entry.dwSize = ctypes.sizeof(entry)
    if not kernel32.Module32FirstW(snap, ctypes.byref(entry)):
        kernel32.CloseHandle(snap)
        return 0, 0
    base = ctypes.cast(entry.modBaseAddr, ctypes.c_void_p).value or 0
    size = entry.modBaseSize
    kernel32.CloseHandle(snap)
    return base, size


def threads_of(pid: int) -> list[int]:
    out = []
    snap = kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0)
    entry = THREADENTRY32()
    entry.dwSize = ctypes.sizeof(entry)
    ok = kernel32.Thread32First(snap, ctypes.byref(entry))
    while ok:
        if entry.th32OwnerProcessID == pid:
            out.append(entry.th32ThreadID)
        ok = kernel32.Thread32Next(snap, ctypes.byref(entry))
    kernel32.CloseHandle(snap)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description="Dump module return addresses per thread")
    ap.add_argument("--process", default="s2_mp64_ship.exe")
    ap.add_argument("--depth", type=int, default=8192, help="stack bytes to scan")
    ap.add_argument("--all", action="store_true", help="print threads with no hits too")
    ap.add_argument("--max-hits", type=int, default=40)
    args = ap.parse_args()

    pid = find_process(args.process)
    if not pid:
        print(f"{args.process} not running")
        return 2
    base, size = main_module(pid)
    if not base:
        print("could not read module base")
        return 2
    print(f"pid {pid}  module base 0x{base:X}  size 0x{size:X}")
    print("addresses below are IDA addresses (VA - base)\n")

    proc = kernel32.OpenProcess(PROCESS_ALL, False, pid)
    if not proc:
        print(f"OpenProcess failed: {ctypes.get_last_error()} (run as admin?)")
        return 2

    buf = ctypes.create_string_buffer(args.depth)
    read = ctypes.c_size_t(0)
    ctx = ctypes.create_string_buffer(CONTEXT_SIZE + 16)
    # CONTEXT must be 16-byte aligned.
    aligned = ctypes.cast(
        (ctypes.addressof(ctx) + 15) & ~15, ctypes.POINTER(ctypes.c_byte))

    for tid in threads_of(pid):
        h = kernel32.OpenThread(THREAD_ALL, False, tid)
        if not h:
            continue
        kernel32.SuspendThread(h)
        ctypes.memset(aligned, 0, CONTEXT_SIZE)
        ctypes.cast(aligned, ctypes.POINTER(w.DWORD))[0x30 // 4] = CONTEXT_FULL
        got = kernel32.GetThreadContext(h, aligned)
        rsp = rip = 0
        if got:
            raw = ctypes.string_at(aligned, CONTEXT_SIZE)
            rsp = int.from_bytes(raw[OFF_RSP:OFF_RSP + 8], "little")
            rip = int.from_bytes(raw[OFF_RIP:OFF_RIP + 8], "little")

        hits = []
        if rsp:
            kernel32.ReadProcessMemory(proc, ctypes.c_void_p(rsp), buf,
                                       args.depth, ctypes.byref(read))
            data = buf.raw[:read.value]
            seen = set()
            for off in range(0, len(data) - 8, 8):
                val = int.from_bytes(data[off:off + 8], "little")
                if base < val < base + size:
                    ida = val - base
                    if ida not in seen:
                        seen.add(ida)
                        hits.append((rsp + off, ida))
                if len(hits) >= args.max_hits:
                    break

        kernel32.ResumeThread(h)
        kernel32.CloseHandle(h)

        if not hits and not args.all:
            continue
        rip_ida = (rip - base) if base < rip < base + size else None
        rip_txt = f"IDA_0x{rip_ida:X}" if rip_ida is not None else f"0x{rip:X} (outside module)"
        print(f"--- tid {tid}  rip={rip_txt}  rsp=0x{rsp:X}  ({len(hits)} module refs)")
        for stack_at, ida in hits:
            print(f"      [rsp+0x{stack_at - rsp:04X}]  IDA_0x{ida:X}")
        print()

    kernel32.CloseHandle(proc)
    return 0


if __name__ == "__main__":
    sys.exit(main())
