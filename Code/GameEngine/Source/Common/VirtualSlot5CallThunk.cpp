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
};

void VirtualSlot8CallThunk::invokeZero()
{
    invoke(0);
}

void VirtualSlot8CallThunk::invokeZeroAlternate()
{
    invoke(0);
}
