//
// Created by overlord on 6/26/25.
//

#ifndef BASE_H
#define BASE_H

#include <cstdint>
// Short typedefs for fixed-width integers
using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

// Floating point typedefs
using f32 = float;
using f64 = double;

// Useful macros
#define BIT(x) (1 << (x))
#define UNUSED(x) (void)(x)
#define TODO() assert(false && "TODO: Implement this!")
#define PANIC(msg) do { std::cerr << "PANIC: " << msg << std::endl; std::abort(); } while(0)

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
#   define PLATFORM_WINDOWS 1
#else
#   define PLATFORM_WINDOWS 0
#endif

#if defined(__linux__)
#   define PLATFORM_LINUX 1
#else
#   define PLATFORM_LINUX 0
#endif

#if defined(__APPLE__)
#   define PLATFORM_MAC 1
#else
#   define PLATFORM_MAC 0
#endif

// Debug macro
#ifndef NDEBUG
#   define DEBUG 1
#else
#   define DEBUG 0
#endif

// Inline helper
#ifndef FORCE_INLINE
#   ifdef _MSC_VER
#       define FORCE_INLINE __forceinline
#   elif defined(__GNUC__) || defined(__clang__)
#       define FORCE_INLINE inline __attribute__((always_inline))
#   else
#       define FORCE_INLINE inline
#   endif
#endif

// Defer macro (C++17 and up)
#if __cplusplus >= 201703L
#   include <utility>
#   define DEFER(code) auto UNIQUE_NAME(_defer_) = ::DeferHelper([&](){code;})

template<typename F>
struct DeferHelper {
    F f;

    explicit DeferHelper(F f) : f(f) {
    }

    ~DeferHelper() { f(); }
};

#   define UNIQUE_NAME(base) CONCAT(base, __COUNTER__)
#   define CONCAT(a, b) CONCAT_INNER(a, b)
#   define CONCAT_INNER(a, b) a##b
#endif

// Example: DEFER({ std::cout << "End of scope!\n"; });


#endif //BASE_H
