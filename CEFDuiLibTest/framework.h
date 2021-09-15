// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO:  在此处引用程序需要的其他头文件
#define WM_AFTER_BROSWER_CREATE					WM_USER+0x1001

#define WM_LOADSTART							WM_USER+0x2000
#define WM_LOADEND								WM_USER+0x2001
#define WM_LOADPOPUP							WM_USER+0x2002
#define WM_TITLECHANGE							WM_USER+0x2003
