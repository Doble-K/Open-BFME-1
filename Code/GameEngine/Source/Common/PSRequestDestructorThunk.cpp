// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <string>

class PSPlayerStats
{
public:
	~PSPlayerStats();

private:
	char m_data[0x1C4];
};

class PSRequest
{
public:
	~PSRequest();

private:
	int m_requestType;
	PSPlayerStats m_player;
	std::string m_cdkey;
	std::string m_nick;
	std::string m_password;
	std::string m_email;
	int m_addDiscon;
	int m_addDesync;
	int m_lastHouse;
	std::string m_results;
};

PSRequest::~PSRequest()
{
}
