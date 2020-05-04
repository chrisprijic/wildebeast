#pragma once

#ifdef WB_DEBUG

#include "wb/core/types.h"
#include "wb/core/macros.h"
#include "wb/debug/assert.h"

// define breakpoint
#if defined(WB_PLATFORM_WINDOWS)
#define WB_BREAKPOINT() __debugbreak()
#else
#error "Platform doesn't support breakpoint yet!"
#endif


// Core assert implementation, call as "WB_ASSERT(statement, msg)(var1, var2, ...);"
#define WB_ASSERT_SOURCE_INFO(condition, msg) {__FILE__, __LINE__, condition, msg}
#define WB_ASSERT_IMPL_VAR(arg) .Variable(WB_TO_STRING(arg), arg)
#define WB_ASSERT_IMPL_VARS(...) WB_FOR_EACH_VA(WB_ASSERT_IMPL_VAR, __VA_ARGS__), WB_BREAKPOINT())
#define WB_ASSERT(condition, msg) (condition) ? WB_NOFUNCTION() : (Assert(WB_ASSERT_SOURCE_INFO(WB_TO_STRING(condition), msg)) WB_ASSERT_IMPL_VARS

#else
// define these to be empty when not debugging
#define WB_ASSERT(condition, msg)
#define WB_BREAKPOINT()

#endif // #ifdef WB_DEBUG