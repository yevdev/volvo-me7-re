#!/usr/bin/env python3
"""ME7 50GPHJ coverage meter -- how much of the bin + defs is named / documented.

PURE TEXT ANALYSIS. Reads only derived artifacts:
  data/xref/functions.csv, data/xref/callgraph.csv,
  loadkit/function_names.csv, loadkit/map_names.csv
It NEVER opens the raw .bin and never touches hex. It is the progress meter for the
me7-coverage / me7-identify-function / me7-name-maps skills.

Run from anywhere:  py scripts/coverage-report.py
Writes: data/coverage/coverage-report.md  and  data/coverage/worklist.csv
"""
import csv, os, bisect
from collections import deque, defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
def P(*a): return os.path.join(REPO, *a)

def load_funcs():
    funcs = {}
    with open(P('data', 'xref', 'functions.csv'), encoding='utf-8') as f:
        for r in csv.DictReader(f):
            try: ea = int(r['ea'], 16)
            except Exception: continue
            funcs[ea] = {
                'name': r['name'],
                'cal': int(r['n_cal_refs'] or 0),
                'ram': int(r['n_ram_refs'] or 0),
                'callers': int(r['n_callers'] or 0),
                'cal_refs': [int(x, 16) for x in (r['cal_refs'] or '').split() if x],
            }
    return funcs

def load_named():
    named = {}
    p = P('loadkit', 'function_names.csv')
    if os.path.exists(p):
        with open(p, encoding='utf-8') as f:
            for r in csv.DictReader(f):
                try: named[int(r['addr'], 16)] = r['name']
                except Exception: pass
    return named

def load_dict():
    addrs = []
    with open(P('loadkit', 'map_names.csv'), encoding='utf-8') as f:
        for r in csv.DictReader(f):
            try: addrs.append(int(r['addr'], 16))
            except Exception: pass
    return sorted(set(addrs))

def reachable(funcs):
    edges = defaultdict(list)
    p = P('data', 'xref', 'callgraph.csv')
    if os.path.exists(p):
        with open(p, encoding='utf-8') as f:
            for r in csv.DictReader(f):
                try: edges[int(r['caller_ea'], 16)].append(int(r['callee_ea'], 16))
                except Exception: pass
    roots = [0xB81C, 0xB6E6, 0xB3A2, 0xB218, 0xBB16]   # periodic scheduler roots
    seen = set(r for r in roots if r in funcs); q = deque(seen)
    while q:
        for m in edges.get(q.popleft(), []):
            if m in funcs and m not in seen:
                seen.add(m); q.append(m)
    return seen

