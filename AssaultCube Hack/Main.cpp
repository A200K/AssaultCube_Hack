#include <windows.h>
#include "Hooks.h"
#include "Utils.h"
#include "HackMain.h"

DWORD WINAPI MainThread( LPVOID lpParameter )
{
	//Hook an ingame function so we won't get conflicts with differnt opengl.dll versions, I used to hook wglSwapBuffers before

	OnInitialize( );

	dwDrawHudJmpBack = reinterpret_cast< DWORD >( Utils::DetourFunction( reinterpret_cast< void* >( OFFSET_GL_DRAWHUD_MIDFUNC ), gl_DrawHud, 13 ) );

	return EXIT_SUCCESS;
}

//Dll Entry Point
BOOL WINAPI DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_ATTACH )
	{
		CreateThread( 0, 0, MainThread, 0, 0, 0 );
	}

	return TRUE;
}
