struct Rva8DFA0IdentityWithArgumentThunk
{
    Rva8DFA0IdentityWithArgumentThunk *identity(int unused);
};

Rva8DFA0IdentityWithArgumentThunk *Rva8DFA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
