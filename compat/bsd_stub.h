/*
 * Copyright (C) 2025, RTBSD
 *
 * SPDX-License-Identifier: BSD 3-Clause
 */
#ifndef BSD_STUBS_H
#define BSD_STUBS_H

/* basic types */
typedef unsigned int boolean_t;
typedef uintptr_t vm_paddr_t;
typedef uintptr_t vm_offset_t;
typedef size_t vm_size_t;
typedef char vm_memattr_t;
typedef uintptr_t rman_res_t;

typedef void *pci_chipset_tag_t;
typedef void *isa_chipset_tag_t;

/*
 * Bus address and size types
 */
typedef uintptr_t bus_addr_t;
typedef uintptr_t bus_size_t;

/*
 * Access methods for bus resources and address space.
 */
typedef uintptr_t bus_space_tag_t;
typedef uintptr_t bus_space_handle_t;

#define BUS_SPACE_MAP_CACHEABLE 0x01
#define BUS_SPACE_MAP_LINEAR 0x02
#define BUS_SPACE_MAP_PREFETCHABLE 0x04
#define BUS_SPACE_MAP_NONPOSTED 0x08

/* Memory attribute configuration. */
#define VM_MEMATTR_DEVICE_nGnRnE 0
#define VM_MEMATTR_UNCACHEABLE 1
#define VM_MEMATTR_WRITE_BACK 2
#define VM_MEMATTR_WRITE_THROUGH 3
#define VM_MEMATTR_DEVICE_nGnRE 4

#define VM_MEMATTR_DEVICE VM_MEMATTR_DEVICE_nGnRE
#define VM_MEMATTR_DEVICE_NP VM_MEMATTR_DEVICE_nGnRnE

enum arm64_bus
{
	ARM64_BUS_NONE,
	ARM64_BUS_FDT,
	ARM64_BUS_ACPI,
};

/*
 *	bus_dma_tag_t
 *
 *	A machine-dependent opaque type describing the characteristics
 *	of how to perform DMA mappings.  This structure encapsultes
 *	information concerning address and alignment restrictions, number
 *	of S/G segments, amount of data per S/G segment, etc.
 */
struct bus_dma_tag
{
};
typedef struct bus_dma_tag *bus_dma_tag_t;

/*
 *	bus_dmamap_t
 *
 *	DMA mapping instance information.
 */
struct bus_dmamap
{
};
typedef struct bus_dmamap *bus_dmamap_t;

/* netbsd/prop_dictionary.h */
struct _prop_dictionary
{
};
typedef struct _prop_dictionary *prop_dictionary_t;

#define prop_dictionary_set_uint32(...)

/* netbsd/pmf.h */
struct pmf_qual
{
};
typedef struct pmf_qual pmf_qual_t;

#define pmf_get_platform(...) "null"
#define pmf_device_register(...) true
#define pmf_device_deregister(...)
#define pmf_system_suspend(...) true
#define pmf_system_resume(...) 0U
#define pmf_system_bus_resume(...) 0U
#define pmf_system_bus_resume(...) 0U

/* acpi.h */
#define acpi_md_pdc(...) 0U
#define acpi_md_OsDisableInterrupt()
#define acpi_md_OsEnableInterrupt()
#define acpi_md_OsGetRootPointer() 0U
#define acpi_md_intr_establish(...) NULL
#define acpi_md_intr_disestablish(...)
#define acpi_md_intr_mask(...)
#define acpi_md_intr_unmask(...)
#define acpi_md_sleep(...) 0U
#define acpitimer_init(...)
#define acpitimer_detach() 0U
#define acpi_wakedev_init(...) \
	{                          \
	}
#define acpi_wakedev_add(...)
#define acpi_wakedev_commit(...)

#define ACPI_INTR_XREF 1
#define ACPI_MSI_XREF 2
#define ACPI_GPIO_XREF 3

/* callout.h */
struct callout
{
	void *co;
};

typedef struct callout callout_t;

#define callout_init(c, mpsafe) bsd_osal_callout_init(c)
#define callout_init_mtx(c, mtx, flags) bsd_osal_callout_init(c)
#define callout_reset(c, timeout, ftn, arg) bsd_osal_callout_reset(c, timeout, ftn, arg)
#define callout_setfunc(c, ftn, arg) bsd_osal_callout_reset(c, 0U, ftn, arg)
#define callout_stop(c) bsd_osal_callout_stop(c)
#define callout_halt(c, ...) bsd_osal_callout_stop(c)
#define callout_drain(c) bsd_osal_callout_drain(c)
#define callout_schedule(c, toticks) bsd_osal_callout_schedule(c, toticks)
#define callout_destroy(c) bsd_osal_callout_destory(c)

