#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Black {

	class BLACK_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
//引擎日志宏
#define BK_INIT ::Black::Log::Init()

//核心日志宏
#define BK_CORE_TRACE(...)       ::Black::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BK_CORE_INFO(...)        ::Black::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BK_CORE_WARN(...)		 ::Black::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BK_CORE_ERROR(...)		 ::Black::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BK_CORE_FATAL(...)		 ::Black::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//客户端日志宏
#define BK_TRACE(...)         ::Black::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BK_INFO(...)          ::Black::Log::GetClientLogger()->info(__VA_ARGS__)
#define BK_WARN(...)		  ::Black::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BK_ERROR(...)		  ::Black::Log::GetClientLogger()->error(__VA_ARGS__)
#define BK_FATAL(...)		  ::Black::Log::GetClientLogger()->fatal(__VA_ARGS__)