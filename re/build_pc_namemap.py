"""Build the MWR-PC playerState index -> NAME map: the transcoder's spine.

PS4 gives NAMES (271 entries, recovered by emulating the initializer).
PC  gives the WIRE FORMAT (252 entries: offset/size/encoder/flags).
They are the same table in the same ORDER, with fields inserted/removed between
builds - PS4 has 19 more. So this is a sequence ALIGNMENT, not a lookup.

⚠ The dossier warns "do NOT generate it by encoder-signature matching". That
warning is about matching fields INDEPENDENTLY by signature, which is ambiguous
(pm_flags is 31 bits on PS4 and 32 on PC). An order-preserving alignment is a
different and much stronger claim: one field's signature is ambiguous, a
monotonic alignment of 250+ is not. The result is then VALIDATED against anchors
the dossier established by other means.

Rule that survives either way: NAMES from PS4, every WIDTH/ENCODER/OFFSET from PC.
"""
import json, os

RE = os.path.dirname(os.path.abspath(__file__))
L = lambda n: json.load(open(os.path.join(RE, n), encoding="utf-8"))

ps4 = [t for t in L("ps4_named_netfields.json")["tables"]
       if t["label"] == "PlayerState"][0]["fields"]
pc = L("mwrpc_ps_table.json")

# signature used for alignment: (size, encoder). Offsets differ between builds,
# and flags differ too (PC 528 vs PS4 16), so neither can be part of the key.
def sig(f):
    return (f["size"], f["bits"])

A = [sig(f) for f in ps4]
B = [sig(f) for f in pc]

# classic LCS over the signature sequences
n, m = len(A), len(B)
dp = [[0] * (m + 1) for _ in range(n + 1)]
for i in range(n - 1, -1, -1):
    for j in range(m - 1, -1, -1):
        dp[i][j] = dp[i + 1][j + 1] + 1 if A[i] == B[j] else max(dp[i + 1][j], dp[i][j + 1])

pairs = []
i = j = 0
while i < n and j < m:
    if A[i] == B[j]:
        pairs.append((i, j)); i += 1; j += 1
    elif dp[i + 1][j] >= dp[i][j + 1]:
        i += 1
    else:
        j += 1

print(f"PS4 {n} fields, PC {m} fields, aligned {len(pairs)} "
      f"({100.0*len(pairs)/m:.1f}% of PC covered)")

namemap = {}
for a, b in pairs:
    namemap[b] = {"name": ps4[a]["name"], "ps4_i": a,
                  "offset": pc[b]["offset"], "size": pc[b]["size"],
                  "bits": pc[b]["bits"], "flags": pc[b]["flags"],
                  "ps4_bits": ps4[a]["bits"], "ps4_offset": ps4[a]["offset"]}

# ---- validate against anchors the dossier established independently ----
ANCHORS = {0: "commandTime", 3: "weapState[0].weaponTime", 4: "legsTimer",
           6: "legsAnim", 7: "weapState[0].weapAnim", 12: "origin[0]",
           27: "weapCommon.fWeaponPosFrac", 33: "weapState[0].weaponDelay"}
ok = bad = miss = 0
print("\nvalidation against dossier-established anchors:")
for idx, want in sorted(ANCHORS.items()):
    got = namemap.get(idx, {}).get("name")
    if got is None:
        print(f"   PC[{idx:3}] expected {want:32} -> NOT ALIGNED"); miss += 1
    elif got == want:
        print(f"   PC[{idx:3}] {got:32} OK"); ok += 1
    else:
        print(f"   PC[{idx:3}] expected {want:32} got {got}   MISMATCH"); bad += 1
print(f"   {ok} ok, {bad} mismatched, {miss} unaligned")

# encoder disagreements are expected and must be visible
diff = [(b, v["name"], v["ps4_bits"], v["bits"])
        for b, v in namemap.items() if v["ps4_bits"] != v["bits"]]
print(f"\nfields where PS4 and PC encoders DIFFER: {len(diff)} (use PC)")
for b, nm, p4, pcb in diff[:8]:
    print(f"   PC[{b:3}] {nm:34} ps4={p4} pc={pcb}")

unmapped = [i for i in range(m) if i not in namemap]
print(f"\nPC entries with no name: {len(unmapped)} -> {unmapped[:20]}")

json.dump({"namemap": {str(k): v for k, v in namemap.items()},
           "unmapped_pc": unmapped},
          open(os.path.join(RE, "mwrpc_ps_namemap.json"), "w", encoding="utf-8"),
          indent=1)

# ---- gap fill: a PC entry bracketed by two aligned neighbours whose PS4 span
# contains exactly ONE unused field is that field. Same set-difference-of-one
# logic used for the function naming, and it recovers the encoder-changed cases.
aligned = sorted(pairs)
used_ps4 = {a for a, _ in pairs}
filled = 0
for k in range(len(aligned) - 1):
    a0, b0 = aligned[k]
    a1, b1 = aligned[k + 1]
    gap_pc = list(range(b0 + 1, b1))
    gap_ps4 = [x for x in range(a0 + 1, a1) if x not in used_ps4]
    if len(gap_pc) == 1 and len(gap_ps4) == 1:
        b, a = gap_pc[0], gap_ps4[0]
        namemap[b] = {"name": ps4[a]["name"], "ps4_i": a,
                      "offset": pc[b]["offset"], "size": pc[b]["size"],
                      "bits": pc[b]["bits"], "flags": pc[b]["flags"],
                      "ps4_bits": ps4[a]["bits"], "ps4_offset": ps4[a]["offset"],
                      "via": "gap-fill"}
        used_ps4.add(a)
        filled += 1

print(f"\ngap-filled: {filled}   total named: {len(namemap)}/{len(pc)} "
      f"({100.0*len(namemap)/len(pc):.1f}%)")
still = sorted(i for i in range(len(pc)) if i not in namemap)
print(f"still unnamed: {len(still)} -> {still[:24]}")

gf = [(b, v['name'], v['ps4_bits'], v['bits']) for b, v in namemap.items()
      if v.get('via') == 'gap-fill' and v['ps4_bits'] != v['bits']]
print(f"\ngap-filled fields whose ENCODER CHANGED between builds ({len(gf)}) - "
      f"these are why alignment alone missed them:")
for b, nm, p4, pcb in sorted(gf)[:10]:
    print(f"   PC[{b:3}] {nm:34} ps4_bits={p4} -> PC_bits={pcb}   (USE PC)")

json.dump({"namemap": {str(k): v for k, v in namemap.items()},
           "unmapped_pc": still},
          open(os.path.join(RE, "mwrpc_ps_namemap.json"), "w", encoding="utf-8"),
          indent=1)
