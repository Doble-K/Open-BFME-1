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
