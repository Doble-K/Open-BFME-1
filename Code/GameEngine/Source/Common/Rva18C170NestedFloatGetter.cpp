struct Rva18C170NestedFloat
{
    float value;
};

struct Rva18C170NestedFloatGetter
{
    unsigned char unused[8];
    Rva18C170NestedFloat *nested;

    float get_value();
};

float Rva18C170NestedFloatGetter::get_value()
{
    return nested->value;
}
