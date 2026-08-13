struct SixthShardSevenIdentityWithArgumentThunk
{
    SixthShardSevenIdentityWithArgumentThunk *identity(int unused);
};

SixthShardSevenIdentityWithArgumentThunk *SixthShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
