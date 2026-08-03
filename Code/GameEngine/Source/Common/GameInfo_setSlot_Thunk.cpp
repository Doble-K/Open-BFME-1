// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift GameInfo::setSlot __emit thunk to clean C++. Bounds-checked
// slot lookup, slot-0 flag fixups on the by-value GameSlot copy, then the
// virtual-slot update call; the by-value argument is destroyed at state -1.

class GameSlot
{
public:
    ~GameSlot();

    unsigned int m_f0;
    unsigned int m_type;
    unsigned char m_f8;
    unsigned char m_f9;
    unsigned char m_pad[0x44 - 0xA];
};

class GI_SlotObj
{
public:
    void setSlotData(GameSlot *slot);
};

class GameInfo
{
public:
    void setSlot(int slot, GameSlot slotObj);

private:
    unsigned char m_pad[0x14];
    GI_SlotObj *m_slots[8];
};

// ?setSlot@GameInfo@@QAEXHVGameSlot@@@Z
void GameInfo::setSlot(int slot, GameSlot slotObj)
{
    if (slot >= 0 && slot < 8 && m_slots[slot]) {
        if (slot == 0) {
            slotObj.m_f8 = 1;
            if (slotObj.m_type == 5)
                slotObj.m_f9 = 1;
        }
        m_slots[slot]->setSlotData(&slotObj);
    }
}
