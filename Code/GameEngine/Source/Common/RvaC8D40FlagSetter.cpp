struct RvaC8D40FlagSetter
{
    unsigned char unused[36];
    unsigned char enabled;

    void set_enabled();
};

void RvaC8D40FlagSetter::set_enabled()
{
    enabled = true;
}
