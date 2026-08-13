struct Rva943E10NodeMotion
{
    unsigned char data[28];
    ~Rva943E10NodeMotion();
};

Rva943E10NodeMotion::~Rva943E10NodeMotion()
{
}

class Rva943E10CompressedAnim
{
public:
    void free();

private:
    unsigned char data[24];
    Rva943E10NodeMotion *node_motion;
};

void Rva943E10CompressedAnim::free()
{
    if (node_motion != 0) {
        delete[] node_motion;
    }
}
