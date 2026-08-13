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
