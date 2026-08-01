// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

enum GSOverlayType
{
    GSOverlayType_Thunk
};

__declspec(naked) void GameSpyOpenOverlay(GSOverlayType)
{
    __asm {
        _emit 0E9h
        _emit 07Ah
        _emit 0C5h
        _emit 05Fh
        _emit 000h
    }
}
