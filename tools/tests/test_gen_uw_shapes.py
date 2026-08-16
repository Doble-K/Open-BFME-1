"""The funclet templates gen_uw emits, pinned to the bytes a probe compile made.

Every fixture below is a body MSVC 7.1 actually produced for the C++ the
emitters write -- captured from a probe TU compiled with the same
`/DNDEBUG /MD /EHsc` the generated files carry -- with the relocation slots
zeroed. Two claims are under test and they have to hold together:

  * the retail-side reader decodes each template's displacement, callee and
    member offset out of those bytes, in BOTH the int8 and int32 encodings of
    the frame reference (the disp32 twin is the same C++ at a bigger frame);
  * the emitted-side reader turns the same bytes back into the same key, so a
    row anchored to a $L label reproduces the funclet the key came from.

A shape that only round-trips through the reader proves nothing about codegen,
so the layout arithmetic the emitters do -- member offsets, the EBP-0x10 pad
ladder, and the 4-byte slot the frame already has -- is asserted separately
against the emitted source text.
"""
import importlib.util
import re
import struct
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


gen_uw = _load("gen_uw")

RVA = 0x00BF0000
DTOR = "??1Gen_uw_0000d828@@QAE@XZ"
MEMBER_DTOR = "??1Gen_uwm_0000d828@@QAE@XZ"
TARGET = 0x0000D828


def body(hexed, call_at):
    """A probe body with its REL32 slot aimed at TARGET from RVA."""
    raw = bytearray(bytes.fromhex(hexed))
    struct.pack_into("<i", raw, call_at, TARGET - (RVA + call_at + 4))
    return bytes(raw)


# hex, REL32 offset, expected (kind, disp, member offset)
TEMPLATES = [
    ("8d 4d f0 e9 00000000", 4, ("A", -0x10, 0)),
    ("8d 8d f0 fd ff ff e9 00000000", 7, ("A", -0x210, 0)),
    ("8d 4d 04 e9 00000000", 4, ("B", 4, 0)),
    ("8b 45 f0 50 e8 00000000 59 c3", 5, ("C", -0x10, 0)),
    ("8b 85 f0 fd ff ff 50 e8 00000000 59 c3", 8, ("C", -0x210, 0)),
    ("8b 4d f0 e9 00000000", 4, ("M", -0x10, 0)),
    ("8b 8d f0 fd ff ff e9 00000000", 7, ("M", -0x210, 0)),
    ("8b 4d f0 83 c1 04 e9 00000000", 7, ("M", -0x10, 4)),
    ("8b 4d f0 81 c1 98 00 00 00 e9 00000000", 10, ("M", -0x10, 0x98)),
    ("8b 8d f0 fd ff ff 83 c1 04 e9 00000000", 10, ("M", -0x210, 4)),
    ("8b 8d f0 fd ff ff 81 c1 08 06 00 00 e9 00000000", 13, ("M", -0x210, 0x608)),
]


@pytest.mark.parametrize("hexed,call_at,expected", TEMPLATES)
def test_retail_bytes_decode_to_the_template_that_made_them(hexed, call_at, expected):
    kind, disp, target, offset = gen_uw.classify(RVA, body(hexed.replace(" ", ""), call_at))

    assert (kind, disp, offset) == expected
    assert target == TARGET, "the destructor address comes out of the displacement"


@pytest.mark.parametrize("hexed,call_at,expected", TEMPLATES)
def test_emitted_bytes_decode_back_to_the_key_the_row_is_anchored_to(
        hexed, call_at, expected):
    kind, disp, offset = expected
    raw = bytes.fromhex(hexed.replace(" ", ""))
    callee = gen_uw.DELETE_NAME if kind == "C" else (
        MEMBER_DTOR if kind == "M" else DTOR)

    key = gen_uw.emitted_key(raw, {call_at: callee})

    funclet = gen_uw.Funclet(kind, RVA, len(raw), disp, TARGET, offset)
    assert key == gen_uw.key_of(funclet)


def test_a_label_running_past_its_funclet_still_decodes():
    """read_object_symbol_bytes hands back everything to the end of the section,
    so the emitted side is recognised by opcode and never by length."""
    raw = bytes.fromhex("8b4df083c104e900000000") + b"\xcc" * 40

    assert gen_uw.emitted_key(raw, {7: MEMBER_DTOR}) == ("M", -0x10, TARGET, 4)


