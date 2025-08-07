#ifndef _SYS_CPU_H_
#define _SYS_CPU_H_

typedef	unsigned long cpuid_t;

struct cpu_info {
	cpuid_t ci_cpuid;
	uint32_t ci_acpiid;
	char cpu_name[25];
	uint64_t mpidr;
};

extern u_int maxcpus;
extern struct cpu_info cpusinfo[32];

#define cpu_info_store			cpusinfo

#define	CPU_IS_PRIMARY(ci)		((ci)->ci_cpuid == 0)
#define	CPU_INFO_ITERATOR		int
#define	CPU_INFO_FOREACH(cii, ci)	cii = 0, ci =  &cpusinfo[0]; cii < arm_cpu_max; cii++, ci++

static inline const char *cpu_name(struct cpu_info *ci)
{
	return ci->cpu_name;
}

#endif	/* !_SYS_CPU_H_ */
