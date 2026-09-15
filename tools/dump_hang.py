"""Poll s2_mp64_ship.exe until ACTIVE theater, then dump draw-related thread stacks."""
from __future__ import annotations

import ctypes
import ctypes.wintypes as w
import sys
import time

kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
psapi = ctypes.WinDLL("psapi", use_last_error=True)
advapi32 = ctypes.WinDLL("advapi32", use_last_error=True)

TH32CS_SNAPTHREAD = 0x4
TH32CS_SNAPPROCESS = 0x2
CONTEXT_AMD64 = 0x100000
CONTEXT_CONTROL = CONTEXT_AMD64 | 0x1
CONTEXT_INTEGER = CONTEXT_AMD64 | 0x2


def ida_rva(ida: int) -> int:
    # IDA imagebase is 0 for s2x_dump — runtime VA = module_base + IDA abs.
    # (Mod `_b` uses base=module+0x1000 and literals already minus 0x1000; same end VA.)
    return ida


# (ida, size) — sizes from IDA where known
FUNCS = {
    "CG_DrawActiveFrame": (0x68DC0, 0x202E),
    "CL_CreateCmd": (0x9DC60, 0x3E7),
    "CL_IsDemoPlaying": (0x910400, 0x40),
    "CL_GetLocalClientActive": (0x795D0, 0xC00),
    "CG_GetLocalClientGlobals": (0x15330, 0x1800),
    "sub_17A570": (0x17A570, 0x80),
    "Sleep_wrap": (0x675600, 0x30),
    "SCR_DrawScreen": (0xF20D0, 0x478),
    "CL_ClientFrame": (0x6E0940, 0x180),
    "CL_WritePacket": (0x84C10, 0xF5C),
    "clientLoop_6E1020": (0x6E1020, 0x3E6),
    "scrTick_F25A0": (0xF25A0, 0xAD),
    "fence_8BC6F0": (0x8BC6F0, 0x181),
    "PredictPS_4EFA0": (0x4EFA0, 0xC00),
}


class THREADENTRY32(ctypes.Structure):
    _fields_ = [
        ("dwSize", w.DWORD),
        ("cntUsage", w.DWORD),
        ("th32ThreadID", w.DWORD),
        ("th32OwnerProcessID", w.DWORD),
        ("tpBasePri", w.LONG),
        ("tpDeltaPri", w.LONG),
        ("dwFlags", w.DWORD),
    ]


class PROCESSENTRY32W(ctypes.Structure):
    _fields_ = [
        ("dwSize", w.DWORD),
        ("cntUsage", w.DWORD),
        ("th32ProcessID", w.DWORD),
        ("th32DefaultHeapID", ctypes.POINTER(ctypes.c_ulong)),
        ("th32ModuleID", w.DWORD),
        ("cntThreads", w.DWORD),
        ("th32ParentProcessID", w.DWORD),
        ("pcPriClassBase", w.LONG),
        ("dwFlags", w.DWORD),
        ("szExeFile", w.WCHAR * 260),
    ]


class MODULEINFO(ctypes.Structure):
    _fields_ = [("lpBaseOfDll", ctypes.c_void_p), ("SizeOfImage", w.DWORD), ("EntryPoint", ctypes.c_void_p)]


