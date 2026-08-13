struct VirtualSlot5CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void invoke(int value);

    void invokeOne();
};

void VirtualSlot5CallThunk::invokeOne()
{
    invoke(1);
}

struct VirtualSlot8CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void invoke(int value);

    void invokeZero();
    void invokeZeroAlternate();
    void invokeZeroThird();
    void invokeOne();
    void invokeZeroFourth();
    void invokeZeroFifth();
    void invokeZeroSixth();
    void invokeZeroSeventh();
};

void VirtualSlot8CallThunk::invokeZero()
{
    invoke(0);
}

void VirtualSlot8CallThunk::invokeZeroAlternate()
{
    invoke(0);
}

void VirtualSlot8CallThunk::invokeZeroThird()
{
    invoke(0);
}

void VirtualSlot8CallThunk::invokeOne()
{
    invoke(1);
}

void VirtualSlot8CallThunk::invokeZeroFourth()
{
    invoke(0);
}

void VirtualSlot8CallThunk::invokeZeroFifth()
{
    invoke(0);
}

void VirtualSlot8CallThunk::invokeZeroSixth()
{
    invoke(0);
}

void VirtualSlot8CallThunk::invokeZeroSeventh()
{
    invoke(0);
}

struct VirtualSlot2CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke();

    void invokeIgnoringArgument(int unused);
};

void VirtualSlot2CallThunk::invokeIgnoringArgument(int)
{
    invoke();
}

struct VirtualSlot2IntCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke(int value);

    void invokeSix();
    void invokeSixAlternate();
};

void VirtualSlot2IntCallThunk::invokeSix()
{
    invoke(6);
}

void VirtualSlot2IntCallThunk::invokeSixAlternate()
{
    invoke(6);
}

struct VirtualSlot9CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void invoke(int value);

    void invokeOne();
};

void VirtualSlot9CallThunk::invokeOne()
{
    invoke(1);
}

struct VirtualSlot11CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void invoke(int first, int second);

    void invokeZeroOne();
};

void VirtualSlot11CallThunk::invokeZeroOne()
{
    invoke(0, 1);
}

struct VirtualSlot2MemberCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke(int value);

    unsigned long padding[4];
    int value;

    void invokeMember();
    void invokeMemberAlternate();
    void invokeMemberThird();
    void invokeMemberFourth();
    void invokeMemberFifth();
    void invokeMemberSixth();
    void invokeMemberSeventh();
    void invokeMemberEighth();
};

void VirtualSlot2MemberCallThunk::invokeMember()
{
    invoke(value);
}

void VirtualSlot2MemberCallThunk::invokeMemberAlternate()
{
    invoke(value);
}

void VirtualSlot2MemberCallThunk::invokeMemberThird()
{
    invoke(value);
}

void VirtualSlot2MemberCallThunk::invokeMemberFourth()
{
    invoke(value);
}

void VirtualSlot2MemberCallThunk::invokeMemberFifth()
{
    invoke(value);
}

void VirtualSlot2MemberCallThunk::invokeMemberSixth()
{
    invoke(value);
}

void VirtualSlot2MemberCallThunk::invokeMemberSeventh()
{
    invoke(value);
}

void VirtualSlot2MemberCallThunk::invokeMemberEighth()
{
    invoke(value);
}

struct VirtualSlot10IncrementedMemberCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void invoke(int value);

    unsigned long padding[17];
    int value;

    void invokeNext();
};

void VirtualSlot10IncrementedMemberCallThunk::invokeNext()
{
    invoke(value + 1);
}

struct EmbeddedVirtualSlot1Thunk
{
    virtual void slot0();
    virtual void invoke();

    unsigned long padding[2];
};

struct EmbeddedVirtualSlot1CallFacet
{
    unsigned long value;

    void invokeIgnoringArgument(int unused);
    void invokeIgnoringArgumentAlternate(int unused);
};