def main():
    funcs = load_funcs(); named = load_named(); dic = load_dict(); reach = reachable(funcs)
    dset = set(dic)
    total = len(funcs); nnamed = len(set(named) & set(funcs))

    # function naming by calibration-touch bucket (the tuning-relevant frontier)
    def bucket(pred):
        fs = [ea for ea, d in funcs.items() if pred(d)]
        return len(fs), sum(1 for ea in fs if ea in named)
    b30 = bucket(lambda d: d['cal'] >= 30)
    b10 = bucket(lambda d: d['cal'] >= 10)
    b1  = bucket(lambda d: d['cal'] >= 1)
    rn = len(reach & set(named))

    # calibration attribution: every cal address the code touches vs the named dictionary
    code_cal = set()
    reader = defaultdict(list)
    for ea, d in funcs.items():
        for a in d['cal_refs']:
            code_cal.add(a); reader[a].append(ea)
    def nb(a):
        i = bisect.bisect_right(dic, a) - 1
        return dic[i] if i >= 0 else None
    exact = w64 = w256 = 0; orphans = []
    for a in code_cal:
        if a in dset: exact += 1; continue
        n = nb(a); gap = (a - n) if n is not None else 1 << 30
        if gap <= 64: w64 += 1
        elif gap <= 256: w256 += 1
        else: orphans.append(a)
    attributed = exact + w64 + w256
    cc = max(1, len(code_cal))

    # cluster orphan cal addrs into candidate unknown map regions
    orphans.sort(); clusters = []
    for a in orphans:
        if clusters and a - clusters[-1]['hi'] <= 48:
            clusters[-1]['hi'] = a; clusters[-1]['n'] += 1
        else:
            clusters.append({'lo': a, 'hi': a, 'n': 1})
    for c in clusters:
        rs = set()
        for a in range(c['lo'], c['hi'] + 1):
            rs.update(reader.get(a, []))
        # pick the reader that touches the cluster most
        best = sorted(rs, key=lambda ea: -sum(1 for a in funcs[ea]['cal_refs'] if c['lo'] <= a <= c['hi']))
        c['reader'] = best[0] if best else None
    clusters.sort(key=lambda c: -((c['hi'] - c['lo'] + 1) * c['n']))

    # dict entries the resolved code never reads (indirect / axis-only / unused)
    cc_sorted = sorted(code_cal)
    untouched = 0
    for a in dic:
        i = bisect.bisect_left(cc_sorted, a)
        near = min([abs(a - cc_sorted[j]) for j in (i - 1, i) if 0 <= j < len(cc_sorted)] or [1 << 30])
        if near > 64: untouched += 1

    def nm(ea): return named.get(ea) or (funcs[ea]['name'] if ea in funcs else 'sub_%05X' % ea)

    os.makedirs(P('data', 'coverage'), exist_ok=True)
    md = []
    md.append("# GPHJ ME7.0 coverage report")
    md.append("")
    md.append("Generated by `scripts/coverage-report.py` from the derived xref/def artifacts (no hex).")
    md.append("")
    md.append("## Function naming")
    md.append(f"- carved functions: **{total}**  |  named in loadkit DB: **{nnamed}** ({100*nnamed/total:.1f}%)")
    md.append(f"- scheduler-reachable functions: **{len(reach)}**  |  of those named: **{rn}** ({100*rn/max(1,len(reach)):.1f}%)")
    md.append(f"- functions reading >=30 cal maps: {b30[0]}  named: **{b30[1]}** ({100*b30[1]/max(1,b30[0]):.0f}%)")
    md.append(f"- functions reading >=10 cal maps: {b10[0]}  named: **{b10[1]}** ({100*b10[1]/max(1,b10[0]):.0f}%)")
    md.append(f"- functions reading  >=1 cal map : {b1[0]}  named: **{b1[1]}** ({100*b1[1]/max(1,b1[0]):.0f}%)")
    md.append("")
    md.append("## Calibration / defs attribution")
    md.append(f"- distinct cal addresses the code reads: **{len(code_cal)}**")
    md.append(f"- attributed to a named map (exact/<=64B/<=256B): **{attributed}** = **{100*attributed/cc:.1f}%**")
    md.append(f"  (exact={exact}, within64B={w64}, within256B={w256})")
    md.append(f"- ORPHAN cal addresses (>256B from any name): **{len(orphans)}** in **{len(clusters)}** clusters -> the defs gap")
    md.append(f"- named dict maps the code never reads (indirect/axis-only/unused): {untouched}/{len(dic)}")
    md.append("")
    md.append("## Worklist A -- unnamed functions by calibration-touch (bin coverage)")
    md.append("| function | cal | ram | reachable | one-line hint |")
    md.append("|---|---:|---:|:--:|---|")
    unfns = sorted((d['cal'], -d['ram'], ea) for ea, d in funcs.items()
                   if ea not in named and d['cal'] >= 8)
    for cal, negram, ea in sorted(unfns, reverse=True)[:25]:
        md.append(f"| `sub_{ea:05X}` | {cal} | {-negram} | {'yes' if ea in reach else '-'} | reads {cal} cal maps; run me7-identify-function |")
    md.append("")
    md.append("## Worklist B -- orphan map clusters (defs coverage)")
    md.append("| region | span(B) | refs | reader | action |")
    md.append("|---|---:|---:|---|---|")
    for c in clusters[:25]:
        rd = nm(c['reader']) if c['reader'] else '?'
        md.append(f"| `0x{c['lo']:05X}-0x{c['hi']:05X}` | {c['hi']-c['lo']+1} | {c['n']} | `{rd}` | run me7-name-maps |")
    md.append("")
    open(P('data', 'coverage', 'coverage-report.md'), 'w', encoding='utf-8', newline='\n').write("\n".join(md))

    with open(P('data', 'coverage', 'worklist.csv'), 'w', encoding='utf-8', newline='') as f:
        w = csv.writer(f)
        w.writerow(['type', 'key', 'cal', 'ram', 'reachable', 'reader', 'skill'])
        for cal, negram, ea in sorted(unfns, reverse=True):
            w.writerow(['function', 'sub_%05X' % ea, cal, -negram, 'yes' if ea in reach else 'no', '', 'me7-identify-function'])
        for c in clusters:
            w.writerow(['mapcluster', '0x%05X-0x%05X' % (c['lo'], c['hi']), c['hi']-c['lo']+1, c['n'], '',
                        nm(c['reader']) if c['reader'] else '', 'me7-name-maps'])

    print("COVERAGE_REPORT_DONE")
    print(f"  functions named: {nnamed}/{total}  reachable-named: {rn}/{len(reach)}")
    print(f"  cal attribution: {100*attributed/cc:.1f}%  orphan clusters: {len(clusters)}")
    print(f"  wrote data/coverage/coverage-report.md + worklist.csv")

if __name__ == '__main__':
    main()