class CONTEXT(ctypes.Structure):
    _fields_ = [
        ("P1Home", ctypes.c_ulonglong), ("P2Home", ctypes.c_ulonglong), ("P3Home", ctypes.c_ulonglong),
        ("P4Home", ctypes.c_ulonglong), ("P5Home", ctypes.c_ulonglong), ("P6Home", ctypes.c_ulonglong),
        ("ContextFlags", w.DWORD), ("MxCsr", w.DWORD),
        ("SegCs", w.WORD), ("SegDs", w.WORD), ("SegEs", w.WORD), ("SegFs", w.WORD),
        ("SegGs", w.WORD), ("SegSs", w.WORD), ("EFlags", w.DWORD),
        ("Dr0", ctypes.c_ulonglong), ("Dr1", ctypes.c_ulonglong), ("Dr2", ctypes.c_ulonglong),
        ("Dr3", ctypes.c_ulonglong), ("Dr6", ctypes.c_ulonglong), ("Dr7", ctypes.c_ulonglong),
        ("Rax", ctypes.c_ulonglong), ("Rcx", ctypes.c_ulonglong), ("Rdx", ctypes.c_ulonglong),
        ("Rbx", ctypes.c_ulonglong), ("Rsp", ctypes.c_ulonglong), ("Rbp", ctypes.c_ulonglong),
        ("Rsi", ctypes.c_ulonglong), ("Rdi", ctypes.c_ulonglong),
        ("R8", ctypes.c_ulonglong), ("R9", ctypes.c_ulonglong), ("R10", ctypes.c_ulonglong),
        ("R11", ctypes.c_ulonglong), ("R12", ctypes.c_ulonglong), ("R13", ctypes.c_ulonglong),
        ("R14", ctypes.c_ulonglong), ("R15", ctypes.c_ulonglong), ("Rip", ctypes.c_ulonglong),
        ("FltSave", ctypes.c_byte * 512), ("VectorRegister", ctypes.c_byte * (26 * 16)),
        ("VectorControl", ctypes.c_ulonglong), ("DebugControl", ctypes.c_ulonglong),
        ("LastBranchToRip", ctypes.c_ulonglong), ("LastBranchFromRip", ctypes.c_ulonglong),
        ("LastExceptionToRip", ctypes.c_ulonglong), ("LastExceptionFromRip", ctypes.c_ulonglong),
    ]


def enable_debug_privilege():
    class LUID(ctypes.Structure):
        _fields_ = [("LowPart", w.DWORD), ("HighPart", w.LONG)]

    class LUID_AND_ATTRIBUTES(ctypes.Structure):
        _fields_ = [("Luid", LUID), ("Attributes", w.DWORD)]

    class TOKEN_PRIVILEGES(ctypes.Structure):
        _fields_ = [("PrivilegeCount", w.DWORD), ("Privileges", LUID_AND_ATTRIBUTES * 1)]

    token = w.HANDLE()
    if not advapi32.OpenProcessToken(kernel32.GetCurrentProcess(), 0x28, ctypes.byref(token)):
        return
    luid = LUID()
    advapi32.LookupPrivilegeValueW(None, "SeDebugPrivilege", ctypes.byref(luid))
    tp = TOKEN_PRIVILEGES(1)
    tp.Privileges[0].Luid = luid
    tp.Privileges[0].Attributes = 2
    advapi32.AdjustTokenPrivileges(token, False, ctypes.byref(tp), 0, None, None)
    kernel32.CloseHandle(token)


def find_pid(name: str) -> int:
    snap = kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
    pe = PROCESSENTRY32W()
    pe.dwSize = ctypes.sizeof(pe)
    ok = kernel32.Process32FirstW(snap, ctypes.byref(pe))
    while ok:
        if pe.szExeFile.lower() == name.lower():
            pid = pe.th32ProcessID
            kernel32.CloseHandle(snap)
            return pid
        ok = kernel32.Process32NextW(snap, ctypes.byref(pe))
    kernel32.CloseHandle(snap)
    raise RuntimeError(f"{name} not found")


def enum_modules(hproc):
    mods = (ctypes.c_void_p * 1024)()
    needed = w.DWORD()
    # 3 = LIST_MODULES_ALL (32+64). Retry a few times — early process may be empty.
    out = []
    for _ in range(20):
        needed.value = 0
        if not psapi.EnumProcessModulesEx(hproc, mods, ctypes.sizeof(mods), ctypes.byref(needed), 3):
            time.sleep(0.25)
            continue
        n = needed.value // ctypes.sizeof(ctypes.c_void_p)
        if n <= 0:
            time.sleep(0.25)
            continue
        out = []
        for i in range(n):
            base = int(mods[i] or 0)
            if not base:
                continue
            namebuf = (w.WCHAR * 260)()
            psapi.GetModuleBaseNameW(hproc, ctypes.c_void_p(base), namebuf, 260)
            mi = MODULEINFO()
            psapi.GetModuleInformation(hproc, ctypes.c_void_p(base), ctypes.byref(mi), ctypes.sizeof(mi))
            out.append((namebuf.value, base, int(mi.SizeOfImage)))
        if out:
            return out
        time.sleep(0.25)
    return out


