struct Rva9ED50ValueSetterThunk
{
    int value;

    Rva9ED50ValueSetterThunk *setValue(int newValue);
};

Rva9ED50ValueSetterThunk *Rva9ED50ValueSetterThunk::setValue(int newValue)
{
    value = newValue;
    return this;
}
