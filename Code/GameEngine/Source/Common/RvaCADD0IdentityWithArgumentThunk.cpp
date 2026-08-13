struct RvaCADD0IdentityWithArgumentThunk
{
    RvaCADD0IdentityWithArgumentThunk *identity(int unused);
};

RvaCADD0IdentityWithArgumentThunk *RvaCADD0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
