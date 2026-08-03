// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class GameSpyPeerMessageQueueInterface
{
public:
	static GameSpyPeerMessageQueueInterface * __cdecl createNewMessageQueue();
};

// ?createNewMessageQueue@GameSpyPeerMessageQueueInterface@@SAPAV1@XZ
__declspec(naked) GameSpyPeerMessageQueueInterface * __cdecl GameSpyPeerMessageQueueInterface::createNewMessageQueue()
{
	__asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xfb
        __emit 0x29
        __emit 0x04
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x6a
        __emit 0x78
        __emit 0xe8
        __emit 0xf3
        __emit 0x38
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x04
        __emit 0x24
        __emit 0x85
        __emit 0xc0
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x16
        __emit 0x8b
        __emit 0xc8
        __emit 0xe8
        __emit 0x63
        __emit 0xbb
        __emit 0x9b
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
	}
}
