// 031-earlysend — take a guest's commands to the wire the tick they exist.
//
// The candidate fix for the guest's input lag, and the arm the latency probe
// (030-netlatprobe) exists to measure. Retail drains the command list only from
// Network::update, which runs only on a logic tick -- 5 a second. So a guest
// command sits in TheCommandList for up to a whole 200 ms quantum before it even
// LEAVES the machine, and only then can the router bind it to a frame. The host
// pays nothing for this: it stamps and executes its own commands inside the same
// tick that wrapped them.
//
// This drains the list from the client half instead, which runs every engine
// tick (~33 ms). The hook sits immediately before the engine's own
// liteupdate(FALSE) at RVA 0x0006BA53, so anything queued here is flushed to the
// wire by the very next instruction of the retail path -- there is no second
// mechanism to add and no timer to tune.
//
// What it deliberately does NOT touch, because those are the ways this could
// change the game rather than fix it:
//   * the 5 Hz quantum (RVA 0x00682074). Game time per logic frame is the
//     compiled-in LOGICFRAMES_PER_SECOND, so raising the rate multiplies the
//     speed of the game. That is the naive trap, not the fix.
//   * the frame ceiling and its writers, and GameLogic's cadence. Commands only
//     arrive EARLIER; the router still executes them at 5 Hz, in the same order,
//     on the same frames.
//
// Why draining twice in one tick is safe: the pump removes and destroys every
// message it takes (RVA 0x00682941), so a logic tick that pumps again after this
// one finds the list empty. GameLogic::update runs its command dispatch and
// clears the list only when its phase argument is 1, so an interpolation tick
// can never see a half-drained list either.
//
// There is no loader and no CRT here: tools/cave.py drops this into a section
// appended to the retail image. Addresses are absolute: fixed-base 0x400000
// image, DllCharacteristics 0x0000, so no ASLR.

#define TheNetwork (*(void **)0x012F7714)

enum {
    NET_CONMGR = 0x08,   // TheNetwork -> ConnectionManager
    NET_STATUS = 0x0C    // 1 while a match is up; the retail pump's own gate
};

// Network::getCommandsFromCommandList. Reached by absolute address rather than
// through a vtable because it is not virtual. MSVC 7.1 rejects __thiscall, so
// the engine's thiscall methods are declared __fastcall with an unused edx --
// same registers, same callee-cleans rule, the same ABI at this arity.
typedef void(__fastcall *Pump)(void *self, void *edx);
#define c_pump ((Pump)0x00A828D0)

static const unsigned char *at(const void *base, int offset) {
    return (const unsigned char *)base + offset;
}
static int i32(const void *base, int offset) { return *(const int *)at(base, offset); }
static void *ptr(const void *base, int offset) { return *(void **)at(base, offset); }

// Reached from the shim tools/cave.py generates, which has already saved every
// register and flag. Its argument is the ecx the hooked code was running with,
// which here is whatever the previous call left behind -- the instruction this
// detour displaced is the one that loads TheNetwork -- so it is ignored and the
// global is read directly.
extern "C" __declspec(dllexport) void __cdecl earlysend(void *ecx) {
    (void)ecx;
    void *net = TheNetwork;
    if (net == 0) {
        return;
    }
    // The same three conditions the retail pump is guarded by. Outside a match
    // there is no command list worth draining, and the loading screens drive
    // this path themselves.
    if (i32(net, NET_STATUS) != 1) {
        return;
    }
    if (ptr(net, NET_CONMGR) == 0) {
        return;
    }
    c_pump(net, 0);
}
