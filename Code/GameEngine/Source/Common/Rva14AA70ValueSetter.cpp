struct Rva14AA70ValueSetter
{
    int value;

    Rva14AA70ValueSetter *set(int newValue);
};

Rva14AA70ValueSetter *Rva14AA70ValueSetter::set(int newValue)
{
    value = newValue;
    return this;
}
