// cl: /O2 /Ob0

class Object
{
public:
	bool isUsingAirborneLocomotor() const;
};

bool __stdcall rva001dc880(Object *obj)
{
	return obj->isUsingAirborneLocomotor();
}
