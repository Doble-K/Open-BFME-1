// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Xfer;

namespace FXParticleSystem {

class RenderObjectUpdateModuleInfo {
public:
    RenderObjectUpdateModuleInfo(const RenderObjectUpdateModuleInfo &that);
    virtual ~RenderObjectUpdateModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    RenderObjectUpdateModuleInfo &operator=(const RenderObjectUpdateModuleInfo &that);
};

// ??0RenderObjectUpdateModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
RenderObjectUpdateModuleInfo::RenderObjectUpdateModuleInfo(const RenderObjectUpdateModuleInfo &that)
{
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(VariableBlock *)((char *)this + 0x4) = *(const VariableBlock *)((const char *)&that + 0x4);
    *(VariableBlock *)((char *)this + 0x10) = *(const VariableBlock *)((const char *)&that + 0x10);
    *(VariableBlock *)((char *)this + 0x1c) = *(const VariableBlock *)((const char *)&that + 0x1c);
    *(VariableBlock *)((char *)this + 0x28) = *(const VariableBlock *)((const char *)&that + 0x28);
    *(VariableBlock *)((char *)this + 0x34) = *(const VariableBlock *)((const char *)&that + 0x34);
    *(VariableBlock *)((char *)this + 0x40) = *(const VariableBlock *)((const char *)&that + 0x40);
    *(VariableBlock *)((char *)this + 0x4c) = *(const VariableBlock *)((const char *)&that + 0x4c);
    *(VariableBlock *)((char *)this + 0x58) = *(const VariableBlock *)((const char *)&that + 0x58);
    *(VariableBlock *)((char *)this + 0x64) = *(const VariableBlock *)((const char *)&that + 0x64);
    *(VariableBlock *)((char *)this + 0x70) = *(const VariableBlock *)((const char *)&that + 0x70);
    *(VariableBlock *)((char *)this + 0x7c) = *(const VariableBlock *)((const char *)&that + 0x7c);
    *(VariableBlock *)((char *)this + 0x88) = *(const VariableBlock *)((const char *)&that + 0x88);
    *(unsigned int *)((char *)this + 0x94) = *(const unsigned int *)((const char *)&that + 0x94);
}

}
