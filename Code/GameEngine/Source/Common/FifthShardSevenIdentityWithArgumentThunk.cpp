struct FifthShardSevenIdentityWithArgumentThunk
{
    FifthShardSevenIdentityWithArgumentThunk *identity(int unused);
};

FifthShardSevenIdentityWithArgumentThunk *FifthShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
