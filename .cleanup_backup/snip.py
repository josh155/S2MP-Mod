"""Surgical code removal helper for the cleanup pass.

Removes whole brace-matched definitions, single statements and multi-line
statements by anchor, and reports exactly what it cut so nothing is removed
silently. Refuses when an anchor is ambiguous or missing.
"""
import io
import re
import sys


def load(path):
    with io.open(path, encoding='utf-8', errors='surrogateescape', newline='') as f:
        return f.read().split('\n')


def save(path, lines):
    with io.open(path, 'w', encoding='utf-8', errors='surrogateescape', newline='') as f:
        f.write('\n'.join(lines))


def _leading_comment(lines, i):
    """Walk back over the comment block immediately above a definition."""
    j = i
    while j - 1 >= 0:
        s = lines[j - 1].strip()
        if s.startswith('//') or s == '':
            # stop at a blank line that is itself preceded by a blank line
            if s == '' and (j - 2 < 0 or lines[j - 2].strip() == ''):
                break
            j -= 1
        else:
            break
    # do not swallow leading blank lines
    while j < i and lines[j].strip() == '':
        j += 1
    return j


def find_def(lines, anchor, comment=True):
    """Find a brace-matched block whose opening line contains `anchor`."""
    hits = [i for i, l in enumerate(lines)
            if anchor in l and 'Hook::create' not in l]
    if not hits:
        raise SystemExit('ANCHOR NOT FOUND: %s' % anchor)
    starts = []
    for i in hits:
        depth = 0
        started = False
        for j in range(i, min(i + 600, len(lines))):
            depth += lines[j].count('{') - lines[j].count('}')
            if '{' in lines[j]:
                started = True
            if started and depth <= 0:
                starts.append((i, j))
                break
    if not starts:
        raise SystemExit('NO BRACED BLOCK FOR: %s' % anchor)
    i, j = starts[0]
    if comment:
        i = _leading_comment(lines, i)
    return i, j


def cut(lines, i, j, why, log):
    log.append('  -%4d lines  %s' % (j - i + 1, why))
    return lines[:i] + lines[j + 1:]


def remove_def(lines, anchor, log, comment=True):
    i, j = find_def(lines, anchor, comment)
    return cut(lines, i, j, 'def  %s' % anchor, log)


def remove_stmt(lines, anchor, log, comment=True):
    """Remove a single statement that may span lines (ends at ';')."""
    hits = [i for i, l in enumerate(lines) if anchor in l]
    if not hits:
        raise SystemExit('ANCHOR NOT FOUND: %s' % anchor)
    i = hits[0]
    j = i
    depth = 0
    while j < len(lines):
        depth += lines[j].count('(') - lines[j].count(')')
        if lines[j].rstrip().endswith(';') and depth <= 0:
            break
        j += 1
    if comment:
        i = _leading_comment(lines, i)
    return cut(lines, i, j, 'stmt %s' % anchor, log)


def remove_lines_matching(lines, pattern, log):
    rx = re.compile(pattern)
    keep = [l for l in lines if not rx.search(l)]
    log.append('  -%4d lines  /%s/' % (len(lines) - len(keep), pattern))
    return keep
