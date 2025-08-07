cmake_minimum_required(VERSION 3.16)
project(libbsd C)

# 指定交叉编译工具链
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER aarch64-none-elf-gcc)
set(CMAKE_AR aarch64-none-elf-ar)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__RTBSD_LIBBSD__")

# 选项，和 makefile 保持一致
option(CONFIG_USE_FREEBSD_FDT "Enable FDT support" OFF)
option(CONFIG_USE_FREEBSD_ACPI "Enable ACPI support" OFF)

if(CONFIG_USE_FREEBSD_FDT)
    add_definitions(-DFDT=1)
endif()
if(CONFIG_USE_FREEBSD_ACPI)
    add_definitions(-DDEV_ACPI=1)
endif()

# 基础源文件
set(SRCS
    core/bsd_core.c
    osal/bsd_osal_threadx.c
    compat/freebsd/local/bus_if.c
    compat/freebsd/local/device_if.c
    freebsd/sys/kern/subr_kobj.c
    freebsd/sys/kern/kern_module.c
    freebsd/sys/kern/subr_bus.c
    freebsd/sys/kern/kern_linker.c
    freebsd/sys/kern/subr_rman.c
    freebsd/sys/kern/subr_sbuf.c
    freebsd/sys/arm64/arm64/autoconf.c
    freebsd/sys/arm64/arm64/nexus.c
)

# FDT 相关
if(CONFIG_USE_FREEBSD_FDT)
    list(APPEND SRCS
        compat/freebsd/local/ofw_if.c
        compat/freebsd/local/ofw_bus_if.c
        freebsd/sys/dev/ofw/ofw_bus_subr.c
        freebsd/sys/dev/ofw/ofw_fdt.c
        freebsd/sys/dev/ofw/ofw_pcib.c
        freebsd/sys/dev/ofw/ofw_subr.c
        freebsd/sys/dev/ofw/ofwbus.c
        freebsd/sys/dev/ofw/openfirm.c
        freebsd/sys/dev/fdt/fdt_common.c
        freebsd/sys/dev/fdt/simplebus.c
        freebsd/usr.sbin/ofwdump/ofwdump.c
        freebsd/usr.sbin/ofwdump/ofw_util.c
        # libfdt
        freebsd/sys/contrib/libfdt/fdt_addresses.c
        freebsd/sys/contrib/libfdt/fdt_empty_tree.c
        freebsd/sys/contrib/libfdt/fdt_overlay.c
        freebsd/sys/contrib/libfdt/fdt_ro.c
        freebsd/sys/contrib/libfdt/fdt_rw.c
        freebsd/sys/contrib/libfdt/fdt_strerror.c
        freebsd/sys/contrib/libfdt/fdt_sw.c
        freebsd/sys/contrib/libfdt/fdt_wip.c
        freebsd/sys/contrib/libfdt/fdt.c
    )
endif()

# ACPI 相关
if(CONFIG_USE_FREEBSD_ACPI)
    list(APPEND SRCS
        compat/freebsd/local/acpi_bus_if.c
        compat/freebsd/local/acpi_if.c
        freebsd/lib/libnetbsd/sys/kern/subr_autoconf.c
        freebsd/lib/libnetbsd/sys/kern/subr_device.c
        freebsd/lib/libnetbsd/sys/lib/libkern/pmatch.c
        freebsd/lib/libnetbsd/sys/lib/libkern/strlist.c
        freebsd/lib/libnetbsd/netbsd.c
        freebsd/sys/arm64/acpica/OsdEnvironment.c
        freebsd/sys/dev/acpica/Osd/OsdDebug.c
        freebsd/sys/dev/acpica/Osd/OsdHardware.c
        freebsd/sys/dev/acpica/Osd/OsdInterrupt.c
        freebsd/sys/dev/acpica/Osd/OsdMemory.c
        freebsd/sys/dev/acpica/Osd/OsdSchedule.c
        freebsd/sys/dev/acpica/Osd/OsdStream.c
        freebsd/sys/dev/acpica/Osd/OsdSynch.c
        freebsd/sys/dev/acpica/Osd/OsdTable.c
        freebsd/lib/libnetbsd/sys/arm/fdt/acpi_fdt.c
        freebsd/lib/libnetbsd/sys/arm/acpi/cpu_acpi.c
        freebsd/lib/libnetbsd/sys/dev/acpi/acpi.c
        freebsd/lib/libnetbsd/sys/dev/acpi/acpi_util.c
        freebsd/lib/libnetbsd/sys/dev/acpi/acpi_resource.c
        freebsd/lib/libnetbsd/sys/dev/acpi/acpi_pcd.c
        freebsd/lib/libnetbsd/sys/dev/acpi/acpi_pcc.c
        freebsd/lib/libnetbsd/sys/dev/acpi/acpi_cppc.c
        freebsd/lib/libnetbsd/sys/dev/acpi/acpi_tz.c
        freebsd/lib/libnetbsd/sys/dev/acpi/acpi_power.c
        freebsd/sys/arm64/acpica/acpi_machdep.c
        freebsd/sys/dev/acpica/acpi_package.c
        freebsd/sys/dev/acpica/acpi_resource.c
        freebsd/sys/dev/acpica/acpi.c
        freebsd/usr.sbin/acpi/acpidump/acpi.c
        freebsd/usr.sbin/acpi/acpidump/acpidump.c
        # acpica
    )
    # ACPICA 组件
    file(GLOB ACPICA_SRCS
        freebsd/sys/contrib/dev/acpica/components/dispatcher/*.c
        freebsd/sys/contrib/dev/acpica/components/events/*.c
        freebsd/sys/contrib/dev/acpica/components/executer/*.c
        freebsd/sys/contrib/dev/acpica/components/hardware/*.c
        freebsd/sys/contrib/dev/acpica/components/namespace/*.c
        freebsd/sys/contrib/dev/acpica/components/parser/*.c
        freebsd/sys/contrib/dev/acpica/components/resources/*.c
        freebsd/sys/contrib/dev/acpica/components/tables/*.c
        freebsd/sys/contrib/dev/acpica/components/utilities/*.c
    )
    list(APPEND SRCS ${ACPICA_SRCS})
endif()

add_library(bsd STATIC ${SRCS})

# 头文件路径整合自 include.mk
target_include_directories(bsd PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/compat
    ${CMAKE_CURRENT_SOURCE_DIR}/freebsd/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/freebsd/sys
    ${CMAKE_CURRENT_SOURCE_DIR}/freebsd/sys/contrib/libfdt
    ${CMAKE_CURRENT_SOURCE_DIR}/freebsd/sys/contrib/dev/acpica/include
    ${CMAKE_CURRENT_SOURCE_DIR}/freebsd/sys/contrib/dev/acpica/include/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/freebsd/sys/contrib/dev/acpica/compiler
    ${CMAKE_CURRENT_SOURCE_DIR}/freebsd/usr.sbin/acpi/acpidump
    ${CMAKE_CURRENT_SOURCE_DIR}/freebsd/usr.sbin/ofwdump
)

set_target_properties(bsd PROPERTIES OUTPUT_NAME "bsd")