class CameraClass
{
};

class BaseHeightMapRenderObjClass
{
public:
    void renderTrees(CameraClass *);
};

class BaseHeightMapRenderTreesShim
{
public:
    void render(CameraClass *camera);
};

void BaseHeightMapRenderObjClass::renderTrees(CameraClass *camera)
{
    ((BaseHeightMapRenderTreesShim *)this)->render(camera);
}
