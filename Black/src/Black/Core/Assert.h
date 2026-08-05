#pragma once

#include "Black/Core/Base.h"
#include "Black/Core/Log.h"
#include <filesystem>

#ifdef BK_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define BK_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { BK##type##ERROR(msg, __VA_ARGS__); BK_DEBUGBREAK(); } }
	#define BK_INTERNAL_ASSERT_WITH_MSG(type, check, ...) BK_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define BK_INTERNAL_ASSERT_NO_MSG(type, check) BK_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", BK_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define BK_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define BK_INTERNAL_ASSERT_GET_MACRO(...) BK_EXPAND_MACRO( BK_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, BK_INTERNAL_ASSERT_WITH_MSG, BK_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define BK_ASSERT(...) BK_EXPAND_MACRO( BK_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define BK_CORE_ASSERT(...) BK_EXPAND_MACRO( BK_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define BK_ASSERT(...)
	#define BK_CORE_ASSERT(...)
#endif
