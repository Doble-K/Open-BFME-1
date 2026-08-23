// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0082B0A0Identity
{
public:
    Rva0082B0A0Identity *self();
    void touch();
};

Rva0082B0A0Identity *Rva0082B0A0Identity::self()
{
    return this;
}

void Rva0082B0A0Identity::touch()
{
}

class Rva0082B0E0Identity
{
public:
    Rva0082B0E0Identity *self();
    void touch();
};

Rva0082B0E0Identity *Rva0082B0E0Identity::self()
{
    return this;
}

void Rva0082B0E0Identity::touch()
{
}

class Rva0082B140Helpers
{
public:
    int firstValue(int value);
    int secondValue(int value);
    int maximumIndex();
    void ignoreValue(int value);
    int upperWord();

private:
    int m_lowerWord;
    int m_upperWord;
};

int Rva0082B140Helpers::firstValue(int value)
{
    return value;
}

int Rva0082B140Helpers::secondValue(int value)
{
    return value;
}

int Rva0082B140Helpers::maximumIndex()
{
    return 0x3fffffff;
}

void Rva0082B140Helpers::ignoreValue(int)
{
}

int Rva0082B140Helpers::upperWord()
{
    return m_upperWord;
}
