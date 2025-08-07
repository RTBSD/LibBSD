/*
 * Copyright (C) 2025, RTBSD
 *
 * SPDX-License-Identifier: BSD 3-Clause
 */
#ifndef LIBBSD_COMPAT_H
#define LIBBSD_COMPAT_H

#undef max
#undef min
#undef ALIGN
#undef rounddown
#undef roundup
#undef UL

#include <bsd_def.h>

#if defined(LIBBSD_WITH_NEW_LIBC)
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <strings.h> /*strcasecmp */
#include <stdatomic.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include <inttypes.h>
#endif

#include <bsd_errno.h>
#include <bsd_util.h>
#include <bsd_stub.h>
#include <bsd_osal.h>
#include <sys/ctype.h>

#if defined(LIBBSD_FREEBSD) /* FreeBSD basic compat header files */
typedef	struct _device	*device_t;

#define BSD_DEVICE_NAME device_get_nameunit
#define BSD_DEVICE_UNIT device_get_unit

#include <sys/queue.h>
#include <sys/endian.h>
#include <sys/kobj.h>
#include <sys/sbuf.h>
#include <sys/linker_set.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/bus.h>
#include <sys/_bus_dma.h>
#include <sys/rman.h>
#include <freebsd/local/bus_if.h>
#include <freebsd/local/device_if.h>
#include <freebsd/machine/bus.h>
#include <freebsd/machine/resource.h>
#include <freebsd/machine/intr.h>

#if defined(LIBBSD_FREEBSD_FDT) && (FDT) /* FreeBSD compat header files for FDT */
#include <dev/ofw/openfirm.h>
#include <contrib/libfdt/libfdt.h>
#include <dev/fdt/fdt_common.h>
#include <dev/ofw/ofwvar.h>
#include <dev/ofw/ofw_bus.h>
#include <dev/ofw/ofw_bus_subr.h>
#include <dev/ofw/ofwpci.h>
#include <dev/ofw/ofw_pci.h>
#include <dev/ofw/ofw_subr.h>
#include <dev/pci/pcivar.h>
#include <dev/pci/pcireg.h>
#include <dev/pci/pcib_private.h>
#include <freebsd/local/pci_if.h>
#include <freebsd/local/pcib_if.h>
#include <freebsd/local/ofw_if.h>
#include <dev/fdt/simplebus.h>
#endif /* LIBBSD_FREEBSD_FDT */

#if defined(LIBBSD_FREEBSD_ACPI) && (DEV_ACPI) /* FreeBSD compat header files for ACPI */
#include <arm64/include/acpica_machdep.h>
#include <contrib/dev/acpica/include/acpi.h>
#include <contrib/dev/acpica/include/accommon.h>
#include <contrib/dev/acpica/include/acdebug.h>
#include <freebsd/local/acpi_bus_if.h>
#include <freebsd/local/acpi_if.h>
#include <dev/acpica/acpiio.h>
#include <dev/acpica/acpivar.h>
#endif /* LIBBSD_FREEBSD_ACPI */
#endif /* LIBBSD_FREEBSD */

#if defined(LIBBSD_NETBSD) /* NetBSD basic compat header files */
struct device;
typedef struct device *device_t;

#define BSD_DEVICE_NAME  device_xname
#define BSD_DEVICE_UNIT  device_unit

#include <libnetbsd/sys/sys/queue.h>
#include <libnetbsd/sys/sys/device_if.h>
#include <libnetbsd/sys/sys/device.h>
#include <libnetbsd/sys/sys/device_calls.h>
#include <libnetbsd/sys/lib/libkern/strlist.h>
#include <libnetbsd/sys/sys/cpu.h>

#if defined(LIBBSD_NETBSD_ACPI) && (DEV_ACPI)  /* NetBSD compat header files for ACPI */
#include <contrib/dev/acpica/include/acpi.h>
#include <contrib/dev/acpica/include/accommon.h>
#include <libnetbsd/sys/dev/acpi/acpica.h>
#include <libnetbsd/sys/dev/acpi/acpi_util.h>
#include <libnetbsd/sys/dev/acpi/acpireg.h>
#include <libnetbsd/sys/dev/acpi/acpivar.h>
#include <libnetbsd/sys/dev/acpi/acpi_intr.h>
#endif /* LIBBSD_NETBSD_ACPI */
#endif /* LIBBSD_NETBSD */

#endif