enum DisabledType
{
	DisabledTypePlaceholder
};

class Money
{
public:
	void deposit(unsigned int, bool);
};

class Object
{
public:
	void setDisabledUntil(DisabledType, unsigned int);
};

class MoneyDepositShim
{
public:
	void deposit(unsigned int amount, bool playSound);
};

class ObjectSetDisabledUntilShim
{
public:
	void setDisabledUntil(DisabledType type, unsigned int frame);
};

void Money::deposit(unsigned int amount, bool playSound)
{
	((MoneyDepositShim *)this)->deposit(amount, playSound);
}

void Object::setDisabledUntil(DisabledType type, unsigned int frame)
{
	((ObjectSetDisabledUntilShim *)this)->setDisabledUntil(type, frame);
}
