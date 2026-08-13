struct SecondShardSevenIdentityWithArgumentThunk
{
    SecondShardSevenIdentityWithArgumentThunk *identity(int unused);
};

SecondShardSevenIdentityWithArgumentThunk *SecondShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
