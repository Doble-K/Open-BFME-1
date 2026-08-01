class Object;

class FXListAtBonePosFXNugget
{
protected:
	void doFxAtBones(const Object *, int) const;
};

__declspec(naked) void FXListAtBonePosFXNugget::doFxAtBones(const Object *, int) const
{
	__asm {
		_emit 0E9h
		_emit 015h
		_emit 0CCh
		_emit 041h
		_emit 000h
	}
}
