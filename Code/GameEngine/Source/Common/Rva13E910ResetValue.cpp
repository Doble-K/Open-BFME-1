class Rva13E910ResetValue {
public:
    Rva13E910ResetValue *reset();

private:
    unsigned int m_value;
};

Rva13E910ResetValue *Rva13E910ResetValue::reset()
{
    m_value = 0;
    return this;
}