struct EmbeddedVirtualSlot1CallOwner : EmbeddedVirtualSlot1Thunk, EmbeddedVirtualSlot1CallFacet
{
};

void EmbeddedVirtualSlot1CallFacet::invokeIgnoringArgument(int)
{
    EmbeddedVirtualSlot1Thunk *owner = reinterpret_cast<EmbeddedVirtualSlot1Thunk *>(
        reinterpret_cast<unsigned char *>(this) - sizeof(EmbeddedVirtualSlot1Thunk));
    owner->invoke();
}

void EmbeddedVirtualSlot1CallFacet::invokeIgnoringArgumentAlternate(int)
{
    EmbeddedVirtualSlot1Thunk *owner = reinterpret_cast<EmbeddedVirtualSlot1Thunk *>(
        reinterpret_cast<unsigned char *>(this) - sizeof(EmbeddedVirtualSlot1Thunk));
    owner->invoke();
}

struct EmbeddedVirtualSlot2Thunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke();
};

struct EmbeddedVirtualSlot2CallOwner
{
    unsigned long padding[5];
    EmbeddedVirtualSlot2Thunk embedded;

    void invokeIgnoringArgument(int unused);
};

void EmbeddedVirtualSlot2CallOwner::invokeIgnoringArgument(int)
{
    embedded.invoke();
}

struct SecondaryBaseVirtualSlot11Primary
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void invoke();

    unsigned long padding[7];
};

struct SecondaryBaseVirtualSlot11Facet
{
    unsigned long value;

    void invokeIgnoringArgument(int unused);
};

struct SecondaryBaseVirtualSlot11Owner : SecondaryBaseVirtualSlot11Primary,
                                         SecondaryBaseVirtualSlot11Facet
{
};

void SecondaryBaseVirtualSlot11Facet::invokeIgnoringArgument(int)
{
    SecondaryBaseVirtualSlot11Primary *owner = reinterpret_cast<SecondaryBaseVirtualSlot11Primary *>(
        reinterpret_cast<unsigned char *>(this) - sizeof(SecondaryBaseVirtualSlot11Primary));
    owner->invoke();
}

struct VirtualSlot2ArgumentThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke();
};

struct VirtualSlot2ArgumentCallOwner
{
    void invokeArgument(VirtualSlot2ArgumentThunk *target);
};

void VirtualSlot2ArgumentCallOwner::invokeArgument(VirtualSlot2ArgumentThunk *target)
{
    target->invoke();
}

extern void *TheTerrainLogic;

struct VirtualSlot4GlobalCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void invoke(void *value);

    void invokeTerrainLogic();
};

void VirtualSlot4GlobalCallThunk::invokeTerrainLogic()
{
    invoke(TheTerrainLogic);
}

struct VirtualSlot11SecondArgumentCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void invoke(int value);

    void invokeSecond(int unused, int value);
    void invokeSecondAlternate(int unused, int value);
    void invokeSecondThird(int unused, int value);
    void invokeSecondFourth(int unused, int value);
};

void VirtualSlot11SecondArgumentCallThunk::invokeSecond(int, int value)
{
    invoke(value);
}

void VirtualSlot11SecondArgumentCallThunk::invokeSecondAlternate(int, int value)
{
    invoke(value);
}

void VirtualSlot11SecondArgumentCallThunk::invokeSecondThird(int, int value)
{
    invoke(value);
}

void VirtualSlot11SecondArgumentCallThunk::invokeSecondFourth(int, int value)
{
    invoke(value);
}

struct ProducedValue
{
    int value;
};

extern int __stdcall produceStoredValue(int value);

ProducedValue &__stdcall storeProducedValue(ProducedValue &result, int value)
{
    result.value = produceStoredValue(value);
    return result;
}

struct VirtualSlot3FlagThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void invoke();

    unsigned char padding[0x46];
    bool invoked;

    void invokeAndSet();
};

void VirtualSlot3FlagThunk::invokeAndSet()
{
    invoke();
    invoked = true;
}

