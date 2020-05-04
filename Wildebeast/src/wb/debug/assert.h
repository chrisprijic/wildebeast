#pragma once

#include "wb/debug/log.h"

namespace wb {
    struct SourceInfo {
        char* File;
        long  Line;
        char* AssertText;
        char* AssertMessage;
    };

    class Assert {
    public:
        Assert(const SourceInfo& info) { logSource(info); }
        ~Assert() {}

        template<typename T>
        Assert& Variable(const char* const name, const T& value) {
            WB_CORE_ERROR("[ASSERT]     o Variable {} = {} ({})", name, value, typeid(T).name());
            return *this;
        }
    private:
        Assert& logSource(const SourceInfo& info) {
            WB_CORE_ERROR("[ASSERT] ASSERTION \"{}\" FAILED. {}", info.AssertText, info.AssertMessage);
            WB_CORE_ERROR("[ASSERT] In file \"{}\", on line: {}", info.File, info.Line);

            return*this;
        }
    };
}