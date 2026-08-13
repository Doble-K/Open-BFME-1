struct InlineRangeState
{
    bool flag;
    char padding[3];
    unsigned long size;
    InlineRangeState *begin;
    InlineRangeState *end;
};

struct InlineRangeResetThunk
{
    InlineRangeState *state;

    void reset();
    void resetAlternate();
};

void InlineRangeResetThunk::reset()
{
    state->flag = false;
    state->size = 0;
    state->begin = state;
    state->end = state;
}

void InlineRangeResetThunk::resetAlternate()
{
    state->flag = false;
    state->size = 0;
    state->begin = state;
    state->end = state;
}
