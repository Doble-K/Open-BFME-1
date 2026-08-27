// 030-netlatprobe — where a multiplayer command's latency actually goes.
//
// Five detours, one translation unit, one JSONL line per event. The question it
// exists to answer is why a guest feels input lag a host does not. The engine
// paces the whole match at 5 Hz (200 ms per logic frame) and a guest's input
// pump runs only on those ticks, so a guest command waits for the next tick
// merely to LEAVE the machine and is then bound by the router to a later frame
// than the host's would be. That wrap delay is the quantity a send-side fix
// shrinks, so it is the quantity this measures — on retail first, so the defect
// has to reproduce before anything is credited with removing it.
//
// Every line carries the clock, the seat, the logic frame and the router's
// published frame ceiling, so every headline metric is recomputable offline
// from one seat's file:
//   * wrap delay   t(send) - t(input), per seat, in order — what the fix moves
//   * end to end   t(frame) - t(input)
//   * game speed   the slope of the frame field against the clock, which is
//                  what must NOT move: 5 logic frames per wall second, both
//                  arms, or the fix changed the pace of the game
//   * backlog      ceiling - frame. The one quantity reading the binary could
//                  not settle: whether a loaded guest ALSO falls behind the
//                  ceiling, which would be a second delay term no send-side
//                  change can touch. Two reads, so it rides every line.
//
// The clock is QueryPerformanceCounter rather than timeGetTime: its resolution
// needs no assumption about whether timeBeginPeriod is in effect under wine.
// It is 64-bit and this code has no 64-bit arithmetic, so both halves are
// emitted raw and the division happens offline.
//
// There is no loader and no CRT here: tools/cave.py drops this into a section
// appended to the retail image and jumps into it from mid-function. Nothing may
// need a static initializer, an exception, or a runtime-library helper — see
// modbuild.py's undefined-externals check, which fails the build on one.
// Addresses are absolute: fixed-base 0x400000 image, DllCharacteristics 0x0000.

// ---- the game's own CRT, called through its import table ------------------
struct FILE;

typedef FILE *(__cdecl *FOpen)(const char *, const char *);
typedef int(__cdecl *FPrintf)(FILE *, const char *, ...);
typedef int(__cdecl *FFlush)(FILE *);
typedef char *(__cdecl *GetEnv)(const char *);
typedef int(__cdecl *SPrintf)(char *, const char *, ...);
// QueryPerformance* are __stdcall; declaring them __cdecl would leave the
// argument on the stack at every call and walk the frame off a cliff.
typedef int(__stdcall *QueryCounter)(unsigned *);

#define c_fopen (*(FOpen *)0x013593BC)
#define c_fprintf (*(FPrintf *)0x013593C0)
#define c_fflush (*(FFlush *)0x013593A8)
#define c_getenv (*(GetEnv *)0x013593FC)
#define c_sprintf (*(SPrintf *)0x0135948C)
#define c_qpc (*(QueryCounter *)0x01358EB4)
#define c_qpf (*(QueryCounter *)0x01358EB8)

// ---- the engine's globals and struct layouts -----------------------------
#define TheGameLogic (*(void **)0x012F0898)
#define TheNetwork (*(void **)0x012F7714)

enum {
    GL_FRAME = 0x3C,       // current logic frame
    GL_DESYNC = 0x6C,      // non-zero once this machine has seen a desync

    NET_CONMGR = 0x08,     // TheNetwork -> ConnectionManager
    NET_STATUS = 0x0C,     // 1 while a match is up; the pump's own gate
    NET_STALLS = 0x2C,     // cumulative client stall count, only ever incremented

    CM_LOCALSLOT = 0x12028,
    CM_ROUTERSLOT = 0x1202C,
    CM_CEILING = 0x1205C,  // the frame the router published; clients clamp to it

    MSG_OWNER = 0x0C,      // GameMessage -> the list it was appended to
    MSG_TYPE = 0x10,

    CMD_EXEC = 0x08,       // NetCommandMsg: execution frame, -1 until bound
    CMD_PLAYER = 0x0C,
    CMD_ID = 0x10,         // UnsignedShort
    CMD_TYPE = 0x14,       // 4 = a game command, 3 = the per-tick frame info

    REF_MSG = 0x00,        // NetCommandRef -> NetCommandMsg
    REF_RELAY = 0x0C,      // the one-byte relay mask

    // The pump's own filter (cmp 0x3e8/jle, cmp 0x7cf/jge at RVA 0x682904):
    // the game messages that reach the wire. Anything outside it is mouse
    // movement and camera noise, which would bury the file it shares.
    CMD_LOW = 0x3E9,
    CMD_HIGH = 0x7CE
};

