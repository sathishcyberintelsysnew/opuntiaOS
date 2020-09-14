#ifndef __oneOS__API_H
#define __oneOS__API_H

#ifndef __oneOS__TYPES_H
#define __oneOS__TYPES_H

typedef unsigned long  uint64_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef long           int64_t;
typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef char           bool;

#define true  1
#define false 0

#endif

enum __sysid {
    SYSPRINT = 0,
    SYSEXIT,
    SYSFORK,
    SYSREAD,
    SYSWRITE,
    SYSOPEN,
    SYSCLOSE,
    SYSWAITPID,
    SYSCREAT,
    SYSLINK,
    SYSUNLINK,
    SYSEXEC,
    SYSCHDIR,
    SYSSIGACTION,
    SYSSIGRETURN,
    SYSRAISE,
    SYSGETPID,
    SYSKILL,
    SYSMKDIR,
    SYSRMDIR,
    SYSMMAP,
    SYSMUNMAP,
    SYSSOCKET,
    SYSBIND,
    SYSCONNECT,
    SYSGETDENTS,
    SYSIOCTL,
    SYSSETPGID,
    SYSGETPGID,
    SYSPTHREADCREATE,
    SYSSLEEP,
};
typedef enum __sysid sysid_t;

typedef uint32_t pid_t;

#define MAP_SHARED 0x01
#define MAP_PRIVATE 0x02
#define MAP_FIXED 0x10
#define MAP_ANONYMOUS 0x20
#define MAP_STACK 0x40

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXEC 0x4
#define PROT_NONE 0x0

struct mmap_params {
    uint32_t addr;
    uint32_t size;
    uint32_t alignment;
    uint32_t prot;
    uint32_t flags;
    uint32_t fd;
    uint32_t offset;
};
typedef struct mmap_params mmap_params_t;

/**
 * FILES
 */

#define EXT2_S_IFSOCK 0xC000
#define EXT2_S_IFLNK 0xA000
#define EXT2_S_IFREG 0x8000
#define EXT2_S_IFBLK 0x6000
#define EXT2_S_IFDIR 0x4000
#define EXT2_S_IFCHR 0x2000
#define EXT2_S_IFIFO 0x1000

#define EXT2_S_ISUID 0x0800
#define EXT2_S_ISGID 0x0400
#define EXT2_S_ISVTX 0x0200

#define EXT2_S_IRUSR 0x0100
#define EXT2_S_IWUSR 0x0080
#define EXT2_S_IXUSR 0x0040
#define EXT2_S_IRGRP 0x0020
#define EXT2_S_IWGRP 0x0010
#define EXT2_S_IXGRP 0x0008
#define EXT2_S_IROTH 0x0004
#define EXT2_S_IWOTH 0x0002
#define EXT2_S_IXOTH 0x0001

typedef uint16_t mode_t;

/**
 * SOCKETS
 */

enum SOCK_DOMAINS {
    PF_LOCAL,
    PF_INET,
    PF_INET6,
    PF_IPX,
    PF_NETLINK,
    PF_X25,
    PF_AX25,
    PF_ATMPVC,
    PF_APPLETALK,
    PF_PACKET,
};

enum SOCK_TYPES {
    SOCK_STREAM,
    SOCK_DGRAM,
    SOCK_SEQPACKET,
    SOCK_RAW,
    SOCK_RDM,
    SOCK_PACKET,
};

/**
 * IOCTL
 */

/* TTY */
#define TIOCGPGRP 0x0101
#define TIOCSPGRP 0x0102

/**
 * THREADS
 */

struct thread_create_params {
    uint32_t entry_point;
    uint32_t stack_start;
    uint32_t stack_size;
};
typedef struct thread_create_params thread_create_params_t;

#endif /* __oneOS__API_H */