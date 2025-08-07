/******************************************************************************
 *
 * Name: acbaremetal.h - OS specific defines, etc.
 *
 *****************************************************************************/

#ifndef __ACRTBSD_BAREMETAL_H__
#define __ACRTBSD_BAREMETAL_H__

#if defined(__RTBSD_LIBBSD__)
#define LIBBSD_FREEBSD
#include <bsd_compat.h>
#endif

#ifdef __aarch64__
#define ACPI_MACHINE_WIDTH          64
#define COMPILER_DEPENDENT_INT64    long
#define COMPILER_DEPENDENT_UINT64   unsigned long
#else
#define ACPI_MACHINE_WIDTH          32
#define COMPILER_DEPENDENT_INT64    long long
#define COMPILER_DEPENDENT_UINT64   unsigned long long
#endif

/* 使用 ACPICA 内部实现的互斥锁 */
#define ACPI_MUTEX_TYPE 1

/* 启用 ACPI 应用程序支持 */
/* #define ACPI_APPLICATION */

/* 启用单线程模式 */
#define ACPI_SINGLE_THREADED

/* 启用大型命名空间节点支持 */
#define ACPI_LARGE_NAMESPACE_NODE

/* 使用标准 C 头文件 */
/* #define ACPI_USE_STANDARD_HEADERS */

/* 使用系统提供的 C 标准库 */
#define ACPI_USE_SYSTEM_CLIBRARY

/* 使用系统 C 标准库的文件接口 */
/* #define ACPI_USB_SYSTEM_CLIBRARY_FILEIO */

/* 使用自定义的 calloc */
#define USE_NATIVE_ALLOCATE_ZEROED

/* 启用调试打印 */
// #define ACPI_DEBUG_OUTPUT

/* 启用 AcpiOsCreateCache 等接口 */
#define ACPI_USE_LOCAL_CACHE

/* 简化 GPE 相关接口实现 */
#define ACPI_REDUCED_HARDWARE  1

/******************************************************************************
 *
 * FUNCTION:    AcpiEnableDbgPrint
 *
 * PARAMETERS:  Enable, 	            - Enable/Disable debug print
 *
 * RETURN:      None
 *
 * DESCRIPTION: Enable/disable debug print
 *
 *****************************************************************************/

void AcpiEnableDbgPrint (
    bool Enable);

#endif /* __ACRTBSD_BAREMETAL_H__ */