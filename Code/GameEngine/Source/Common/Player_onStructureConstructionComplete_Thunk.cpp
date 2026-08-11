// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of construction completion dispatch.

class Object;

class ScriptEngine
{
public:
	void notifyOfObjectCreationOrDestruction();
};

class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *);
	void addObjectToPathfindMap(Object *);
};

class AI
{
private:
	char Pad[0x0C];

public:
	Pathfinder *PathfinderInstance;
};

class AIPlayer
{
public:
	virtual void Slot0();
	virtual void Slot1();
	virtual void Slot2();
	virtual void Slot3();
	virtual void Slot4();
	virtual void Slot5();
	virtual void Slot6();
	virtual void Slot7();
	virtual void onStructureProduced(Object *, Object *);
};

class StructureCompletionInterface
{
public:
	virtual void Slot0();
	virtual void Slot1();
	virtual void Slot2();
	virtual void onConstructionComplete(Object *);
};

class Object
{
public:
	void friend_adjustPowerForPlayer(bool);
	StructureCompletionInterface *getStructureCompletionInterface();
};

class ControlBar
{
private:
	char Pad[0x24];

public:
	bool UIDirty;
};

class Player
{
public:
	void onStructureConstructionComplete(Object *, Object *, bool);

private:
	char Pad[0x220];
	AIPlayer *PlayerAI;
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;
extern ControlBar *TheControlBar;

void Player::onStructureConstructionComplete(Object *builder, Object *structure, bool)
{
	TheScriptEngine->notifyOfObjectCreationOrDestruction();
	TheAI->PathfinderInstance->removeObjectFromPathfindMap(structure);
	TheAI->PathfinderInstance->addObjectToPathfindMap(structure);
	structure->friend_adjustPowerForPlayer(true);

	if (PlayerAI != 0) {
		PlayerAI->onStructureProduced(builder, structure);
	}

	if (TheControlBar != 0) {
		TheControlBar->UIDirty = true;
	}

	if (structure->getStructureCompletionInterface() != 0) {
		structure->getStructureCompletionInterface()->onConstructionComplete(builder);
	}
}
