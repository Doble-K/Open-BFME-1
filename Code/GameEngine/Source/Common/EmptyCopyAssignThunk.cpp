struct EmptyCopyAssignThunk
{
    EmptyCopyAssignThunk &assign(const EmptyCopyAssignThunk &other);
};

EmptyCopyAssignThunk &EmptyCopyAssignThunk::assign(const EmptyCopyAssignThunk &)
{
    return *this;
}
