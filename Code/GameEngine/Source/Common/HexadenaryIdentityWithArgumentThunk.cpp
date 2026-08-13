struct HexadenaryIdentityWithArgumentThunk
{
    HexadenaryIdentityWithArgumentThunk *identity(int unused);
};

HexadenaryIdentityWithArgumentThunk *HexadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
