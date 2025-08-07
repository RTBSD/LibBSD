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


#ifndef _acpi_bus_if_h_
#define _acpi_bus_if_h_

/** @brief Unique descriptor for the ACPI_BUS_MAP_INTR() method */
extern struct kobjop_desc acpi_bus_map_intr_desc;
/** @brief A function implementing the ACPI_BUS_MAP_INTR() method */
typedef int acpi_bus_map_intr_t(device_t bus, device_t dev, u_int irq, int trig,
                                int pol);

static __inline int ACPI_BUS_MAP_INTR(device_t bus, device_t dev, u_int irq,
                                      int trig, int pol)
{
        kobjop_t _m;
        int rc;
        KOBJOPLOOKUP(((kobj_t)bus)->ops,acpi_bus_map_intr);
        rc = ((acpi_bus_map_intr_t *) _m)(bus, dev, irq, trig, pol);
        return (rc);
}

#endif /* _acpi_bus_if_h_ */