/* mutex.h */
struct mtx
{
	void *mtx_lock;
};

typedef struct mtx kmutex_t;

#define mtx_init(m, ...) bsd_osal_mtx_init(m)
#define mtx_destroy(m, ...) bsd_osal_mtx_destroy(m)
#define mtx_lock(m, ...) bsd_osal_mtx_lock(m)
#define mtx_lock_spin(m, ...) bsd_osal_mtx_lock(m)
#define mtx_unlock(m, ...) bsd_osal_mtx_unlock(m)
#define mtx_unlock_spin(m, ...) bsd_osal_mtx_unlock(m)
#define mtx_owned(m, ...) bsd_osal_mtx_own(m)
#define mtx_assert(m, ...) bsd_osal_mtx_assert(m)
#define mtx_sleep(chan, m, pri, wmesg, timeout) bsd_osal_mtx_sleep(m, timeout)

#define mutex_init(m, ...) bsd_osal_mtx_init(m)
#define mutex_destroy(m) bsd_osal_mtx_destroy(m)
#define mutex_enter(m) bsd_osal_mtx_lock(m)
#define mutex_exit(m) bsd_osal_mtx_unlock(m)
#define mutex_tryenter(m) bsd_osal_mtx_lock(m)
#define mutex_owned(m) bsd_osal_mtx_own(m)

/* sx.h */
struct sx
{
	void *sx_lock;
};

#define sx_init(sx, desc) bsd_osal_sx_init(sx)
#define sx_slock(sx) bsd_osal_sx_slock(sx)
#define sx_sunlock(sx) bsd_osal_sx_sunlock(sx)
#define sx_xlock(sx) bsd_osal_sx_xlock(sx)
#define sx_xunlock(sx) bsd_osal_sx_xunlock(sx)
#define sx_assert(sx, what) bsd_osal_sx_assert(sx, what)

/* Flags passed to witness_assert. */
#define LA_MASKASSERT 0x000000ff  /* Mask for witness defined asserts. */
#define LA_UNLOCKED 0x00000000	  /* Lock is unlocked. */
#define LA_LOCKED 0x00000001	  /* Lock is at least share locked. */
#define LA_SLOCKED 0x00000002	  /* Lock is exactly share locked. */
#define LA_XLOCKED 0x00000004	  /* Lock is exclusively locked. */
#define LA_RECURSED 0x00000008	  /* Lock is recursed. */
#define LA_NOTRECURSED 0x00000010 /* Lock is not recursed. */

#define SX_LOCKED LA_LOCKED
#define SX_SLOCKED LA_SLOCKED
#define SX_XLOCKED LA_XLOCKED
#define SX_UNLOCKED LA_UNLOCKED
#define SX_RECURSED LA_RECURSED
#define SX_NOTRECURSED LA_NOTRECURSED

#define SX_SYSINIT(...)

/* condvar.h */
struct cv
{
	void *cond;
};

typedef struct kcondvar
{
	void *cond;
} kcondvar_t;

#define cv_init(c, desc) bsd_osal_cv_init(c)
#define cv_destroy(c) bsd_osal_cv_destory(c)
#define cv_signal(c) bsd_osal_cv_signal(c)
#define cv_broadcast(c) bsd_osal_cv_broadcast(c)
#define cv_wait_sig(c, lock) bsd_osal_cv_wait(c, 0xFFFFFFFF)
#define cv_wait(c, lock) bsd_osal_cv_wait(c, 0xFFFFFFFF)
#define cv_timedwait_sig(c, lock, timeo) bsd_osal_cv_wait(c, timeo)
#define cv_timedwait(c, lock, timeo) bsd_osal_cv_wait(c, timeo)

/* task.h */
struct task
{
	void *ta;
	uint32_t td_tid;
};

struct thread
{
	void *ta;
	uint32_t td_tid;
};

struct timeout_task
{
};
struct lwp
{
};

typedef struct lwp lwp_t;

/* taskqueue.h */
struct taskqueue
{
	void *queue;
};

