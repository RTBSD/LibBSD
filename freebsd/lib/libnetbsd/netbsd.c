/*
 * Copyright (C) 2025, RTBSD
 *
 * SPDX-License-Identifier: BSD 3-Clause
 */
#define LIBBSD_NETBSD
#define LIBBSD_NETBSD_ACPI
#include <bsd_compat.h>
#include <libnetbsd/sys/sys/device_impl.h>

int cppc_cpufreq_get(device_t self, uint32_t *fq);
int cppc_cpufreq_set(device_t self, uint32_t fq);
void acpitz_poll_status(device_t dv, uint32_t *tmp);

u_int arm_cpu_max = 1U;
struct cpu_info cpusinfo[32];
kmutex_t acpi_interrupt_list_mtx;

/* use NetBSD drivers with mimimal modifications as possible */
#define CA_MATCH_CALL(ca, ret, parent, cf, aux) \
    do { \
        if (ca->ca_match) \
        { \
            ret = ca->ca_match(parent, cf, aux);\
        } \
    } while (0)

#define CA_ATTACH_CALL(ca, parent, self, aux) \
    do { \
        if (ca->ca_attach) \
        { \
            ca->ca_attach(parent, self, aux);\
        } \
    } while (0)

#define CA_DEATTACH_CALL(ca, self, flag) \
    do { \
        if (ca->ca_detach) \
        { \
            ca->ca_detach(self, flag);\
        } \
    } while (0)

#define CA_DEVSIZE(ca)      (ca->ca_devsize)
#define CA_DEVNAME(ca)      (ca->ca_name)

/* refernce to NetBSD drivers defined */
extern struct cfattach acpi_fdt_ca;
extern struct cfattach acpi_ca;
extern struct cfattach cpu_acpi_ca;
extern struct cfattach acpitz_ca;
extern struct cfattach acpipcd_ca;
extern struct cfattach acpipcc_ca;
extern struct cfattach acpicppc_ca;

static device_t root_dev = NULL;
static device_t acpi_fdt_dev = NULL;
static device_t acpi_dev = NULL;
static struct devicelist acpi_madtbus_dev_list = 
    TAILQ_HEAD_INITIALIZER(acpi_madtbus_dev_list);
static struct devicelist acpi_sdtbus_dev_list = 
    TAILQ_HEAD_INITIALIZER(acpi_sdtbus_dev_list);
static struct devicelist acpi_nodebus_dev_list = 
    TAILQ_HEAD_INITIALIZER(acpi_nodebus_dev_list);

static device_t netbsd_alloc_device(struct cfattach *ca, int unit)
{
    device_t new_dev;

    new_dev = bsd_osal_malloc(sizeof(struct device));
    BSD_ASSERT(new_dev);
    new_dev->dv_unit = unit;
    new_dev->dv_cfattach = ca;

    if (ca) {
        new_dev->dv_private = bsd_osal_malloc(CA_DEVSIZE((ca)));
        BSD_ASSERT(new_dev->dv_private);

        snprintf(new_dev->dv_xname, sizeof(new_dev->dv_xname), "%s%d", CA_DEVNAME((ca)), unit);
    } else {
        new_dev->dv_private = NULL;
        snprintf(new_dev->dv_xname, sizeof(new_dev->dv_xname), "%s", "netbsd-root");
    }

    return new_dev;
}

static void netbsd_free_device(device_t dev)
{
    BSD_ASSERT(dev);
    BSD_ASSERT(dev->dv_private);

    CA_DEATTACH_CALL((dev->dv_cfattach), dev, 0U);

    bsd_osal_free(dev->dv_private);
    bsd_osal_free(dev);
}

int netbsd_init(void)
{
    struct cfattach *driver = &acpi_fdt_ca;

    /* a dummy root device node */
    root_dev = netbsd_alloc_device(NULL, 0);

    /* acpi_fdt_attach */
    acpi_fdt_dev = netbsd_alloc_device(driver, 0);
    CA_ATTACH_CALL(driver, root_dev, acpi_fdt_dev, NULL);

    /* auto detect device on acpi-bus */
    return 0;
}

static void netbsd_free_device_list(struct devicelist *list)
{
    device_t dev;

    TAILQ_FOREACH(dev, list, dv_list) {
        if (dev) {
            TAILQ_REMOVE(list, dev, dv_list);
            netbsd_free_device(dev);
        }
    }
}

void netbsd_deinit(void)
{
    netbsd_free_device_list(&acpi_nodebus_dev_list);
    memset(&acpi_nodebus_dev_list, 0, sizeof(acpi_nodebus_dev_list));

    netbsd_free_device(acpi_dev);
    acpi_dev = NULL;
    netbsd_free_device(acpi_fdt_dev);
    acpi_fdt_dev = NULL;
    netbsd_free_device(root_dev);
    root_dev = NULL;
}

static device_t acpibus_config_found(device_t parent, struct acpibus_attach_args *aa)
{
    int is_match;
    struct cfattach *driver = &acpi_ca;

    CA_MATCH_CALL(driver, is_match, parent, NULL, (void *)aa);
    if (!is_match) {
        return NULL;
    }

    acpi_dev = netbsd_alloc_device(driver, 0);
    CA_ATTACH_CALL(driver, acpi_fdt_dev, acpi_dev, aa);

    return acpi_dev;
}

