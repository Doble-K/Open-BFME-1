// cl: /DNDEBUG /MD /O2 /Ob2
// Open-BFME5: clean C++ lift of the retail pointer-range count helper.

class PointerRangeCount
{
public:
	unsigned int size() const;

private:
	void **m_begin;
	void **m_end;
};

unsigned int PointerRangeCount::size() const
{
	return m_end - m_begin;
}
