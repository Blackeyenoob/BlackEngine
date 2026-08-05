#pragma once

#include "Black/Core/PlatformDetection.h"

#include <memory>

// DLL export/import macros
#ifdef BK_PLATFORM_WINDOWS
	#ifdef BK_BUILD_DLL
		#define BLACK_API __declspec(dllexport)
	#else
		#define BLACK_API __declspec(dllimport)
	#endif
#else
	#error Black only supports Windows!
#endif

#ifdef BK_DEBUG
	#if defined(BK_PLATFORM_WINDOWS)
		#define BK_DEBUGBREAK() __debugbreak()
	#elif defined(BK_PLATFORM_LINUX)
		#include <signal.h>
		#define BK_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
#ifndef BK_ENABLE_ASSERTS
	#define BK_ENABLE_ASSERTS
#endif
#else
	#define BK_DEBUGBREAK()
#endif

#define BK_EXPAND_MACRO(x) x
#define BK_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define BK_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

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

#include "Black/Core/Log.h"
#include "Black/Core/Assert.h"
