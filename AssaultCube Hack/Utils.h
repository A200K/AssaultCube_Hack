#ifndef UTILS_H
#define UTILS_H

#include <windows.h>

namespace Utils
{

#define M_PI 3.141592653589793F

	bool IsValidPtr( void *pPointer );
	void *DetourFunction( void *pLocation, void *pDetour, DWORD dwLength );
	bool MemoryEdit( void *pMemory, void *pSource, DWORD dwLength );
}


#endif