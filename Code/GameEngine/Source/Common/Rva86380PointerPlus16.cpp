class Rva86380PointerPlus16
{
public:
    unsigned char *get_value();

private:
    unsigned char *value;
};

unsigned char *Rva86380PointerPlus16::get_value()
{
    return value + 16;
}
