#include "HackMain.h"
#include "Menu.h"
#include "GameFunctions.h"
#include "RenderFunctions.h"

using namespace AssaultCube;
using namespace Utils;

CMenu *g_Menu = NULL;

void OnInitialize( )
{
	g_Menu = new CMenu( );

	g_Menu->AddHack( new CHack( "Player ESP", false ) );
	g_Menu->AddHack( new CHack( "Entity ESP", false ) );
	g_Menu->AddHack( new CHack( "Grenade ESP", false ) );
	g_Menu->AddHack( new CHack( "Aimbot", false ) );
	g_Menu->AddHack( new CHack( "Fly", false ) );
	g_Menu->AddHack( new CHack( "No Recoil", false ) );
	g_Menu->AddHack( new CHack( "Mass Kill", false ) );
	g_Menu->AddHack( new CHack( "Voice Spam", false ) );
	g_Menu->AddHack( new CHack( "Spam", false ) );
	g_Menu->AddHack( new CHack( "Quick Grenade", false ) );
	g_Menu->AddHack( new CHack( "Entity Magnet", false ) );

	GameFunctions::AddHudLine( "Hack loaded." );
}


void OnHackSet( CHack *pHack )
{
	//Disable fly mode once.
	if( !_stricmp( pHack->GetName( ), "Fly" ) && !pHack->GetEnabled( ) && Game::GetInstance( ) && Game::GetInstance( )->m_LocalPlayer )
	{
		Game::GetInstance( )->m_LocalPlayer->m_SpectateMode = SM_NONE;
	}

	//Patch Recoil
	if( !_stricmp( pHack->GetName( ), "No Recoil" ) )
	{
		GameFunctions::PatchRecoil( pHack->GetEnabled( ) );
	}

}

void MenuRender( )
{
	glPushMatrix( );

	float flScale = 0.8F;

	glScalef( flScale, flScale, 1.0F );

	int MENUX = 20;
	int MENUY = 180;
	int MENUYOFFSET = 20;
	int MENUOPTOFFSET = 200;

	GameFunctions::DrawString( MENUX, MENUY - 30, 255, 255, 255, "A200K's AssaultCube Hack" );

	int i = 0;
	for( auto item = g_Menu->GetHacks( ).begin( ); item != g_Menu->GetHacks( ).end( ); ++item )
	{
		CHack *pHack = *item._Ptr; //item->second;

		if( i == g_Menu->GetSelectedIndex( ) )
		{
			GameFunctions::DrawString( MENUX, MENUY + MENUYOFFSET * i, 255, 0, 0, pHack->GetName( ) );
			GameFunctions::DrawString( MENUX + MENUOPTOFFSET, MENUY + MENUYOFFSET * i, 255, 50, 50, pHack->GetEnabled( ) ? "On" : "Off" );
		}
		else
		{
			GameFunctions::DrawString( MENUX, MENUY + MENUYOFFSET * i, 255, 255, 255, pHack->GetName( ) );
			GameFunctions::DrawString( MENUX + MENUOPTOFFSET, MENUY + MENUYOFFSET * i, 150, 150, 150, pHack->GetEnabled( ) ? "On" : "Off" );
		}

		++i;
	}

	glScalef( 1 / flScale, 1 / flScale, 1.0F );

	glPopMatrix( );
}

void MenuInput( )
{

	if( GetAsyncKeyState( VK_DOWN ) & 1 )
	{
		if( g_Menu->GetSelectedIndex( ) < g_Menu->GetHacks( ).size( ) - 1 )
			g_Menu->SetSelectedIndex( g_Menu->GetSelectedIndex( ) + 1 );
	}

	if( GetAsyncKeyState( VK_UP ) & 1 )
	{
		if( g_Menu->GetSelectedIndex( ) > 0 )
			g_Menu->SetSelectedIndex( g_Menu->GetSelectedIndex( ) - 1 );
	}

	if( GetAsyncKeyState( VK_RIGHT ) & 1 )
	{
		CHack* pHack = g_Menu->GetHacks( ).at( g_Menu->GetSelectedIndex( ) );
		pHack->SetEnabled( true );
		OnHackSet( pHack );
	}

	if( GetAsyncKeyState( VK_LEFT ) & 1 )
	{
		CHack* pHack = g_Menu->GetHacks( ).at( g_Menu->GetSelectedIndex( ) );
		pHack->SetEnabled( false );
		OnHackSet( pHack );
	}

}


