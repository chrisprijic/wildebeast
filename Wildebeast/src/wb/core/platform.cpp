#include "wbpch.h"
#include "wb/core/platform.h"

#ifdef WB_PLATFORM_WINDOWS
#include "platform/windows/windows_platform.h"
#endif

namespace wb {
    Platform* Platform::Create() {
#ifdef WB_PLATFORM_WINDOWS
        return new WindowsPlatform();
#else
        return nullptr;
#endif
    }
}