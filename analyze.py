"""Tables from results/<platform>/: python3 analyze.py > results/summary.md

For each platform: how many different answers each method gave across thread
counts, how far from the correctly rounded answer, and what it cost. Across
platforms: how many results of each elementary function differ bit for bit.
"""
import csv
import itertools
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
RESULTS = os.path.join(HERE, "results")


def ordered(bits):
    """Doubles as integers in the order of their values, so that the distance
    between two is a count of representable doubles (ULPs)."""
    b = int(bits, 16)
    return b if b < 1 << 63 else (1 << 63) - b


def ulps(a, b):
    return abs(ordered(a) - ordered(b))


def value(bits):
    return struct.unpack("<d", struct.pack("<Q", int(bits, 16)))[0]


def rows(path):
    with open(path) as f:
        return list(csv.DictReader(f))


def ms(ns):
    return float(ns) / 1e6


def platforms():
    return sorted(p for p in os.listdir(RESULTS)
                  if os.path.isfile(os.path.join(RESULTS, p, "env.txt")))


def env(platform):
    with open(os.path.join(RESULTS, platform, "env.txt")) as f:
        return f.read().strip()


def sum_table(platform):
    base = os.path.join(RESULTS, platform)
    ref = {}
    with open(os.path.join(base, "reference.csv")) as f:
        for line in f:
            name, bits, _ = line.strip().split(",")
            ref[name.replace(".bin", "")] = bits
    data = rows(os.path.join(base, "sum.csv"))
    out = []
    for dataset in ("uniform", "mixed"):
        out.append(f"\n**{dataset}** (correctly rounded sum {value(ref[dataset]):.17g})\n")
        out.append("| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |")
        out.append("|---|---|---|---|---|---|")
        methods = []
        for r in data:
            if r["data"] == dataset and r["method"] not in methods:
                methods.append(r["method"])
        for m in methods:
            rs = [r for r in data if r["data"] == dataset and r["method"] == m]
            distinct = sorted({r["bits"] for r in rs})
            errs = sorted({ulps(b, ref[dataset]) for b in distinct})
            err = str(errs[0]) if len(errs) == 1 else f"{errs[0]}–{errs[-1]}"
            one = next((r for r in rs if r["threads"] == "1"), rs[0])
            best = min(rs, key=lambda r: float(r["median_ns"]))
            out.append(f"| {m} | {len(distinct)} of {len(rs)} | {err} | "
                       f"{ms(one['median_ns']):.2f} | {ms(best['median_ns']):.2f} | {best['threads']} |")
    return "\n".join(out)


def mc_table(platform):
    data = rows(os.path.join(RESULTS, platform, "mc.csv"))
    out = ["| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |",
           "|---|---|---|---|---|---|"]
    methods = []
    for r in data:
        if r["method"] not in methods:
            methods.append(r["method"])
    for m in methods:
        rs = [r for r in data if r["method"] == m]
        distinct = sorted({r["bits"] for r in rs})
        vals = sorted(value(b) for b in distinct)
        seen = f"{vals[0]:.17g}" if len(vals) == 1 else f"{vals[0]:.17g} … {vals[-1]:.17g}"
        one = next((r for r in rs if r["threads"] == "1"), rs[0])
        best = min(rs, key=lambda r: float(r["median_ns"]))
        out.append(f"| {m} | {len(distinct)} of {len(rs)} | {seen} | "
                   f"{ms(one['median_ns']):.1f} | {ms(best['median_ns']):.1f} | {best['threads']} |")
    return "\n".join(out)


def math_table(platform):
    data = rows(os.path.join(RESULTS, platform, "math.csv"))
    out = ["| function | C library (ns/call) | std/num (ns/call) |", "|---|---|---|"]
    by = {r["fn"]: r["ns_per_call"] for r in data}
    for fn in ("sin", "sinnear", "cos", "exp", "expunit", "log"):
        if f"libm-{fn}" in by:
            out.append(f"| {fn} | {by['libm-' + fn]} | {by['num-' + fn]} |")
    return "\n".join(out)


