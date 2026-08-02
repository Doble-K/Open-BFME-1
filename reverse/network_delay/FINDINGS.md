# Multiplayer delay reconstruction

Goal: recover the original BFME 1 multiplayer command-delay path, byte-verify it,
and document the exact BFME addresses needed for any future opt-in patch. This
track does not change gameplay behavior.

## The answer: a router-published frame ceiling

The delay is recovered and byte-matched. It is not Zero Hour's run-ahead. BFME
clamps every client to a shared **frame ceiling** stored on the connection
manager at `+0x1205C`, which the packet router republishes from its own current
frame on a fixed timer.

| Item | RVA | Size | Role |
| --- | --- | --- | --- |
| `BFMENativeNetwork::getFrameAdvanceCount` | `0x00681F70` | 395 | native vtable `0x0111A968` slot `+0x3C`; how many logic frames may run now |
| `BFMENativeNetwork::getFramePacingStatus` | `0x00682160` | 214 | slot `+0x40`; same two paths, returns 0/1/2 |
| `BFMEConnectionManager::update` | `0x0066AB30` | 814 | the per-tick pass; the only caller of sendFrameInfo |
| `BFMEConnectionManager::sendFrameInfo` | `0x00665D10` | 354 | builds command type 3 and, as router, sets the ceiling |
| `BFMEConnectionManager::processIncomingCommand` | `0x0066A3F0` | 580 | case 3 raises a client's ceiling to the announced frame |
| `BFMEConnectionManager::areFrameCommandsComplete` | `0x006633E0` | 89 | the readiness gate |
| `BFMEConnectionManager::getFrameHeadroom` | `0x00664320` | 142 | ceiling minus current frame, for both roles |
| `BFMEConnectionManager::runRelayPass` | `0x0066A740` | 792 | the router's receive-and-relay pass |
| `BFMEDisconnectManager::update` | `0x0066C8D0` | 1122 | the timeout sweep update runs alongside it |

### How a frame is released

`getFrameAdvanceCount` returns 1 when `+0x0C` says we are not in a network game,
and 1 again on frame 0. Otherwise it splits on the virtual predicate at native
slot `+0x8C`:

* **Not the packet router.** `allowance = connectionManager->+0x1205C - TheGameLogic->getFrame() + 1`.
  If that is positive it consults `areFrameCommandsComplete`; when the frame's
  commands are not yet in it calls its own slot `+0x24` and returns 0, otherwise
  it clears the stall flag at `+0x28` and returns the allowance. When the
  allowance is already non-positive it bumps the stall counter at `+0x2C`,
  records the frame in the `0x012F7728` global, and returns the non-positive
  value.
