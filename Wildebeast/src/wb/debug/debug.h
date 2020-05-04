#pragma once

#ifdef WB_DEBUG

#include "wb/core/types.h"
#include "wb/debug/log.h"
#include <sstream>

#ifdef WB_PLATFORM_WINDOWS
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif


// FOR loop magic for VA ARGS in macros....
#define FE_0(P,X) P(X)
#define FE_1(P,X,X1) P(X) FE_0(P,X1)
#define FE_2(P,X,X1,X2) P(X) FE_1(P,X1,X2)
#define FE_3(P,X,X1,X2,X3) P(X) FE_2(P,X1,X2,X3)
#define FE_4(P,X,X1,X2,X3,X4) P(X) FE_3(P,X1,X2,X3,X4)
#define FE_5(P,X,X1,X2,X3,X4,X5) P(X) FE_4(P,X1,X2,X3,X4,X5)
#define FE_6(P,X,X1,X2,X3,X4,X5,X6) P(X) FE_5(P,X1,X2,X3,X4,X5,X6)
#define FE_7(P,X,X1,X2,X3,X4,X5,X6,X7) P(X) FE_6(P,X1,X2,X3,X4,X5,X6,X7)
#define FE_8(P,X,X1,X2,X3,X4,X5,X6,X7,X8) P(X) FE_7(P,X1,X2,X3,X4,X5,X6,X7,X8)
#define FE_9(P,X,X1,X2,X3,X4,X5,X6,X7,X8,X9) P(X) FE_8(P,X1,X2,X3,X4,X5,X6,X7,X8,X9)
#define GET_FE_IMPL(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,NAME,...) NAME
#define GET_FE(A) GET_FE_IMPL A
#define GET_FE_GLUE(x, y) x y
#define FOR_EACH_VA(P,...) GET_FE_GLUE(GET_FE((__VA_ARGS__,FE_9,FE_8,FE_7,FE_6,FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)), (P,__VA_ARGS__))


// defines a void (empty/useless) function
#define NOFUNCTION(...) (void)0

// makes a string out of a macro or variable
#define TO_STRING(x) #x


// asserts condition, and can provide additional variables to print out values.
#define ASSERT_IMPL_VAR(arg) "     o [Variable]: " << TO_STRING(arg) << " = " << arg << "\n" << 
#define ASSERT_IMPL_VARS(...) FOR_EACH_VA(ASSERT_IMPL_VAR, __VA_ARGS__) "")).str().c_str());
#define ASSERT(c, msg) std::stringstream ss; (c) ? NOFUNCTION() : Log::LogAssert("ASSERTION FAILURE: {}", (static_cast<std::stringstream&>(ss << "Assertion '" << TO_STRING(c) << "' failed. " << msg << "\n    FILE: " << __FILENAME__ << "\n    LINE: " << __LINE__ << "\n" << ASSERT_IMPL_VARS

#endif