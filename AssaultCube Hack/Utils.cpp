#include "Utils.h"

namespace Utils
{
	bool IsValidPtr( void *pPointer )
	{
		if( pPointer && HIWORD( pPointer ) )
		{
			if( !IsBadReadPtr( pPointer, sizeof( DWORD_PTR ) ) )
				return true;
		}
		return false;
	}

	void *DetourFunction( void *pLocation, void *pDetour, DWORD dwLength )
	{
		void *pTrampoline = VirtualAlloc( NULL, dwLength + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );

		memcpy( pTrampoline, pLocation, dwLength );

		*reinterpret_cast< BYTE* >( reinterpret_cast< DWORD >( pTrampoline ) + dwLength ) = 0xE9;
		*reinterpret_cast< DWORD* >( reinterpret_cast< DWORD >( pTrampoline ) + dwLength + 1 ) = reinterpret_cast< DWORD >( pLocation ) - ( reinterpret_cast< DWORD >( pTrampoline ) + dwLength );

		DWORD dwOldProtection = NULL;
		VirtualProtect( pLocation, dwLength, PAGE_EXECUTE_READWRITE, &dwOldProtection );

		*reinterpret_cast< BYTE* >( reinterpret_cast< DWORD >( pLocation ) ) = 0xE9;
		*reinterpret_cast< DWORD* >( reinterpret_cast< DWORD >( pLocation ) + 1 ) = reinterpret_cast< DWORD >( pDetour ) - ( reinterpret_cast< DWORD >( pLocation ) + 5 );

		for( size_t i = 5; i < dwLength; i++ )
			*reinterpret_cast< BYTE* >( reinterpret_cast< DWORD >( pLocation ) + i ) = 0x90;

		VirtualProtect( pLocation, dwLength, dwOldProtection, NULL );

		return pTrampoline;
	}

	bool MemoryEdit( void *pMemory, void *pSource, DWORD dwLength )
	{
		DWORD dwOldProtect = NULL;
		if( VirtualProtect( pMemory, dwLength, PAGE_EXECUTE_READWRITE, &dwOldProtect ) )
		{
			for( size_t i = 0; i < dwLength; i++ )
				*reinterpret_cast< BYTE* >( reinterpret_cast< DWORD >( pMemory ) + i ) = *reinterpret_cast< BYTE* >( reinterpret_cast< DWORD >( pSource ) + i );

			VirtualProtect( pMemory, dwLength, dwOldProtect, 0 );
			return true;
		}
		return false;
	}
}


