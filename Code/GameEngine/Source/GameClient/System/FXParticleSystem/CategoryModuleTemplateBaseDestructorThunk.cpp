// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate / CategoryModuleTemplateBase dual-vtbl empty dtors.
// Retail shape: if (this) write sec@+4 then pri@0; else write sec@0 then pri@this(null).

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<0>
{
public:
	virtual ~CategoryModuleTemplate();
};

CategoryModuleTemplate<0>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x01073760u;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplate<1>
{
public:
	virtual ~CategoryModuleTemplate();
};

CategoryModuleTemplate<1>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F978u;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplate<2>
{
public:
	virtual ~CategoryModuleTemplate();
};

CategoryModuleTemplate<2>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F9E8u;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplate<3>
{
public:
	virtual ~CategoryModuleTemplate();
};

CategoryModuleTemplate<3>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F9E4u;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplate<4>
{
public:
	virtual ~CategoryModuleTemplate();
};

CategoryModuleTemplate<4>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F9CCu;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplate<5>
{
public:
	virtual ~CategoryModuleTemplate();
};

CategoryModuleTemplate<5>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F9ACu;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplate<8>
{
public:
	virtual ~CategoryModuleTemplate();
};

CategoryModuleTemplate<8>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0107375Cu;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplateBase<0>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

CategoryModuleTemplateBase<0>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x01073760u;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplateBase<1>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

CategoryModuleTemplateBase<1>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F978u;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplateBase<2>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

CategoryModuleTemplateBase<2>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F9E8u;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplateBase<3>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

CategoryModuleTemplateBase<3>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F9E4u;
	*(volatile unsigned int *)this = 0x01073758u;
}

template <>
class __declspec(novtable) CategoryModuleTemplateBase<7>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

CategoryModuleTemplateBase<7>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110FA14u;
	*(volatile unsigned int *)this = 0x01073758u;
}

}