Player *GetAimbotTarget( Game *pGame, Player *pLocalPlayer )
{
	Player *pAimTarget = nullptr;
	float flClosestDist = INFINITY;

	for( int i = 0; i < pGame->m_PlayerCount; i++ )
	{
		Player* pPlayer = pGame->GetPlayer( i );
		if( !IsValidPtr( pPlayer ) )
			continue;

		if( pPlayer == pLocalPlayer )
			continue;

		if( pPlayer->m_State != CS_ALIVE )
			continue;

		if( pPlayer->m_Health <= 0 || pPlayer->m_Health > 100 )
			continue;

		if( pPlayer->m_HeadPos.x == 0 && pPlayer->m_HeadPos.y == 0 && pPlayer->m_HeadPos.z == 0 )
			continue;

		if( GameFunctions::GotTeamMates( ) )
		{
			if( pLocalPlayer->m_Team == pPlayer->m_Team )
				continue;
		}

		if( !GameFunctions::IsVisible( pLocalPlayer->m_HeadPos, pPlayer->m_HeadPos ) )
			continue;

		float flDist = pPlayer->m_HeadPos.dist( pLocalPlayer->m_HeadPos );

		if( flDist < flClosestDist )
		{
			flClosestDist = flDist;
			pAimTarget = pPlayer;
		}
	}

	return pAimTarget;
}

void DrawESP( Player *pTargetPlayer, Player *pLocalPlayer )
{
	Vec3 vHeadPos = pTargetPlayer->m_HeadPos;
	Vec3 vFootPos = pTargetPlayer->m_FootPos;

	vHeadPos.z += 0.8F; //Regular head pos is not high enough

	Vec3 vScreenHead, vScreenFoot;
	if( GameFunctions::WorldToScreen( vHeadPos, &vScreenHead ) && GameFunctions::WorldToScreen( vFootPos, &vScreenFoot ) )
	{
		float flHeight = abs( vScreenFoot.y - vScreenHead.y );
		float flWidth = flHeight / 2.0F;

		RenderFunctions::Color32 color = GameFunctions::IsVisible( pLocalPlayer->m_HeadPos, pTargetPlayer->m_HeadPos ) ? RenderFunctions::Color32( 1.0F, 1.0F, 0.0F, 1.0F ) : RenderFunctions::Color32( 1.0F, 0.0F, 0.0F, 1.0F );

		RenderFunctions::DrawRect( vScreenHead.x - flWidth / 2, vScreenHead.y, vScreenHead.x + flWidth / 2, vScreenHead.y + flHeight, color, false );

		RenderFunctions::DrawHealthBar( vScreenHead.x - flWidth / 2, vScreenHead.y - 14, flWidth, 6.0F, ( float )( ( float )pTargetPlayer->m_Health / 100.0F ), RenderFunctions::Color32( 0.0F, 1.0F, 0.0F, 1.0F ) );

		GameFunctions::DrawString( vScreenFoot.x - flWidth / 2, vScreenFoot.y + 4, ( int )( color.r * 255 ), ( int )( color.g * 255 ), ( int )( color.b * 255 ), pTargetPlayer->m_Name );
	}
}

