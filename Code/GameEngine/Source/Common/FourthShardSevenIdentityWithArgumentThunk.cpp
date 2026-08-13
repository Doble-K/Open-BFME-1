struct FourthShardSevenIdentityWithArgumentThunk
{
    FourthShardSevenIdentityWithArgumentThunk *identity(int unused);
};

FourthShardSevenIdentityWithArgumentThunk *FourthShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
