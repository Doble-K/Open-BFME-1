struct ThirdShardSevenIdentityWithArgumentThunk
{
    ThirdShardSevenIdentityWithArgumentThunk *identity(int unused);
};

ThirdShardSevenIdentityWithArgumentThunk *ThirdShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
