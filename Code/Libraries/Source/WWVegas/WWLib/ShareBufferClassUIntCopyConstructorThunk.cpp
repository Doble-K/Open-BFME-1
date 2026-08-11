// cl: /DNDEBUG /MD /EHsc

void *operator new[](unsigned int size);

// BFME ShareBufferClass<T> layout (see sharebuf.h): RefCountClass base (vtbl +
// NumRefs), then RawBuffer (actual allocation), Array (aligned view handed
// out), Count, Alignment. The 2-arg copy constructor always allocates a fresh
// buffer sized off Count and, when Alignment is non-zero, rounds the raw
// allocation up to that alignment for Array while keeping RawBuffer pointed
// at the original allocation (freed later by the destructor).
class RefCountClass
{
public:
    RefCountClass(void) : NumRefs(1) {}
    RefCountClass(const RefCountClass &) : NumRefs(1) {}
    void Add_Ref(void) { NumRefs++; }
    void Release_Ref(void);
    int Num_Refs(void) { return NumRefs; }
    virtual void Delete_This(void);

protected:
    virtual ~RefCountClass(void) {}

private:
    int NumRefs;
};

template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
    ShareBufferClass(const ShareBufferClass &);

protected:
    Type *RawBuffer;
    Type *Array;
    int Count;
    int Alignment;
};

template <class Type>
ShareBufferClass<Type>::ShareBufferClass(const ShareBufferClass<Type> &that) :
    Count(that.Count)
{
    Alignment = that.Alignment;
    void *raw;
    if (Alignment == 0) {
        raw = ::operator new[](Count * sizeof(Type));
        Array = (Type *)raw;
    } else {
        raw = ::operator new[](Count * sizeof(Type) + Alignment);
        Array = (Type *)(((unsigned int)raw + Alignment - 1) & ~(unsigned int)(Alignment - 1));
    }
    RawBuffer = (Type *)raw;
    for (int i = 0; i < Count; i++) {
        Array[i] = that.Array[i];
    }
}

template ShareBufferClass<unsigned int>::ShareBufferClass(
    const ShareBufferClass<unsigned int> &);
