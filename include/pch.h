#ifndef PCH_H
#define PCH_H

// We are making heavy use of low-level C-APIs and are (hopefully ;)) aware
// of what where doing with C-style casts which is what C26461 warns about.
#pragma warning(disable : 26493)

#include "../res/targetver.h"

#include <map>

#include <Windows.h>
#include <Vfw.h>
#include <CommCtrl.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
    name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
    processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#endif