struct Rva1ADD10FalseWithTwoArgumentsThunk
{
    bool reject(int first, int second);
};

bool Rva1ADD10FalseWithTwoArgumentsThunk::reject(int, int)
{
    return false;
}
