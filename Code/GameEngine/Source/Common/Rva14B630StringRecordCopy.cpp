class AsciiString
{
public:
    AsciiString(const AsciiString &source);

private:
    void *data;
};

struct Rva14B630StringRecord
{
    AsciiString text;
    int value;

    Rva14B630StringRecord(const Rva14B630StringRecord &source);
};

Rva14B630StringRecord::Rva14B630StringRecord(const Rva14B630StringRecord &source) :
    text(source.text),
    value(source.value)
{
}