def find_game_base(modules):
    for name, base, size in modules:
        low = name.lower()
        if low == "s2_mp64_ship.exe" or low.endswith("s2_mp64_ship.exe"):
            return base
        if "s2_mp64" in low and low.endswith(".exe"):
            return base
    # Fallback: largest .exe module (main image)
    best = None
    for name, base, size in modules:
        if name.lower().endswith(".exe"):
            if best is None or size > best[2]:
                best = (name, base, size)
    return best[1] if best else None


def read_u32(hproc, addr):
    buf = w.DWORD()
    n = ctypes.c_size_t()
    if not kernel32.ReadProcessMemory(hproc, ctypes.c_void_p(addr), ctypes.byref(buf), 4, ctypes.byref(n)):
        return None
    return buf.value


def read_u8(hproc, addr):
    buf = ctypes.c_ubyte()
    n = ctypes.c_size_t()
    if not kernel32.ReadProcessMemory(hproc, ctypes.c_void_p(addr), ctypes.byref(buf), 1, ctypes.byref(n)):
        return None
    return buf.value


def read_qwords(hproc, addr, count):
    raw = (ctypes.c_ulonglong * count)()
    n = ctypes.c_size_t()
    if not kernel32.ReadProcessMemory(hproc, ctypes.c_void_p(addr), raw, 8 * count, ctypes.byref(n)):
        return []
    return list(raw)[: n.value // 8]


def resolve(addr, modules):
    for name, base, size in modules:
        if base <= addr < base + size:
            return f"{name}+0x{addr - base:X}"
    return f"0x{addr:X}"


def in_func(addr, game_base):
    out = []
    for name, (ida, size) in FUNCS.items():
        start = game_base + ida_rva(ida)
        if start <= addr < start + size:
            out.append(f"{name}+0x{addr - start:X}")
    return out


def is_code_ptr(addr, modules, game_base, mod_base):
    if addr & 0xF:  # reject obviously unaligned (still allow 1-byte x64)
        pass
    for name, base, size in modules:
        # skip image base itself / DOS header / typical non-text
        if base < addr < base + size and addr >= base + 0x1000:
            low = name.lower()
            if low.endswith(".exe") or low.endswith(".dll"):
                return True
    return False


def dump_once(hproc, modules, game_base, mod_base):
    fence = read_u32(hproc, game_base + ida_rva(0xFFC90E4))
    conn = read_u32(hproc, game_base + ida_rva(0x1BAF4E4))
    st = read_u32(hproc, game_base + ida_rva(0xC5FBA44))
    print(f"connstate={conn} serverTime={st} fence={fence}", flush=True)

    # Try resolve cg via renderer back-ptr and dump demoType/gate
    rd = None
    # qword at IDA 0x8AFCB38 (runtime note said 0x8AFBB38 — try both)
    for ida_q in (0x8AFCB38, 0x8AFBB38):
        raw = (ctypes.c_ulonglong * 1)()
        n = ctypes.c_size_t()
        if kernel32.ReadProcessMemory(
            hproc, ctypes.c_void_p(game_base + ida_rva(ida_q)), raw, 8, ctypes.byref(n)
        ) and raw[0]:
            rd = int(raw[0])
            print(f"renderer_q ida=0x{ida_q:X} val=0x{rd:X}", flush=True)
            if rd > 0x1E6C10:
                cg = rd - 0x1E6C10
                dt = read_u32(hproc, cg + 0x5980)
                gate = read_u32(hproc, cg + 0x5990)
                print(f"cg=0x{cg:X} demoType={dt} gate@5990={gate}", flush=True)
            break

    snap = kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0)
    te = THREADENTRY32()
    te.dwSize = ctypes.sizeof(te)
    tids = []
    pid = find_pid("s2_mp64_ship.exe")
    if kernel32.Thread32First(snap, ctypes.byref(te)):
        while True:
            if te.th32OwnerProcessID == pid:
                tids.append(te.th32ThreadID)
            if not kernel32.Thread32Next(snap, ctypes.byref(te)):
                break
    kernel32.CloseHandle(snap)

    reports = []
    for tid in tids:
        ht = kernel32.OpenThread(0x1F03FF, False, tid)
        if not ht:
            continue
        kernel32.SuspendThread(ht)
        ctx = CONTEXT()
        ctx.ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER
        ok = kernel32.GetThreadContext(ht, ctypes.byref(ctx))
        rip, rsp = (ctx.Rip, ctx.Rsp) if ok else (0, 0)
        stack = read_qwords(hproc, rsp, 80) if ok else []
        kernel32.ResumeThread(ht)
        kernel32.CloseHandle(ht)
        if not ok:
            continue

        frames = []
        tags = []
        for a in [rip] + stack:
            if not is_code_ptr(a, modules, game_base, mod_base):
                continue
            lab = resolve(a, modules)
            near = in_func(a, game_base)
            in_mod = bool(mod_base and mod_base + 0x1000 <= a < mod_base + 0x800000)
            low = lab.lower()
            keep = bool(near) or in_mod
            if "ntdll" in low or "win32u" in low or "kernelbase" in low:
                if any(k in low for k in ("wait", "delay", "sleep", "msgwait", "getmessage", "ntuser")):
                    keep = True
                    tags.append("WAIT")
            if keep:
                if near:
                    tags.extend(near)
                if in_mod:
                    tags.append("IN_MOD")
                frames.append((a, lab, near))

        # dedupe
        seen = set()
        uniq = []
        for f in frames:
            if f[0] in seen:
                continue
            seen.add(f[0])
            uniq.append(f)
            if len(uniq) >= 24:
                break

        interesting = any(
            ("DrawActive" in t or "CreateCmd" in t or "GetLocal" in t or "Predict" in t
             or "SCR_Draw" in t or "ClientFrame" in t or "IN_MOD" in t or "WAIT" in t
             or "Sleep" in t or "fence" in t or "sub_17A570" in t)
            for t in tags
        )
        # Always keep if RIP itself is inside the game image (narrow hung-draw case).
        rip_in_game = game_base and game_base + 0x1000 <= rip < game_base + 0x2000000
        rip_in_mod = bool(mod_base and mod_base + 0x1000 <= rip < mod_base + 0x800000)
        if interesting or rip_in_game or rip_in_mod:
            reports.append((tid, list(dict.fromkeys(tags)), uniq, resolve(rip, modules)))

    # Sort: prefer threads with named game frames / mod / wait
    def rank(item):
        tags = item[1]
        score = 0
        for t in tags:
            if "DrawActive" in t or "SCR_Draw" in t:
                score += 100
            elif "IN_MOD" in t:
                score += 80
            elif "GetLocal" in t or "CreateCmd" in t:
                score += 70
            elif "WAIT" in t or "Sleep" in t:
                score += 40
            elif "ClientFrame" in t:
                score += 20
        return -score

    reports.sort(key=rank)
    print(f"\n=== MATCHING THREADS ({len(reports)}) ===", flush=True)
    for tid, tags, frames, riplab in reports[:40]:
        print(f"\n--- tid={tid} RIP={riplab}", flush=True)
        print(f"    tags={tags}", flush=True)
        for a, lab, near in frames:
            extra = ("  << " + ",".join(near)) if near else ""
            print(f"  0x{a:016X}  {lab}{extra}", flush=True)
    return conn, st, fence, reports


