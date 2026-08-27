# Measuring the guest's input lag

A host feels snappy and a guest does not. Reading the binary settled why: all
game logic runs at a compiled-in 5 Hz (200 ms a logic frame), and a guest's
input pump runs only on those ticks, so a guest command waits for the next tick
merely to **leave** the machine and is then bound by the router to a later frame
than the host's would be. The gap is structural and does not shrink with ping.

`overlay/features/030-netlatprobe` measures that on real clients; `tools/netlat.py`
reads what it wrote. Nothing here changes the game — measure the defect first, or
a fix gets credited with an improvement nobody demonstrated.

## Build and run

```bash
python3 tools/modbuild.py --only 030-netlatprobe -o build/overlay/netlat.exe
```

`--dist` refuses to carry it: `overlay/dist` is what every ladder player runs and
this writes tens of lines a second. Each client appends JSONL to
`%APPDATA%\My Battle for Middle-earth Files\NetLat.jsonl`, or `BFME_LAT_PATH`.

```bash
python3 tools/netlat.py --preflight run1/*.jsonl   # on the FIRST capture
python3 tools/netlat.py --check-clocks run1/*.jsonl
```

Run `--preflight` before booking a campaign. It checks what reading the binary
could not: that the input hook fires at all (its target was never confirmed to be
the path input takes — if it is dead, re-aim it or filter on `TheCommandList`),
that both list-appends are visible, whether the command id is a real join key,
and that the seats shared one host clock.

## The five hooks

| RVA | Function | Emits |
|---|---|---|
| `0x0008A4E0` | `GameMessageList::appendMessage` | a command entering a list |
| `0x00664740` | `ConnectionManager::sendLocalCommand` | it leaving the machine |
| `0x00663100` | `ConnectionManager::relayCommand` | the router binding it to a frame |
| `0x00682A90` | `Network::relayCommandsToCommandList` | the per-logic-frame heartbeat |
| `0x00665D10` | `ConnectionManager::sendFrameInfo` | the router publishing the ceiling |

All five are hooked at the function's **entry**, which is what lets the shim lift
the target's own first argument (`cave.py`'s `args=("ecx","stack:0")`): a
thiscall's `this` arrives in ecx and the message it was called with does not.

Every line carries the clock, seat, logic frame and ceiling, so each metric is
recomputable from one seat's file. All seats share the host's
QueryPerformanceCounter, so timestamps compare across prefixes with no
synchronisation — which is the only reason a true cross-machine latency is
measurable here.

## What the numbers mean

* **wrap delay** — `t(send) - t(ready)`. The placebo killer: produced by the exact
  code path a send-side fix changes, so an inert fix cannot move it. Retail should
  sit near half a tick; a working fix takes it under a frame.
* **end to end** — input to the frame the router bound the command to. A guest
  never learns its own execution frame, so this only exists across two files.
* **logic rate** — 5 frames a wall second, from the frame *field*, not by counting
  events (a frame event can fire on a tick that does not advance the frame).
  This must not move: a latency win bought by running the game faster is not a fix.
* **backlog** — `ceiling - frame`. The one term static reading could not settle. If
  a loaded guest sits at 2-3, there is a second delay no send-side change can
  touch and the contingency is the pacing constant, not more send-side work.

The analysis refuses rather than reporting a number it cannot stand behind: a file
with no events, a join whose sides disagree on how many commands there were, or a
command that came out executing before it was issued.

## Future improvements

Measured after `031-earlysend` landed: the send side is essentially solved
(guest send -> the router binding it, median **14 ms**, was 35.6), and **96% of
what remains** is the guest taking a median **308 ms** to reach the frame the
router already bound its command to. Ranked by what the data says is left:

**1. The catch-up dead band — the big one, one float.** A guest sits permanently
one logic frame behind (backlog measured at exactly 1.0, p95 1.0, max 1: it never
drains). `GameEngine::execute` computes
`target = max(1.0, allowance * 0.1 + 0.7)` (`fmul` 0.1 at `0x01075C70`, `fadd`
0.7 at `0x01075C6C`, floor 1.0 at `0x01075334`) where a guest's `allowance` is
`ceiling - frame + 1`. It only asks a client to speed up at allowance >= 4, and
the guest lives at allowance 2 -- inside a band where the controller is
deliberately neutral, so a 200 ms phase lag once acquired is permanent.

Raising 0.7 to 0.9 makes allowance 2 yield 1.1, so the guest closes the gap and
goes neutral again at allowance 1. Self-limiting, and correctness is untouched:
`areFrameCommandsComplete` still gates every frame. Worth **up to ~200 ms** --
more than earlysend itself.

The catch: that lag IS the jitter buffer. Spending it turns loss and jitter into
hitches rather than smooth-but-delayed play, which is the trade RotWK's delay fix
made. Measure it clean AND under `netem` before believing either half.

**2. The 2 s retransmit timer** (`mov [edx+0x1C],2000` at RVA `0x006623DB`, a
single imm32). Irrelevant on a clean LAN, but it is what the ugly tails under
loss are made of -- p95 2144 ms and max 4095 ms in the netem arms. Cutting it to
~400 ms should pull those tails in; dedup already tolerates duplicate delivery.

**3. Raising the 5 Hz logic rate.** Halves every lockstep term at once, and is
the trap: game time per logic frame is the compiled-in `LOGICFRAMES_PER_SECOND`,
so the rate cannot move without rescaling every duration constant in the game.
Not a latency task.

## Gates

Baseline first — the defect must reproduce before anything is credited with
removing it: guest-minus-host wrap gap in [60, 160] ms, and near-flat when RTT is
added with `netem`. Then the fix arm, same instrument: wrap under 35 ms, logic
rate unchanged within 0.5% on every seat and both arms, no desync flagged, and one
run under added loss (the every-tick pump is only exercised there).