struct VirtualSlot21FirstArgumentThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void invoke(int value);

    void invokeFirst(int value, int unused1, int unused2, int unused3, int unused4, int unused5);
};

void VirtualSlot21FirstArgumentThunk::invokeFirst(int value, int, int, int, int, int)
{
    invoke(value);
}

struct VirtualSlot25EmbeddedArgumentsThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void invoke(void *first, void *second);

    unsigned char padding[0x4C - sizeof(void *)];
    int second;

    void invokeEmbedded();
};

void VirtualSlot25EmbeddedArgumentsThunk::invokeEmbedded()
{
    invoke(reinterpret_cast<unsigned char *>(this) + 0x38, &second);
}

struct Offset24IntegerSetterThunk
{
    unsigned char padding[0x18];
    int value;

    void setValue(int newValue);
};

void Offset24IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset68BooleanSetterThunk
{
    unsigned char padding[0x44];
    bool value;

    void setValue(bool newValue);
};

void Offset68BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct Offset64IntegerSetterThunk
{
    unsigned char padding[0x40];
    int value;

    void setValue(int newValue);
};

void Offset64IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset117BooleanSetterThunk
{
    unsigned char padding[0x75];
    bool value;

    void setValue(bool newValue);
};

void Offset117BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct Offset108IntegerSetterThunk
{
    unsigned char padding[0x6C];
    int value;

    void setValue(int newValue);
};

void Offset108IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset118FlagSetterThunk
{
    unsigned char padding[0x76];
    bool value;

    void set();
};

void Offset118FlagSetterThunk::set()
{
    value = true;
}

struct Offset96IntegerPairSetterThunk
{
    unsigned char padding[0x60];
    int first;
    int second;

    void setValues(int firstValue, int secondValue);
};

void Offset96IntegerPairSetterThunk::setValues(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
}

struct SparseIntegerResetThunk
{
    unsigned char padding[0x58];
    int first;
    int second;
    unsigned char gap[8];
    int third;

    void reset();
};

void SparseIntegerResetThunk::reset()
{
    first = 0;
    second = 0;
    third = 0;
}

struct Offset116BooleanSetterThunk
{
    unsigned char padding[0x74];
    bool value;

    void setValue(bool newValue);
};

void Offset116BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct Offset112IntegerSetterThunk
{
    unsigned char padding[0x70];
    int value;

    void setValue(int newValue);
};

void Offset112IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset132BooleanGetterThunk
{
    unsigned char padding[0x84];
    bool value;

    bool get() const;
};

bool Offset132BooleanGetterThunk::get() const
{
    return value;
}

struct Offset136IntegerGetterThunk
{
    unsigned char padding[0x88];
    int value;

    int get() const;
};

int Offset136IntegerGetterThunk::get() const
{
    return value;
}

struct Offset140IntegerPairSetterThunk
{
    unsigned char padding[0x8c];
    int first;
    int second;

    void setValues(int firstValue, int secondValue);
};

void Offset140IntegerPairSetterThunk::setValues(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
}

struct Offset140IntegerPairValidityThunk
{
    unsigned char padding[0x8c];
    int first;
    int second;

    bool isValid() const;
};

bool Offset140IntegerPairValidityThunk::isValid() const
{
    return first != -1 && second != -1;
}

struct IntegerTripleCopyValue
{
    int first;
    int second;
    int third;
};

struct Offset140IntegerTripleCopyThunk
{
    unsigned char padding[0x8c];
    IntegerTripleCopyValue value;

    int *copyTo(int *destination);
};

int *Offset140IntegerTripleCopyThunk::copyTo(int *destination)
{
    *reinterpret_cast<IntegerTripleCopyValue *>(destination) = value;
    return destination;
}

struct Offset152IntegerResetThunk
{
    unsigned char padding[0x98];
    int value;

    void reset();
};

void Offset152IntegerResetThunk::reset()
{
    value = 0;
}

