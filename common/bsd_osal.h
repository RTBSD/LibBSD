/*
 * Copyright (C) 2025, RTBSD
 *
 * SPDX-License-Identifier: BSD 3-Clause
 */
#ifndef BSD_OSAL_H
#define BSD_OSAL_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define CONFIG_BSD_OSAL_THREAD_SET_ARGV void *argument

typedef void *bsd_osal_thread_t;
typedef void *bsd_osal_callout_t;
typedef void *bsd_osal_condvar_t;
typedef void *bsd_osal_sem_t;
typedef void *bsd_osal_mutex_t;
typedef void *bsd_osal_rwlock_t;
typedef void *bsd_osal_mq_t;
typedef void (*bsd_thread_entry_t)(CONFIG_BSD_OSAL_THREAD_SET_ARGV);
typedef void (*bsd_timer_handler_t)(void *argument);
typedef void (*bsd_callout_func_t)(void *);
typedef void (*bsd_intr_handle_t)(void *);

int bsd_osal_init(void);

void *bsd_osal_malloc(size_t size);
void *bsd_osal_realloc(void *ptr, size_t size);
void bsd_osal_free(void *ptr);
char *bsd_osal_strdup(const char *str, size_t *lenp);

void bsd_osal_callout_init(bsd_osal_callout_t c);
void bsd_osal_callout_destory(bsd_osal_callout_t c);
int bsd_osal_callout_reset(bsd_osal_callout_t c, int timeout, bsd_callout_func_t ftn, void *arg);
void bsd_osal_callout_stop(bsd_osal_callout_t c);
void bsd_osal_callout_drain(bsd_osal_callout_t c);
int bsd_osal_callout_schedule(bsd_osal_callout_t c, int to_ticks);

void bsd_osal_mtx_init(bsd_osal_mutex_t m);
void bsd_osal_mtx_destroy(bsd_osal_mutex_t m);
void bsd_osal_mtx_lock(bsd_osal_mutex_t m);
void bsd_osal_mtx_unlock(bsd_osal_mutex_t m);
bool bsd_osal_mtx_own(bsd_osal_mutex_t m);
void bsd_osal_mtx_assert(bsd_osal_mutex_t m);
int bsd_osal_mtx_sleep(bsd_osal_mutex_t m, int timeout);

void bsd_osal_cv_init(bsd_osal_condvar_t c);
void bsd_osal_cv_destory(bsd_osal_condvar_t c);
void bsd_osal_cv_signal(bsd_osal_condvar_t c);
void bsd_osal_cv_broadcast(bsd_osal_condvar_t c);
int bsd_osal_cv_wait(bsd_osal_condvar_t c, uint32_t timeout);

void bsd_osal_sx_init(bsd_osal_rwlock_t sx);
void bsd_osal_sx_slock(bsd_osal_rwlock_t sx);
void bsd_osal_sx_sunlock(bsd_osal_rwlock_t sx);
void bsd_osal_sx_xlock(bsd_osal_rwlock_t sx);
void bsd_osal_sx_xunlock(bsd_osal_rwlock_t sx);
void bsd_osal_sx_assert(bsd_osal_rwlock_t sx, int what);

void bsd_osal_sleep(int micro_seconds);
uint32_t bsd_osal_get_tick_rate(void);
uint64_t bsd_osal_get_current_tick(void);

int bsd_osal_intr_disable(void);
void bsd_osal_intr_restore(int flag);
void bsd_osal_intr_setup_irq(int irqno, bsd_intr_handle_t handler, void *arg);
int bsd_osal_intr_teardown(int irqno);
int bsd_osal_intr_active(int irqno);
int bsd_osal_intr_deactivate(int irqno);

uint8_t bsd_osal_read_uint8(uintptr_t base, size_t offset);
uint16_t bsd_osal_read_uint16(uintptr_t base, size_t offset);
uint32_t bsd_osal_read_uint32(uintptr_t base, size_t offset);
uint64_t bsd_osal_read_uint64(uintptr_t base, size_t offset);

void bsd_osal_write_uint8(uintptr_t base, size_t offset, uint8_t data);
void bsd_osal_write_uint16(uintptr_t base, size_t offset, uint16_t data);
void bsd_osal_write_uint32(uintptr_t base, size_t offset, uint32_t data);
void bsd_osal_write_uint64(uintptr_t base, size_t offset, uint64_t data);

void bsd_osal_panic(const char *fmt, ...);
void bsd_osal_assert(bool expr, const char *func, int line);

enum
{
    LIBBSD_PRINT_NORAML = 0,
    LIBBSD_PRINT_ERROR,
    LIBBSD_PRINT_NAIVE,
    LIBBSD_PRINT_DEBUG,
    LIBBSD_PRINT_VERBOSE
};
int bsd_osal_printf(int level, const char *fmt, ...);
int bsd_osal_dev_printf(int level, const char *dev_name, const char *fmt, ...);

void *bsd_osal_get_fdt(void);
void *bsd_osal_get_acpi(void);

#endif