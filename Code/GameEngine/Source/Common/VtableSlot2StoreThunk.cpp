struct VtableSlot2Result
{
    unsigned long value;
};

struct VtableSlot2StoreThunk
{
    unsigned long *vtable;

    VtableSlot2Result get() const;
};

VtableSlot2Result VtableSlot2StoreThunk::get() const
{
    VtableSlot2Result result = { vtable[2] };
    return result;
}
