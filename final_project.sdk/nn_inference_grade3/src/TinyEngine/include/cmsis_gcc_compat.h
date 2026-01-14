/* CMSIS Compatibility Header for ARM Cortex-A9 GCC
 * Provides missing CMSIS definitions for Xilinx SDK
 */

#ifndef CMSIS_GCC_COMPAT_H
#define CMSIS_GCC_COMPAT_H

#include <stdint.h>

/* Define __STATIC_INLINE if not already defined */
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline __attribute__((always_inline))
#endif

/* Define __STATIC_FORCEINLINE if not already defined */
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE static inline __attribute__((always_inline))
#endif

/* Define __ALIGNED if not already defined */
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif

/* Define __PACKED if not already defined */
#ifndef __PACKED
#define __PACKED __attribute__((packed))
#endif

/* Count Leading Zeros - GCC builtin */
#ifndef __CLZ
__STATIC_FORCEINLINE uint8_t __CLZ(uint32_t value)
{
    if (value == 0U) {
        return 32U;
    }
    return (uint8_t)__builtin_clz(value);
}
#endif

/* Saturating Add */
#ifndef __QADD
__STATIC_FORCEINLINE int32_t __QADD(int32_t x, int32_t y)
{
    int64_t sum = (int64_t)x + (int64_t)y;
    if (sum > 0x7FFFFFFF) {
        return 0x7FFFFFFF;
    } else if (sum < -0x80000000LL) {
        return -0x80000000;
    }
    return (int32_t)sum;
}
#endif

/* Saturating Subtract */
#ifndef __QSUB
__STATIC_FORCEINLINE int32_t __QSUB(int32_t x, int32_t y)
{
    int64_t diff = (int64_t)x - (int64_t)y;
    if (diff > 0x7FFFFFFF) {
        return 0x7FFFFFFF;
    } else if (diff < -0x80000000LL) {
        return -0x80000000;
    }
    return (int32_t)diff;
}
#endif

/* Signed Saturate */
#ifndef __SSAT
__STATIC_FORCEINLINE int32_t __SSAT(int32_t val, uint32_t sat)
{
    int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    int32_t min = -1 - max;
    if (val > max) {
        return max;
    } else if (val < min) {
        return min;
    }
    return val;
}
#endif

/* Unsigned Saturate */
#ifndef __USAT
__STATIC_FORCEINLINE uint32_t __USAT(int32_t val, uint32_t sat)
{
    uint32_t max = (1U << sat) - 1U;
    if (val > (int32_t)max) {
        return max;
    } else if (val < 0) {
        return 0U;
    }
    return (uint32_t)val;
}
#endif

/* Signed Multiply Accumulate Long */
#ifndef __SMLAL
__STATIC_FORCEINLINE int64_t __SMLAL(int64_t acc, int32_t x, int32_t y)
{
    return acc + ((int64_t)x * (int64_t)y);
}
#endif

#endif /* CMSIS_GCC_COMPAT_H */
