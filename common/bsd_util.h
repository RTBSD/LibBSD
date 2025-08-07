/*
 * Copyright (C) 2025, RTBSD
 *
 * SPDX-License-Identifier: BSD 3-Clause
 */
#ifndef BSD_UTIL_H
#define BSD_UTIL_H

#if defined(__CC_ARM)
#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed))
#endif
#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT __packed struct
#endif
#ifndef __PACKED_UNION
#define __PACKED_UNION __packed union
#endif
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif
#elif defined(__GNUC__)
#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_UNION
#define __PACKED_UNION union __attribute__((packed, aligned(1)))
#endif
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif
#elif defined(__ICCARM__) || defined(__ICCRX__) || defined(__ICCRISCV__)
#ifndef __USED
#if defined(__ICCARM_V8) || defined(__ICCRISCV__)
#define __USED __attribute__((used))
#else
#define __USED __root
#endif
#endif

#ifndef __WEAK
#if defined(__ICCARM_V8) || defined(__ICCRISCV__)
#define __WEAK __attribute__((weak))
#else
#define __WEAK _Pragma("__weak")
#endif
#endif

#ifndef __PACKED
#if defined(__ICCARM_V8) || defined(__ICCRISCV__)
#define __PACKED __attribute__((packed, aligned(1)))
#else
/* Needs IAR language extensions */
#define __PACKED __packed
#endif
#endif

#ifndef __PACKED_STRUCT
#if defined(__ICCARM_V8) || defined(__ICCRISCV__)
#define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
#else
/* Needs IAR language extensions */
#define __PACKED_STRUCT __packed struct
#endif
#endif

#ifndef __PACKED_UNION
#if defined(__ICCARM_V8) || defined(__ICCRISCV__)
#define __PACKED_UNION union __attribute__((packed, aligned(1)))
#else
/* Needs IAR language extensions */
#define __PACKED_UNION __packed union
#endif
#endif

#ifndef __ALIGNED
#if defined(__ICCARM_V8) || defined(__ICCRISCV__)
#define __ALIGNED(x) __attribute__((aligned(x)))
#elif (__VER__ >= 7080000)
/* Needs IAR language extensions */
#define __ALIGNED(x) __attribute__((aligned(x)))
#else
#warning No compiler specific solution for __ALIGNED.__ALIGNED is ignored.
#define __ALIGNED(x)
#endif
#endif

#endif

#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif
#ifndef __ALIGN_END
#define __ALIGN_END __attribute__((aligned(4)))
#endif

#ifndef ARG_UNUSED
#define ARG_UNUSED(x) (void)(x)
#endif

#ifndef LO_BYTE
#define LO_BYTE(x) ((uint8_t)(x & 0x00FF))
#endif

#ifndef HI_BYTE
#define HI_BYTE(x) ((uint8_t)((x & 0xFF00) >> 8))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef BCD
#define BCD(x) ((((x) / 10) << 4) | ((x) % 10))
#endif

#ifdef BIT
#undef BIT
#define BIT(n) (1UL << (n))
#else
#define BIT(n) (1UL << (n))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) \
    ((int)((sizeof(array) / sizeof((array)[0]))))
#endif

#ifndef TRUE
#define TRUE 1U
#endif

#ifndef FALSE
#define FALSE 0U
#endif

/*
 * Return the number of elements in a statically-allocated array,
 * __x.
 */
#define	__arraycount(__x)	(sizeof(__x) / sizeof(__x[0]))

/*
 * The following macro is used to remove the volatile cast-away warnings
 * from gcc -Wcast-qual; as above it should be used with caution
 * because it can hide valid errors or warnings.  Valid uses include
 * making it possible to pass a volatile pointer to memset().
 * For the same reasons as above, we use unsigned long and not intptr_t.
 */
#define __UNVOLATILE(a)	((void *)(unsigned long)(volatile void *)(a))

#ifndef ___STRING
#define	___STRING(x)	__STRING(x)
#endif

#ifndef __ASSEMBLER__
/* __BIT(n): nth bit, where __BIT(0) == 0x1. */
#define	__BIT(__n)							      \
	(((__UINTMAX_TYPE__)(__n) >= __CHAR_BIT__ * sizeof(__UINTMAX_TYPE__)) \
	    ? 0								      \
	    : ((__UINTMAX_TYPE__)1 <<					      \
		(__UINTMAX_TYPE__)((__n) &				      \
		    (__CHAR_BIT__ * sizeof(__UINTMAX_TYPE__) - 1))))

/* __MASK(n): first n bits all set, where __MASK(4) == 0b1111. */
#define	__MASK(__n)	(__BIT(__n) - 1)

/* Macros for min/max. */
#define	__MIN(a,b)	((/*CONSTCOND*/(a)<=(b))?(a):(b))
#define	__MAX(a,b)	((/*CONSTCOND*/(a)>(b))?(a):(b))

/* __BITS(m, n): bits m through n, m < n. */
#define	__BITS(__m, __n)	\
	((__BIT(__MAX((__m), (__n)) + 1) - 1) ^ (__BIT(__MIN((__m), (__n))) - 1))
#endif /* !__ASSEMBLER__ */

