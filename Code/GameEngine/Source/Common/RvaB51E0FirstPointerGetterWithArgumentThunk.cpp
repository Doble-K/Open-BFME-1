struct RvaB51E0FirstPointerGetterWithArgumentThunk
{
    void *value;

    void *get(int unused);
};

void *RvaB51E0FirstPointerGetterWithArgumentThunk::get(int)
{
    return value;
}
