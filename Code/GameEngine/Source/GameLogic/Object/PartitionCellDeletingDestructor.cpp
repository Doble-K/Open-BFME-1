// cl: /DNDEBUG /MD /EHsc

class PartitionCell
{
    unsigned char data[0x98];

public:
    ~PartitionCell();
};

void deletePartitionCellArray(PartitionCell *cells)
{
    delete[] cells;
}
