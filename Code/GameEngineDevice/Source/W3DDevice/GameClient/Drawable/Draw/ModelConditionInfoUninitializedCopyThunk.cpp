// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ModelConditionInfo
{
public:
	struct HideShowSubObjInfo;
};

namespace _STL
{
	struct __false_type;

	template <class In, class Out>
	__declspec(naked) Out __uninitialized_copy(In, In, Out, const __false_type &)
	{
		__asm {
			_emit 0E9h
			_emit 0D5h
			_emit 071h
			_emit 03Ah
			_emit 000h
		}
	}

	template ModelConditionInfo::HideShowSubObjInfo *__uninitialized_copy<const ModelConditionInfo::HideShowSubObjInfo *, ModelConditionInfo::HideShowSubObjInfo *>(const ModelConditionInfo::HideShowSubObjInfo *, const ModelConditionInfo::HideShowSubObjInfo *, ModelConditionInfo::HideShowSubObjInfo *, const __false_type &);
}
