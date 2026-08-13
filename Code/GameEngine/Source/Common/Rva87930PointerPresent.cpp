class Rva87930PointerPresent
{
public:
    unsigned int has_value();

private:
    void *value;
};

unsigned int Rva87930PointerPresent::has_value()
{
    return value != 0;
}
