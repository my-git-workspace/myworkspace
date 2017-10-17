CFLAGS += -I/home/msys/qnap/qnap/working/zpool-porting/qnap/ZFSOnLinux/zfs/include
CFLAGS += -I/home/msys/qnap/qnap/working/zpool-porting/qnap/ZFSOnLinux/zfs/lib/libspl/include
LDFLAGS += -L/home/msys/qnap/qnap/working/zpool-porting/qnap/ZFSOnLinux/zfs/lib/libefi  
CFLAGS += -D_GNU_SOURCE
all:
	gcc ${CFLAGS} ${LDFLAGS} main.c -o main -DQNAP_ZFS_LINUX -lefi -lz -luuid
.PHONY:
	${RM} -f main