#define taskqueue_create_fast(...) NULL
#define taskqueue_start_threads(...)
#define taskqueue_drain(...)
#define taskqueue_enqueue(...)
#define TASK_INIT(...)
#define TASKQUEUE_DEFINE_THREAD(...)

#define msleep(...)
#define thread_lock(...)
#define thread_unlock(...)
#define sched_bind(...)
#define sched_unbind(...)
#define suspendclock(...)
#define resumeclock(...)

/* time.h */
struct bintime
{
	uint64_t sec;
	uint64_t frac;
};
#define tvtohz(...) 0U
#define binuptime(...)

/* netbsd/kmem.h */
/*
 * Flags to memory allocation functions.
 */
#define M_NOWAIT 0x0001		 /* do not block */
#define M_WAITOK 0x0002		 /* ok to block */
#define M_NORECLAIM 0x0080	 /* do not reclaim after failure */
#define M_ZERO 0x0100		 /* bzero the allocation */
#define M_NOVM 0x0200		 /* don't ask VM for pages */
#define M_USE_RESERVE 0x0400 /* can alloc out of reserve memory */
#define M_NODUMP 0x0800		 /* don't dump pages in this allocation */
#define M_FIRSTFIT 0x1000	 /* only for vmem, fast fit */
#define M_BESTFIT 0x2000	 /* only for vmem, low fragmentation */
#define M_EXEC 0x4000		 /* allocate executable space */
#define M_NEXTFIT 0x8000	 /* only for vmem, follow cursor */

#define M_VERSION 2020110501

#define MINALLOCSIZE 8U

#define kmem_zalloc(sz, ...) bsd_osal_malloc(sz)
#define kmem_alloc(sz, ...) bsd_osal_malloc(sz)
#define kmem_free(ptr, sz) bsd_osal_free(ptr)
#define bsd_malloc(sz, ...) bsd_osal_malloc(sz)
#define bsd_realloc(ptr, sz, ...) bsd_osal_realloc(ptr, sz)
#define bsd_free(ptr, ...) bsd_osal_free(ptr)

#define kmem_tmpbuf_alloc(sz, ...) bsd_osal_malloc(sz)
#define kmem_tmpbuf_free(ptr, ...) bsd_osal_free(ptr)
#define kmem_strfree(str) bsd_osal_free(str)

#define kmem_strdup(str, ...) bsd_osal_strdup(str, NULL)

#define malloc_domainset(sz, ...) bsd_osal_malloc(sz)

/* atomic.h */
/* 原子比较并交换操作 */
#define atomic_cmpset_32(p, cmpval, newval) \
	__sync_bool_compare_and_swap((volatile unsigned int *)p, cmpval, newval)

#define atomic_cmpset_int(p, cmpval, newval) \
	__sync_bool_compare_and_swap((volatile unsigned int *)p, cmpval, newval)

/* 原子清除操作 */
#define atomic_clear_int(address, setmask) \
	__sync_fetch_and_and((volatile unsigned int *)address, ~setmask)

/* 原子设置操作 */
#define atomic_set_int(p, val) \
	__sync_fetch_and_or((volatile unsigned int *)p, val)

/* 原子加载获取操作 */
#define atomic_load_acq_int(flag) \
	__sync_fetch_and_add((volatile unsigned int *)flag, 0)

/* 原子加法操作 */
#define atomic_add_int(ptr, val) \
	__sync_fetch_and_add((volatile int *)ptr, val)

/* 原子加载获取操作 */
/* 这里简单用 __sync_fetch_and_add 模拟，实际语义可能不完全等同 */
#define atomic_load_acquire(p) \
	__sync_fetch_and_add((volatile typeof(*p) *)p, 0)

/* 原子存储宽松操作 */
#define atomic_store_relaxed(p, v) \
	(*(volatile typeof(*p) *)p = v)

/* 原子存储释放操作 */
/* 简单实现，可能不满足严格的释放语义 */
#define atomic_store_release(p, v) \
	__sync_synchronize();          \
	(*(volatile typeof(*p) *)p = v)

/* 内存屏障释放操作 */
#define membar_release() \
	__sync_synchronize()

/* 内存屏障获取操作 */
#define membar_acquire() \
	__sync_synchronize()

/* efi.h */
#define preload_search_by_type(...) NULL
#define preload_fetch_addr(...) NULL
#define preload_fetch_size(...) 0U

/* netbsd/libkern.h */
int pmatch(const char *, const char *, const char **);

