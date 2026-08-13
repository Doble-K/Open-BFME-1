struct Rva14B3D0Value
{
    int value;
};

struct Rva14B3D0IndirectValue
{
    Rva14B3D0Value *source;

    Rva14B3D0Value *copyTo(Rva14B3D0Value *destination);
};

Rva14B3D0Value *Rva14B3D0IndirectValue::copyTo(Rva14B3D0Value *destination)
{
    *destination = *source;
    return destination;
}
