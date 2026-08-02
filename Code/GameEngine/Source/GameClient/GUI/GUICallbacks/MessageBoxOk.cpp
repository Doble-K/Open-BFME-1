// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GameWindow;
class UnicodeString {};

GameWindow *MessageBoxOk(UnicodeString, UnicodeString, void (*)(void));

class MessageBoxOkShim
{
public:
    static GameWindow *run(UnicodeString title, UnicodeString body, void (*cb)(void));
};

GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body, void (*cb)(void))
{
    return MessageBoxOkShim::run(title, body, cb);
}
