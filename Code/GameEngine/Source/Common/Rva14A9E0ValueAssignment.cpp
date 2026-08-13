struct Rva14A9E0ValueAssignment
{
    int value;

    Rva14A9E0ValueAssignment *assign(const Rva14A9E0ValueAssignment *source);
};

Rva14A9E0ValueAssignment *Rva14A9E0ValueAssignment::assign(const Rva14A9E0ValueAssignment *source)
{
    value = source->value;
    return this;
}
