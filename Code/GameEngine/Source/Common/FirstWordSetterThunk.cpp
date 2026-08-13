struct FirstWordSetterThunk
{
    unsigned long value;

    FirstWordSetterThunk *set(unsigned long newValue);
};

FirstWordSetterThunk *FirstWordSetterThunk::set(unsigned long newValue)
{
    value = newValue;
    return this;
}
