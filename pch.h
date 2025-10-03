#ifndef PCH_H
#define PCH_H

#include "targetver.h"

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