class Rva86450PointerPlus16
{
public:
    unsigned char *get_value();

private:
    unsigned char *value;
};

unsigned char *Rva86450PointerPlus16::get_value()
{
    return value + 16;
}
