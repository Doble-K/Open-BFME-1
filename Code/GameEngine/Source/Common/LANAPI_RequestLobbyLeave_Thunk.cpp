// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift LANAPI::RequestLobbyLeave __emit thunk to clean C++.
// Retail builds a 0x1D8-byte packet on the stack (field at +4 = 7), passes
// it to the virtual at slot 0xC4, forwards it to another member with a zero
// arg, then conditionally calls a method on the member object at this+0x4C.

class LANAPIRequestPacket
{
public:
    unsigned int m_00;
    unsigned int m_04;
    unsigned char m_pad[0x1D4];
};

class LANAPIMemberObject
{
public:
    void flushQueue();
};

class LANAPI
{
public:
    virtual void vslot00();
    virtual void vslot01();
    virtual void vslot02();
    virtual void vslot03();
    virtual void vslot04();
    virtual void vslot05();
    virtual void vslot06();
    virtual void vslot07();
    virtual void vslot08();
    virtual void vslot09();
    virtual void vslot10();
    virtual void vslot11();
    virtual void vslot12();
    virtual void vslot13();
    virtual void vslot14();
    virtual void vslot15();
    virtual void vslot16();
    virtual void vslot17();
    virtual void vslot18();
    virtual void vslot19();
    virtual void vslot20();
    virtual void vslot21();
    virtual void vslot22();
    virtual void vslot23();
    virtual void vslot24();
    virtual void vslot25();
    virtual void vslot26();
    virtual void vslot27();
    virtual void vslot28();
    virtual void vslot29();
    virtual void vslot30();
    virtual void vslot31();
    virtual void vslot32();
    virtual void vslot33();
    virtual void vslot34();
    virtual void vslot35();
    virtual void vslot36();
    virtual void vslot37();
    virtual void vslot38();
    virtual void vslot39();
    virtual void vslot40();
    virtual void vslot41();
    virtual void vslot42();
    virtual void vslot43();
    virtual void vslot44();
    virtual void vslot45();
    virtual void vslot46();
    virtual void vslot47();
    virtual void vslot48();
    virtual void sendPacket(LANAPIRequestPacket *);

    void queuePacket(LANAPIRequestPacket *, int);
    virtual void RequestLobbyLeave(bool);

private:
    unsigned char m_pad[0x48];
    LANAPIMemberObject *m_member;
};

// ?RequestLobbyLeave@LANAPI@@UAEX_N@Z
void LANAPI::RequestLobbyLeave(bool flag)
{
    LANAPIRequestPacket pkt;
    pkt.m_00 = 7;
    sendPacket(&pkt);
    queuePacket(&pkt, 0);
    if (flag) {
        m_member->flushQueue();
    }
}
