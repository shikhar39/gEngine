#pragma once

#ifdef EG_PLATFORM_WINDOWS
	#ifdef EG_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else	
		#define ENGINE_API __declspec(dllimport)
	#endif // EG_BUILD_DLL
#else
	#error Engine is currently supported by windows only
#endif // EG_PLATFORM_WINDOWS