void OnRenderFrame( )
{
	//Toggle Menu
	if( GetAsyncKeyState( VK_INSERT ) & 1 )
		g_Menu->SetIsVisible( !g_Menu->GetIsVisible( ) );

	if( g_Menu->GetIsVisible( ) )
	{
		MenuRender( );
		MenuInput( );
	}

	//Main Code

	Game *pGame = Game::GetInstance( );
	if( !IsValidPtr( pGame ) )
		return;

	Player *pLocalPlayer = pGame->m_LocalPlayer;
	if( IsValidPtr( pLocalPlayer ) )
	{
		Weapon *pLocalWeapon = pLocalPlayer->GetCurrentWeapon( );

		if( g_Menu->GetHack( "Aimbot" )->GetEnabled( ) )
		{
			if( !pLocalWeapon->m_Reloading )
			{
				if( GetAsyncKeyState( VK_RBUTTON ) & 0x8000 )
				{
					Player *pAimTarget = GetAimbotTarget( pGame, pLocalPlayer );
					if( IsValidPtr( pAimTarget ) )
					{
						Vec3 vAimPos = Vec3( pAimTarget->m_HeadPos.x, pAimTarget->m_HeadPos.y, pAimTarget->m_HeadPos.z );

						GameFunctions::DoAimBot( pLocalPlayer, vAimPos );

						//if ( bAutoShoot )
						//	pLocalPlayer->m_IsShooting = !pLocalPlayer->m_IsShooting;
					}
					//else
					//if ( bAutoShoot )
					//	pLocalPlayer->m_IsShooting = false;
				}
			}

		}

		if( g_Menu->GetHack( "Voice Spam" )->GetEnabled( ) )
		{
			if( g_Menu->GetHack( "Voice Spam" )->GetLastTick( ) < GetTickCount( ) )
			{
				g_Menu->GetHack( "Voice Spam" )->SetLastTick( GetTickCount( ) + 4100 );

				//Usually no normal player will see you are spamming, you won't hear the spam either. But for some reason some admins can still find our you are spamming lol.
				GameFunctions::SendToServer( SV_VOICECOM, "ri", S_COMINGINWITHTHEFLAG );
			}
		}

		if( g_Menu->GetHack( "Fly" )->GetEnabled( ) )
		{
			pLocalPlayer->m_SpectateMode = SM_FLY;
		}


		if( g_Menu->GetHack( "Spam" )->GetEnabled( ) )
		{
			//Spams "Player % switched to team %" into the chat lol
			if( g_Menu->GetHack( "Spam" )->GetLastTick( ) < GetTickCount( ) )
			{
				g_Menu->GetHack( "Spam" )->SetLastTick( GetTickCount( ) + 20 );

				GameFunctions::SendToServer( SV_SWITCHTEAM, "ri", TEAM_SPECT );
				GameFunctions::SendToServer( SV_TRYSPAWN, "r" );
			}
		}

		if( g_Menu->GetHack( "Quick Grenade" )->GetEnabled( ) )
			pLocalPlayer->m_Weapons[GUN_GRENADE]->m_Info->m_AttackDelay = 0;
		else
			pLocalPlayer->m_Weapons[GUN_GRENADE]->m_Info->m_AttackDelay = 650;

		if( g_Menu->GetHack( "Mass Kill" )->GetEnabled( ) )
		{
			for( int i = 0; i < pGame->m_PlayerCount; i++ )
			{
				Player* pPlayer = pGame->GetPlayer( i );
				if( !IsValidPtr( pPlayer ) )
					continue;

				if( pPlayer == pLocalPlayer )
					continue;

				if( pPlayer->m_State != CS_ALIVE )
					continue;

				if( pPlayer->m_Health <= 0 || pPlayer->m_Health > 100 )
					continue;

				if( pPlayer->m_HeadPos.x == 0 && pPlayer->m_HeadPos.y == 0 && pPlayer->m_HeadPos.z == 0 )
					continue;

				if( GameFunctions::GotTeamMates( ) )
				{
					if( pLocalPlayer->m_Team == pPlayer->m_Team ) //No Teammates
						continue;
				}

				if( GetAsyncKeyState( VK_RBUTTON ) )
				{
					if( g_Menu->GetHack( "Mass Kill" )->GetLastTick( ) < GetTickCount( ) )
					{

						g_Menu->GetHack( "Mass Kill" )->SetLastTick( GetTickCount( ) + pLocalPlayer->GetCurrentWeapon( )->m_Info->m_AttackDelay );

						if( pLocalPlayer->GetCurrentWeapon( )->m_Reloading == 0 && ( *pLocalPlayer->GetCurrentWeapon( )->m_Ammo > 0 || *pLocalPlayer->GetCurrentWeapon( )->m_AmmoInReserve ) )
						{
							if( ( *pLocalPlayer->GetCurrentWeapon( )->m_Ammo )-- <= 0 )
							{
								g_Menu->GetHack( "Mass Kill" )->SetLastTick( GetTickCount( ) + pLocalPlayer->GetCurrentWeapon( )->m_Info->m_ReloadTime );
							}
							else
							{
								// Take care with shotgun though, there are special checks and handling for this one.
								GameFunctions::SendShot( pPlayer, pLocalPlayer, pLocalPlayer->m_GunSelect ); //Only works in multiplayer
							}
						}
					}
				}
			}
		}

		if( g_Menu->GetHack( "Entity Magnet" )->GetEnabled( ) )
		{
			EntityList *pEntities = EntityList::GetInstance( );
			if( IsValidPtr( pEntities ) )
			{
				for( int i = 0; i < pEntities->m_EntityCount; i++ )
				{
					Entity *pEntity = pEntities->GetEntity( i );
					if( !IsValidPtr( pEntity ) )
						continue;

					// Only spawned items
					if( pEntity->spawned == FALSE )
						continue;

					float flNewZ = ( float )( 1 + sinf( *reinterpret_cast< DWORD* >( OFFSET_LASTMILLIS ) / 100.0f + pEntity->x + pEntity->y ) / 20 );
					// fix height according to the map data
					flNewZ += ( &( *reinterpret_cast< sqr** >( OFFSET_WORLD ) )[( ( pEntity->y ) << ( *reinterpret_cast< DWORD* >( OFFSET_SFACTOR ) ) ) + ( pEntity->x )] )->floor + pEntity->attr1;

					Vec3 vPos = Vec3( pEntity->x, pEntity->y, flNewZ );

					float flDistance = pLocalPlayer->m_FootPos.dist( vPos );

					// Sadly the server sided anti cheat detects and reports you if the range is >= 10

					if( flDistance < 10.0 )
					{
						GameFunctions::SendToServer( SV_ITEMPICKUP, "ri", i );
					}
				}
			}
		}

		if( g_Menu->GetHack( "Grenade ESP" )->GetEnabled( ) )
		{
			BounceEntityList *pEntityList = BounceEntityList::GetInstance( );

			for( int i = 0; i < pEntityList->m_EntityCount; i++ )
			{
				BounceEntity *pEntity = pEntityList->GetEntity( i );
				if( !IsValidPtr( pEntity ) )
					continue;

				if( pEntity->m_Bouncetype != BT_NADE )
					continue;

				Vec3 vScreen;
				if( GameFunctions::WorldToScreen( pEntity->m_HeadPos, &vScreen ) )
				{
					DWORD dwCurrentMillis = *reinterpret_cast< DWORD* >( OFFSET_LASTMILLIS );
					DWORD dwExplodeTime = pEntity->m_Millis + pEntity->m_TimeToLive;

					DWORD dwTimeLeft = dwExplodeTime - dwCurrentMillis;

					GameFunctions::DrawString( vScreen.x, vScreen.y, 255, 128, 100, "[%ims]", dwTimeLeft );
				}
			}
		}

		if( g_Menu->GetHack( "Player ESP" )->GetEnabled( ) )
		{
			for( int i = 0; i < pGame->m_PlayerCount; i++ )
			{
				Player* pPlayer = pGame->GetPlayer( i );
				if( !IsValidPtr( pPlayer ) )
					continue;

				if( pPlayer == pLocalPlayer )
					continue;

				if( pPlayer->m_State != CS_ALIVE )
					continue;

				if( pPlayer->m_Health <= 0 || pPlayer->m_Health > 100 )
					continue;

				if( pPlayer->m_HeadPos.x == 0 && pPlayer->m_HeadPos.y == 0 && pPlayer->m_HeadPos.z == 0 )
					continue;

				if( GameFunctions::GotTeamMates( ) )
				{
					if( pLocalPlayer->m_Team == pPlayer->m_Team ) //No Teammates
						continue;
				}

				DrawESP( pPlayer, pLocalPlayer );
			}
		}

		if( g_Menu->GetHack( "Entity ESP" )->GetEnabled( ) )
		{
			EntityList *pEntities = EntityList::GetInstance( );
			if( IsValidPtr( pEntities ) )
			{
				for( int i = 0; i < pEntities->m_EntityCount; i++ )
				{
					Entity *pEntity = pEntities->GetEntity( i );
					if( !IsValidPtr( pEntity ) )
						continue;

					// Only visible items
					if( pEntity->spawned == FALSE )
						continue;

					// very ugly way but this is what the engine does because the items bounce slightly up and down
					float flNewZ = ( float )( 1 + sinf( *reinterpret_cast< DWORD* >( OFFSET_LASTMILLIS ) / 100.0f + pEntity->x + pEntity->y ) / 20 );
					// fix height according to the map data
					flNewZ += ( &( *reinterpret_cast< sqr** >( OFFSET_WORLD ) )[( ( pEntity->y ) << ( *reinterpret_cast< DWORD* >( OFFSET_SFACTOR ) ) ) + ( pEntity->x )] )->floor + pEntity->attr1;

					Vec3 vPos = Vec3( pEntity->x, pEntity->y, flNewZ );

					Vec3 vScreen;
					if( GameFunctions::WorldToScreen( vPos, &vScreen ) )
					{
						//Entities seem to spawn right above the gound, so the actual entity pos might be lower than this, but if you press E you will see the actual entity point, too lazy to calculate the real Z pos.

						if( pEntity->type == I_HEALTH )
							GameFunctions::DrawString( vScreen.x, vScreen.y, 255, 255, 255, "[Health]" );
						else if( pEntity->type == I_AMMO || pEntity->type == I_CLIPS )
							GameFunctions::DrawString( vScreen.x, vScreen.y, 255, 255, 255, "[Ammo]" );
						else if( pEntity->type == I_AKIMBO )
							GameFunctions::DrawString( vScreen.x, vScreen.y, 255, 255, 255, "[Akimbo]" );
						else if( pEntity->type == I_ARMOUR || pEntity->type == I_HELMET )
							GameFunctions::DrawString( vScreen.x, vScreen.y, 255, 255, 255, "[Armor]" );
						else if( pEntity->type == CTF_FLAG )
							GameFunctions::DrawString( vScreen.x, vScreen.y, 255, 255, 255, "[Flag]" );
						else if( pEntity->type == I_GRENADE )
							GameFunctions::DrawString( vScreen.x, vScreen.y, 255, 255, 255, "[Grenade]" );
						//else
						//	GameFunctions::DrawString( vScreen.x, vScreen.y, 255, 255, 255, "[%X]", pEntity );
					}
				}
			}
		}
	}

}
