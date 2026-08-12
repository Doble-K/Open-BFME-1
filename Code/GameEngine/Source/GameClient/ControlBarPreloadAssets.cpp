// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

enum TimeOfDay { TIME_OF_DAY_INVALID = 0 };

class ControlBarSchemeManager
{
public:
	void bfme_preloadAssets_impl();
};

class ControlBar
{
public:
    void bfme_preloadAssets_wrapper();

private:
	char m_pad000[0x30];
	ControlBarSchemeManager *m_controlBarSchemeManager;
};

void ControlBar::bfme_preloadAssets_wrapper()
{
	if (m_controlBarSchemeManager)
		m_controlBarSchemeManager->bfme_preloadAssets_impl();
}
