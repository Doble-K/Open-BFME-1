struct ShardSevenIdentityWithArgumentThunk
{
    ShardSevenIdentityWithArgumentThunk *identity(int unused);
};

ShardSevenIdentityWithArgumentThunk *ShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
