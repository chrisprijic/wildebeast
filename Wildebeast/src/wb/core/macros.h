#pragma once

// FOR loop magic for VA ARGS in macros....
#define WB_FE_0(P,X) P(X)
#define WB_FE_1(P,X,X1) P(X) WB_FE_0(P,X1)
#define WB_FE_2(P,X,X1,X2) P(X) WB_FE_1(P,X1,X2)
#define WB_FE_3(P,X,X1,X2,X3) P(X) WB_FE_2(P,X1,X2,X3)
#define WB_FE_4(P,X,X1,X2,X3,X4) P(X) WB_FE_3(P,X1,X2,X3,X4)
#define WB_FE_5(P,X,X1,X2,X3,X4,X5) P(X) WB_FE_4(P,X1,X2,X3,X4,X5)
#define WB_FE_6(P,X,X1,X2,X3,X4,X5,X6) P(X) WB_FE_5(P,X1,X2,X3,X4,X5,X6)
#define WB_FE_7(P,X,X1,X2,X3,X4,X5,X6,X7) P(X) WB_FE_6(P,X1,X2,X3,X4,X5,X6,X7)
#define WB_FE_8(P,X,X1,X2,X3,X4,X5,X6,X7,X8) P(X) WB_FE_7(P,X1,X2,X3,X4,X5,X6,X7,X8)
#define WB_FE_9(P,X,X1,X2,X3,X4,X5,X6,X7,X8,X9) P(X) WB_FE_8(P,X1,X2,X3,X4,X5,X6,X7,X8,X9)
#define WB_GET_FE_IMPL(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,NAME,...) NAME
#define WB_GET_FE(A) WB_GET_FE_IMPL A
#define WB_GET_FE_GLUE(x, y) x y
#define WB_FOR_EACH_VA(P,...) WB_GET_FE_GLUE(WB_GET_FE((__VA_ARGS__,WB_FE_9,WB_FE_8,WB_FE_7,WB_FE_6,WB_FE_5,WB_FE_4,WB_FE_3,WB_FE_2,WB_FE_1,WB_FE_0)), (P,__VA_ARGS__))


// defines a void (empty/useless) function
#define WB_NOFUNCTION(...) (void)0

// makes a string out of a macro or variable
#define WB_TO_STRING(x) #x