/* sysctl.h */
struct sysctl_ctx_list
{
};
struct sysctl_oid
{
};
struct sysctl_req
{
	void *newptr;
};
#define SYSCTL_HANDLER_ARGS void *oidp, void *arg1, \
							uint32_t arg2, struct sysctl_req *req
#define SYSCTL_NODE(name, ...) \
	struct                     \
	{                          \
	} name __used
#define SYSCTL_INT(...)
#define SYSCTL_UINT(...)
#define SYSCTL_BOOL(...)
#define SYSCTL_PROC(...)
#define SYSCTL_ULONG(...)
#define SYSCTL_STRING(...)
#define SYSCTL_ADD_NODE(...) NULL
#define SYSCTL_ADD_U16(...) NULL
#define SYSCTL_ADD_PROC(...) NULL
#define SYSCTL_ADD_STRING(...) NULL
#define sysctl_handle_int(...) EOPNOTSUPP
#define sysctl_handle_string(...) EOPNOTSUPP
#define sysctl_ctx_init(ctx) \
	do                       \
	{                        \
		(void)(ctx);         \
	} while (0)
#define sysctl_ctx_free(ctx) \
	do                       \
	{                        \
		(void)(ctx);         \
	} while (0)

#define sysctl_lookup(...) 0U
#define sysctl_teardown(...)

#define SYSCTL_DECL(...)
#define SYSCTL_SETUP(...)

#define CTL_EOL 0U

/* netbsd/sysctl.h */
struct sysctlnode
{
	void *sysctl_data;
	int sysctl_num;
};
#define SYSCTLFN_PROTO const int *, u_int, void *,     \
					   size_t *, const void *, size_t, \
					   const int *, struct lwp *, const struct sysctlnode *
#define SYSCTLFN_ARGS const int *name, u_int namelen,  \
					  void *oldp, size_t *oldlenp,     \
					  const void *newp, size_t newlen, \
					  const int *oname, struct lwp *l, \
					  const struct sysctlnode *rnode

/* tslog.h */
#define TSRAW(a, b, c)
#define TSENTER() TSRAW("ENTER", __func__, NULL)
#define TSENTER2(x) TSRAW("ENTER", __func__, x)
#define TSEXIT() TSRAW("EXIT", __func__, NULL)
#define TSLINE() TSRAW("EVENT", __FILE__, __XSTRING(__LINE__))
#define TSEXIT2(x) TSRAW(TS_EXIT, __func__, x)

/* event_handler.h */
#define EVENTHANDLER_DECLARE(...)
#define EVENTHANDLER_INVOKE(...)
#define EVENTHANDLER_REGISTER(...)

/* malloc.h */
struct malloc_type
{
};
#define MALLOC_DEFINE(type, shortdesc, longdesc) struct malloc_type type[1] = {};
#define MALLOC_DECLARE(type) extern struct malloc_type type[1]

/* module.h */
/* Commands passed to module control routine. */
typedef enum modcmd
{
	MODULE_CMD_INIT,	   /* mandatory */
	MODULE_CMD_FINI,	   /* mandatory */
	MODULE_CMD_STAT,	   /* optional */
	MODULE_CMD_AUTOUNLOAD, /* optional */
} modcmd_t;

#define module_autoload(...)
#define MODULE(...)

/* netbsd/barrier.h */
#define membar_sync() __asm __volatile("dmb ish" ::: "memory")

/* iodev.h */
#define iodev_read_1(a) 0
#define iodev_read_2(a) 0
#define iodev_read_4(a) 0
#define iodev_write_1(a, v)
#define iodev_write_2(a, v)
#define iodev_write_4(a, v)

/* selinfo.h */
struct selinfo
{
};

/* printf */
#define panic bsd_osal_panic
#define BSD_PANIC bsd_osal_panic
#define BSD_ASSERT(expr, ...) bsd_osal_assert(expr, __func__, __LINE__)
#define KASSERT(expr, ...) bsd_osal_assert(expr, __func__, __LINE__)
#define KDASSERT(expr, ...) bsd_osal_assert(expr, __func__, __LINE__)
#define KASSERTMSG(expr, ...) bsd_osal_assert(expr, __func__, __LINE__)

