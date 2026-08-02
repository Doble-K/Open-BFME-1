// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

void PopulateLobbyPlayerListbox();

class PopulateLobbyPlayerListboxShim
{
public:
    static void run();
};

void PopulateLobbyPlayerListbox()
{
    PopulateLobbyPlayerListboxShim::run();
}
