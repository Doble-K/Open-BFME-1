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
    void resetThird();
    void resetFourth();
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

void InlineRangeResetThunk::resetThird()
{
    state->flag = false;
    state->size = 0;
    state->begin = state;
    state->end = state;
}

void InlineRangeResetThunk::resetFourth()
{
    state->flag = false;
    state->size = 0;
    state->begin = state;
    state->end = state;
}
