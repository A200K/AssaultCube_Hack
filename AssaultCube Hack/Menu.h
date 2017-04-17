#ifndef MENU_H
#define MENU_H

#include <Windows.h>
#include <vector>

//Very simple menu lol

class CHack
{
public:
	CHack( char *pName, bool pEnabled );

	inline char *GetName( )
	{
		return this->m_Name;
	}

	inline bool GetEnabled( )
	{
		return this->m_Enabled;
	}


	inline void SetEnabled( bool bValue )
	{
		this->m_Enabled = bValue;
	}

	inline DWORD GetLastTick( )
	{
		return this->m_LastTick;
	}

	inline void SetLastTick( DWORD dwValue )
	{
		this->m_LastTick = dwValue;
	}

private:
	char m_Name[32];
	bool m_Enabled;
	DWORD m_LastTick;
};


class CMenu
{
public:

	CMenu( );

	void AddHack( CHack *pHack );

	int GetHackCount( );

	CHack *GetHack( char *pName );

	inline std::vector<CHack *> &GetHacks( )
	{
		return this->m_Hacks;
	}

	inline int GetSelectedIndex( )
	{
		return this->m_SelectedIndex;
	}

	inline void SetSelectedIndex( int iValue )
	{
		this->m_SelectedIndex = iValue;
	}

	inline bool GetIsVisible( )
	{
		return this->m_Visible;
	}

	inline void SetIsVisible( bool bValue )
	{
		this->m_Visible = bValue;
	}

private:
	std::vector<CHack *> m_Hacks;
	int m_SelectedIndex;
	bool m_Visible;
};

#endif