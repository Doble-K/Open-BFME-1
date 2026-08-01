// cl: /DNDEBUG /MD /EHsc

class LadderList
{
public:
    ~LadderList();
};

void destroyLadderListForThunk(LadderList *list)
{
    delete list;
}
