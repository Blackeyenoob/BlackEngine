#pragma once

#ifdef BK_PLATFORM_WINDOWS
	#ifdef BK_BUILD_DLL
#define BLACK_API __declspec(dllexport)
	#else
#define BLACK_API __declspec(dllimport)
	#endif // DEBUG
#else
	#error Black only Supports Windows!
#endif // BK_PLATFORM_WINDOWS

#define BIT(x) (1 << x)