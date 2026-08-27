# Fixing BFME 1's off-host input delay

## The problem

On the host, units respond almost immediately. On a guest, they don't. Players
have described this for twenty years; nobody has fixed it in BFME 1.

## What causes it

The engine, not your connection.

BFME 1 runs all game logic at 5 frames per second — one frame every 200 ms. A
guest's input queue is drained only inside that tick, so a command waits for the
next one *merely to leave the machine*. The host doesn't wait: it stamps and
executes its own commands inside the same tick.

Two delays then stack: the host binds an arriving command to *its* current
frame, and a guest already trails by a full quantum — so the guest waits roughly
two ticks, not one.

## The fix

One 5-byte detour (`031-earlysend`, 106 bytes of payload). It drains the command
queue every engine tick (~33 ms) rather than only on the 5 Hz logic tick, sited
immediately before the engine's own network flush — so a command queued there
reaches the wire on the next instruction.

It deliberately does **not** touch the 5 Hz quantum, the frame ceiling, or the
logic cadence. Raising the tick rate would multiply the game's speed — the trap,
not the fix. Commands only leave *earlier*.

## How we tested it

Two real clients (host and guest) play a LAN match on separate network stacks,
each issuing ~200 scripted commands at random intervals. A second overlay logs
every command's journey on a clock shared by both machines. Retail is measured
**first**: the defect must reproduce before anything is credited with removing
it. Twelve matches; ranges are best-to-worst of three per build.

## Results — clean LAN (milliseconds)

| | Retail | Fixed |
|---|---|---|
| Command sent → it runs (guest) | 395.7 `[395.1–396.1]` | **309.1** `[303.4–320.9]` |
| Host vs guest gap | 395.5 | **224.7** |
| Command leaves after its tick | 198.0 `[198.0–198.5]` | **105.2** `[102.3–105.3]` |
| Logic rate (frames/sec) | 5.000 | 5.000 |

No retail match overlaps any fixed match — the gain is ~90x the run-to-run
spread. The unchanged logic rate means game speed, resource rates and animation
timing are untouched: the fix moves *when a command is sent*, nothing else.

## Results — 40 ms ping, 1% loss (milliseconds)

| | Retail | Fixed |
|---|---|---|
| Command sent → it runs (guest) | 576 `[409–696]` | 609 `[449–658]` |
| Command leaves after its tick | 191.8 | **103.8** |

Here the builds are **indistinguishable**: each spreads ~±150 ms, more than the
gap between them. The fix still halves the send cadence, but under loss the delay
is dominated by the guest falling behind and catching up, which it cannot
address. Expect a large gain on good connections, little on poor ones.

No desync occurred in any of the twelve matches.

## Shipping

It compiles into the same single `lotrbfme.exe` as the win-detection feature —
one file, identical for every player.