static const unsigned char *at(const void *base, int offset) {
    return (const unsigned char *)base + offset;
}
static int i32(const void *base, int offset) { return *(const int *)at(base, offset); }
static unsigned u32(const void *base, int offset) { return *(const unsigned *)at(base, offset); }
static unsigned u16(const void *base, int offset) {
    return *(const unsigned short *)at(base, offset);
}
static unsigned char u8(const void *base, int offset) { return *at(base, offset); }
static void *ptr(const void *base, int offset) { return *(void **)at(base, offset); }

// ---- where the records land ----------------------------------------------
static const char PATH_ENV[] = "BFME_LAT_PATH";
static const char PATH_FMT[] = "%s\\My Battle for Middle-earth Files\\NetLat.jsonl";

// Held open for the life of the process, unlike the game-result feature's
// open-per-record: this writes tens of lines a second and an fopen/fclose pair
// each time would be an instrument heavy enough to move what it measures. Each
// line is still flushed, so a crash costs at most the last line.
static FILE *s_file;
static int s_opened;   // the open was attempted; do not retry it every event
static char s_path[512];
static unsigned s_qpc[2];

// A failure here is deliberately silent in the payload and loud downstream:
// there is no console to report to from inside a code cave, and the analysis
// refuses a file with no events rather than reporting zero latency.
static FILE *file() {
    if (s_opened == 0) {
        s_opened = 1;
        const char *path = c_getenv(PATH_ENV);
        if (path == 0) {
            c_sprintf(s_path, PATH_FMT, c_getenv("APPDATA"));
            path = s_path;
        }
        s_file = c_fopen(path, "a");
        if (s_file != 0) {
            unsigned freq[2];
            freq[0] = 0;
            freq[1] = 0;
            c_qpf(freq);
            // The clock's own scale, once, so a reader never has to assume it.
            c_fprintf(s_file, "{\"ev\":\"open\",\"qfreqlo\":%u,\"qfreqhi\":%u}\n",
                      freq[0], freq[1]);
        }
    }
    return s_file;
}

// Only in a match. Every hook here fires in the shell too -- appendMessage runs
// for every menu click -- and a measurement of the shell is noise in the file
// the match's numbers come out of.
static void *live_conmgr() {
    void *net = TheNetwork;
    if (net == 0) {
        return 0;
    }
    if (i32(net, NET_STATUS) != 1) {
        return 0;
    }
    return ptr(net, NET_CONMGR);
}

// The half of every line that does not depend on which hook wrote it. The seat
// and the router flag ride each line rather than being written once at start,
// so a file that lost its head is still attributable, and so a slot that
// changes mid-capture cannot be silently mis-attributed to the old seat.
static void head(FILE *out, void *cm, const char *ev) {
    s_qpc[0] = 0;
    s_qpc[1] = 0;
    c_qpc(s_qpc);
    void *logic = TheGameLogic;
    int frame = logic != 0 ? i32(logic, GL_FRAME) : -1;
    int local = i32(cm, CM_LOCALSLOT);
    c_fprintf(out,
              "{\"ev\":\"%s\",\"qlo\":%u,\"qhi\":%u,\"f\":%d,\"c\":%d,"
              "\"slot\":%d,\"router\":%d",
              ev, s_qpc[0], s_qpc[1], frame, i32(cm, CM_CEILING),
              local, local == i32(cm, CM_ROUTERSLOT));
}

static void end(FILE *out) {
    c_fprintf(out, "}\n");
    c_fflush(out);
}

// ---- the detour entry points ---------------------------------------------
// Each is reached from the shim tools/cave.py generates, which has saved every
// register and flag. The second argument is the hooked function's own first
// argument, lifted off its stack frame by the shim: a thiscall's `this` arrives
// in ecx but everything it was called WITH is on the stack.

