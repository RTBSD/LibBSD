/*
 * This file is @generated automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   freebsd/sys/dev/acpica/acpi_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#define LIBBSD_FREEBSD
#define LIBBSD_FREEBSD_ACPI
#include <bsd_compat.h>

static int
acpi_generic_id_probe(device_t bus, device_t dev, char **ids,
    char **match)
{
        return (ENXIO);
}

struct kobjop_desc acpi_id_probe_desc = {
        0, { &acpi_id_probe_desc, (kobjop_t)acpi_generic_id_probe }
};

struct kobjop_desc acpi_evaluate_object_desc = {
        0, { &acpi_evaluate_object_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc acpi_get_property_desc = {
        0, { &acpi_get_property_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc acpi_pwr_for_sleep_desc = {
        0, { &acpi_pwr_for_sleep_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc acpi_scan_children_desc = {
        0, { &acpi_scan_children_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc acpi_get_features_desc = {
        0, { &acpi_get_features_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc acpi_ec_read_desc = {
        0, { &acpi_ec_read_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc acpi_ec_write_desc = {
        0, { &acpi_ec_write_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc acpi_batt_get_info_desc = {
        0, { &acpi_batt_get_info_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc acpi_batt_get_status_desc = {
        0, { &acpi_batt_get_status_desc, (kobjop_t)kobj_error_method }
};