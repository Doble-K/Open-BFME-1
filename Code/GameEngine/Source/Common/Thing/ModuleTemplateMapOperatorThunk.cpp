class ModuleFactory
{
public:
	class ModuleTemplate
	{
	};

	class ModuleTemplateMap
	{
	public:
		ModuleTemplate &operator[](int const &);
	};
};

__declspec(naked) ModuleFactory::ModuleTemplate &ModuleFactory::ModuleTemplateMap::operator[](int const &)
{
	__asm {
		_emit 0E9h
		_emit 05Eh
		_emit 092h
		_emit 010h
		_emit 000h
	}
}
