struct RvaCA7E0IdentityWithArgumentThunk
{
    RvaCA7E0IdentityWithArgumentThunk *identity(int unused);
};

RvaCA7E0IdentityWithArgumentThunk *RvaCA7E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
