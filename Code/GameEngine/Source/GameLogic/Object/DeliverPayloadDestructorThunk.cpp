// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class DeliverPayloadNugget
{
public:
	class Payload
	{
	public:
		~Payload();
	};
};

__declspec(naked) DeliverPayloadNugget::Payload::~Payload()
{
	__asm {
		_emit 0E9h
		_emit 0F1h
		_emit 01Ah
		_emit 032h
		_emit 000h
	}
}