struct Offset172IntegerPairSetterThunk
{
    unsigned char padding[0xac];
    int first;
    int second;

    void setValues(int firstValue, int secondValue);
};

void Offset172IntegerPairSetterThunk::setValues(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
}

struct Offset156FloatGetterThunk
{
    unsigned char padding[0x9c];
    float value;

    float get() const;
};

float Offset156FloatGetterThunk::get() const
{
    return value;
}

struct Offset164FloatGetterThunk
{
    unsigned char padding[0xa4];
    float value;

    float get() const;
};

float Offset164FloatGetterThunk::get() const
{
    return value;
}

struct TwoIntegerClearThunk
{
    int first;
    int second;

    TwoIntegerClearThunk();
};

TwoIntegerClearThunk::TwoIntegerClearThunk() :
    first(0),
    second(0)
{
}

struct VirtualSlot9NoArgumentCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void invoke();

    void call();
};

void VirtualSlot9NoArgumentCallThunk::call()
{
    invoke();
}

struct OffsetZeroIntegerSetterReturningThisThunk
{
    int value;

    OffsetZeroIntegerSetterReturningThisThunk *setValue(int newValue);
};

OffsetZeroIntegerSetterReturningThisThunk *OffsetZeroIntegerSetterReturningThisThunk::setValue(int newValue)
{
    value = newValue;
    return this;
}

struct Offset40IntegerSetterThunk
{
    unsigned char padding[0x28];
    int value;

    void setValue(int newValue);
};

void Offset40IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset60IntegerSetterThunk
{
    unsigned char padding[0x3c];
    int value;

    void setValue(int newValue);
};

void Offset60IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset4IntegerSetterThunk
{
    unsigned char padding[4];
    int value;

    void setValue(int newValue);
};

void Offset4IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset65BooleanSetterThunk
{
    unsigned char padding[0x41];
    bool value;

    void setValue(bool newValue);
};

void Offset65BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct Offset64BooleanSetterThunk
{
    unsigned char padding[0x40];
    bool value;

    void setValue(bool newValue);
};

void Offset64BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct OffsetZeroIntegerSetterReturningThisAlternateThunk
{
    int value;

    OffsetZeroIntegerSetterReturningThisAlternateThunk *setValue(int newValue);
};

OffsetZeroIntegerSetterReturningThisAlternateThunk *OffsetZeroIntegerSetterReturningThisAlternateThunk::setValue(int newValue)
{
    value = newValue;
    return this;
}

struct OffsetZeroIntegerCopyReturningThisThunk
{
    int value;

    OffsetZeroIntegerCopyReturningThisThunk *copyFrom(const OffsetZeroIntegerCopyReturningThisThunk *other);
    OffsetZeroIntegerCopyReturningThisThunk *copyFromAlternate(const OffsetZeroIntegerCopyReturningThisThunk *other);
};

OffsetZeroIntegerCopyReturningThisThunk *OffsetZeroIntegerCopyReturningThisThunk::copyFrom(const OffsetZeroIntegerCopyReturningThisThunk *other)
{
    value = other->value;
    return this;
}

OffsetZeroIntegerCopyReturningThisThunk *OffsetZeroIntegerCopyReturningThisThunk::copyFromAlternate(const OffsetZeroIntegerCopyReturningThisThunk *other)
{
    value = other->value;
    return this;
}

struct OffsetZeroSecondIntegerSetterReturningThisThunk
{
    int value;

    OffsetZeroSecondIntegerSetterReturningThisThunk *setSecond(int unused, int newValue);
};

OffsetZeroSecondIntegerSetterReturningThisThunk *OffsetZeroSecondIntegerSetterReturningThisThunk::setSecond(int, int newValue)
{
    value = newValue;
    return this;
}

void copyIntegerIfDestinationNotNull(int *destination, const int *source)
{
    if (destination != 0)
    {
        *destination = *source;
    }
}