#define aprint_normal(fmt, ...) bsd_osal_printf(LIBBSD_PRINT_NORAML, fmt, ##__VA_ARGS__)
#define aprint_error(fmt, ...) bsd_osal_printf(LIBBSD_PRINT_ERROR, fmt, ##__VA_ARGS__)
#define aprint_naive(fmt, ...) bsd_osal_printf(LIBBSD_PRINT_NAIVE, fmt, ##__VA_ARGS__)
#define aprint_debug(fmt, ...) bsd_osal_printf(LIBBSD_PRINT_DEBUG, fmt, ##__VA_ARGS__)
#define aprint_verbose(fmt, ...) bsd_osal_printf(LIBBSD_PRINT_VERBOSE, fmt, ##__VA_ARGS__)

#define aprint_normal_dev(dev, fmt, ...) bsd_osal_dev_printf(LIBBSD_PRINT_NORAML, BSD_DEVICE_NAME(dev), fmt, ##__VA_ARGS__)
#define aprint_error_dev(dev, fmt, ...) bsd_osal_dev_printf(LIBBSD_PRINT_ERROR, BSD_DEVICE_NAME(dev), fmt, ##__VA_ARGS__)
#define aprint_naive_dev(dev, fmt, ...) bsd_osal_dev_printf(LIBBSD_PRINT_NAIVE, BSD_DEVICE_NAME(dev), fmt, ##__VA_ARGS__)
#define aprint_debug_dev(dev, fmt, ...) bsd_osal_dev_printf(LIBBSD_PRINT_DEBUG, BSD_DEVICE_NAME(dev), fmt, ##__VA_ARGS__)
#define aprint_verbose_dev(dev, fmt, ...) bsd_osal_dev_printf(LIBBSD_PRINT_VERBOSE, BSD_DEVICE_NAME(dev), fmt, ##__VA_ARGS__)

#define device_printf(dev, fmt, ...) bsd_osal_dev_printf(LIBBSD_PRINT_NORAML, BSD_DEVICE_NAME(dev), fmt, ##__VA_ARGS__)

/* system.h */
#define pause(msg, micro_seconds) bsd_osal_sleep(micro_seconds)
#define DELAY(micro_seconds) 	  bsd_osal_sleep(micro_seconds)
#define delay(micro_seconds) 	  bsd_osal_sleep(micro_seconds)
#define wakeup_one(...)
#define wakeup(...)

#define hz bsd_osal_get_tick_rate()
#define ticks bsd_osal_get_current_tick()
#define get_cyclecount() bsd_osal_get_current_tick()

/* pmap.h */
static inline void *pmap_mapbios(vm_paddr_t pa, vm_size_t size) { return (void *)pa; }
static inline void *pmap_mapdev(vm_paddr_t pa, vm_size_t size) { return (void *)pa; }
static inline void pmap_unmapdev(void *va, vm_size_t size) {}
static inline void pmap_unmapbios(void *va, vm_size_t size) {}

/* netbsd/sysmonvar.h */
struct envsys_data
{
	uint32_t sensor;	/* sensor number */
	uint32_t units;		/* type of sensor */
	uint32_t state;		/* sensor state */
	uint32_t flags;		/* sensor flags */
	uint32_t rpms;		/* for fans, nominal RPMs */
	int32_t rfact;		/* for volts, factor x 10^4 */
	int32_t value_cur;	/* current value */
	int32_t value_prev; /* previous value */
	int32_t value_max;	/* max value */
	int32_t value_min;	/* min value */
};
typedef struct envsys_data envsys_data_t;

/* sensor states */
enum envsys_states
{
	ENVSYS_SVALID = 10, /* sensor state is valid */
	ENVSYS_SINVALID,	/* sensor state is invalid */
	ENVSYS_SCRITICAL,	/* sensor state is critical */
	ENVSYS_SCRITUNDER,	/* sensor state is critical under */
	ENVSYS_SCRITOVER,	/* sensor state is critical over */
	ENVSYS_SWARNUNDER,	/* sensor state is warn under */
	ENVSYS_SWARNOVER	/* sensor state is warn over */
};

/*
 * Thresholds/limits that are being monitored
 */

enum envsys_lims
{
	ENVSYS_LIM_CRITMAX,
	ENVSYS_LIM_WARNMAX,
	ENVSYS_LIM_WARNMIN,
	ENVSYS_LIM_CRITMIN,
	ENVSYS_LIM_LASTLIM
};

struct sysmon_envsys_lim
{
	int32_t critmax;
	int32_t warnmax;
	int32_t warnmin;
	int32_t critmin;
};

