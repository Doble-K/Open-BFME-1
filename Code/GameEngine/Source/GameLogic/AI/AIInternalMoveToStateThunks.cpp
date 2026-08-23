enum StateReturnType
{
};

enum StateExitType
{
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType);
	virtual StateReturnType update();
};

class AIMoveOutOfTheWayState
{
public:
	virtual StateReturnType update();
};

class AIInternalMoveToStateOnEnterShim
{
public:
	StateReturnType onEnter();
};

class AIInternalMoveToStateUpdateShim
{
public:
	StateReturnType update();
};

class AIMoveOutOfTheWayStateUpdateShim
{
public:
	StateReturnType update();
};

StateReturnType AIInternalMoveToState::onEnter()
{
	return ((AIInternalMoveToStateOnEnterShim *)this)->onEnter();
}

StateReturnType AIInternalMoveToState::update()
{
	return ((AIInternalMoveToStateUpdateShim *)this)->update();
}

StateReturnType AIMoveOutOfTheWayState::update()
{
	return ((AIMoveOutOfTheWayStateUpdateShim *)this)->update();
}
