import os

EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or '/usr/bin'

# 选项
use_aarch64 = ARGUMENTS.get('AARCH64', '0') == '1'
use_fdt = ARGUMENTS.get('FDT', '0') == '1'
use_acpi = ARGUMENTS.get('ACPI', '0') == '1'
use_gdb_stub = ARGUMENTS.get('GDBSTUB', '0') == '1'

if use_aarch64:
    cc_prefix = 'aarch64-none-elf-gcc'
    ar_prefix = 'aarch64-none-elf-ar'

env = Environment(
    tools=['default', 'gcc'],
    CC=EXEC_PATH + '/' + cc_prefix,
    AR=EXEC_PATH + '/' + ar_prefix,
    CFLAGS=[
        '-D__RTBSD_LIBBSD__',
        '-std=gnu99',
        '-ffunction-sections',
        '-fdata-sections',
        '-Wall',
        '-Wno-unused-function',
    ],
    CPPPATH=[
        '.',
        'common',
        'core',
        'compat',
        'freebsd/lib',
        'freebsd/sys',
        'freebsd/sys/contrib/libfdt',
        'freebsd/sys/contrib/dev/acpica/include',
        'freebsd/sys/contrib/dev/acpica/include/platform',
        'freebsd/sys/contrib/dev/acpica/compiler',
        'freebsd/usr.sbin/acpi/acpidump',
        'freebsd/usr.sbin/ofwdump',
    ]
)

if use_aarch64:
    env.Append(CFLAGS=['-DAARCH64=1'])
if use_fdt:
    env.Append(CFLAGS=['-DFDT=1'])
if use_acpi:
    env.Append(CFLAGS=['-DDEV_ACPI=1'])
if use_gdb_stub:
    env.Append(CFLAGS=['-DKDB=1'])

# 基础源文件
sources = [
    'core/bsd_core.c',
    'compat/freebsd/local/bus_if.c',
    'compat/freebsd/local/device_if.c',
    'freebsd/sys/kern/subr_kobj.c',
    'freebsd/sys/kern/kern_module.c',
    'freebsd/sys/kern/subr_bus.c',
    'freebsd/sys/kern/kern_linker.c',
    'freebsd/sys/kern/subr_rman.c',
    'freebsd/sys/kern/subr_sbuf.c',
    'freebsd/sys/libkern/memmem.c',
    'freebsd/sys/libkern/strchrnul.c',
]

if use_aarch64:
    sources += [
    'freebsd/sys/arm64/arm64/autoconf.c',
    'freebsd/sys/arm64/arm64/nexus.c',
    ]

if use_fdt:
    sources += [
        'compat/freebsd/local/ofw_if.c',
        'compat/freebsd/local/ofw_bus_if.c',
        'freebsd/sys/dev/ofw/ofw_bus_subr.c',
        'freebsd/sys/dev/ofw/ofw_fdt.c',
        'freebsd/sys/dev/ofw/ofw_pcib.c',
        'freebsd/sys/dev/ofw/ofw_subr.c',
        'freebsd/sys/dev/ofw/ofwbus.c',
        'freebsd/sys/dev/ofw/openfirm.c',
        'freebsd/sys/dev/fdt/fdt_common.c',
        'freebsd/sys/dev/fdt/simplebus.c',
        'freebsd/usr.sbin/ofwdump/ofwdump.c',
        'freebsd/usr.sbin/ofwdump/ofw_util.c',
        # libfdt
        'freebsd/sys/contrib/libfdt/fdt_addresses.c',
        'freebsd/sys/contrib/libfdt/fdt_empty_tree.c',
        'freebsd/sys/contrib/libfdt/fdt_overlay.c',
        'freebsd/sys/contrib/libfdt/fdt_ro.c',
        'freebsd/sys/contrib/libfdt/fdt_rw.c',
        'freebsd/sys/contrib/libfdt/fdt_strerror.c',
        'freebsd/sys/contrib/libfdt/fdt_sw.c',
        'freebsd/sys/contrib/libfdt/fdt_wip.c',
        'freebsd/sys/contrib/libfdt/fdt.c',
    ]

if use_acpi:
    sources += [
        'compat/freebsd/local/acpi_bus_if.c',
        'compat/freebsd/local/acpi_if.c',
        'freebsd/lib/libnetbsd/sys/kern/subr_autoconf.c',
        'freebsd/lib/libnetbsd/sys/kern/subr_device.c',
        'freebsd/lib/libnetbsd/sys/lib/libkern/pmatch.c',
        'freebsd/lib/libnetbsd/sys/lib/libkern/strlist.c',
        'freebsd/lib/libnetbsd/netbsd.c',
        'freebsd/sys/arm64/acpica/OsdEnvironment.c',
        'freebsd/sys/dev/acpica/Osd/OsdDebug.c',
        'freebsd/sys/dev/acpica/Osd/OsdHardware.c',
        'freebsd/sys/dev/acpica/Osd/OsdInterrupt.c',
        'freebsd/sys/dev/acpica/Osd/OsdMemory.c',
        'freebsd/sys/dev/acpica/Osd/OsdSchedule.c',
        'freebsd/sys/dev/acpica/Osd/OsdStream.c',
        'freebsd/sys/dev/acpica/Osd/OsdSynch.c',
        'freebsd/sys/dev/acpica/Osd/OsdTable.c',
        'freebsd/lib/libnetbsd/sys/arm/fdt/acpi_fdt.c',
        'freebsd/lib/libnetbsd/sys/arm/acpi/cpu_acpi.c',
        'freebsd/lib/libnetbsd/sys/dev/acpi/acpi.c',
        'freebsd/lib/libnetbsd/sys/dev/acpi/acpi_util.c',
        'freebsd/lib/libnetbsd/sys/dev/acpi/acpi_resource.c',
        'freebsd/lib/libnetbsd/sys/dev/acpi/acpi_pcd.c',
        'freebsd/lib/libnetbsd/sys/dev/acpi/acpi_pcc.c',
        'freebsd/lib/libnetbsd/sys/dev/acpi/acpi_cppc.c',
        'freebsd/lib/libnetbsd/sys/dev/acpi/acpi_tz.c',
        'freebsd/lib/libnetbsd/sys/dev/acpi/acpi_power.c',
        'freebsd/sys/arm64/acpica/acpi_machdep.c',
        'freebsd/sys/dev/acpica/acpi_package.c',
        'freebsd/sys/dev/acpica/acpi_resource.c',
        'freebsd/sys/dev/acpica/acpi.c',
        'freebsd/usr.sbin/acpi/acpidump/acpi.c',
        'freebsd/usr.sbin/acpi/acpidump/acpidump.c',
    ]
    # ACPICA 组件
    for subdir in [
        'dispatcher', 'events', 'executer', 'hardware',
        'namespace', 'parser', 'resources', 'tables', 'utilities'
    ]:
        sources += Glob('freebsd/sys/contrib/dev/acpica/components/%s/*.c' % subdir)

if use_gdb_stub and use_aarch64:
    sources += [
        'freebsd/sys/arm64/arm64/debug_monitor.c',
        'freebsd/sys/arm64/arm64/gdb_machdep.c',
        'freebsd/sys/dev/uart/uart_dbg.c',
        'freebsd/sys/gdb/gdb_main.c',
        'freebsd/sys/gdb/gdb_packet.c',
        'freebsd/sys/kern/subr_kdb.c',
    ]

# 生成静态库
lib = env.StaticLibrary('bsd', sources)
Default(lib)