def test_gen_uw_new_is_not_mistaken_for_an_address_bearing_name():
    """Gen_uw_new shares the Gen_uw_ prefix and carries no address; taking eight
    characters on faith turns it into a ValueError inside the label walk."""
    assert gen_uw.emitted_target("??1Gen_uw_new@@QAE@XZ", "??1Gen_uw_") is None
    assert gen_uw.emitted_target(DTOR, "??1Gen_uw_") == TARGET


def struct_offsets(text, name):
    """Byte offset of each Gen_uwm_ member in an emitted host struct."""
    fields = re.search(r"struct %s \{(.*?)\};" % name, text, re.S).group(1)
    offsets, position = [], 0
    for filler, member in re.findall(r"char q\d+\[(\d+)\];|(Gen_uwm_\w+ a\d+;)", fields):
        if filler:
            position += int(filler)
        else:
            offsets.append(position)
            position += 4
    return offsets


def test_the_member_host_puts_every_member_where_retail_says_it_is():
    wanted = (0, 4, 0x98, 0x9C, 0x2A9BC4)

    text = gen_uw.emit_member(TARGET, 0, wanted)

    assert struct_offsets(text, "Gen_uwh0_0000d828") == list(wanted)
    assert text.count("Gen_uwm_0000d828 a") == len(wanted), (
        "one member per offset")
    assert "Gen_uwm_0000d828 z;" in text, (
        "a member is only unwound because a LATER member's constructor threw past "
        "it, so without the trailing member the last offset emits no funclet")


def test_the_host_constructor_is_marked_absent_from_retail():
    """It is the only definition this generator writes that no row claims, and the
    commit hook refuses a Class::Method definition the ledger does not declare.
    Retail has no such constructor -- only the funclets it makes MSVC emit."""
    text = gen_uw.emit_member(TARGET, 0, (4,))

    assert "// ??0Gen_uwh0_0000d828@@QAE@XZ absent-from-retail" in text
    assert text.index("absent-from-retail") < text.index(
        "Gen_uwh0_0000d828::Gen_uwh0_0000d828"), "the marker precedes its definition"


def test_a_member_host_walks_this_down_with_the_same_pad_the_locals_use():
    assert "char pad[2120]; gen_uw_sink(pad);" in gen_uw.emit_member(TARGET, 2120, (4,))
    assert "char pad" not in gen_uw.emit_member(TARGET, 0, (4,))


def test_a_four_byte_pad_cannot_move_a_local_so_the_ladder_does():
    """`char pad[4]` lands in the spare slot the frame already has. It is the one
    displacement the pad rule does not reach, and the only reason two ladder
    locals survive in the emitter at all."""
    assert "char pad[4]" not in gen_uw.emit_local(TARGET, 4)
    assert gen_uw.emit_local(TARGET, 4).count("Gen_uw_0000d828 v") == 2
    assert "char pad[8]; gen_uw_sink(pad);" in gen_uw.emit_local(TARGET, 8)


@pytest.mark.parametrize("unit,funclets", [
    (gen_uw.Unit("local", TARGET, 1, (2120,)), [("A", -0x858, 0)]),
    (gen_uw.Unit("param", TARGET, 2, (2,)), [("B", 4, 0), ("B", 8, 0)]),
    (gen_uw.Unit("new", None, 1, (8,)), [("C", -0x18, 0)]),
    (gen_uw.Unit("member", TARGET, 2, (12, (0, 0x98))), [("M", -0x1C, 0), ("M", -0x1C, 0x98)]),
])
def test_a_unit_claims_exactly_the_keys_its_funclets_ask_for(unit, funclets):
    """`missing` stops the run on a key claimed here that the compiler did not
    produce, so this mapping is the whole reason no row can be anchored to a
    label that reproduces something else."""
    expected = [gen_uw.key_of(gen_uw.Funclet(kind, RVA, 8, disp, TARGET, offset))
                for kind, disp, offset in funclets]

    assert sorted(gen_uw.unit_keys(unit)) == sorted(expected)


@pytest.mark.parametrize("disp,offset,why", [
    (-0x10 + 2, 0, "a slot 2 bytes below EBP-0x10 is not on the 4-byte ladder"),
    (-0x0C, 0, "above EBP-0x10 there is no pad that reaches it"),
    (-0x10, 6, "a 6-byte member offset is not a field a struct layout produces"),
    (-0x10, -4, "a negative member offset is not a field at all"),
])
def test_an_unplaceable_slot_is_declined_with_the_reason_recorded(disp, offset, why):
    funclet = gen_uw.Funclet("M", RVA, 11, disp, TARGET, offset)

    assert not gen_uw.on_the_ladder(funclet), why
    assert gen_uw.unreachable(funclet), "the reason becomes a tombstone's reason column"
