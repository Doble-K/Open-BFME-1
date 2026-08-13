struct Rva14AA20OffsetView
{
    char *base;

    char *payload();
};

char *Rva14AA20OffsetView::payload()
{
    return base + 8;
}
