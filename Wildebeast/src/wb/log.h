#pragma once

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace wb {

	class WB_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define WB_CORE_TRACE(...)    ::wb::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WB_CORE_INFO(...)     ::wb::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WB_CORE_WARN(...)     ::wb::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WB_CORE_ERROR(...)    ::wb::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WB_CORE_FATAL(...)    ::wb::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define WB_TRACE(...)	      ::wb::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WB_INFO(...)	      ::wb::Log::GetClientLogger()->info(__VA_ARGS__)
#define WB_WARN(...)	      ::wb::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WB_ERROR(...)	      ::wb::Log::GetClientLogger()->error(__VA_ARGS__)
#define WB_FATAL(...)	      ::wb::Log::GetClientLogger()->fatal(__VA_ARGS__)