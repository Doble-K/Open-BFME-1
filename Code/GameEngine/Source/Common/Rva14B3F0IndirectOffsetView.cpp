struct Rva14B3F0Storage
{
    char *base;
};

struct Rva14B3F0IndirectView
{
    Rva14B3F0Storage *storage;

    char *payload();
};

char *Rva14B3F0IndirectView::payload()
{
    return storage->base + 8;
}
