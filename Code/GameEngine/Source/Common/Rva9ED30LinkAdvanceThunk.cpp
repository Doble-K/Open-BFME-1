struct Rva9ED30LinkAdvanceThunk
{
    Rva9ED30LinkAdvanceThunk *next;

    Rva9ED30LinkAdvanceThunk *advanceLink();
};

Rva9ED30LinkAdvanceThunk *Rva9ED30LinkAdvanceThunk::advanceLink()
{
    next = next->next;
    return this;
}