static device_t acpimadtbus_config_found(device_t parent, ACPI_SUBTABLE_HEADER *hdrp)
{
    struct cfattach *drivers[] = {&cpu_acpi_ca};
    static int units[] = {0};
    BSD_ASSERT(__arraycount(drivers) == __arraycount(units));
    device_t new_dev = NULL;
    int is_match;

    for (int i = 0; i < __arraycount(drivers); i++) {
        CA_MATCH_CALL(drivers[i], is_match, parent, NULL, (void *)hdrp);
        if (!is_match) {
            continue;
        }

        new_dev = netbsd_alloc_device(drivers[i], units[i]);
        BSD_ASSERT(new_dev);

        CA_ATTACH_CALL(drivers[i], parent, new_dev, (void *)hdrp);
        TAILQ_INSERT_TAIL(&acpi_madtbus_dev_list, new_dev, dv_list);
        
        units[i]++;
        break; /* just need to find one device */
    }

    return new_dev;
}

static device_t acpisdtbus_config_found(device_t parent, ACPI_TABLE_HEADER *hdrp)
{
    struct cfattach *drivers[] = {&acpipcc_ca};
    static int units[] = {0};
    BSD_ASSERT(__arraycount(drivers) == __arraycount(units));
    device_t new_dev = NULL;
    int is_match;

    for (int i = 0; i < __arraycount(drivers); i++) {
        CA_MATCH_CALL(drivers[i], is_match, parent, NULL, (void *)hdrp);
        if (!is_match) {
            continue;
        }

        new_dev = netbsd_alloc_device(drivers[i], units[i]);
        BSD_ASSERT(new_dev);

        CA_ATTACH_CALL(drivers[i], parent, new_dev, (void *)hdrp);
        TAILQ_INSERT_TAIL(&acpi_sdtbus_dev_list, new_dev, dv_list);
        
        units[i]++;
        break; /* just need to find one device */
    }

    return new_dev;
}

static device_t acpinodebus_config_found(device_t parent, struct acpi_attach_args *aa, int (*print)(void *aux, const char *))
{
    struct cfattach *drivers[] = {&acpitz_ca, &acpipcd_ca, &acpicppc_ca};
    static int units[] = {0, 0, 0};
    BSD_ASSERT(__arraycount(drivers) == __arraycount(units));
    device_t new_dev = NULL;
    int is_match;

    for (int i = 0; i < __arraycount(drivers); i++) {
        CA_MATCH_CALL(drivers[i], is_match, parent, NULL, (void *)aa);
        if (!is_match) {
            continue;
        }

        if (print) {
            (void)print((void *)aa, parent->dv_xname);
        }

        new_dev = netbsd_alloc_device(drivers[i], units[i]);
        BSD_ASSERT(new_dev);

        CA_ATTACH_CALL(drivers[i], parent, new_dev, (void *)aa);
        TAILQ_INSERT_TAIL(&acpi_nodebus_dev_list, new_dev, dv_list);
        
        units[i]++;
        break; /* just need to find one device */
    }

    return new_dev;
}

device_t
config_found(device_t parent, void *aux, cfprint_t print,
    const struct cfargs * const cfargs)
{
    if ((cfargs->iattr == NULL) || (strlen(cfargs->iattr) == 0)) {
        return NULL;
    }

    if (!strcmp(cfargs->iattr, "acpibus")) {
        return acpibus_config_found(parent, (struct acpibus_attach_args *)aux);
    } else if (!strcmp(cfargs->iattr, "acpimadtbus")) {
        return acpimadtbus_config_found(parent, (ACPI_SUBTABLE_HEADER *)aux);
    } else if (!strcmp(cfargs->iattr, "acpisdtbus")) {
        return acpisdtbus_config_found(parent, (ACPI_TABLE_HEADER *)aux);
    } else if (!strcmp(cfargs->iattr, "acpinodebus")) {
        return acpinodebus_config_found(parent, (struct acpi_attach_args *)aux, print);
    }
}

int bsd_get_acpi_cppc_cpu_frequency(uint32_t cpu_id, uint32_t *freq)
{
    device_t dev;
    int ret = 0;
    bool found = false;
    struct devicelist *list = &acpi_nodebus_dev_list; /* acpicppc is in node bus */

    TAILQ_FOREACH(dev, list, dv_list) {
        if ((dev->dv_cfattach != &acpicppc_ca) || (dev->dv_unit != cpu_id)) {
            continue;
        }

        BSD_ASSERT(freq);
        found = true;
        ret = cppc_cpufreq_get(dev, freq);
    }

    return found ? ret : ENODEV;
}

int bsd_set_acpi_cppc_cpu_frequency(uint32_t cpu_id, uint32_t freq)
{
    device_t dev;
    int ret = 0;
    bool found = false;
    struct devicelist *list = &acpi_nodebus_dev_list; /* acpicppc is in node bus */

    TAILQ_FOREACH(dev, list, dv_list) {
        if ((dev->dv_cfattach != &acpicppc_ca) || (dev->dv_unit != cpu_id)) {
            continue;
        }

        BSD_ASSERT(freq);
        found = true;
        ret = cppc_cpufreq_set(dev, freq);
    }

    return found ? ret : ENODEV;
}

int bsd_get_acpi_cpu_temperature(uint32_t *temp)
{
    device_t dev;
    bool found = false;
    struct devicelist *list = &acpi_nodebus_dev_list; /* acpi_tz is in node bus */

    TAILQ_FOREACH(dev, list, dv_list) {
        if (dev->dv_cfattach != &acpitz_ca) {
            continue;
        }

        assert(temp);
        found = true;
        acpitz_poll_status(dev, temp);
        printf("%s sensored %d C\n", dev->dv_xname, ((*temp) / 10));
    }

    return found ? 0 : ENODEV;
}
