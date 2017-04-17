#include "Menu.h"

CHack::CHack( char *pName, bool pEnabled )
{
	strcpy_s( this->m_Name, pName );
	this->m_Enabled = pEnabled;
	this->m_LastTick = 0;
}

CMenu::CMenu( )
{
	this->m_SelectedIndex = 0;
	this->m_Visible = true;
}

void CMenu::AddHack( CHack* pHack )
{
	this->m_Hacks.push_back( pHack );
}

int CMenu::GetHackCount( )
{
	return this->m_Hacks.size( );
}

CHack *CMenu::GetHack( char* pName )
{

	for each( CHack *pHack in this->m_Hacks )
	{
		if( !strcmp( pName, pHack->GetName( ) ) )
			return pHack;
	}

	return nullptr;
}