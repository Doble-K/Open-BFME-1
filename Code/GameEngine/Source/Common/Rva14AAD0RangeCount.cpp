struct Rva14AAD0Element
{
    int first;
    int second;
};

struct Rva14AAD0Range
{
    Rva14AAD0Element *begin;
    Rva14AAD0Element *end;
};

struct Rva14AAD0RangeView
{
    Rva14AAD0Range *range;

    int count();
};

int Rva14AAD0RangeView::count()
{
    return range->end - range->begin;
}
