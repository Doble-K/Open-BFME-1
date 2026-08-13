// cl: /DNDEBUG /MD /O2 /Ob2
// Open-BFME5: clean C++ lift of the retail four-byte table lookup helper.

struct Stride4TableEntry
{
	unsigned int value;
};

class Stride4Table
{
public:
	Stride4TableEntry *lookup(unsigned int index) const;

private:
	Stride4TableEntry *m_entries;
};

Stride4TableEntry *Stride4Table::lookup(unsigned int index) const
{
	return &m_entries[index];
}
