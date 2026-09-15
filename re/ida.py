"""Minimal JSON-RPC client for ida-pro-mcp servers.

The MCP namespaces are only registered at session start, so an IDB opened
mid-session (e.g. MWR-PC on 14347) is unreachable through the tool layer.
Direct JSON-RPC is the documented fallback and works identically.

    from ida import call, pyeval
    pyeval(14347, "def main(): return 1\nmain()")
"""
from __future__ import annotations

import json
import re
import urllib.request

PORTS = {
    "s2": 13337,
    "aw": 12345,
    "s2xbox": 12346,
    "mwrps4": 9999,
    "mwrpc": 14347,
    "mw3": 14200,     # COD_MW3_MPsub (Mac, NAMED reference), imagebase 0x1000
    "mw3steam": 13999,  # iw5mp_dumpx64.exe (new 64-bit Steam client, TARGET), imagebase 0x140000000
    "cod4": 18337,    # "Call of Duty 4 Multiplayer.i64"  NAMED reference, imagebase 0x1000
    "cod4x": 19337,   # "iw3mp_dump.exe.i64"              CoD4X target, imagebase 0x400000
}


def call(port, tool, args=None, timeout=600):
    if isinstance(port, str):
        port = PORTS[port]
    payload = json.dumps(
        {
            "jsonrpc": "2.0",
            "id": 1,
            "method": "tools/call",
            "params": {"name": tool, "arguments": args or {}},
        }
    ).encode()
    req = urllib.request.Request(
        f"http://127.0.0.1:{port}/mcp",
        data=payload,
        headers={"Content-Type": "application/json"},
    )
    with urllib.request.urlopen(req, timeout=timeout) as r:
        body = json.loads(r.read().decode("utf-8", "replace"))
    if "error" in body:
        raise RuntimeError(body["error"])
    result = body["result"]
    content = result.get("content", [])

    # A large result is TRUNCATED in-band and the server hands back a URL for
    # the complete artifact. Follow it - otherwise big decompiles silently
    # arrive as a fragment (a 86 KB function came back as 1 KB).
    for c in content:
        t = c.get("text", "")
        if t.startswith("Output truncated"):
            m = re.search(r"(http://\S+\.json)", t)
            if m:
                with urllib.request.urlopen(m.group(1), timeout=timeout) as r2:
                    return json.loads(r2.read().decode("utf-8", "replace"))

    # structuredContent is already parsed and is not truncated for small results
    if isinstance(result.get("structuredContent"), (dict, list)):
        return result["structuredContent"]

    text = "".join(c.get("text", "") for c in content)
    try:
        return json.loads(text)
    except Exception:
        pass
    # Large replies (e.g. a big decompile) arrive as SEVERAL concatenated JSON
    # objects rather than one. Decode them all and merge; string fields that
    # were split across objects are re-joined in order.
    dec, objs, i = json.JSONDecoder(), [], 0
    while i < len(text):
        try:
            o, j = dec.raw_decode(text, i)
            objs.append(o)
            i = j
        except ValueError:
            i += 1
    if not objs:
        return text
    if len(objs) == 1:
        return objs[0]
    if all(isinstance(o, dict) for o in objs):
        merged = {}
        for o in objs:
            for k, v in o.items():
                if k in merged and isinstance(v, str) and isinstance(merged[k], str):
                    if not merged[k].endswith(v):
                        merged[k] += v
                else:
                    merged.setdefault(k, v)
        return merged
    return objs


def pyeval(port, code, timeout=600):
    """Run python inside IDA and return the evaluated value.

    py_eval answers {'result': <python repr>, 'stdout': ..., 'stderr': ...},
    so the repr is literal_eval'd back into a real object. Anything the
    script printed is raised if it wrote to stderr.

    NOTE: py_eval runs under exec with split globals/locals, so a nested def
    cannot see names bound at the top level. Wrap everything in one
    `def main(): ...` and call it as the final expression.
    """
    import ast

    r = call(port, "py_eval", {"code": code}, timeout=timeout)
    if not isinstance(r, dict):
        return r
    if r.get("stderr"):
        raise RuntimeError(r["stderr"][:4000])
    out = r.get("result", "")
    try:
        return ast.literal_eval(out)
    except Exception:
        return out
