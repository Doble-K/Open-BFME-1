class Locomotor;
class LocomotorTemplate;

class LocomotorStore
{
public:
	Locomotor *newLocomotor(const LocomotorTemplate *) const;
};

__declspec(naked) Locomotor *LocomotorStore::newLocomotor(const LocomotorTemplate *) const
{
	__asm {
		_emit 0E9h
		_emit 03Ah
		_emit 04Fh
		_emit 01Ah
		_emit 000h
	}
}
