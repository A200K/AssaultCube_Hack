#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <windows.h>
#include <iostream>
#include <GL/GL.h>
#include "Classes.h"
#include "Utils.h"

#pragma comment( lib, "OPENGL32.lib" )

using namespace AssaultCube;

namespace GameFunctions
{
	//Templates
	extern bool( __cdecl *SendToServer )( int type, const char *fmt, ... );

	extern float( __cdecl *GetFOV )( );

	extern void( __cdecl *RenderRadarIcon )( float x, float y, float s, int col, int row );

	extern void( *GiveDamage )( int damage, Player *target, Player *actor, int gun, bool gib, bool local );


	//Functions
	bool GotTeamMates( );

	void AddHudLine( char* pText );

	bool WorldToScreen( Vec3 vPos, Vec3 *pvOut );

	void EngineDrawString( char *pText, int x, int y, int r, int g, int b, int pUnknown = -1, int pUnknown2 = -1 );

	bool IsVisible( Vec3 vFrom, Vec3 vTo );

	void DrawString( int x, int y, int r, int g, int b, char *pText, ... );

	void DoAimBot( AssaultCube::Player *pLocalPlayer, Vec3 vAimPos );

	void GetAimAngles( Vec3 vLocalPosition, Vec3 vTargetPosition, float *pflYaw, float *pflPitch );

	void SendShot( Player *pTargePlayer, Player *pLocalPlayer, int pWeapon, bool bGib = false );

	void PatchRecoil( bool bNoRecoil );
}



#endif