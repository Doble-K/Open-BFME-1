// cl: /DNDEBUG /MD /EHsc

// GameWindow::winSetInputFunc, retail 0x00478E70. Nineteen bytes: a null
// function pointer is ignored rather than stored, and the result is always
// WIN_ERR_OK - retail clears eax on both paths, so the caller cannot tell the
// two apart.

typedef int Int;
typedef unsigned int UnsignedInt;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

class GameWindow;

typedef WindowMsgHandledType (*GameWinInputFunc)( GameWindow *window, UnsignedInt msg, UnsignedInt data1, UnsignedInt data2 );

class GameWindow
{
public:
	Int winSetInputFunc( GameWinInputFunc input );

private:
	unsigned char m_unmodelled_00[ 0x1E0 ];
	GameWinInputFunc m_input;				// +0x1E0
};

// ?winSetInputFunc@GameWindow@@QAEHP6A?AW4WindowMsgHandledType@@PAV1@III@Z@Z
Int GameWindow::winSetInputFunc( GameWinInputFunc input )
{
	if( input )
		m_input = input;

	return 0;
}
