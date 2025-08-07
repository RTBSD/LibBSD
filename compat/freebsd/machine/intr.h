/*
 * Copyright (C) 2025, RTBSD
 *
 * SPDX-License-Identifier: BSD 3-Clause
 */
#ifndef _MACHINE_INTR_H
#define _MACHINE_INTR_H

#if !defined(__RTBSD_LIBBSD__)
#include <sys/systm.h>
#endif

#define	INTR_IRQ_INVALID	0xFFFFFFFF

enum intr_map_data_type {
	INTR_MAP_DATA_ACPI = 0,
	INTR_MAP_DATA_FDT,
	INTR_MAP_DATA_GPIO,
	INTR_MAP_DATA_MSI,

	/* Placeholders for platform specific types */
	INTR_MAP_DATA_PLAT_1 = 1000,
	INTR_MAP_DATA_PLAT_2,
	INTR_MAP_DATA_PLAT_3,
	INTR_MAP_DATA_PLAT_4,
	INTR_MAP_DATA_PLAT_5,
};

struct intr_map_data {
	size_t			len;
	enum intr_map_data_type	type;
};

struct intr_map_data_msi {
	struct intr_map_data	hdr;
	struct intr_irqsrc 	*isrc;
};

#if !defined(__RTBSD_LIBBSD__)
int intr_disable(void);
void intr_restore(int s);
int intr_setup_irq(device_t, struct resource *, driver_filter_t, driver_intr_t,
    void *, int, void **);
int intr_teardown_irq(device_t, struct resource *, void *);
int intr_describe_irq(device_t, struct resource *, void *, const char *);
int intr_activate_irq(device_t, struct resource *);
int intr_deactivate_irq(device_t, struct resource *);

struct intr_map_data *intr_alloc_map_data(enum intr_map_data_type, size_t, int);
u_int intr_map_irq(device_t, intptr_t, struct intr_map_data *);
#endif

#endif