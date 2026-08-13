struct RvaA21E0Offset840AddressGetter
{
    unsigned char unused[840];
    unsigned char storage;

    unsigned char *get_value();
};

unsigned char *RvaA21E0Offset840AddressGetter::get_value()
{
    return &storage;
}
