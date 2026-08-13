extern int DualIndexedDispatchFirst;
extern int DualIndexedDispatchSecond;

extern void __cdecl dispatchIndexedValue(
    void *target,
    int index,
    void *value,
    int count,
    int *first,
    int *second);

struct DualIndexedDispatchThunk
{
    unsigned char padding[0x54];
    void *value;

    void dispatch(void *target);
};

void DualIndexedDispatchThunk::dispatch(void *target)
{
    dispatchIndexedValue(target, 1, value, 2, &DualIndexedDispatchFirst, &DualIndexedDispatchSecond);
    dispatchIndexedValue(target, 2, value, 2, &DualIndexedDispatchFirst, &DualIndexedDispatchSecond);
}
