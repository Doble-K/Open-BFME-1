// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Object;

class Player
{
public:
	void iterateObjects(void (*)(Object *, void *), void *) const;
};

class PlayerIterateObjectsShim
{
public:
	void iterateObjects(void (*)(Object *, void *), void *) const;
};

void Player::iterateObjects(void (*cb)(Object *, void *), void *userData) const
{
	((PlayerIterateObjectsShim const *)this)->iterateObjects(cb, userData);
}
