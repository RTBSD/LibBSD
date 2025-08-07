/*
 * This file is @generated automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   freebsd/sys/dev/acpica/acpi_bus_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#define LIBBSD_FREEBSD
#define LIBBSD_FREEBSD_ACPI
#include <bsd_compat.h>

static acpi_bus_map_intr_t acpi_bus_default_map_intr;

int
acpi_bus_default_map_intr(device_t bus, device_t dev, u_int irq,
    int trig, int pol)
{
        device_t parent;

        /* Pass up the hierarchy */
        parent = device_get_parent(bus);
        if (parent != NULL)
                return (ACPI_BUS_MAP_INTR(parent, dev, irq, trig, pol));

        panic("Unable to map interrupt %u", irq);
}

struct kobjop_desc acpi_bus_map_intr_desc = {
        0, { &acpi_bus_map_intr_desc, (kobjop_t)acpi_bus_default_map_intr }
};