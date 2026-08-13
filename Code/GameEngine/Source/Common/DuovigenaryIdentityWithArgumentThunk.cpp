struct DuovigenaryIdentityWithArgumentThunk
{
    DuovigenaryIdentityWithArgumentThunk *identity(int unused);
};

DuovigenaryIdentityWithArgumentThunk *DuovigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
