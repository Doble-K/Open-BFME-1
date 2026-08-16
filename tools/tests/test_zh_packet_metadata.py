"""What a Zero Hour work packet is allowed to assert about its own address.

A packet's address and size are not observations, they are the sweep's guess:
the address is wherever a masked needle aligned, and the size is the length of
the Zero Hour body, not of the retail one. Both were printed as fact. A
contributor who trusts them writes a ledger row at an address the function does
not start at, or for an extent it does not have, and the row byte-matches
anyway -- build.py copies DIR32 relocation bytes out of retail rather than
proving them -- so the gate cannot catch what the packet manufactured.

Every path here runs over a synthetic image and a scratch ledger under tmp_path.
The real packet directory is derived and rewritten wholesale, so a test that
pointed at it would delete the live queue.
"""
import csv
import importlib.util
import json
import re
import sys
import types
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
csv.field_size_limit(10_000_000)

import build  # noqa: E402


def _load(name):
    spec = importlib.util.spec_from_file_location(name, ROOT / "tools" / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


zh_sweep = _load("zh_sweep")

TEXT_RVA = 0x1000
LEDGER_HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
# One 32-byte function the inventory knows, its int3 padding, and a 16-byte one
# after it. Everything else is nop, so nothing but these bounds a body.
KNOWN = {0x2000: 32, 0x3000: 16}
PAD = 0x2020
SOURCE = "reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/T.cpp"


def image():
    text = bytearray(b"\x90" * 0x4000)
    text[PAD - TEXT_RVA : PAD - TEXT_RVA + 16] = b"\xcc" * 16
    return bytes(text)


def near(rva, size, sym="?candidate@Thing@@QAEXXZ", align=0.9, relocs=3):
    return {"sym": sym, "obj": "T.obj", "source": SOURCE, "size": size, "relocs": relocs,
            "rva": rva, "bucket": "near", "align": align, "claimed": False}


def run_packets(tmp_path, monkeypatch, records, ledger_rows=(), relocs=()):
    """do_packets over a synthetic image; returns {rva: packet text}."""
    text = image()
    ledger = tmp_path / "functions.csv"
    ledger.write_text(LEDGER_HEADER + "\r\n" + "".join(r + "\r\n" for r in ledger_rows),
                      encoding="utf-8")
    inventory = tmp_path / "ghidra_functions.csv"
    inventory.write_text("rva,size,name\n"
                         + "".join(f"0x{rva:x},{size},FUN_{rva:08x}\n"
                                   for rva, size in KNOWN.items()), encoding="utf-8")
    (tmp_path / "match.json").write_text(json.dumps(list(records)))
    packets = tmp_path / "packets"
    monkeypatch.setattr(zh_sweep, "MATCH_JSON", tmp_path / "match.json")
    monkeypatch.setattr(zh_sweep, "PACKET_DIR", packets)
    monkeypatch.setattr(zh_sweep, "OUT_DIR", tmp_path)
    monkeypatch.setattr(zh_sweep, "ROOT", tmp_path)
    monkeypatch.setattr(zh_sweep, "retail_text", lambda: (TEXT_RVA, text))
    monkeypatch.setattr(zh_sweep, "packet_relocs",
                        lambda objects: {("T.obj", r["sym"]): list(relocs) for r in records})
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    monkeypatch.setattr(build, "GHIDRA_FUNCTIONS", inventory)
    monkeypatch.setattr(build, "read_target_bytes",
                        lambda rva, size: text[rva - TEXT_RVA : rva - TEXT_RVA + size])

    zh_sweep.do_packets(types.SimpleNamespace())

    return {int(p.stem, 16): p.read_text() for p in packets.glob("*.md")}


def served_size(packet):
    """The size tools/next_work.py parses out of a packet to serve it."""
    return int(re.search(r"- (\d+) bytes", packet).group(1))


def flat(packet):
    """The packet as one line: its prose is wrapped, its claims are not."""
    return " ".join(packet.split())


def test_an_interior_address_is_never_presented_as_a_function_start(tmp_path, monkeypatch):
    """0x2010 is 16 bytes inside a body the inventory knows. The sweep placed a
    candidate there anyway, which is how 25 of 335 live packets were addressed."""
    written = run_packets(tmp_path, monkeypatch, [near(0x2010, 24)])

    packet = flat(written[0x2010])
    assert "**This address is not a function start.**" in packet
    assert "16 byte(s) inside the function at 0x00002000" in packet
    assert "Do not add a ledger row at this address" in packet
    assert "confirmed function start" not in packet


def test_a_confirmed_start_says_so_and_says_where_from(tmp_path, monkeypatch):
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 16)])

    packet = flat(written[0x3000])
    assert "address is a confirmed function start (reverse/ghidra_functions.csv)" in packet
    assert "not a function start" not in packet


def test_the_packet_quotes_retails_extent_not_the_candidates_length(tmp_path, monkeypatch):
    """The size bug: `size` was the Zero Hour body's length. Retail's body at
    0x3000 is 16 bytes; a 24-byte candidate must not widen the claim to 24."""
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 24)])

    packet = written[0x3000]
    assert served_size(packet) == 16
    assert "the candidate body is 24 bytes long" in flat(packet)
    assert "Retail disassembly (16 bytes from this address)" in packet


def test_an_unmeasurable_extent_is_labelled_unverified_not_guessed(tmp_path, monkeypatch):
    """No inventory row and no int3 run in range: the candidate's length is all
    there is, so it is served with that said out loud rather than as an extent."""
    written = run_packets(tmp_path, monkeypatch, [near(0x3200, 24)])

    packet = written[0x3200]
    assert served_size(packet) == 24
    assert "an UNVERIFIED size" in flat(packet)
    assert "no inventory row confirms a function starts at this address" in flat(packet)


def test_agreement_is_measured_over_compared_bytes_not_blanked_ones(tmp_path, monkeypatch):
    """match.json's `align` scores a blanked relocation byte as agreeing, so the
    sentence "outside relocation sites" was never the number it printed. Here 8
    of 24 bytes are relocation slots: 0.9 over the whole body is 22 matching, of
    which 8 were never compared, so 14 of 16 -- 87.5%, not 90.0%."""
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 24, align=0.9)],
                          relocs=[(4, zh_sweep.DIR32, "?g@@3HA"),
                                  (12, zh_sweep.REL32, "?callee@@YAXXZ")])

    packet = flat(written[0x3000])
    assert "agrees on 87.5% of the bytes outside relocation sites: 14 of 16" in packet
    assert "the other 8 byte(s) of its 24-byte body are relocation slots" in packet
    assert "the sweep's own 90.0% counts every blanked byte as agreeing" in packet


def test_tied_candidates_are_not_offered_as_an_identity(tmp_path, monkeypatch):
    """Masking hides which global and which callee a body uses, so equally
    aligned candidates are indistinguishable -- 0x002EFAF0 landed under the
    wrong one of three."""
    written = run_packets(tmp_path, monkeypatch, [
        near(0x3000, 16, sym="?first@Thing@@QAEXXZ"),
        near(0x3000, 16, sym="?second@Thing@@QAEXXZ")])

    assert "2 of the candidates below align equally well" in flat(written[0x3000])


def test_no_packet_for_ground_the_ledger_already_claims(tmp_path, monkeypatch):
    """The claim is re-asked against the live ledger and against the extent the
    packet would quote, not against the snapshot taken when the match ran."""
    claimed = "?owner@Thing@@QAEXXZ,,0x00003000,16,Code/Thing.cpp,matched,"
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 16)], ledger_rows=[claimed])

    assert written == {}
