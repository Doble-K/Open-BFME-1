class Object;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

struct ThingTemplatePowerABI
{
	void *vtable;
	Overridable *nextOverride;
	char pad[0x410];
	int energyProduction;
};

class Energy
{
public:
	void objectEnteringInfluence(Object *object);
	void objectLeavingInfluence(Object *object);
};

class Player
{
	public:
	char pad[0xA4];
	Energy energy;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Object
{
private:
	char pad0[4];
	ThingTemplatePowerABI *thingTemplate;
	char pad8[0x19C];
	void *disabledStates;
	char pad1A8[0x94];
	Team *team;

public:
	void friend_adjustPowerForPlayer(bool incoming);
};

void Object::friend_adjustPowerForPlayer(bool incoming)
{
	if (disabledStates != 0) {
		ThingTemplatePowerABI *powerTemplate = thingTemplate;
		if (powerTemplate != 0 && powerTemplate->nextOverride != 0) {
			powerTemplate = reinterpret_cast<ThingTemplatePowerABI *>(
				const_cast<Overridable *>(powerTemplate->nextOverride->getFinalOverride()));
		}
		if (powerTemplate->energyProduction > 0)
			return;
	}

	Player *player = team != 0 ? team->getControllingPlayer() : 0;
	if (player == 0)
		return;

	Energy *energy = &player->energy;
	if (energy == 0)
		return;

	if (incoming)
		energy->objectEnteringInfluence(this);
	else
		energy->objectLeavingInfluence(this);
}
