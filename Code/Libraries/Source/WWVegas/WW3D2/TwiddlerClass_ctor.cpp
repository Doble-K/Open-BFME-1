// cl: /DNDEBUG /MD /EHsc

// TwiddlerClass's constructor, retail 0x0078F500. The base's constructor and
// then this class's own vftable pointer; nothing else is touched.

class TwiddlerClassBase
{
public:
	TwiddlerClassBase();

	virtual void twiddlerClassBaseAnchor();
};

class TwiddlerClass : public TwiddlerClassBase
{
public:
	TwiddlerClass();

	virtual void twiddlerClassAnchor();
};

// ??0TwiddlerClass@@QAE@XZ
TwiddlerClass::TwiddlerClass()
{
}