// GameMessageList::appendMessage(list, msg) — a command entering a message
// list. The body is shared by TheMessageStream, TheCommandList and the raw
// GameMessageList, so the list itself is emitted rather than filtered on: which
// one a command lands in, and when, is exactly the pipeline being measured.
extern "C" __declspec(dllexport) void __cdecl netlat_input(void *list, void *msg) {
    // Ordered by how much each test rejects, cheapest first, because this is
    // the hottest hook in the build: appendMessage runs for every menu click
    // and every mouse movement, thousands of times a second, all through
    // startup and loading. The match test is one load and one compare and
    // rejects every one of those, so it goes first.
    void *cm = live_conmgr();
    if (cm == 0) {
        return;
    }
    if (msg == 0) {
        return;
    }
    unsigned type = u32(msg, MSG_TYPE);
    if (type < CMD_LOW || type > CMD_HIGH) {
        return;
    }
    FILE *out = file();
    if (out == 0) {
        return;
    }
    head(out, cm, "input");
    // `msg` is the identity: one GameMessage is appended to TheMessageStream
    // and then, once the translators have run, to TheCommandList, and it is the
    // same object both times. `owner` is the list it was in BEFORE this append
    // (appendMessage writes the new one after the point this rides), so the two
    // together are the whole path a command takes before anything sends it.
    c_fprintf(out, ",\"type\":%u,\"msg\":%u,\"list\":%u,\"owner\":%u", type,
              (unsigned)msg, (unsigned)list, u32(msg, MSG_OWNER));
    end(out);
}

// ConnectionManager::sendLocalCommand(cm, msg) — the command leaving this
// machine. t(send) - t(input) is the wrap delay, and it is the placebo killer:
// it is produced by the exact code path a send-side fix changes, so a fix that
// does nothing cannot move it.
extern "C" __declspec(dllexport) void __cdecl netlat_send(void *ecx, void *msg) {
    (void)ecx;
    if (msg == 0) {
        return;
    }
    void *cm = live_conmgr();
    if (cm == 0) {
        return;
    }
    FILE *out = file();
    if (out == 0) {
        return;
    }
    head(out, cm, "send");
    // Type 4 is a game command and type 3 the per-tick frame info every client
    // sends; both are emitted so the join can filter to 4 and the cadence of 3
    // still shows the tick rate the machine is really running at.
    c_fprintf(out, ",\"type\":%u,\"cmd\":%u,\"player\":%u,\"exec\":%d",
              u32(msg, CMD_TYPE), u16(msg, CMD_ID), u32(msg, CMD_PLAYER),
              i32(msg, CMD_EXEC));
    end(out);
}

// ConnectionManager::relayCommand(cm, ref) — the router binding an arriving
// command to a frame. Runs on the router only. `exec` is read before the bind,
// so -1 here is a command that arrived unstamped and is about to be pinned to
// whatever frame the router is on: the moment a guest's latency is decided.
extern "C" __declspec(dllexport) void __cdecl netlat_relay(void *ecx, void *ref) {
    (void)ecx;
    if (ref == 0) {
        return;
    }
    void *msg = ptr(ref, REF_MSG);
    if (msg == 0) {
        return;
    }
    void *cm = live_conmgr();
    if (cm == 0) {
        return;
    }
    FILE *out = file();
    if (out == 0) {
        return;
    }
    head(out, cm, "relay");
    c_fprintf(out, ",\"type\":%u,\"cmd\":%u,\"player\":%u,\"exec\":%d,\"mask\":%u",
              u32(msg, CMD_TYPE), u16(msg, CMD_ID), u32(msg, CMD_PLAYER),
              i32(msg, CMD_EXEC), u8(ref, REF_RELAY));
    end(out);
}

// Network::relayCommandsToCommandList(net, frame) — once per logic frame, just
// before the frame runs. This is the per-frame heartbeat every rate is measured
// from: the frame field's slope against the clock is the game's speed, and it
// is what a latency fix must leave untouched.
extern "C" __declspec(dllexport) void __cdecl netlat_frame(void *ecx, void *frame) {
    void *cm = live_conmgr();
    if (cm == 0) {
        return;
    }
    FILE *out = file();
    if (out == 0) {
        return;
    }
    head(out, cm, "frame");
    void *logic = TheGameLogic;
    // The desync flag is the correctness gate. The obvious observables are the
    // wrong shape: the router's overrun counter zeroes itself on every clean
    // quantum, so sampling it at exit reads 0 almost always.
    c_fprintf(out, ",\"exec\":%d,\"desync\":%u,\"stalls\":%u",
              (int)(unsigned)frame,
              logic != 0 ? u8(logic, GL_DESYNC) : 0,
              ecx != 0 ? u32(ecx, NET_STALLS) : 0);
    end(out);
}

// ConnectionManager::sendFrameInfo(cm) — the router publishing the ceiling that
// every client clamps to. Router only, once per 200 ms quantum: the cadence
// the whole match is paced by.
extern "C" __declspec(dllexport) void __cdecl netlat_ceiling(void *ecx) {
    (void)ecx;
    void *cm = live_conmgr();
    if (cm == 0) {
        return;
    }
    FILE *out = file();
    if (out == 0) {
        return;
    }
    head(out, cm, "ceiling");
    end(out);
}
