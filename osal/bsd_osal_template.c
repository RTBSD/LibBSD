#include "bsd_osal.h"

#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif

__WEAK int bsd_osal_init(void) { return 0; }

__WEAK void *bsd_osal_malloc(size_t size) { return 0; }
__WEAK void *bsd_osal_realloc(void *ptr, size_t size) { return 0; }
__WEAK void bsd_osal_free(void *ptr) {}
__WEAK char *bsd_osal_strdup(const char *str, size_t *lenp) { return 0; }

__WEAK void bsd_osal_callout_init(bsd_osal_callout_t c) {}
__WEAK void bsd_osal_callout_destory(bsd_osal_callout_t c) {}
__WEAK int bsd_osal_callout_reset(bsd_osal_callout_t c, int timeout, bsd_callout_func_t ftn, void *arg) { return 0; }
__WEAK void bsd_osal_callout_stop(bsd_osal_callout_t c) {}
__WEAK void bsd_osal_callout_drain(bsd_osal_callout_t c) {}
__WEAK int bsd_osal_callout_schedule(bsd_osal_callout_t c, int to_ticks) { return 0; }

__WEAK void bsd_osal_mtx_init(bsd_osal_mutex_t m) {}
__WEAK void bsd_osal_mtx_destroy(bsd_osal_mutex_t m) {}
__WEAK void bsd_osal_mtx_lock(bsd_osal_mutex_t m) {}
__WEAK void bsd_osal_mtx_unlock(bsd_osal_mutex_t m) {}
__WEAK bool bsd_osal_mtx_own(bsd_osal_mutex_t m) { return false; }
__WEAK void bsd_osal_mtx_assert(bsd_osal_mutex_t m) {}
__WEAK int bsd_osal_mtx_sleep(bsd_osal_mutex_t m, int timeout) { return 0; }

__WEAK void bsd_osal_cv_init(bsd_osal_condvar_t c) {}
__WEAK void bsd_osal_cv_destory(bsd_osal_condvar_t c) {}
__WEAK void bsd_osal_cv_signal(bsd_osal_condvar_t c) {}
__WEAK void bsd_osal_cv_broadcast(bsd_osal_condvar_t c) {}
__WEAK int bsd_osal_cv_wait(bsd_osal_condvar_t c, uint32_t timeout) { return 0; }

__WEAK void bsd_osal_sx_init(bsd_osal_rwlock_t sx) {}
__WEAK void bsd_osal_sx_slock(bsd_osal_rwlock_t sx) {}
__WEAK void bsd_osal_sx_sunlock(bsd_osal_rwlock_t sx) {}
__WEAK void bsd_osal_sx_xlock(bsd_osal_rwlock_t sx) {}
__WEAK void bsd_osal_sx_xunlock(bsd_osal_rwlock_t sx) {}
__WEAK void bsd_osal_sx_assert(bsd_osal_rwlock_t sx, int what) {}

__WEAK void bsd_osal_sleep(int micro_seconds) {}
__WEAK uint32_t bsd_osal_get_tick_rate(void) { return 0; }
__WEAK uint64_t bsd_osal_get_current_tick(void) { return 0; }

__WEAK int bsd_osal_intr_disable(void) { return 0; }
__WEAK void bsd_osal_intr_restore(int flag) {}
__WEAK void bsd_osal_intr_setup_irq(int irqno, bsd_intr_handle_t handler, void *arg) {}
__WEAK int bsd_osal_intr_teardown(int irqno) { return 0; }
__WEAK int bsd_osal_intr_active(int irqno) { return 0; }
__WEAK int bsd_osal_intr_deactivate(int irqno) { return 0; }

__WEAK uint8_t bsd_osal_read_uint8(uintptr_t base, size_t offset) { return 0; }
__WEAK uint16_t bsd_osal_read_uint16(uintptr_t base, size_t offset) { return 0; }
__WEAK uint32_t bsd_osal_read_uint32(uintptr_t base, size_t offset) { return 0; }
__WEAK uint64_t bsd_osal_read_uint64(uintptr_t base, size_t offset) { return 0; }

__WEAK void bsd_osal_write_uint8(uintptr_t base, size_t offset, uint8_t data) {}
__WEAK void bsd_osal_write_uint16(uintptr_t base, size_t offset, uint16_t data) {}
__WEAK void bsd_osal_write_uint32(uintptr_t base, size_t offset, uint32_t data) {}
__WEAK void bsd_osal_write_uint64(uintptr_t base, size_t offset, uint64_t data) {}

__WEAK void bsd_osal_panic(const char *fmt, ...) {}
__WEAK void bsd_osal_assert(bool expr, const char *func, int line) {}

__WEAK int bsd_osal_printf(int level, const char *fmt, ...) { return 0; }
__WEAK int bsd_osal_dev_printf(int level, const char *dev_name, const char *fmt, ...) { return 0; }

__WEAK void *bsd_osal_get_fdt(void) { return 0; }
__WEAK void *bsd_osal_get_acpi(void) { return 0; }

__WEAK int bsd_osal_uart_dbg_init(void) {return 0;}
__WEAK int bsd_osal_uart_dbg_deinit(void) {return 0;}
__WEAK void bsd_osal_uart_dbg_putc(int c) {}
__WEAK int bsd_osal_uart_dbg_getc(void) {return -1;}

__WEAK void bsd_osal_icache_sync_range(uintptr_t base, size_t size) {}