def wait_for_pid(name: str) -> int:
    print(f"Waiting for {name}...")
    sys.stdout.flush()
    while True:
        try:
            return find_pid(name)
        except RuntimeError:
            time.sleep(0.5)


def main():
    enable_debug_privilege()
    wait_active = "--wait" in sys.argv or "-w" in sys.argv
    wait_proc = wait_active or "--attach" in sys.argv or "-a" in sys.argv
    if wait_proc:
        pid = wait_for_pid("s2_mp64_ship.exe")
    else:
        pid = find_pid("s2_mp64_ship.exe")
    print(f"PID={pid}", flush=True)
    hproc = kernel32.OpenProcess(0x1F0FFF, False, pid)
    if not hproc:
        raise RuntimeError(f"OpenProcess {ctypes.get_last_error()}")
    # Give the process a moment to map its main image.
    time.sleep(1.0)
    modules = enum_modules(hproc)
    if not modules:
        raise RuntimeError("EnumProcessModulesEx empty (need admin/SeDebug?)")
    print(f"modules={len(modules)} first={[m[0] for m in modules[:8]]}", flush=True)
    game_base = find_game_base(modules)
    mod_base = None
    for name, base, size in modules:
        if name.lower() == "s2mp-mod.dll":
            mod_base = base
    if game_base:
        print(f"game=0x{game_base:X}", flush=True)
    else:
        raise RuntimeError(f"game module missing; saw={[m[0] for m in modules[:20]]}")
    if mod_base:
        print(f"mod =0x{mod_base:X}", flush=True)
    elif wait_active:
        print("WARN: s2mp-mod.dll not loaded yet", flush=True)

    if wait_active:
        print("Waiting for connstate==10 (ACTIVE). Start demo_play now...", flush=True)
        last = None
        while True:
            # Process may restart mid-wait — reattach.
            try:
                cur = find_pid("s2_mp64_ship.exe")
            except RuntimeError:
                print("  process gone — waiting for relaunch...", flush=True)
                pid = wait_for_pid("s2_mp64_ship.exe")
                kernel32.CloseHandle(hproc)
                hproc = kernel32.OpenProcess(0x1F0FFF, False, pid)
                if not hproc:
                    raise RuntimeError(f"OpenProcess {ctypes.get_last_error()}")
                time.sleep(1.0)
                modules = enum_modules(hproc)
                game_base = find_game_base(modules)
                mod_base = None
                for name, base, size in modules:
                    if name.lower() == "s2mp-mod.dll":
                        mod_base = base
                print(f"reattach PID={pid} game=0x{game_base:X} mod={hex(mod_base) if mod_base else None}", flush=True)
                last = None
                continue
            if cur != pid:
                pid = cur
                kernel32.CloseHandle(hproc)
                hproc = kernel32.OpenProcess(0x1F0FFF, False, pid)
                modules = enum_modules(hproc)
                game_base = find_game_base(modules)
                mod_base = None
                for name, base, size in modules:
                    if name.lower() == "s2mp-mod.dll":
                        mod_base = base
                print(f"reattach PID={pid} game=0x{game_base:X}", flush=True)
                last = None

            conn = read_u32(hproc, game_base + ida_rva(0x1BAF4E4))
            st = read_u32(hproc, game_base + ida_rva(0xC5FBA44))
            if conn is None:
                print("  RPM failed — waiting...", flush=True)
                time.sleep(0.5)
                continue
            if (conn, st) != last:
                print(f"  poll connstate={conn} serverTime={st}", flush=True)
                last = (conn, st)
            if conn >= 9:  # PRIMED or ACTIVE — hang can be either
                time.sleep(1.5)
                break
            time.sleep(0.25)

    # sample 3 times a second apart
    for i in range(3):
        print(f"\n########## SAMPLE {i+1} ##########")
        dump_once(hproc, modules, game_base, mod_base)
        time.sleep(0.8)

    kernel32.CloseHandle(hproc)
    print("\nDONE")


if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print("ERROR:", e)
        sys.exit(1)
