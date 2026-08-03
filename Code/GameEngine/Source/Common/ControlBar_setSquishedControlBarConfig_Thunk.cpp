// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift ControlBar::setSquishedControlBarConfig __emit thunk to
// clean C++. Retail: early-out when the flag at +0x20 is already 1, then set
// it and call arrange on the member at +0x34, a helper on this, Display's
// vfn at slot 0x30 feeding Mouse's vfn at slot 0x40, and adjust on the
// member at +0x30 with the window-manager inner field and 1.

class ControlBarArranger
{
public:
    void arrange(int, int);
};

class ControlBarAdjuster
{
public:
    void adjust(int, int);
};

class CBDisplay
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual int vfn30();
};

class CBMouse
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void vfn40(int);
};

class CBWindowManagerInner
{
public:
    unsigned char m_pad[4];
    int m_04;
};

class CBWindowManager
{
public:
    unsigned char m_pad[0x0C];
    CBWindowManagerInner *m_0C;
};

extern CBDisplay *g_cbDisplay;
extern CBMouse *g_cbMouse;
extern CBWindowManager *g_cbWindowManager;

class ControlBar
{
public:
    void helper();

protected:
    void setSquishedControlBarConfig();

private:
    unsigned char m_pad[0x18];
    int m_18;
    int m_1C;
    int m_20;
    unsigned char m_pad2[0x0C];
    ControlBarAdjuster *m_30;
    ControlBarArranger *m_34;
};

// ?setSquishedControlBarConfig@ControlBar@@IAEXXZ
void ControlBar::setSquishedControlBarConfig()
{
    if (m_20 == 1) {
        return;
    }
    m_20 = 1;
    m_34->arrange(m_18, m_1C);
    helper();
    g_cbMouse->vfn40(g_cbDisplay->vfn30());
    m_30->adjust(g_cbWindowManager->m_0C->m_04, 1);
}
