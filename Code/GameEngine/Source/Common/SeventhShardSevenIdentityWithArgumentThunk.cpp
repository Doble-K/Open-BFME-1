struct SeventhShardSevenIdentityWithArgumentThunk
{
    SeventhShardSevenIdentityWithArgumentThunk *identity(int unused);
};

SeventhShardSevenIdentityWithArgumentThunk *SeventhShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
