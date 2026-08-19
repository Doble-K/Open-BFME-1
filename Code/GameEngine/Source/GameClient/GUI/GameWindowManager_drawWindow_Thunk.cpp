// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;

enum
{
	WIN_ERR_OK = 0,
	WIN_ERR_INVALID_WINDOW = -2,
	WIN_STATUS_HIDDEN = 0x10,
	WIN_STATUS_BORDER = 0x1000,
	WIN_STATUS_SEE_THRU = 0x10000,
	GWS_SCROLL_LISTBOX = 0x20
};

class GameWindow;

class GameWindowDraw
{
public:
	virtual void slot0();
	virtual void draw(GameWindow *window, void *instanceData);
};

class GameWindow
{
public:
	virtual void slot0();
	virtual void slot4();
	virtual void slot8();
	virtual Int draw(void *instanceData);

	UnsignedInt winGetStyle();
	void winDrawBorder();

private:
	friend class GameWindowManager;

	GameWindowDraw *m_draw;
	UnsignedInt m_status;
	unsigned char m_pad0c[0x24];
	unsigned char m_instData[0x1c8];
	GameWindow *m_next;
	GameWindow *m_previous;
	GameWindow *m_parent;
	GameWindow *m_child;
};

class GameWindowManager
{
protected:
	Int drawWindow(GameWindow *window);
};

// ?drawWindow@GameWindowManager@@IAEHPAVGameWindow@@@Z
Int GameWindowManager::drawWindow(GameWindow *window)
{
	if (!window)
		return WIN_ERR_INVALID_WINDOW;

	if (!(window->m_status & WIN_STATUS_HIDDEN))
	{
		if (!(window->m_status & WIN_STATUS_SEE_THRU))
		{
			if (window->draw(window->m_instData) != 1 && window->m_draw)
				window->m_draw->draw(window, window->m_instData);
		}

		if (window->winGetStyle() & GWS_SCROLL_LISTBOX)
		{
			if ((window->m_status & WIN_STATUS_BORDER) &&
				!(window->m_status & WIN_STATUS_SEE_THRU))
				window->winDrawBorder();
		}

		GameWindow *child = window->m_child;
		while (child && child->m_next)
			child = child->m_next;

		for (; child; child = child->m_previous)
			drawWindow(child);

		if (!(window->winGetStyle() & GWS_SCROLL_LISTBOX))
		{
			if ((window->m_status & WIN_STATUS_BORDER) &&
				!(window->m_status & WIN_STATUS_SEE_THRU))
				window->winDrawBorder();
		}
	}

	return WIN_ERR_OK;
}
