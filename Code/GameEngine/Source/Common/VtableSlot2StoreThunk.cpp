struct VtableSlot2Result
{
    unsigned long value;
};

struct VtableSlot2StoreThunk
{
    unsigned long *vtable;

    VtableSlot2Result get() const;
    VtableSlot2Result getAlternate() const;
    VtableSlot2Result getThird() const;
    VtableSlot2Result getFourth() const;
    VtableSlot2Result getFifth() const;
    VtableSlot2Result getSixth() const;
    VtableSlot2Result getSeventh() const;
    VtableSlot2Result getEighth() const;
};

VtableSlot2Result VtableSlot2StoreThunk::get() const
{
    VtableSlot2Result result = { vtable[2] };
    return result;
}

VtableSlot2Result VtableSlot2StoreThunk::getAlternate() const
{
    VtableSlot2Result result = { vtable[2] };
    return result;
}

VtableSlot2Result VtableSlot2StoreThunk::getThird() const
{
    VtableSlot2Result result = { vtable[2] };
    return result;
}

VtableSlot2Result VtableSlot2StoreThunk::getFourth() const
{
    VtableSlot2Result result = { vtable[2] };
    return result;
}

VtableSlot2Result VtableSlot2StoreThunk::getFifth() const
{
    VtableSlot2Result result = { vtable[2] };
    return result;
}

VtableSlot2Result VtableSlot2StoreThunk::getSixth() const
{
    VtableSlot2Result result = { vtable[2] };
    return result;
}

VtableSlot2Result VtableSlot2StoreThunk::getSeventh() const
{
    VtableSlot2Result result = { vtable[2] };
    return result;
}

VtableSlot2Result VtableSlot2StoreThunk::getEighth() const
{
    VtableSlot2Result result = { vtable[2] };
    return result;
}
