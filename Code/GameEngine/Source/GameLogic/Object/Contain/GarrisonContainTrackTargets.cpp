// cl: /DNDEBUG /MD /EHsc

struct Coord3D
{
    float x;
    float y;
    float z;
};

class Object;

enum ObjectID
{
    INVALID_OBJECT_ID = 0
};

class AIUpdateInterface
{
public:
    Object *getCurrentVictim() const;
    const Coord3D *getCurrentVictimPos() const;
};

class BodyStateInterface
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual int getDamageState() const;
};

class Object
{
public:
    const Coord3D *getPosition() const { return &m_position; }
    ObjectID getID() const { return m_id; }
    AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
    BodyStateInterface *getBody() const { return m_body; }

private:
    unsigned char m_pad00[0x38];
    Coord3D m_position;
    unsigned char m_pad44[0x30];
    ObjectID m_id;
    unsigned char m_pad78[0x188];
    BodyStateInterface *m_body;
    AIUpdateInterface *m_ai;
};

struct ContainedNode
{
    ContainedNode *next;
    ContainedNode *previous;
    Object *object;
};

static float calcDistanceSquared(const Coord3D &first, const Coord3D &second)
{
    const float dx = first.x - second.x;
    const float dy = first.y - second.y;
    const float dz = first.z - second.z;
    return dx * dx + dy * dy + dz * dz;
}

class GarrisonContain
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual int getObjectGarrisonPointIndex(ObjectID objectID);

protected:
    void trackTargets();
    int findClosestFreeGarrisonPointIndex(int conditionIndex,
                                          const Coord3D *targetPosition);
    void removeObjectFromGarrisonPoint(Object *object, int index);
    void putObjectAtGarrisonPoint(Object *object, ObjectID targetID,
                                  int conditionIndex, int index);

private:
    unsigned char m_pad04[4];
    Object *m_object;
    unsigned char m_pad0c[0x2c];
    ContainedNode *m_containedItems;
    unsigned char m_pad3c[0x3c0];
    Coord3D m_garrisonPoints[3][40];
};

// ?trackTargets@GarrisonContain@@IAEXXZ
void GarrisonContain::trackTargets()
{
    int conditionIndex = -1;
    switch (m_object->getBody()->getDamageState())
    {
        case 0: conditionIndex = 0; break;
        case 1: conditionIndex = 1; break;
        case 2: conditionIndex = 2; break;
        case 3: conditionIndex = 2; break;
    }

    for (ContainedNode *iterator = m_containedItems->next;
         iterator != m_containedItems;
         iterator = iterator->next)
    {
        Object *const object = iterator->object;
        const int currentIndex = getObjectGarrisonPointIndex(object->getID());
        if (currentIndex == -1)
            continue;

        AIUpdateInterface *const ai = object->getAIUpdateInterface();
        if (!ai)
            continue;

        Object *const victim = ai->getCurrentVictim();
        const Coord3D *victimPosition = ai->getCurrentVictimPos();
        if (!victim && !victimPosition)
            continue;
        if (victim)
            victimPosition = victim->getPosition();

        const Coord3D *const objectPosition = object->getPosition();
        const int newIndex = findClosestFreeGarrisonPointIndex(
            conditionIndex, victimPosition);
        if (newIndex == -1)
            continue;

        const float currentDistance = calcDistanceSquared(
            *victimPosition, *objectPosition);
        const float newDistance = calcDistanceSquared(
            *victimPosition, m_garrisonPoints[conditionIndex][newIndex]);
        if (newDistance < currentDistance)
        {
            removeObjectFromGarrisonPoint(object, currentIndex);
            putObjectAtGarrisonPoint(object,
                                     victim ? victim->getID() : INVALID_OBJECT_ID,
                                     conditionIndex, newIndex);
        }
    }
}
