// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "line3d.h"

class RetailScaleDispatch
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
	virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74();
	virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84();
	virtual void v85(); virtual void v86(); virtual void v87(); virtual void v88(); virtual void v89();
	virtual void Scale(float, float, float);
};

class Line3DClassResetThunk : public Line3DClass
{
public:
	void Reset(const Vector3 & new_start, const Vector3 & new_end, float new_width);
};

void Line3DClassResetThunk::Reset(const Vector3 & new_start, const Vector3 & new_end, float new_width)
{
	float new_length = (new_end - new_start).Length();
	if (new_length == 0) {
		new_length = 0.001f;
	}
	float width_scale = new_width / Width;
	((RetailScaleDispatch *)this)->Scale((new_length / Length), width_scale, width_scale);
	Length = new_length;
	Width = new_width;

	Matrix3D transform(true);
	transform.Obj_Look_At(new_start, new_end, 0.0);
	Set_Transform(transform);
	Matrix3D inv;
	transform.Get_Orthogonal_Inverse(inv);

	Invalidate_Cached_Bounding_Volumes();

	RenderObjClass *container = Get_Container();
	if (container) container->Update_Obj_Space_Bounding_Volumes();
}
