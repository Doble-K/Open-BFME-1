class W3DVolumetricShadowManager
{
public:
    bool ReAcquireResources();
};

class W3DVolumetricShadowManagerReAcquireShim
{
public:
    bool reacquire();
};

bool W3DVolumetricShadowManager::ReAcquireResources()
{
    return ((W3DVolumetricShadowManagerReAcquireShim *)this)->reacquire();
}
