/*
 * Copyright (C) 2025, RTBSD
 *
 * SPDX-License-Identifier: BSD 3-Clause
 */
#ifndef BSD_CORE_H
#define BSD_CORE_H

int bsd_system_init(void);
int bsd_display_acpi_table(void);
int bsd_display_fdt_table(void);
int bsd_get_acpi_cppc_cpu_frequency(uint32_t cpu_id, uint32_t *freq);
int bsd_set_acpi_cppc_cpu_frequency(uint32_t cpu_id, uint32_t freq);
int bsd_get_acpi_cpu_temperature(uint32_t *temp);

#endif