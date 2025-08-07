#ifndef _SYS_UUID_H_
#define	_SYS_UUID_H_

#if !defined(__RTBSD_LIBBSD__)
#include <sys/types.h>
#endif

/* Length of a node address (an IEEE 802 address). */
#define	_UUID_NODE_LEN		6

/*
 * See also:
 *      http://www.opengroup.org/dce/info/draft-leach-uuids-guids-01.txt
 *      http://www.opengroup.org/onlinepubs/009629399/apdxa.htm
 *
 * A DCE 1.1 compatible source representation of UUIDs.
 */
struct uuid {
	uint32_t	time_low;
	uint16_t	time_mid;
	uint16_t	time_hi_and_version;
	uint8_t		clock_seq_hi_and_reserved;
	uint8_t		clock_seq_low;
	uint8_t		node[_UUID_NODE_LEN];
};

/* XXX namespace pollution? */
typedef struct uuid uuid_t;

__BEGIN_DECLS
int	uuidgen(struct uuid *, int);
__END_DECLS

#endif /* _SYS_UUID_H_ */