typedef union
{
	int32_t sel_limit_list[ENVSYS_LIM_LASTLIM];
	struct sysmon_envsys_lim sel_limits;
} sysmon_envsys_lim_t;

struct sysmon_pswitch
{
	const char *smpsw_name; /* power switch name */
	int smpsw_type;			/* power switch type */
};

#define sysmon_power_settype(...)
#define sysmon_pswitch_register(...) 0U
#define sysmon_pswitch_unregister(...)
#define sysmon_pswitch_event(...)

struct sysmon_envsys
{
};

#define sysmon_envsys_register(...) 0U
#define sysmon_envsys_unregister(...) \
	{                                 \
	}
#define sysmon_envsys_create(...) NULL
#define sysmon_envsys_destroy(...)

#define PSWITCH_TYPE_POWER 0	 /* power button */
#define PSWITCH_TYPE_SLEEP 1	 /* sleep button */
#define PSWITCH_TYPE_LID 2		 /* lid switch */
#define PSWITCH_TYPE_RESET 3	 /* reset button */
#define PSWITCH_TYPE_ACADAPTER 4 /* AC adapter presence */
#define PSWITCH_TYPE_HOTKEY 5	 /* hotkey button */

#define PSWITCH_EVENT_PRESSED 0	 /* button pressed, lid closed, AC off */
#define PSWITCH_EVENT_RELEASED 1 /* button released, lid open, AC on */

/* power.h */
#define power_pm_register(...)

/* netbsd/autoconf.h */
#define ifattr_match(...) NULL
#define config_search(...) NULL
#define config_defer(...) NULL
#define config_cfattach_lookup(...) NULL
#define config_detach_children(...) 0

/* netbsd/irq.h */
typedef uint32_t intr_handle_t;

#define intr_string(...) NULL

/* Interrupt sharing types. */
#define IST_NONE 0	/* none */
#define IST_PULSE 1 /* pulsed */
#define IST_EDGE 2	/* edge-triggered */
#define IST_LEVEL 3 /* level-triggered */

/* env.h */
#define kern_getenv(...) NULL
#define freeenv(...)
#define testenv(...) false

/* conf.h */
struct cdev
{
};

#define devctl_notify(...)

/* Power management system type */
#define POWER_PM_TYPE_ACPI 0x01
#define POWER_PM_TYPE_NONE 0xff

/* Sleep state */
#define POWER_SLEEP_STATE_STANDBY 0x00
#define POWER_SLEEP_STATE_SUSPEND 0x01
#define POWER_SLEEP_STATE_HIBERNATE 0x02

/* Commands for Power management function */
#define POWER_CMD_SUSPEND 0x00

#define RB_HALT 0x008	   /* don't reboot, just halt */
#define RB_POWEROFF 0x4000 /* turn the power off if possible */

#define power_pm_get_type() POWER_PM_TYPE_ACPI
#define shutdown_nice(...)
#define stop_all_proc(...)
#define resume_all_proc(...)
#define suspend_all_fs(...)
#define resume_all_fs(...)
#define devctl_process_running() false
#define KERNEL_PANICKED() false

/* linker.h */
struct linker_file
{
};
typedef struct linker_file *linker_file_t;

/* intr.h */
#define intr_disable() bsd_osal_intr_disable()
#define intr_restore(s) bsd_osal_intr_restore(s)
#define intr_setup_irq(...) 0
#define intr_teardown_irq(...) 0
#define intr_describe_irq(...) 0
#define intr_activate_irq(...) 0
#define intr_deactivate_irq(...)
#define intr_alloc_map_data(...) NULL
#define intr_map_irq(...) 0

/* user space */
#define errx(tag, fmt, ...) bsd_osal_printf(LIBBSD_PRINT_ERROR, fmt, ##__VA_ARGS__)
#define err(tag, fmt, ...) bsd_osal_printf(LIBBSD_PRINT_ERROR, fmt, ##__VA_ARGS__)
#define warnx(fmt, ...) bsd_osal_printf(LIBBSD_PRINT_ERROR, fmt, ##__VA_ARGS__)

/* sys.h */
extern int boothowto;
extern int bootverbose;
extern int cold;
extern struct thread *curthread;
extern struct mtx Giant;
extern u_int arm_cpu_max;
extern int errno;
extern int smp_started;
extern enum arm64_bus arm64_bus_method;

#define GIANT_REQUIRED mtx_assert(&Giant, MA_OWNED)

#endif