def repeat_table(platform):
    path = os.path.join(RESULTS, platform, "repeat.csv")
    if not os.path.exists(path):
        return ""
    data = rows(path)
    out = ["| method | threads | runs | distinct results |", "|---|---|---|---|"]
    keys = []
    for r in data:
        k = (r["method"], r["threads"])
        if k not in keys:
            keys.append(k)
    for m, t in keys:
        rs = [r for r in data if r["method"] == m and r["threads"] == t]
        out.append(f"| {m} | {t} | {len(rs)} | {len({r['bits'] for r in rs})} |")
    return "\n".join(out)


def load_bits(platform, impl, fn):
    path = os.path.join(RESULTS, platform, "bits", f"{platform}-{impl}-{fn}.bin")
    if not os.path.exists(path):
        return None
    raw = open(path, "rb").read()
    return struct.unpack("<%dQ" % (len(raw) // 8), raw)


def sword_cross(names):
    """Every answer each method gave, on every platform and at every thread
    count: one row per method, with the number of distinct results."""
    out = ["| experiment | method | platforms | runs | distinct results |", "|---|---|---|---|---|"]
    for exp, file in (("E1 mixed", "sum.csv"), ("E1 uniform", "sum.csv"), ("E2", "mc.csv")):
        seen = {}
        want = None
        for p in names:
            path = os.path.join(RESULTS, p, file)
            if not os.path.exists(path):
                continue
            if exp.startswith("E1"):
                h = inputs(p).get(exp.split()[1] + ".bin")
                want = want or h
                if h is None or h != want:
                    out.append(f"| {exp} | — | {p} left out: its input differs | | |")
                    continue
            for r in rows(path):
                if exp.startswith("E1") and r["data"] != exp.split()[1]:
                    continue
                seen.setdefault(r["method"], []).append((p, r["bits"]))
        for m, got in seen.items():
            plats = sorted({p for p, _ in got})
            out.append(f"| {exp} | {m} | {len(plats)} | {len(got)} | {len({b for _, b in got})} |")
    return "\n".join(out)


def inputs(platform):
    path = os.path.join(RESULTS, platform, "inputs.txt")
    if not os.path.exists(path):
        return {}
    with open(path) as f:
        return dict(line.split() for line in f if line.strip())


def cross_table(names):
    # Comparing results is only meaningful over the same arguments.
    files = {"sin": "trig.bin", "cos": "trig.bin", "exp": "exp.bin", "log": "log.bin"}
    out = ["| function | platforms | C library: results that differ | std/num: results that differ |",
           "|---|---|---|---|"]
    for fn in ("sin", "cos", "exp", "log"):
        for a, b in itertools.combinations(names, 2):
            ha, hb = inputs(a).get(files[fn]), inputs(b).get(files[fn])
            if ha is None or ha != hb:
                out.append(f"| {fn} | {a} vs {b} | inputs differ | inputs differ |")
                continue
            cells = []
            for impl in ("libm", "num"):
                x, y = load_bits(a, impl, fn), load_bits(b, impl, fn)
                if x is None or y is None:
                    cells.append("—")
                    continue
                diff = sum(1 for p, q in zip(x, y) if p != q)
                cells.append(f"{diff} of {len(x)}")
            out.append(f"| {fn} | {a} vs {b} | {cells[0]} | {cells[1]} |")
    return "\n".join(out)


def main():
    names = platforms()
    print("# Results\n")
    for p in names:
        print(f"## {p}\n\n```\n{env(p)}\n```\n")
        if os.path.exists(os.path.join(RESULTS, p, "sum.csv")):
            print("### E1 — summation of 10^7 doubles\n" + sum_table(p) + "\n")
            print("### E1b — the same run repeated, thread count fixed (mixed data)\n\n" + repeat_table(p) + "\n")
            print("### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]\n\n" + mc_table(p) + "\n")
        print("### E3 — elementary functions, cost\n\n" + math_table(p) + "\n")
    if len(names) > 1:
        print("## E1, E2 — Sword's answers on different platforms\n\n" + sword_cross(names) + "\n")
        print("## E3 — the same arguments on different platforms\n\n" + cross_table(names) + "\n")


if __name__ == "__main__":
    sys.exit(main())
