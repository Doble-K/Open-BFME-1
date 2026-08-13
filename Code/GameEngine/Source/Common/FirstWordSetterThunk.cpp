struct FirstWordSetterThunk
{
    unsigned long value;

    FirstWordSetterThunk *set(unsigned long newValue);
    void assign(unsigned long newValue);
};

FirstWordSetterThunk *FirstWordSetterThunk::set(unsigned long newValue)
{
    value = newValue;
    return this;
}

void FirstWordSetterThunk::assign(unsigned long newValue)
{
    value = newValue;
}
