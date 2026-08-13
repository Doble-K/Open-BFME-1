struct EmptyCopyAssignThunk
{
    EmptyCopyAssignThunk &assign(const EmptyCopyAssignThunk &other);
    EmptyCopyAssignThunk &assignAlternate(const EmptyCopyAssignThunk &other);
};

EmptyCopyAssignThunk &EmptyCopyAssignThunk::assign(const EmptyCopyAssignThunk &)
{
    return *this;
}

EmptyCopyAssignThunk &EmptyCopyAssignThunk::assignAlternate(const EmptyCopyAssignThunk &)
{
    return *this;
}
