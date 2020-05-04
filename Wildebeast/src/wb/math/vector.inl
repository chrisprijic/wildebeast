#pragma once

#include "wb/math/vector.h"

namespace wb {
// Helper code reduction macro to add assignment operators for the currently defined vec.
#define ADD_COMPOUND_ASSIGNMENT_OPERATORS \
COMPOUND_ASSIGNMENT(+= ); \
COMPOUND_ASSIGNMENT(-= ); \
COMPOUND_ASSIGNMENT(*= ); \
COMPOUND_ASSIGNMENT(/= ); \
COMPOUND_ASSIGNMENT(%= ); \
COMPOUND_ASSIGNMENT(&= ); \
COMPOUND_ASSIGNMENT(|= ); \
COMPOUND_ASSIGNMENT(^= ); \
COMPOUND_ASSIGNMENT(<<=); \
COMPOUND_ASSIGNMENT(>>=);

// Helper code reduction macro to add global operators for the currently defined vec.
#define ADD_GLOBAL_OPERATORS \
GLOBAL_OPERATOR(+ ); \
GLOBAL_OPERATOR(- ); \
GLOBAL_OPERATOR(* ); \
GLOBAL_OPERATOR(/ ); \
GLOBAL_OPERATOR(% ); \
GLOBAL_OPERATOR(& ); \
GLOBAL_OPERATOR(| ); \
GLOBAL_OPERATOR(^ ); \
GLOBAL_OPERATOR(<<); \
GLOBAL_OPERATOR(>>); 

/************************************************************************/
/* vec2 Implementation                                                  */
/************************************************************************/

    template<typename T>
    inline bool operator==(const vec2<T>& v, const vec2<T>& rhs) {
        return (v.x == rhs.x) && (v.y == rhs.y);
    }
    template<typename T>
    inline bool operator!=(const vec2<T>& v, const vec2<T>& rhs) {
        return (v..x != rhs.x) || (v.y != rhs.y);
    }

    // Code reduction for compound assignment operators.
#define COMPOUND_ASSIGNMENT(OP) \
template<typename T> \
inline vec2<T>& operator##OP##(vec2<T>& v, T a) { \
    v.x OP (a); \
    v.y OP (a); \
    return v; \
} \
template<typename T> \
inline vec2<T>& operator##OP##(vec2<T>& v, const vec2<T>& other) { \
    v.x OP (other.x); \
    v.y OP (other.y); \
    return v; \
}

// Add compound assignment operator code for vec2.
    ADD_COMPOUND_ASSIGNMENT_OPERATORS;

#undef COMPOUND_ASSIGNMENT

    // Code reduction for bitwise and arithmetic operators.
#define GLOBAL_OPERATOR(OP) \
template<typename T> \
inline vec2<T> operator##OP##(const vec2<T>& v, T a) { \
    return vec2<T>{v.x ##OP## a, v.y ##OP## a}; \
} \
template<typename T> \
inline vec2<T> operator##OP##(T a, const vec2<T>& v) { \
    return vec2<T>{a ##OP## v.x, a ##OP## v.y}; \
} \
template<typename T> \
inline vec2<T> operator##OP##(const vec2<T>& v1, const vec2<T>& v2) { \
    return vec2<T>{v1.x ##OP## v2.x, v1.y ##OP## v2.y}; \
}

// Add global operator code for vec2.
    ADD_GLOBAL_OPERATORS;

    template<typename T>
    inline vec2<T> operator~(const vec2<T>& v) {
        return vec2<T>(~v.x, ~v.y);
    }

    template<typename T>
    inline vec2<T> operator-(const vec2<T>& v) {
        return vec2<T>(-v.x, -v.y);
    }

    template<typename T>
    inline T dot(const vec2<T>& u, const vec2<T>& v) {
        return u.x * v.x + u.y * v.y;
    }

    template<typename T>
    inline real length(const vec2<T>& v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    template<typename T>
    inline T lengthSquared(const vec2<T>& v) {
        return (v.x * v.x + v.y * v.y);
    }

    template<typename T>
    inline rvec2 norm(const vec2<T>& v) {
        v /= length(v);
    }

    template<typename T>
    inline rvec2 getNorm(const vec2<T>& v) {
        return v / length(v);
    }

#undef GLOBAL_OPERATOR

    /************************************************************************/
    /* vec3 Implementation                                                  */
    /************************************************************************/

    template<typename T>
    inline bool operator==(const vec3<T>& v, const vec3<T>& rhs) {
        return (v.x == rhs.x) && (v.y == rhs.y) && (v.z == rhs.z);
    }
    template<typename T>
    inline bool operator!=(const vec3<T>& v, const vec3<T>& rhs) {
        return (v.x != rhs.x) || (v.y != rhs.y) || (v.z != rhs.z);
    }

    // Code reduction for compound assignment operators.
#define COMPOUND_ASSIGNMENT(OP) \
template<typename T> \
inline vec3<T>& operator##OP##(vec3<T>& v, T a) { \
    v.x OP (a); \
    v.y OP (a); \
    v.z OP (a); \
    return v; \
} \
template<typename T> \
inline vec3<T>& operator##OP##(vec3<T>& v, const vec3<T>& other) { \
    v.x OP (other.x); \
    v.y OP (other.y); \
    v.z OP (other.z); \
    return v; \
}

// Add compound assignment operator code for vec3.
    ADD_COMPOUND_ASSIGNMENT_OPERATORS;

