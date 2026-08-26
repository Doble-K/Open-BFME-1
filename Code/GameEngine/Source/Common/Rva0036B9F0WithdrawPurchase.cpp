// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

class Money
{
public:
	unsigned int withdraw( unsigned int amount, bool playSound );
};

class Player
{
public:
	char m_unreconstructed00[ 0x48 ];
	Money m_money;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva0036BA60Cost
{
public:
	unsigned int costFor( Player *player, int index ) const;
};

class Rva0036BA60PurchaseContext
{
public:
	unsigned int withdrawPurchaseCost( const Rva0036BA60Cost *cost ) const;

private:
	char m_unreconstructed00[ 8 ];
	Object *m_object;
};

unsigned int Rva0036BA60PurchaseContext::withdrawPurchaseCost( const Rva0036BA60Cost *cost ) const
{
	if( !m_object )
		return 0;

	Player *player = m_object->getControllingPlayer();
	if( !player )
		return 0;

	unsigned int amount = cost->costFor( player, -1 );
	player->m_money.withdraw( amount, true );
	return amount;
}
