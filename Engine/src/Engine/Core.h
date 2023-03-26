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

#ifdef EG_ENABLE_ASSERTS
	#define EG_ASSERT(x, ...) { if(!(x)) { EG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EG_CORE_ASSERT(x, ...) { if(!(x)) { EG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define EG_ASSERT(x, ...)
	#define EG_CORE_ASSERT(x, ...)
#endif //EG_ENABLE_ASSERTS

#define BIT(x) (1 << x)