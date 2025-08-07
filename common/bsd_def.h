/*
 * Copyright (C) 2025, RTBSD
 *
 * SPDX-License-Identifier: BSD 3-Clause
 */
#ifndef BSD_DEF_H
#define BSD_DEF_H

/* macro configuration */
#define LIBBSD_WITH_NEW_LIBC

/* macro stub */
#define	__KERNEL_RCSID(_n, _s)

#ifndef __FreeBSD_version
#define	__FreeBSD_version 1400000
#endif

/* build bsd code as kernel */
#ifndef _KERNEL
#define _KERNEL
#endif

#ifndef INTRNG
#define INTRNG
#endif

#ifdef SMP
#ifndef MAXCPU
#define MAXCPU		1024
#endif
#else
#define MAXCPU		1
#endif

#ifndef MAXPATHLEN
#define MAXPATHLEN  256U
#endif

#ifndef MAXCOMLEN
#define MAXCOMLEN   16
#endif

#ifndef __weak_alias
#define __weak_alias(...)
#endif

#define __CHAR_BIT CHAR_BIT
#define __INT_MAX INT_MAX
#define __SIZE_T_MAX __SIZE_MAX__

#endif