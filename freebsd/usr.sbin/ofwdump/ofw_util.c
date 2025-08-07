/*-
 * Copyright (c) 2002 by Thomas Moestl <tmm@FreeBSD.org>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if defined(__RTBSD_LIBBSD__)
#define LIBBSD_FREEBSD
#define LIBBSD_FREEBSD_FDT
#include <bsd_compat.h>
#include "ofw_util.h"
#else
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <dev/ofw/openfirmio.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "pathnames.h"
#include "ofw_util.h"
#endif

#define	OFW_IOCTL(fd, cmd, val)	do {					\
	if (ioctl(fd, cmd, val) == -1)					\
		err(EX_IOERR, "ioctl(..., " #cmd ", ...) failed");	\
} while (0)

#if !defined(__RTBSD_LIBBSD__)
int
ofw_open(int mode)
{
	int fd;

	if ((fd = open(PATH_DEV_OPENFIRM, mode)) == -1)
		err(EX_UNAVAILABLE, "could not open " PATH_DEV_OPENFIRM);
	return (fd);
}

void
ofw_close(int fd)
{

	close(fd);
}
#endif

phandle_t
ofw_root(int fd)
{
#if !defined(__RTBSD_LIBBSD__)
	return (ofw_peer(fd, 0));
#else
	phandle_t node;

	if ((node = OF_finddevice("/")) == -1)
		return 0;

	return node;
#endif
}

#if !defined(__RTBSD_LIBBSD__)
phandle_t
ofw_optnode(int fd)
{
	phandle_t rv;

	OFW_IOCTL(fd, OFIOCGETOPTNODE, &rv);
	return (rv);
}
#endif

phandle_t
ofw_peer(int fd, phandle_t node)
{
#if !defined(__RTBSD_LIBBSD__)
	phandle_t rv;

	rv = node;
	OFW_IOCTL(fd, OFIOCGETNEXT, &rv);
	return (rv);
#else
	return OF_peer(node);
#endif
}

phandle_t
ofw_child(int fd, phandle_t node)
{
#if !defined(__RTBSD_LIBBSD__)
	phandle_t rv;

	rv = node;
	OFW_IOCTL(fd, OFIOCGETCHILD, &rv);
	return (rv);
#else
	return OF_child(node);
#endif
}

phandle_t
ofw_finddevice(int fd, const char *name)
{
#if !defined(__RTBSD_LIBBSD__)
	struct ofiocdesc d;

	d.of_nodeid = 0;
	d.of_namelen = strlen(name);
	d.of_name = name;
	d.of_buflen = 0;
	d.of_buf = NULL;
	if (ioctl(fd, OFIOCFINDDEVICE, &d) == -1) {
		if (errno == ENOENT)
			err(EX_UNAVAILABLE, "Node '%s' not found", name);
		else
			err(EX_IOERR,
			    "ioctl(..., OFIOCFINDDEVICE, ...) failed");
	}
	return (d.of_nodeid);
#else
	phandle_t node;

	if ((node = OF_finddevice("/")) == -1)
		return 0;

	if ((node = fdt_find_compatible(node, "simple-bus", 1)) == 0)
		return 0;

	if ((node = fdt_find_compatible(node, name, 1)) == 0)
		return 0;

	return node;
#endif
}

int
ofw_firstprop(int fd, phandle_t node, char *buf, int buflen)
{

	return (ofw_nextprop(fd, node, NULL, buf, buflen));
}

int
ofw_nextprop(int fd, phandle_t node, const char *prev, char *buf, int buflen)
{
#if !defined(__RTBSD_LIBBSD__)
	struct ofiocdesc d;

	d.of_nodeid = node;
	d.of_namelen = prev != NULL ? strlen(prev) : 0;
	d.of_name = prev;
	d.of_buflen = buflen;
	d.of_buf = buf;
	if (ioctl(fd, OFIOCNEXTPROP, &d) == -1) {
		if (errno == ENOENT)
			return (0);
		else
			err(EX_IOERR, "ioctl(..., OFIOCNEXTPROP, ...) failed");
	}
	return (d.of_buflen);
#else
	int ret = OF_nextprop(node, prev, buf, buflen);
	return (ret == -1) ? 0 : ret;
#endif
}

static void *
ofw_malloc(int size)
{
	void *p;

#if !defined(__RTBSD_LIBBSD__)
	if ((p = malloc(size)) == NULL)
		err(EX_OSERR, "malloc() failed");
#else
	if ((p = bsd_malloc(size, 0U, 0U)) == NULL)
		err(EX_OSERR, "malloc() failed");	
#endif
	return (p);
}

int
ofw_getprop(int fd, phandle_t node, const char *name, void *buf, int buflen)
{
#if !defined(__RTBSD_LIBBSD__)
	struct ofiocdesc d;

	d.of_nodeid = node;
	d.of_namelen = strlen(name);
	d.of_name = name;
	d.of_buflen = buflen;
	d.of_buf = buf;
	OFW_IOCTL(fd, OFIOCGET, &d);
	return (d.of_buflen);
#else
	ssize_t ret = OF_getproplen(node, name);
	return (ret == -1) ? 0 : (int)ret;
#endif
}

int
ofw_setprop(int fd, phandle_t node, const char *name, const void *buf,
    int buflen)
{
#if !defined(__RTBSD_LIBBSD__)
	struct ofiocdesc d;

	d.of_nodeid = node;
	d.of_namelen = strlen(name);
	d.of_name = name;
	d.of_buflen = buflen;
	d.of_buf = ofw_malloc(buflen);
	memcpy(d.of_buf, buf, buflen);
	OFW_IOCTL(fd, OFIOCSET, &d);
	bsd_free(d.of_buf);
	return (d.of_buflen);
#else
	ssize_t ret = OF_setprop(node, name, buf, buflen);
	return (ret == -1) ? 0 : (int)ret;
#endif
}

int
ofw_getproplen(int fd, phandle_t node, const char *name)
{
#if !defined(__RTBSD_LIBBSD__)
	struct ofiocdesc d;

	d.of_nodeid = node;
	d.of_namelen = strlen(name);
	d.of_name = name;
	OFW_IOCTL(fd, OFIOCGETPROPLEN, &d);
	return (d.of_buflen);
#else
	ssize_t ret = OF_getproplen(node, name);
	return (ret == -1) ? 0 : (int)ret;
#endif
}

int
ofw_getprop_alloc(int fd, phandle_t node, const char *name, void **buf,
    int *buflen, int reserve)
{
#if !defined(__RTBSD_LIBBSD__)
	struct ofiocdesc d;
	int len, rv;

	do {
		len = ofw_getproplen(fd, node, name);
		if (len < 0)
			return (len);
		if (*buflen < len + reserve) {
			if (*buf != NULL)
				bsd_free(*buf);
			*buflen = len + reserve + OFIOCMAXVALUE;
			*buf = ofw_malloc(*buflen);
		}
		d.of_nodeid = node;
		d.of_namelen = strlen(name);
		d.of_name = name;
		d.of_buflen = *buflen - reserve;
		d.of_buf = *buf;
		rv = ioctl(fd, OFIOCGET, &d);
	} while (rv == -1 && errno == ENOMEM);
	if (rv == -1)
		err(EX_IOERR, "ioctl(..., OFIOCGET, ...) failed");
	return (d.of_buflen);
#else
	ssize_t ret = OF_getprop_alloc(node, name, buf);
	return ret;
#endif
}
