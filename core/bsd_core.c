/*
 * Copyright (C) 2025, RTBSD
 *
 * SPDX-License-Identifier: BSD 3-Clause
 */
#define LIBBSD_FREEBSD
#include <bsd_compat.h>
#include <sys/queue_mergesort.h>

#if !defined(__RTBSD_LIBBSD__)
#error "Please define macro __RTBSD_LIBBSD__ first !!!"
#endif

#ifndef BOOTHOWTO
#define BOOTHOWTO 0
#endif
int boothowto = BOOTHOWTO;
int bootverbose = 1;
int cold = 1;
struct thread *curthread;
struct mtx Giant;
int errno = 0;
int smp_started = 0;
#if DEV_ACPI && FDT
#error "Please define only one of DEV_ACPI or FDT !!!"
#endif
#if DEV_ACPI
enum arm64_bus arm64_bus_method = ARM64_BUS_ACPI;
#endif
#if FDT
enum arm64_bus arm64_bus_method = ARM64_BUS_FDT;
#endif

#if DEV_ACPI
int netbsd_init(void);
void netbsd_deinit(void);
#endif

#if KDB
void dbg_init(void);
void kdb_init(void);
void kdb_enter(const char *why, const char *msg);
#endif

RWSET_DECLARE(sysinit_set, struct sysinit);

/*
 * The sysinit lists.  Items are moved to sysinit_done_list when done.
 */
static STAILQ_HEAD(sysinitlist, sysinit) sysinit_list;
static struct sysinitlist sysinit_done_list =
	STAILQ_HEAD_INITIALIZER(sysinit_done_list);

/*
 * Compare two sysinits; return -1, 0, or 1 if a comes before, at the same time
 * as, or after b.
 */
static int
sysinit_compar(struct sysinit *a, struct sysinit *b, void *thunk __unused)
{

	if (a->subsystem < b->subsystem)
		return (-1);
	if (a->subsystem > b->subsystem)
		return (1);
	if (a->order < b->order)
		return (-1);
	if (a->order > b->order)
		return (1);
	return (0);
}

static void
sysinit_mklist(struct sysinitlist *list, struct sysinit **set,
			   struct sysinit **set_end)
{
	struct sysinit **sipp;

	TSENTER();
	TSENTER2("listify");
	STAILQ_INIT(list);
	for (sipp = set; sipp < set_end; sipp++)
		STAILQ_INSERT_TAIL(list, *sipp, next);
	TSEXIT2("listify");
	TSENTER2("mergesort");
	STAILQ_MERGESORT(list, NULL, sysinit_compar, sysinit, next);
	TSEXIT2("mergesort");
	TSEXIT();
}

static void mi_startup(void)
{
	struct sysinit *sip;

	/* Construct and sort sysinit list. */
	sysinit_mklist(&sysinit_list, SET_BEGIN(sysinit_set), SET_LIMIT(sysinit_set));

	/*
	 * Perform each system initialization task from the ordered list.  Note
	 * that if sysinit_list is modified (e.g. by a KLD) we will nonetheless
	 * always perform the earlist-sorted sysinit at each step; using the
	 * STAILQ_FOREACH macro would result in items being skipped if inserted
	 * earlier than the "current item".
	 */
	while ((sip = STAILQ_FIRST(&sysinit_list)) != NULL)
	{
		STAILQ_REMOVE_HEAD(&sysinit_list, next);
		STAILQ_INSERT_TAIL(&sysinit_done_list, sip, next);

		if (sip->subsystem == SI_SUB_DUMMY)
			continue; /* skip dummy task(s)*/

		/* Call function */
		(*(sip->func))(sip->udata);
	}

	printf("mi_startup done\n");
}

int bsd_system_init(void)
{
	int err = 0;

	printf("freebsd start...\n");
	err = bsd_osal_init();
	if (err != 0)
	{
		goto err_exit;
	}
	mi_startup();
	printf("freebsd done\n");

#if DEV_ACPI
	printf("netbsd start...\n");
	err = netbsd_init();
	if (err != 0)
	{
		goto err_exit;
	}
	printf("netbsd done\n");
#endif

#if KDB
	dbg_init();
	kdb_init();
	printf("debug enabled\n");
	kdb_enter("bootflags", "Boot flags requested debugger");
#endif

err_exit:
	if (err != 0)
	{
		printf("bsd_system_init failed with error %d\n", err);
	}
	return err;
}

#if DEV_ACPI
#include "acpidump.h"

int bsd_display_acpi_table(void)
{
	return acpidump_main(0, NULL);
}
#endif

#if FDT
#include "ofwdump.h"

int bsd_display_fdt_table(void)
{
	return ofwdump_main(0, NULL);
}
#endif

#if KDB
extern int kdb_trap(int, int, void *);
int bsd_kdb_trap(int type, int code, void *trapframe)
{
	return kdb_trap(type, code, trapframe);
}
#endif