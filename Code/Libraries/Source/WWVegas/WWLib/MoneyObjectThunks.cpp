enum DisabledType
{
	DisabledTypePlaceholder
};

class Object
{
public:
	void setDisabledUntil(DisabledType, unsigned int);
};

class ObjectSetDisabledUntilShim
{
public:
	void setDisabledUntil(DisabledType type, unsigned int frame);
};

void Object::setDisabledUntil(DisabledType type, unsigned int frame)
{
	((ObjectSetDisabledUntilShim *)this)->setDisabledUntil(type, frame);
}
