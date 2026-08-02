// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString
{
};

class Object
{
};

class MemoryPool
{
};

class GameMessage
{
public:
    enum Type
    {
        Type_Thunk
    };

    __declspec(dllexport) static AsciiString getCommandTypeAsAsciiString(Type);
};

__declspec(naked) AsciiString GameMessage::getCommandTypeAsAsciiString(Type)
{
    __asm {
        _emit 0E9h
        _emit 0E0h
        _emit 0ABh
        _emit 004h
        _emit 000h
    }
}

class AI
{
public:
    __declspec(dllexport) static float getAdjustedVisionRangeForObject(const Object *, int);
};

__declspec(naked) float AI::getAdjustedVisionRangeForObject(const Object *, int)
{
    __asm {
        _emit 0E9h
        _emit 000h
        _emit 05Eh
        _emit 012h
        _emit 000h
    }
}

class W3DShaderManager
{
public:
    __declspec(dllexport) static void startRenderToTexture();
};

class W3DShaderManagerStartRenderToTextureShim
{
public:
    static void start();
};

void W3DShaderManager::startRenderToTexture()
{
    W3DShaderManagerStartRenderToTextureShim::start();
}

class ObjectDefectionHelper
{
public:
    __declspec(dllexport) static MemoryPool *getClassMemoryPool();
};

__declspec(naked) MemoryPool *ObjectDefectionHelper::getClassMemoryPool()
{
    __asm {
        _emit 0E9h
        _emit 0CDh
        _emit 077h
        _emit 066h
        _emit 000h
    }
}

class DX8Wrapper
{
public:
    __declspec(dllexport) static void Set_DX8_Texture_Stage_State(unsigned int, unsigned long, unsigned int);
};

__declspec(naked) void DX8Wrapper::Set_DX8_Texture_Stage_State(unsigned int, unsigned long, unsigned int)
{
    __asm {
        _emit 0E9h
        _emit 058h
        _emit 0F6h
        _emit 069h
        _emit 000h
    }
}
