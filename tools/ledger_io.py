"""Terminator-preserving ledger rewrite. The ONLY safe way to drop/edit rows.

reverse/functions.csv is not uniformly CRLF: at fa05aaa4b it holds 93,713 rows
ending \r\r\n, 11,140 ending \r\n and 309 ending with a bare \n. Every rewrite
that has split on "\r\n" or used str.splitlines() has silently dropped or
duplicated rows (twice this session):

    text.split("\r\n")   -> 104,854 pieces  (loses 306 rows)
    text.splitlines()    -> 198,875 pieces  (invents 93,713 rows)
    csv.reader(StringIO) -> 105,162 records (correct)

So: parse records with csv.reader for *identity*, but rewrite by operating on
the raw bytes record-by-record, keeping each record's own terminator.
"""
import csv
import io
import re

TERM = re.compile(rb"\r*\n")


def split_records(raw):
    """[(payload_bytes, terminator_bytes)] over the whole file, order preserved."""
    out, pos = [], 0
    for m in TERM.finditer(raw):
        out.append((raw[pos:m.start()], m.group(0)))
        pos = m.end()
    if pos != len(raw):
        raise ValueError("ledger does not end with a newline (truncated last row?)")
    return out


def fields(payload):
    return next(csv.reader(io.StringIO(payload.decode("utf-8"))), [])


def rewrite(raw, keep):
    """keep(fields) -> True to retain the record. Terminators are preserved."""
    kept, dropped = [], 0
    for payload, term in split_records(raw):
        if keep(fields(payload)):
            kept.append(payload + term)
        else:
            dropped += 1
    return b"".join(kept), dropped