/* find least significant bit that is set */
#define	__LOWEST_SET_BIT(__mask) ((((__mask) - 1) & (__mask)) ^ (__mask))

#define	__SHIFTOUT(__x, __mask)	(((__x) & (__mask)) / __LOWEST_SET_BIT(__mask))
#define	__SHIFTIN(__x, __mask) ((__x) * __LOWEST_SET_BIT(__mask))
#define	__SHIFTOUT_MASK(__mask) __SHIFTOUT((__mask), (__mask))

#define	__CTASSERT(x)		__CTASSERT0(x, __ctassert, __COUNTER__)
#define	__CTASSERT0(x, y, z)	__CTASSERT1(x, y, z)
#define	__CTASSERT1(x, y, z)	\
	struct y ## z ## _struct { \
		unsigned int y ## z : /*CONSTCOND*/(x) ? 1 : -1; \
	}

#define	CTASSERT(x)		__CTASSERT(x)

/*
 * Return the container of an embedded struct.  Given x = &c->f,
 * container_of(x, T, f) yields c, where T is the type of c.  Example:
 *
 *	struct foo { ... };
 *	struct bar {
 *		int b_x;
 *		struct foo b_foo;
 *		...
 *	};
 *
 *	struct bar b;
 *	struct foo *fp = b.b_foo;
 *
 * Now we can get at b from fp by:
 *
 *	struct bar *bp = container_of(fp, struct bar, b_foo);
 *
 * The 0*sizeof((PTR) - ...) causes the compiler to warn if the type of
 * *fp does not match the type of struct bar::b_foo.
 * We skip the validation for coverity runs to avoid warnings.
 */
#define __validate_container_of(PTR, TYPE, FIELD)			\
    (0 * sizeof((PTR) - &((TYPE *)(((char *)(PTR)) -			\
    offsetof(TYPE, FIELD)))->FIELD))
#define __validate_const_container_of(PTR, TYPE, FIELD)			\
    (0 * sizeof((PTR) - &((const TYPE *)(((const char *)(PTR)) -	\
    offsetof(TYPE, FIELD)))->FIELD))

#define	container_of(PTR, TYPE, FIELD)					\
    ((TYPE *)(((char *)(PTR)) - offsetof(TYPE, FIELD))			\
	+ __validate_container_of(PTR, TYPE, FIELD))
#define	const_container_of(PTR, TYPE, FIELD)				\
    ((const TYPE *)(((const char *)(PTR)) - offsetof(TYPE, FIELD))	\
	+ __validate_const_container_of(PTR, TYPE, FIELD))

#ifndef __aligned
#define __aligned(x) __attribute__((__aligned__(x)))
#endif

#ifndef __diagused
#define __diagused          __attribute__((__unused__))
#endif

/* Delete pseudo-keywords wherever they are not available or needed. */
#ifndef __dead
#define	__dead
#endif

/* The `const' in roundup() prevents gcc-3.3 from calling __divdi3 */
#ifndef rounddown
#define	rounddown(x, y)	(((x)/(y))*(y))
#endif

#ifndef rounddown2
#define rounddown2(x, y) ((x) & (~((y)-1))) /* if y is power of two */
#endif

#ifndef roundup
#define	roundup(x, y)	((((x)+((y)-1))/(y))*(y))  /* to any y */
#endif

#ifndef roundup2
#define roundup2(x, y) \
	(((x) + ((y)-1)) & (~((y)-1))) /* if y is powers of two */
#endif

#define powerof2(x)	((((x)-1)&(x))==0)

#ifndef nitems
#define	nitems(x)	(sizeof((x)) / sizeof((x)[0]))
#endif

#ifndef NBBY
# define NBBY 8		/* number of bits in a byte */
#endif

/* Bit map related macros.  */
#define setbit(a,i)     ((a)[(i)/NBBY] |= 1<<((i)%NBBY))
#define clrbit(a,i)     ((a)[(i)/NBBY] &= ~(1<<((i)%NBBY)))
#define isset(a,i)      ((a)[(i)/NBBY] & (1<<((i)%NBBY)))
#define isclr(a,i)      (((a)[(i)/NBBY] & (1<<((i)%NBBY))) == 0)

static inline u_long
ulmax(u_long a, u_long b)
{
	return (a > b ? a : b);
}
static inline u_long
ulmin(u_long a, u_long b)
{
	return (a < b ? a : b);
}

static inline u_int
uimax(u_int a, u_int b)
{
	return (a > b ? a : b);
}
static inline u_int
uimin(u_int a, u_int b)
{
	return (a < b ? a : b);
}

static inline int
imax(int a, int b)
{
	return (a > b ? a : b);
}
static inline int
imin(int a, int b)
{
	return (a < b ? a : b);
}

static inline __uintmax_t ummax(__uintmax_t a, __uintmax_t b)
{

	return (a > b ? a : b);
}
static inline __uintmax_t ummin(__uintmax_t a, __uintmax_t b)
{

	return (a < b ? a : b);
}

static inline u_int max(u_int a, u_int b) { return (a > b ? a : b); }
static inline u_int min(u_int a, u_int b) { return (a < b ? a : b); }

#endif