struct IndirectIntegerCopyThunk
{
    const int *source;

    int *copyTo(int *destination) const;
};

int *IndirectIntegerCopyThunk::copyTo(int *destination) const
{
    *destination = *source;
    return destination;
}

struct LinkedNodePopValue
{
    LinkedNodePopValue *next;
};

struct LinkedNodePopThunk
{
    LinkedNodePopValue *head;

    LinkedNodePopValue **popTo(LinkedNodePopValue **destination, int unused);
};

LinkedNodePopValue **LinkedNodePopThunk::popTo(LinkedNodePopValue **destination, int)
{
    LinkedNodePopValue *oldHead = head;
    head = oldHead->next;
    *destination = oldHead;
    return destination;
}

struct VirtualMinusOneConstructorThunk
{
    virtual ~VirtualMinusOneConstructorThunk();

    int value;

    VirtualMinusOneConstructorThunk();
    VirtualMinusOneConstructorThunk(const VirtualMinusOneConstructorThunk &other);
};

VirtualMinusOneConstructorThunk::VirtualMinusOneConstructorThunk() :
    value(-1)
{
}

VirtualMinusOneConstructorThunk::VirtualMinusOneConstructorThunk(const VirtualMinusOneConstructorThunk &other) :
    value(other.value)
{
}

VirtualMinusOneConstructorThunk::~VirtualMinusOneConstructorThunk()
{
}

struct ReferenceCountedReleaseValue
{
    virtual void release(int deletingFlag);

    int referenceCount;

    int decrementReferenceCount()
    {
        return --referenceCount;
    }
};

struct ReferencePointerReleaseThunk
{
    ReferenceCountedReleaseValue *value;

    void release();
    void releaseAlternate();
    void releaseThird();
};

void ReferencePointerReleaseThunk::release()
{
    ReferenceCountedReleaseValue *current = value;
    if (current != 0)
    {
        if (current->decrementReferenceCount() <= 0)
        {
            current->release(1);
        }
    }
}

void ReferencePointerReleaseThunk::releaseAlternate()
{
    ReferenceCountedReleaseValue *current = value;
    if (current != 0)
    {
        if (current->decrementReferenceCount() <= 0)
        {
            current->release(1);
        }
    }
}

void ReferencePointerReleaseThunk::releaseThird()
{
    ReferenceCountedReleaseValue *current = value;
    if (current != 0)
    {
        if (current->decrementReferenceCount() <= 0)
        {
            current->release(1);
        }
    }
}

struct ReferencePointerAssignmentThunk
{
    ReferenceCountedReleaseValue *value;

    ReferencePointerAssignmentThunk *assign(const ReferencePointerAssignmentThunk *other);
};

ReferencePointerAssignmentThunk *ReferencePointerAssignmentThunk::assign(const ReferencePointerAssignmentThunk *other)
{
    if (this != other)
    {
        ReferenceCountedReleaseValue *newValue = other->value;
        if (newValue != 0)
        {
            ++newValue->referenceCount;
        }

        ReferenceCountedReleaseValue *oldValue = value;
        if (oldValue != 0 && oldValue->decrementReferenceCount() <= 0)
        {
            oldValue->release(1);
        }

        value = other->value;
    }

    return this;
}

struct PointerPayloadGetterThunk
{
    unsigned char *base;

    unsigned char *getPayload() const;
    unsigned char *getPayloadAlternate() const;
    unsigned char *getPayloadThird() const;
};

unsigned char *PointerPayloadGetterThunk::getPayload() const
{
    return base + 4;
}

unsigned char *PointerPayloadGetterThunk::getPayloadAlternate() const
{
    return base + 4;
}

unsigned char *PointerPayloadGetterThunk::getPayloadThird() const
{
    return base + 4;
}

struct PointerPresenceThunk
{
    void *value;

    bool hasValue() const;
};

bool PointerPresenceThunk::hasValue() const
{
    return value != 0;
}
