// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class GameSpyStagingRoom;

class GameSortStruct
{
public:
    bool operator()(GameSpyStagingRoom *, GameSpyStagingRoom *);
};

__declspec(naked) bool GameSortStruct::operator()(GameSpyStagingRoom *, GameSpyStagingRoom *)
{
    __asm {
        _emit 0E9h
        _emit 0F4h
        _emit 0D5h
        _emit 050h
        _emit 000h
    }
}