#undef COMPOUND_ASSIGNMENT

    // Code reduction for bitwise and arithmetic operators.
#define GLOBAL_OPERATOR(OP) \
template<typename T> \
inline vec3<T> operator##OP##(const vec3<T>& v, T a) { \
    return vec3<T>{v.x ##OP## a, v.y ##OP## a, v.z ##OP## a}; \
} \
template<typename T> \
inline vec3<T> operator##OP##(T a, const vec3<T>& v) { \
    return vec3<T>{a ##OP## v.x, a ##OP## v.y, a ##OP## v.z}; \
} \
template<typename T> \
inline vec3<T> operator##OP##(const vec3<T>& v1, const vec3<T>& v3) { \
    return vec3<T>{v1.x ##OP## v3.x, v1.y ##OP## v3.y, v1.z ##OP## v3.z}; \
}

// Add global operator code for vec3.
    ADD_GLOBAL_OPERATORS;

    template<typename T>
    inline vec3<T> operator~(const vec3<T>& v) {
        return vec3<T>{~v.x, ~v.y, ~v.z};
    }

    template<typename T>
    inline vec3<T> operator-(const vec3<T>& v) {
        return vec3<T>{-v.x, -v.y, -v.z};
    }

#undef GLOBAL_OPERATOR

    template<typename T>
    inline T dot(const vec3<T>& u, const vec3<T>& v) {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    template<typename T>
    inline vec3<T> cross(const vec3<T>& u, const vec3<T>& v) {
        return vec3<T>{u.y* v.z - v.y * u.z, u.z* v.x - u.x * v.z, u.x* v.y - u.y * v.x};
    }

    template<typename T>
    inline real length(const vec3<T>& v) {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    template<typename T>
    inline T lengthSquared(const vec3<T>& v) {
        return (v.x * v.x + v.y * v.y + v.z * v.z);
    }

    template<typename T>
    inline rvec3 norm(const vec3<T>& v) {
        v /= length(v);
    }

    template<typename T>
    inline rvec3 getNorm(const vec3<T>& v) {
        return v / (1.0) * length(v);
    }

    /************************************************************************/
    /* vec4 Implementation                                                  */
    /************************************************************************/

    template<typename T>
    inline bool operator==(const vec4<T>& v, const vec4<T>& rhs) {
        return (v.x == rhs.x) && (v.y == rhs.y) && (v.z == rhs.z) && (v.w == rhs.w);
    }
    template<typename T>
    inline bool operator!=(const vec4<T>& v, const vec4<T>& rhs) {
        return (v.x != rhs.x) || (v.y != rhs.y) || (v.z != rhs.z) || (v.w != rhs.w);
    }

    // Code reduction for compound assignment operators.
#define COMPOUND_ASSIGNMENT(OP) \
template<typename T> \
inline vec4<T>& operator##OP##(vec4<T>& v, T a) { \
    v.x OP (a); \
    v.y OP (a); \
    v.z OP (a); \
    v.w OP (a); \
    return v; \
} \
template<typename T> \
inline vec4<T>& operator##OP##(vec4<T>& v, const vec4<T>& other) { \
    v.x OP (other.x); \
    v.y OP (other.y); \
    v.z OP (other.z); \
    v.w OP (other.w); \
    return v; \
}

// Add compound assignment operator code for vec4.
    ADD_COMPOUND_ASSIGNMENT_OPERATORS;

#undef COMPOUND_ASSIGNMENT

    // Code reduction for bitwise and arithmetic operators.
#define GLOBAL_OPERATOR(OP) \
template<typename T> \
inline vec4<T> operator##OP##(const vec4<T>& v, T a) { \
    return vec4<T>{v.x ##OP## a, v.y ##OP## a, v.z ##OP## a, v.w ##OP## a}; \
} \
template<typename T> \
inline vec4<T> operator##OP##(T a, const vec4<T>& v) { \
    return vec4<T>{a ##OP## v.x, a ##OP## v.y, a ##OP## v.z, a ##OP## v.w}; \
} \
template<typename T> \
inline vec4<T> operator##OP##(const vec4<T>& v1, const vec4<T>& v4) { \
    return vec4<T>{v1.x ##OP## v4.x, v1.y ##OP## v4.y, v1.z ##OP## v4.z, v1.w ##OP## v4.w}; \
}

// Add global operator code for vec4.
    ADD_GLOBAL_OPERATORS;

    template<typename T>
    inline vec4<T> operator~(const vec4<T>& v) {
        return vec4<T>(~v.x, ~v.y, ~v.z, ~v.w);
    }

    template<typename T>
    inline vec4<T> operator-(const vec4<T>& v) {
        return vec4<T>(-v.x, -v.y, -v.z, -v.w);
    }

#undef GLOBAL_OPERATOR

#undef ADD_COMPOUND_ASSIGNMENT_OPERATORS
#undef ADD_GLOBAL_OPERATORS

    template<typename T>
    inline T dot(const vec4<T>& u, const vec4<T>& v) {
        return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
    }

    template<typename T>
    inline real length(const vec4<T>& v) {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    template<typename T>
    inline T lengthSquared(const vec4<T>& v) {
        return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    template<typename T>
    inline rvec4 norm(const vec4<T>& v) {
        v /= length(v);
    }

    template<typename T>
    inline rvec4 getNorm(const vec4<T>& v) {
        return v / length(v);
    }
}