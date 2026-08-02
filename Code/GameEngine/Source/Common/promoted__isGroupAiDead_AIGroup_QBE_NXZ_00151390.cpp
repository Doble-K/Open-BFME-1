// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Grok promote from masm_dumps — retail 0x00151390 size 50
// was: Code/masm_dumps/_cache__isGroupAiDead_AIGroup__QBE_NXZ_151390.asm

struct AIGroupNode {
	AIGroupNode *next;
	void *unused;
	void *object;
};

class AIGroup { public: bool isGroupAiDead(void) const; };

// ?isGroupAiDead@AIGroup@@QBE_NXZ
bool AIGroup::isGroupAiDead(void) const
{
	AIGroupNode *sentinel = *(AIGroupNode **)((const unsigned char *)this + 4);
	AIGroupNode *node = sentinel->next;
	bool dead = true;
	while (node != sentinel) {
		void *object = node->object;
		if (!object)
			goto next;
		if (!dead)
			goto set_false;
		if (*(const unsigned char *)((const unsigned char *)object + 0x344) & 1)
			goto set_true;
		goto set_false;
	set_true:
		dead = true;
		goto next;
	set_false:
		dead = false;
	next:
		node = node->next;
	}
	return dead;
}

