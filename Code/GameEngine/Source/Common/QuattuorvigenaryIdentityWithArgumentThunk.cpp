struct QuattuorvigenaryIdentityWithArgumentThunk
{
    QuattuorvigenaryIdentityWithArgumentThunk *identity(int unused);
};

QuattuorvigenaryIdentityWithArgumentThunk *QuattuorvigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