* **Packet router.** If `hasPacketRouterFrameStall` (`0x00664260`) it zeroes the
  QPC accumulator at `+0x20` and returns 0. Otherwise it adds the
  `QueryPerformanceCounter` delta to that accumulator and compares it against
  **`QueryPerformanceFrequency / 5`** -- a fixed 200ms, five logic ticks per
  second, independent of ping and of frame rate. Below the quantum it returns 0;
  at or above it subtracts one quantum, clamps a backlog of more than two quanta
  (bumping `0x012F7724`, the counter behind the string "Total # of times we've
  hit the run-ahead ceiling" at `0x006EE800`), and returns 1.

### How the ceiling is published

`update` is the only caller of `sendFrameInfo`, so the cadence above is exactly
the cadence of the ceiling. `sendFrameInfo` allocates a `0x28`-byte command type
3, stamps `TheGameLogic->getFrame()` at `+0x1C`, sums `getCommandCount(frame)`
over the eight `FrameDataManager`s at `+0x120E4`, records that total on the local
manager with `setFrameCommandCount` and copies it into the message at `+0x24`.
Then, as packet router, it broadcasts with relay `~(1 << localSlot)` and sets
`+0x1205C` to **its own current frame**; as a client it sends only to the router.

`processIncomingCommand` case 3 is the receiving half: it updates
`m_playerLatestFrame[sender]` at `+0x12060` and the aux dword at `+0x120A0`, and
-- only when it is *not* the router -- raises its own `+0x1205C` to the announced
frame. If that frame is not behind the current one and the message's count at
`+0x24` is not `-1`, it stores the count on the local manager as the expected
total.

So the host runs free and every other player is clamped to a frame the host
published at most 200ms ago. **That is BFME's off-host delay, and it is a
property of the fixed quantum rather than of latency**, which is why it does not
shrink on a LAN. Any future opt-in patch has to change that quantum or the
ceiling it feeds, not hunt for a run-ahead value.

### Readiness

`areFrameCommandsComplete` sums `FrameDataManager::getCommandCount(frame)` over
the eight managers at `+0x120E4`, skipping null and quitting ones, and returns
whether that total equals the local manager's `getFrameCommandCount(frame)`.
BFME therefore tracks one aggregate expected count where Zero Hour matches
counts per player.

### Ruled out

The ZH `Network`/`ConnectionManager` run-ahead path is not merely unmatched, it
is absent: `sendLocalGameMessage`, `allCommandsReady`, `updateRunAhead`,
`setFrameGrouping`, `processRunAheadCommand`, `timeForNewFrame`,
`GetCommandsFromCommandList` and `Network::update` all classify absent in the ZH
sweep, a locate-only probe of the 256-byte `timeForNewFrame` body returned
`0 located`, and BFME has no code xrefs to the `NetworkRunAheadSlack` or
`NetworkRunAheadMetricsTime` strings beyond their INI parse rows.

## BFME command-type correction

The old ZH run-ahead command trail is now ruled out for BFME retail. The BFME
command-type string mapper at `0x00683020` names the relevant values as:

| Value | BFME name |
| --- | --- |
| `3` | `NETCOMMANDTYPE_FRAMEINFO` |
| `4` | `NETCOMMANDTYPE_GAMECOMMAND` |
| `5` | `NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY` |
| `6` | `NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY` |
| `7` | `NETCOMMANDTYPE_REQUESTPLAYERLEAVE` |
| `8` | `NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME` |
| `9` | `NETCOMMANDTYPE_REQUESTFRAMEDATA` |
| `10` | `NETCOMMANDTYPE_PLAYERLEAVE` |
| `11` | `NETCOMMANDTYPE_DESTROYPLAYER` |

This differs from Zero Hour, where values `6` and `7` are run-ahead metrics and
run-ahead. In BFME:

- `0x006741F0` is byte-matched as the command type `7` constructor and initializes
  a single dword payload at `+0x1C`; it is now named
  `BFMENetRequestPlayerLeaveCommandMsg::construct`.
- `0x00674240` and `0x00674250` are byte-matched as the payload setter/getter.
- `0x00677530` writes the type `7` wire payload as a four-byte `D` field after
  `T/R/P/C`; there is no ZH-style frame-rate byte.
- `0x00675BE0` constructs command type `6`, whose callers populate two
  `AsciiString`-like fields. It is GameSpy stats auth-key traffic, not
  run-ahead metrics.

So a future delay fix should not patch BFME command types `6` or `7` as if they
were ZH `NetRunAhead*` classes.

The incoming command dispatcher at `0x0066A3F0` uses the command type at message
offset `+0x14` and a jump table at `0x0066A634`. For the frame-delay path:

| Value | Dispatcher evidence |
| --- | --- |
| `3` | inline frame-info-ish state update for per-player latest frame fields at `+0x12060`/`+0x120A0` |
| `8` | calls `0x00664430`, the next frame-info/request helper to recover |
| `9` | calls matched `BFMEConnectionManager::processRequestFrameDataCommand` at `0x006659B0` |

## BFME-native path

The BFME binary routes the proven multiplayer entry point through a smaller
network wrapper/backend pair. These addresses are current reverse-engineering
anchors, not behavior changes.

| Item | Address | Evidence | Status |
| --- | --- | --- | --- |
| `TheNetwork` global | VA `0x012F76F0` / RVA `0x00EF76F0` | caller at `0x006377D0` stores the `createNetwork` return value, then calls vtable slot `+0x04` | recovered |
| `NetworkInterface::createNetwork` | RVA `0x0065C1F0`, ILT `0x000362C3` | byte-matched row; allocates `0xA8` bytes | matched |
| BFME network wrapper constructor | RVA `0x0065AC30`, ILT `0x00029C12` | byte-matched as `BFMENetwork::construct`; installs vtable VA `0x01119C8C` and initializes wrapper queues/list | matched |
| BFME network wrapper vtable | VA `0x01119C8C` / RVA `0x00D19C8C` | referenced by constructor | recovered |
| backend constructor | RVA `0x006547F0`, ILT `0x00040E44` | byte-matched as `BFMENetworkBackend::construct`; stores owner pointer at backend `+0x68` and initializes list at `+0x5C` | matched |
| backend vtable | VA `0x0111988C` / RVA `0x00D1988C` | installed by backend constructor | recovered |
| backend deleting destructor | RVA `0x00654890` | byte-matched as `BFMENetworkBackend::destroyAndMaybeDelete`; backend vtable slot `+0x00` | matched |
| backend live-handle opener | RVA `0x009DB650` | byte-matched as `BFMENetworkBackend::openLiveHandle`; backend vtable slot `+0x04`, starts thread and stores handle at `+0x48` | matched |
| backend thread start | RVA `0x009DB630` | byte-matched as `BFMENetworkBackendThreadStart`; calls global slot `+0x58`, then backend vtable slot `+0x08` | matched |
| backend event callback | RVA `0x006549C0`, ILT `0x000276B0` | byte-matched as `BFMENetworkBackendEventCallback`; dispatcher calls it through the ILT in multiple cases, callback returns with `ret 0x28` | matched |
| wrapper deleting destructor | RVA `0x0065ADB0` | byte-matched as `BFMENetwork::destroyAndMaybeDelete`; wrapper vtable slot `+0x00` | matched |
| wrapper init | RVA `0x006548C0` | byte-matched as `BFMENetwork::init`; creates backend at wrapper `+0x64` and calls backend vtable slot `+0x04` | matched |
| backend handle check | RVA `0x009DB590` | byte-matched as `BFMENetworkBackend::hasLiveHandle`; reads backend `+0x48` | matched |
| backend handle clear | RVA `0x009DB5A0` | byte-matched as `BFMENetworkBackend::closeLiveHandle`; waits on/clears backend `+0x48` and `+0x44` | matched |
| lock-ref release | RVA `0x009DB400` | byte-matched as `BFMEAutoLockRef::~BFMEAutoLockRef`; releases lock handle at `+0x00` when `+0x04` is false | matched |
| wrapper queue 0 push | RVA `0x0065E050` | byte-matched as `BFMENetwork::pushQueue0`; locks wrapper `+0x04`, appends to queue at `+0x14` | matched |
| wrapper queue 0 pop | RVA `0x0065ADE0` | byte-matched as `BFMENetwork::popQueue0`; locks wrapper `+0x04`, pops queue at `+0x14` into caller output | matched |
| wrapper queue 1 push | RVA `0x0065E120` | byte-matched as `BFMENetwork::pushQueue1`; locks wrapper `+0x0C`, appends to queue at `+0x3C` | matched |
| wrapper queue 1 pop | RVA `0x00658E20` | byte-matched as `BFMENetwork::popQueue1`; locks wrapper `+0x0C`, pops queue at `+0x3C` into caller output | matched |
| wrapper payload-list push | RVA `0x0065E340` | byte-matched as `BFMENetwork::pushList90`; dispatcher calls wrapper slot `+0x20` after building a payload, appending to list at `+0x90` | matched |
| wrapper payload-list find/create | RVA `0x0065AEB0` | byte-matched as `BFMENetwork::findList90`; wrapper slot `+0x24` searches or materializes an entry in list at `+0x90` | matched |
| wrapper state-copy helpers | RVAs `0x00655060`, `0x00655090`, `0x006550C0` | byte-matched as `BFMENetwork::copyState6C`, `copyState78`, `copyState84`; callback uses these to copy wrapper fields `+0x6C`, `+0x78`, `+0x84` | matched |
| backend event dispatcher | RVA `0x0065CA50` | byte-matched as `BFMENetworkBackend::dispatchEvents`; backend vtable slot `+0x08`; body ends at `0x0065D6F2` before EH catch thunk and switch table | matched |
| dispatcher catch thunk | RVA `0x0065D6F3` | byte-matched as `BFMENetworkBackendDispatchCatch`; returns cleanup resume VA `0x00A5CAEB` | matched |
| registered callback | RVA `0x0065C260` | byte-matched as `BFMENetworkRegisteredCallback`; dispatcher pushes callback VA `0x00A5C260` before call to `0x009D5330`; callback calls wrapper slots `+0x18` and `+0x10` | matched |

Known wrapper slots from vtable VA `0x01119C8C`:

| Slot | Body RVA | Current role |
| --- | --- | --- |
| `+0x00` | `0x0065ADB0` | matched as `BFMENetwork::destroyAndMaybeDelete`; scalar deleting destructor wrapper |
| `+0x04` | `0x006548C0` | matched as `BFMENetwork::init`; allocates backend object and calls backend slot `+0x04` |
| `+0x08` | `0x00652AB0` | matched as `BFMENetwork::destroyBackend`; releases lock-ref `+0xA4`, backend handle, then backend `+0x64` |
| `+0x0C` | `0x00651780` | matched as `BFMENetwork::backendHasLiveHandle`; proxies backend pointer at wrapper `+0x64` |
| `+0x10` | `0x0065E050` | matched as `BFMENetwork::pushQueue0`; pushes queue at wrapper `+0x14` |
| `+0x14` | `0x0065ADE0` | matched as `BFMENetwork::popQueue0`; pops queue at wrapper `+0x14`, returns bool |
| `+0x18` | `0x0065E120` | matched as `BFMENetwork::pushQueue1`; pushes queue at wrapper `+0x3C` |
| `+0x1C` | `0x00658E20` | matched as `BFMENetwork::popQueue1`; pops queue at wrapper `+0x3C`, returns bool |
| `+0x20` | `0x0065E340` | matched as `BFMENetwork::pushList90`; appends payload list at wrapper `+0x90` |
| `+0x24` | `0x0065AEB0` | matched as `BFMENetwork::findList90`; searches or creates payload list entry at wrapper `+0x90` |

The wrapper constructor initializes locks at `+0x04`, `+0x0C`, and `+0x9C`;
queue/list structures at `+0x14` and `+0x3C`; object/array regions at `+0x6C`,
`+0x78`, and `+0x84`; backend pointer at `+0x64`; and a current/session-ish
field at `+0x68`.

The dispatcher at `0x0065CA50` is now bounded and byte-matched. Its switch table
starts at `0x0065D6FC`; that table is data and is intentionally not part of the
function row. Cases `4`, `8`, and `9` share the cleanup block at `0x0065D69E`;
case `10` calls helper `0x0062F7F2`; case `0` registers callback VA
`0x00A5C260`; and case `1` reads `LoTRB4MEOnline\MiscPref%d.ini` keys `"0"`
through `"5"` with default value `10`. Treat those key/default reads as GameSpy
misc-preference evidence until another caller proves they feed gameplay delay.

## BFME timing fields

The first native timing slice is now byte-matched:

| Function | RVA | Timing evidence |
| --- | --- | --- |
| `BFMEConnectionManager::isPlayerConnected` | `0x00662A50` | uses `timeGetTime`; compares elapsed time against `TheGlobalData + 0xCBC` (`NetworkPlayerTimeoutTime`); before frame threshold `0x010EAD50`, uses `NetworkPlayerTimeoutTime * 4` |
| `BFMEConnectionManager::isPlayerConnectedForTimeout` | `0x00662B00` | same connection timestamp at peer object `+0x34C`; normally uses caller timeout, but startup path still falls back to `NetworkPlayerTimeoutTime * 4` |
| `BFMEConnectionManager::hasPacketRouterFrameStall` | `0x00664260` | only runs when local player is packet router; after frame `5`, uses `TheGlobalData + 0xCB4` (`NetworkKeepAliveDelay`) to detect stale per-player frame data |
| `BFMEDisconnectManager::hasDisconnectScreenNotifyTimedOut` | `0x0066B510` | compares elapsed time against `TheGlobalData + 0xCC0` (`NetworkDisconnectScreenNotifyTime`) |
| `BFMEConnectionManager::processRequestFrameDataCommand` | `0x006659B0` | command type `9` handler; rejects/clamps requested resend windows using `NetworkKeepAliveDelay`, then calls `0x0040D8CD` with player id and frame range |

These are timeout/readiness gates, not the delay patch itself, but they expose the
retail frame and keep-alive timing constants that a later patch design must not
confuse with ZH run-ahead command traffic.

## BFME frame pacing

ZH `Network::timeForNewFrame` is not a BFME byte match. A locate-only probe of
the 256-byte ZH-shaped body returned `0 located`, and BFME has no code xrefs to
the `NetworkRunAheadSlack`/`NetworkRunAheadMetricsTime` strings beyond their INI
parse-table rows. That rules out the ZH run-ahead pacing body as the direct patch
site.

The BFME-native `Network` object instead initializes QPC pacing state in the
constructor body at `0x006818B0`, now byte-matched as
`BFMENativeNetwork::construct`:

| Field | Constructor evidence |
| --- | --- |
| `+0x08` | connection manager pointer initialized to null |
| `+0x0C` | local/network status initialized to `0` |
| `+0x10` | `QueryPerformanceFrequency` output |
| `+0x18` | initial `QueryPerformanceCounter` output |
| `+0x20`/`+0x24` | QPC accumulator initialized to `0` |
| `+0x28`, `+0x34`, `+0x35` | pacing/status flags initialized to false |
| `+0x38` | frame/player sentinel initialized to `-1` |

The native vtable at `0x0111A968` resolves slot `+0x3C` to `0x00681F70` and
slot `+0x40` to `0x00682160`. Slot `+0x40` is now byte-matched as
`BFMENativeNetwork::getFramePacingStatus`:

| Function | RVA | Pacing evidence |
| --- | --- | --- |
| `BFMENativeNetwork::getFramePacingStatus` | `0x00682160` | returns `1` when not in active network status; without packet-router timing mode, returns `connectionManager->+0x1205C - currentFrame + 1`; otherwise accumulates QPC ticks and returns `0`, `1`, or `2` based on elapsed budget |

Slot `+0x3C` at `0x00681F70` is now byte-matched as
`BFMENativeNetwork::getFrameAdvanceCount` -- see the first section, which is
where the QPF/5 quantum and the four globals `0x012F7718`, `0x012F771C`,
`0x012F7724` and `0x012F7728` are described.

## Landed evidence

- `ConnectionManager.cpp`, `Network.cpp`, `NetCommandMsg.cpp` and
  `MessageStream.cpp` are now trimmed to
  byte-matched surfaces only; the previous unclaimed ZH bodies were removed
  rather than treated as progress.
- `Code/GameEngine/Source/GameNetwork/native_network.cpp` contains the first byte-matched BFME-native
  wrapper/backend code:
  - `BFMENetworkBackend::construct` at `0x006547F0` (constructor body).
  - `BFMENetworkBackend::destroyAndMaybeDelete` at `0x00654890`.
  - `BFMENetworkBackend::openLiveHandle` at `0x009DB650`.
  - `BFMENetworkBackendThreadStart` at `0x009DB630`.
  - `BFMENetworkBackendEventCallback` at `0x006549C0`.
  - `BFMENetwork::construct` at `0x0065AC30` (constructor body).
  - `BFMENetwork::destroyAndMaybeDelete` at `0x0065ADB0`.
  - `BFMENetwork::init` at `0x006548C0`.
  - `BFMENetwork::backendHasLiveHandle` at `0x00651780`.
  - `BFMENetwork::destroyBackend` at `0x00652AB0`.
  - `BFMENetwork::pushQueue0` at `0x0065E050`.
  - `BFMENetworkBackend::hasLiveHandle` at `0x009DB590`.
  - `BFMENetworkBackend::closeLiveHandle` at `0x009DB5A0`.
  - `BFMEAutoLockRef::~BFMEAutoLockRef` at `0x009DB400`.
  - `BFMENetwork::popQueue0` at `0x0065ADE0`.
  - `BFMENetwork::pushQueue1` at `0x0065E120`.
  - `BFMENetwork::popQueue1` at `0x00658E20`.
  - `BFMENetwork::pushList90` at `0x0065E340`.
  - `BFMENetwork::findList90` at `0x0065AEB0`.
  - `BFMENetwork::copyState6C`, `copyState78`, and `copyState84` at
    `0x00655060`, `0x00655090`, and `0x006550C0`.
- `Code/GameEngine/Source/GameNetwork/native_network_callback.cpp` contains `BFMENetworkRegisteredCallback`
  at `0x0065C260`.
- `Code/GameEngine/Source/GameNetwork/native_network_dispatcher.cpp` contains `BFMENetworkBackend::dispatchEvents`
  at `0x0065CA50` and its EH catch thunk at `0x0065D6F3`.
- `Code/GameEngine/Source/GameNetwork/native_netcommandmsg.cpp` contains the BFME command type `7`
  request-player-leave constructor/destructor and its single dword payload
  setter/getter at `0x006741F0`, `0x00674230`, `0x00674240`, and `0x00674250`.
- `Code/GameEngine/Source/GameNetwork/native_connection_timing.cpp` contains the first byte-matched BFME
  player-timeout, packet-router stall, disconnect-screen timeout, and request
  frame-data handler checks at `0x00662A50`, `0x00662B00`, `0x00664260`,
  `0x0066B510`, and `0x006659B0`.
- `Code/GameEngine/Source/GameNetwork/native_network_interface.cpp` contains the native BFME `Network`
  constructor body at `0x006818B0`, anchoring the QPC frame-pacing fields, and
  the QPC-backed pacing-status helper at `0x00682160`.
- The current matched network rows are:
  - `ConnectionManager::processProgress` at `0x00662D20`.
  - `NetworkInterface::createNetwork` at `0x0065C1F0`.
  - `Network::isPacketRouter` at `0x00681B20`.
  - Three STL helper/template rows emitted from `connectionmanager.cpp`.
- The old ZH delay functions are not proven BFME code. Treat ZH as an intent map
  and the BFME-native rows above as the patchable evidence.

## Object layouts pinned by the matched bodies

### ConnectionManager

| Offset | Field |
| --- | --- |
| `+0x00004` | `Connection *m_connections[8]` |
| `+0x12028` | `m_localSlot` |
| `+0x1202C` | `m_packetRouterSlot` |
| `+0x12030` | per-player dword[8], init `-1` |
| `+0x12050` / `+0x12054` / `+0x12058` | dword / word / dword |
| `+0x1205C` | **frame ceiling** |
| `+0x12060` | per-player latest frame[8] |
| `+0x12080` | per-player state[8]: 0 empty, 1 in game, 2-3 leaving |
| `+0x120A0` | per-player dword[8], from FRAMEINFO `+0x20` |
| `+0x120C0` | per-player dword[8] |
| `+0x120E4` | `FrameDataManager *m_frameData[8]` |
| `+0x12104` / `+0x12108` | the two pending-command lists the ack path searches |
| `+0x1210C` .. `+0x12130` | further owned objects, all released by `destroy` |

The constructor (`0x00669630`) and init (`0x00669050`) write the whole tail; the
destructor (`0x00668D90`) releases it. Note the constructor stores **no vtable**
at `+0x00`, so whatever occupies that dword is not a vptr.

### DisconnectManager

36 bytes smaller than the ZH reference: no `m_packetRouterFallback[8]`, no
`m_currentPacketRouterIndex`, no `m_packetRouterTimeout` -- the same edit that
removed PACKETROUTERQUERY and PACKETROUTERACK from its command block.

| Offset | Field |
| --- | --- |
| `+0x000` | vptr |
| `+0x004` | `m_lastFrame` |
| `+0x008` | `m_lastFrameTime` |
| `+0x00C` | `m_disconnectState` |
| `+0x010` | `m_lastKeepAliveSendTime` |
| `+0x014` | `m_playerTimeouts[7]` |
| `+0x030` | `m_playerVotes[8][8]`, row stride 0x40 |
| `+0x230` | `m_disconnectFrames[8]` |
| `+0x250` | `m_disconnectFramesReceived[8]` |
| `+0x258` | `m_haveNotifiedOtherPlayersOfCurrentFrame` |
| `+0x25C` | `m_timeOfDisconnectScreenOn` |
| `+0x260` / `+0x264` / `+0x268` | `m_pingsSent` / `m_pingsRecieved` / `m_pingFrame` |

Carried by `reference/shims/disconnectmanager`. `turnOffScreen` (`0x0066B270`)
is a BFME addition with no ZH counterpart, called unconditionally at the end of
`processDisconnectScreenOff`.

### FrameData

20 bytes, not the ZH reference's 24 -- ZH's leading `m_frame` is gone because the
ring index already is the frame. `m_frameCommandCount` `+0x00`,
`m_commandCount` `+0x04`, `m_commandList` `+0x08`, `m_lastFailedCC` `+0x0C`,
`m_lastFailedFrameCC` `+0x10`. `FrameDataManager` keeps the ZH layout.
`FRAME_DATA_LENGTH` is the runtime global at VA `0x012BA088`. Carried by
`reference/shims/framedata`.

### NetCommandRef

De-pooled and 20 bytes: `m_msg` `+0x00` (where ZH has a vptr), `m_next` `+0x04`,
`m_prev` `+0x08`, `m_relay` `+0x0C`. Proven by `relayCommand` (`0x00663100`) and
`NetCommandList::reset` (`0x006731A0`), which plain-deletes its nodes rather than
returning them to a pool.

## Corrections to earlier notes in this file

* `0x00655360` and `0x006386F0` are **GameSpy persistent-storage serialization**
  (`\wins%d\%d`, `\desyncs%d\%d`), not the lockstep desync reporter. The real
  desync writer is `0x00065470`, which recomputes `GameLogic::getCRC`, compares
  it against a stored value, and on mismatch formats `CLIENT_DESYNC_%s.txt` and
  "Desync detected on frame %d on %u-%u-%u %u:%u:%u". Its only caller is
  `0x0006B910`.
* The `0x0080E000`-`0x0081A000` band is EA's DirtySock middleware -- `commudp`,
  `commtcp`, `protoadvt`, `NetGameUtil`, `comm/datamodem` -- with no counterpart
  in the Zero Hour reference. It carries the GameSpy/online transport, not the
  lockstep path, which still runs through SAGE's own `udp.cpp`.
* `NetCommandList::reset` was pointed at ILT thunk `0x00015479`, which jumps to
  `0x0040AD80`, a different function. Retail's call sites reach the real body at
  `0x006731A0` through thunk `0x0000B9CE`.
* `ConnectionManager::sendFrameDataToPlayer` (`0x00664D20`, two arguments) only
  raises a per-player watermark at `+0x12060`. The three-argument resend that
  actually re-sends stored commands is a different function, `0x00664B40`,
  recorded here as `resendFrameRangeToPlayer`.

## Work plan

1. DONE: unblock targeted ZH sweeps for the GameNetwork files with minimal
   compile shims.
2. DONE: land the first byte-verified `ConnectionManager` and `Network` rows.
3. DONE: prove that the needed path is BFME-native enough that ZH is a search
   map, not the source of truth.
4. DONE: recover the native dispatcher boundary and name the remaining wrapper
   fields before attempting any patch design.
5. DONE: rule out the ZH `NetRunAhead*` command classes for BFME command types
   `6` and `7`.
6. DONE: match the first BFME timing/readiness gates that consume
   `NetworkPlayerTimeoutTime`, `NetworkKeepAliveDelay`, and
   `NetworkDisconnectScreenNotifyTime`.
7. DONE: trace the BFME frame scheduler end to end. Both halves are matched --
   the router publishes the ceiling in `sendFrameInfo` on a
   `QueryPerformanceFrequency / 5` quantum driven by `update`, and clients raise
   theirs in `processIncomingCommand` case 3. `getFrameAdvanceCount` at native
   slot `+0x3C` is the gate that reads it.
8. NEXT: the pieces around the scheduler that are still unclaimed -- the desync
   writer at `0x00065470` and its caller `0x0006B910`, `GameLogic::getCRC`
   (matched only as a MASM dump), and the remaining unnamed bodies in
   `0x00660000`-`0x00672000`, most of which are GameSpy/lobby rather than
   lockstep.

## Non-goals

- Do not lower run-ahead values here.
- Do not add an opt-in patch profile here.
- Do not change matched source away from the original BFME behavior.

---

# The scheduler, decoded (2026-08-02)

`getFrameAdvanceCount` (0x00681F70, vtable +0x3C) is the whole delay. It is still
`__declspec(naked)` assembly in our tree, so nobody had read it. Decoded:

```
int BFMENativeNetwork::getFrameAdvanceCount()
{
    if (m_state(+0x0C) != 1)          return 1;      // not in a network game: free-run

    if (this->vtable[0x8C]())         goto quantum;  // <-- SELECTOR, still unidentified

    if (TheGameLogic->getFrame() == 0) return 1;

    if (!m_stallFlag(+0x28)) {                        // first tick of a stall
        g_stallStart(0x12F7718) = timeGetTime();
        m_stallFlag(+0x28) = 1;
    }

    allowance = m_conMgr(+8)->m_frameCeiling(+0x1205C) - TheGameLogic->getFrame() + 1;

    if (allowance > 0) {
        if (areFrameCommandsComplete(curFrame, FALSE)) {   // 0x006633E0
            m_stallFlag(+0x28) = 0;
            return allowance;                              // <-- the release
        }
        this->vtable[0x24](FALSE);
        return 0;                                          // commands missing: hold
    }
    ... bookkeeping on 0x12F7728, returns allowance ...

quantum:                                                   // the 200ms path
    if (m_conMgr->hasPacketRouterFrameStall()) {           // 0x00664260
        m_accum(+0x20/+0x24) = 0;
        return 0;
    }
    QueryPerformanceCounter(&now);                         // [0x1358EB4]
    m_accum += now - m_lastCounter(+0x18/+0x1C);
    m_lastCounter = now;

    quantum = m_freq(+0x10/+0x14) / 5;                     // __alldiv, divisor 5
    if (m_accum < quantum) return 0;                       // not yet
    m_accum -= quantum;
    if (m_accum > quantum * 2) { g_overrun(0x12F7724)++; m_accum = 0; }  // catch-up clamp
    g_lastAdvance(0x12F771C) = timeGetTime();
    return 1;                                              // exactly ONE frame
}
```

`m_freq` really is the performance frequency: `construct` (0x006818D4) calls
[0x1358EB8] then [0x1358EB4] -- QueryPerformanceFrequency then
QueryPerformanceCounter -- storing them at +0x10/+0x14 and +0x18/+0x1C.

So on the quantum path the caller is released **one logic frame per 200ms**, and
on the normal path it is released `ceiling - currentFrame + 1` frames gated on
`areFrameCommandsComplete`. Nothing here consults ping, which is why the delay
does not shrink on a LAN.

## The one thing that must be identified next

**Virtual slot +0x8C decides which path runs**, and it is unidentified. Everything
about the size of the fix depends on it: if it is "am I the packet router" then
the host is paced at 5Hz and clients follow its ceiling; if it is a loading or
observer state then the quantum path is not the steady-state path at all and the
delay is elsewhere. Do not tune the 5 until this is known.

# The nine network INI fields: six are dead

The GameData block parses nine network timing fields. A def-use scan -- decode
each function, track the register loaded from TheWritableGlobalData (0x012ED5C8),
let callee-saved registers survive calls, then look for [reg+offset] -- gives:

| INI key | offset | reads | verdict |
|---|---|---|---|
| NetworkFPSHistoryLength | 0xCA4 | 0 | parsed, never read |
| NetworkLatencyHistoryLength | 0xCA8 | 0 | parsed, never read |
| NetworkRunAheadMetricsTime | 0xCAC | 0 | parsed, never read |
| NetworkCushionHistoryLength | 0xCB0 | 0 | parsed, never read |
| NetworkKeepAliveDelay | 0xCB8 | 0 | parsed, never read |
| NetworkDisconnectScreenNotifyTime | 0xCC4 | 0 | parsed, never read |
| NetworkRunAheadSlack | 0xCB4 | 10 | live |
| NetworkDisconnectTime | 0xCBC | 3 | live |
| NetworkPlayerTimeoutTime | 0xCC0 | 4 | live |

`NetworkCushionHistoryLength` being dead rules out an adaptive cushion layer.

`NetworkRunAheadSlack` is NOT a lead. It is a stall tolerance:
`hasPacketRouterFrameStall` returns TRUE when any
`m_playerLatestFrame[i] + slack < TheGameLogic->getFrame()`, and its only caller
is the scheduler. Before frame 5 the slack is a hardcoded 3. In
`Connection::doSend` the same field is a retention window -- drop queued commands
more than `slack` frames stale. Neither use shortens command-to-execution
latency, so varying it in INI cannot fix the delay.

# Delay-path functions still needing C++

Generated from the call graph: two levels of callees from the scheduler, both
ceiling writers, the readiness gate, the send path and the frame ring, filtered
to what is unnamed, asm-only or claimed by a thunk row.

 bytes  addr       state       name
  1380  0x680980   UNNAMED     
   937  0x67EE40   UNNAMED     
   750  0x66C3B0   ASM         ?updateDisconnectStatus@DisconnectManager@@IAEXPAVConnection
   608  0x673200   ASM         ?addMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetComma
   581  0x661F10   UNNAMED     
   502  0x6624A0   UNNAMED     
   448  0x670A30   UNNAMED     
   433  0x67E3F0   UNNAMED     
   284  0x67E8C0   UNNAMED     
   272  0x67E760   UNNAMED     
   261  0x67EA30   UNNAMED     
   256  0x676890   UNNAMED     
   256  0x66A030   UNNAMED     
   255  0x6655C0   UNNAMED     
   251  0x67EC70   UNNAMED     
   251  0x67E620   UNNAMED     
   215  0x678AA0   UNNAMED     
   204  0x669B50   UNNAMED     
   187  0x67EB80   UNNAMED     
   187  0x66B2D0   ASM         ?sendKeepAlive@DisconnectManager@@IAEXPAVConnectionManager@@
   174  0x679730   UNNAMED     
   171  0x9D2AB0   UNNAMED     
   170  0x9F70E0   UNNAMED     
   169  0x82C920   UNNAMED     
   164  0x683830   UNNAMED     
   162  0x82E540   ASM         ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z
   156  0x6645B0   UNNAMED     
   153  0x6789E0   UNNAMED     
   152  0x678920   UNNAMED     
   152  0x678860   UNNAMED     
   152  0x6787A0   UNNAMED     
   150  0x6658F0   UNNAMED     
   130  0x679390   UNNAMED     
   130  0x679250   UNNAMED     
   126  0x669960   UNNAMED     
   121  0x669560   UNNAMED     
   114  0x678F10   UNNAMED     
   112  0x50EF20   UNNAMED     
   108  0x6794D0   UNNAMED     
   108  0x679440   UNNAMED     
   108  0x679300   UNNAMED     
   105  0x86AF90   UNNAMED     
   103  0x679650   UNNAMED     
    96  0x6688D0   UNNAMED     
    91  0x662270   UNNAMED     
    87  0x66BD10   THUNK-ONLY  ?processDisconnectVote@DisconnectManager@@IAEXPAVNetCommandM
    86  0x682E80   UNNAMED     
    86  0x679010   UNNAMED     
    86  0x678FA0   UNNAMED     
    86  0x678D40   UNNAMED     
    86  0x678CD0   UNNAMED     
    85  0x82E5F0   ASM         ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    82  0x6652B0   UNNAMED     
    75  0x675CE0   UNNAMED     
    75  0x675C50   UNNAMED     
    75  0x675A20   UNNAMED     
    75  0x6380F0   UNNAMED     
    75  0x638060   UNNAMED     
    74  0x9F6EE4   ASM         ??_L@YGXPAXIHP6EX0@Z1@Z
    74  0x6731A0   UNNAMED     
    70  0x66BFE0   UNNAMED     
    69  0x673840   UNNAMED     
    68  0x673740   UNNAMED     
    62  0x8543B0   UNNAMED     
    62  0x6832C0   UNNAMED     
    61  0x667B50   UNNAMED     
    61  0x50E5A0   UNNAMED     
    60  0x6651C0   UNNAMED     
    59  0x9F7E88   UNNAMED     
    58  0x0800C0   UNNAMED     

