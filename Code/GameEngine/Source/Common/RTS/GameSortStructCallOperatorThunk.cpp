// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class GameSpyStagingRoom;

class GameSortStruct
{
public:
    bool operator()(GameSpyStagingRoom *, GameSpyStagingRoom *);
};

class GameSortStructCallOperatorShim
{
public:
    bool compare(GameSpyStagingRoom *a, GameSpyStagingRoom *b);
};

bool GameSortStruct::operator()(GameSpyStagingRoom *a, GameSpyStagingRoom *b)
{
    return ((GameSortStructCallOperatorShim *)this)->compare(a, b);
}
