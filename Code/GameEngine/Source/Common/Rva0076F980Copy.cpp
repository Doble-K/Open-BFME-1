// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva0076F980Mid
{
public:
	Rva0076F980Mid(const Rva0076F980Mid &other);

private:
	int m_00;
	int m_04;
	int m_08;
};

class Rva0076F980
{
	Rva0036CA00Str m_00;
	Rva0076F980Mid m_04;
	int m_10;

public:
	Rva0076F980(const Rva0076F980 &other);
};

Rva0076F980::Rva0076F980(const Rva0076F980 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_10(other.m_10)
{
}
