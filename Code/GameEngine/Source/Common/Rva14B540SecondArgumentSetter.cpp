struct Rva14B540SecondArgumentSetter
{
    int value;

    Rva14B540SecondArgumentSetter *set(int unused, int newValue);
};

Rva14B540SecondArgumentSetter *Rva14B540SecondArgumentSetter::set(int, int newValue)
{
    value = newValue;
    return this;
}
