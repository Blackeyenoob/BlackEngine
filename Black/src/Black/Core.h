#pragma once

#include <memory>

#ifdef BK_PLATFORM_WINDOWS
	#ifdef BK_BUILD_DLL
#define BLACK_API __declspec(dllexport)
	#else
#define BLACK_API __declspec(dllimport)
	#endif // BK_BUILD_DLL
#else
	#error Black only Supports Windows!
#endif // BK_PLATFORM_WINDOWS

namespace Black {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#ifdef BK_ENABLE_ASSERTS
	#define BK_ASSERT(x, ...) { if(!(x)) { BK_ERROR("Assertion Failed:{0}",__VA_ARGS__); __debugbreak(); } }
	#define BK_CORE_ASSERT(x, ...) { if(!(x)) { BK_CORE_ERROR("Assertion Failed:{0}",__VA_ARGS__); __debugbreak(); } }
#else
	#define BK_ASSERT(x, ...)
	#define BK_CORE_ASSERT(x, ...)
#endif // BK_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define BK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)