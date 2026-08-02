class ModuleFactory
{
public:
    class ModuleTemplate
    {
    };

    class ModuleTemplateMap
    {
    public:
        ModuleTemplate &operator[](const int &);
    };
};

class ModuleTemplateMapOperatorShim
{
public:
    ModuleFactory::ModuleTemplate &at(const int &key);
};

ModuleFactory::ModuleTemplate &ModuleFactory::ModuleTemplateMap::operator[](const int &key)
{
    return ((ModuleTemplateMapOperatorShim *)this)->at(key);
}
