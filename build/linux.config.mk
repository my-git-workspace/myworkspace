#Declare config here
MACHINE_CPUARCH=0
MACHINE_ARCH=0
PLATFORM=lpl

EXTRA_CFLAGS+=-DQNAP_ZFS_LINUX -DQNAP_SCST_LINUX -g 
EXTRA_CFLAGS+= -DNEED_SOLARIS_BOOLEAN
EXTRA_CFLAGS+=-DBYTE_ORDER=__BYTE_ORDER__
EXTRA_CFLAGS+=-DBIG_ENDIAN=__ORDER_BIG_ENDIAN__
EXTRA_CFLAGS+=-DLITTLE_ENDIAN=__ORDER_LITTLE_ENDIAN__
EXTRA_CFLAGS+=-Wformat=0

OPENSOLARIS_USR_DISTDIR= $(PWD)/../../../cddl/contrib/opensolaris
OPENSOLARIS_SYS_DISTDIR= $(PWD)/../../../sys/cddl/contrib/opensolaris

ifeq ($(shell basename $(PWD)), zfs-module)  ##Note for kernel space use $(PWD)
RM_EXTRA_CFLAGS=-DSKEIN_ASM -DSKEIN_USE_ASM=1792
KBUILD_EXTRA_SYMBOLS=$(PWD)/../sys/cddl/compat/lpl/Module.symvers
KBUILD_EXTRA_SYMBOLS+=$(PWD)/../../linux_dependencies/ocf-linux-20171122/ocf/Module.symvers
EXTRA_CFLAGS+=-std=gnu99 -Wno-declaration-after-statement #added for ISO C90 mixed declaration
EXTRA_CFLAGS+=-Wframe-larger-than=8192
EXTRA_CFLAGS+=-Wno-unknown-pragmas
EXTRA_CFLAGS+=-Wno-unused-function ## defined but not used warning
EXTRA_CFLAGS+=-Wno-missing-prototypes
EXTRA_CFLAGS+=-Wno-undef
EXTRA_CFLAGS+=-Wno-strict-prototypes
EXTRA_CFLAGS+=-Wno-cast-qual
EXTRA_CFLAGS+=-Wno-parentheses
EXTRA_CFLAGS+=-Wno-redundant-decls
EXTRA_CFLAGS+=-Wno-missing-braces
EXTRA_CFLAGS+=-Wno-uninitialized
EXTRA_CFLAGS+=-Wno-unused
EXTRA_CFLAGS+=-Wno-inline
EXTRA_CFLAGS+=-Wno-switch
EXTRA_CFLAGS+=-Wno-pointer-arith
EXTRA_CFLAGS+=-Wno-overflow
EXTRA_CFLAGS+=-D_KERNEL
EXTRA_CFLAGS += -Wno-unused-variable #Added to avoid "defined but not used" warning
EXTRA_CFLAGS += -I$(PWD)/../../linux_dependencies
EXTRA_CFLAGS += -I$(PWD)/../../linux_dependencies/ocf-linux-20171122/ocf
RM_SRCS += gfs.c #Skipped in linux platform
VPATH+= $(PWD)/../../zfs/zfs-module
SRCS+= zfs_proc.c
endif

ifeq ($(shell basename $(PWD)), sha256-module)  ##Note for kernel space use $(PWD)
RM_EXTRA_CFLAGS=-no-integrated-as -v
RM_SRCS=sha256-ssse3-asm.S
EXTRA_CFLAGS += -I$(PWD)/../sys/cddl/compat/lpl 
EXTRA_CFLAGS +=	-I$(PWD)/../sys/cddl/contrib/opensolaris/uts/common
endif

ifeq ($(shell basename `pwd`), zpool)
LDFLAGS += -L$(PWD)/../../../../linux_dependencies/libbsd
LDFLAGS += -L$(PWD)/../../../../linux_dependencies/libefi
LIBS +=  -lblkid -lbsd -lefi -lz -luuid 
EXTRA_CFLAGS += -I$(PWD)/../../../../linux_dependencies/libbsd/include
RM_LIB = geom  
EXTRA_CFLAGS += -I$(PWD)/../../../../linux_dependencies/libefi/include
EXTRA_CFLAGS += -Wno-implicit-function-declaration

#-Wl,-rpath added to avoid LD_LIBRARY_PATH
CFLAGS+=-Wl,-rpath,$(PWD)/../../lib/libnvpair
CFLAGS+=-Wl,-rpath,$(PWD)/../../../../linux_dependencies/libbsd
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libuutil
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libumem
CFLAGS+=-Wl,-rpath,$(PWD)/../../../../linux_dependencies/libefi
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libuutil
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libumem
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libzfs
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libzfs_core
CFLAGS+=-Wl,-rpath,$(PWD)/../../lib/libavl
endif

ifeq ($(shell basename `pwd`), libzfs)
LDFLAGS += -L$(PWD)/../../../../linux_dependencies/libbsd	
LDFLAGS += -L$(PWD)/../../../../linux_dependencies/libefi
LDFLAGS+= -L$(PWD)/../libuutil
LIBS +=  -lblkid -lbsd -lssl -lcrypto -lefi -lz -luuid -luutil
RM_LIB=md
EXTRA_CFLAGS += -I$(PWD)/../../../../linux_dependencies/libbsd/include 
EXTRA_CFLAGS +=-Wno-implicit-function-declaration ## added to remove implicit declaration
EXTRA_CFLAGS +=-Wno-cpp
endif

ifeq ($(shell basename `pwd`), libnvpair)
EXTRA_CFLAGS +=-Wno-format-security
endif

ifeq ($(shell basename `pwd`), libuutil)
LIBS += -lpthread 
endif

ifeq ($(shell basename `pwd`), libzpool)
CFLAGS += -I$(PWD)/../../../../linux_dependencies
RM_LIB = md
RM_SRCS = opensolaris_atomic.c #skipping for linux platform TODO if required for linux
EXTRA_CFLAGS += -I$(PWD)/../../../../linux_dependencies/libbsd/include 
LDFLAGS += -L$(PWD)/../../../../linux_dependencies/libbsd
VPATH+=$(PWD)/../../../sys/cddl/compat/lpl/kern
CRYPTO_SRCS+=lpl_atomic.c
LDFLAGS+=-L$(PWD)/../../lib/libumem
LIBS+=-lumem -lbsd
endif

ifeq ($(shell basename `pwd`), zinject)
LDFLAGS += -L$(PWD)/../../../../linux_dependencies/libbsd
LDFLAGS+= -L$(PWD)/../../lib/libavl
RM_LIB = geom
LIBS+=-lbsd -lavl
endif

ifeq ($(shell basename `pwd`), zdb)
RM_LIB = geom
endif

ifeq ($(shell basename `pwd`), zfilecopy)
RM_LIB = geom
SRCS = zfilecopy.c
#-Wl,-rpath added to avoid LD_LIBRARY_PATH
CFLAGS+=-Wl,-rpath,$(PWD)/../../lib/libnvpair
CFLAGS+=-Wl,-rpath,$(PWD)/../../../../linux_dependencies/libbsd
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libuutil
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libumem
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libuutil
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libumem
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libzfs
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libzfs_core
endif

ifeq ($(shell basename `pwd`), zfileclone)
RM_LIB = geom
SRCS = zfileclone.c
endif

ifeq ($(shell basename `pwd`), zstreamdump)
CFLAGS += -I$(PWD)/../../../../linux_dependencies/libspl

SRCS = zstreamdump.c
endif

ifeq ($(shell basename `pwd`), zhack)
RM_LIB = geom
SRCS = zhack.c
endif

ifeq ($(shell basename `pwd`), zlook)
SRCS = zlook.c
endif

ifeq ($(shell basename `pwd`), ztest)
LDFLAGS += -L$(PWD)/../../../../linux_dependencies/libbsd
EXTRA_CFLAGS+= -Wno-implicit-function-declaration
RM_LIB = geom
SRCS = ztest.c
LIBS+=-lbsd 
endif

ifeq ($(shell basename `pwd`), zfs)
RM_LIB=geom jail
LDFLAGS += -L$(PWD)/../../../../linux_dependencies/libbsd	
LIBS+=-lbsd -lz -luuid
EXTRA_CFLAGS+=-Wno-implicit-function-declaration ## added to remove implicit declaration


#-Wl,-rpath added to avoid LD_LIBRARY_PATH
CFLAGS+=-Wl,-rpath,$(PWD)/../../lib/libnvpair
CFLAGS+=-Wl,-rpath,$(PWD)/../../../../linux_dependencies/libbsd
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libuutil
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libumem
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libuutil
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libumem
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libzfs
CFLAGS+=-Wl,-rpath,$(PWD)/../../../cddl/lib/libzfs_core
endif

ifeq ($(shell basename `pwd`), lib)
RM_DIRS = libctf
endif

ifeq ($(shell basename `pwd`), usr.bin)
RM_DIRS = ctfconvert ctfmerge ctfdump sgsmsg
endif

ifeq ($(shell basename `pwd`), nbq)
LIB = scstnbq
endif

ifeq ($(shell basename `pwd`), scstlib)
LIB = scstlib
endif
ifeq ($(shell basename `pwd`), scstzvolfn)
INC_DIR = $(PWD)/../../../../zfs
LIB = scstzvolfn
CFLAGS+=-L$(PWD)/../../../../zfs/cddl/lib/libzfs
CFLAGS+=-L$(PWD)/../../../../zfs/cddl/lib/libnvpair
CFLAGS+=-L$(PWD)/../../../../zfs/cddl/lib/libuutil
CFLAGS+=-L$(PWD)/../../../../zfs/cddl/lib/libavl
RM_LIB=geom
endif
ifeq ($(shell basename `pwd`), main)
LIBS+=-lscstlib -lscstzvolfn -lzfs -lnvpair -lavl -lumem -luutil -lzfs_core
CFLAGS+=-L../../../../../zfs/cddl/lib/libzfs
CFLAGS+=-L../../../../../zfs/cddl/lib/libumem
CFLAGS+=-L../../../../../zfs/cddl/lib/libnvpair
CFLAGS+=-L../../../../../zfs/cddl/lib/libavl
CFLAGS+=-L../../../../../zfs/cddl/lib/libumem
CFLAGS+=-L../../../../../zfs/cddl/lib/libuutil
CFLAGS+=-L../../../../../zfs/cddl/lib/libzfs_core
endif
ifeq ($(shell basename `pwd`), login_app)
LIBS += -lscstnbq -lcares
endif

ifeq ($(shell basename $(PWD)), scst_vdisk)
EXTRA_CFLAGS+=-std=gnu99 -Wno-declaration-after-statement #added for ISO C90 mixed declaration
EXTRA_CFLAGS+=-Wframe-larger-than=8192
EXTRA_CFLAGS+=-Wno-unknown-pragmas
EXTRA_CFLAGS+=-Wno-unused-function ## defined but not used warning
EXTRA_CFLAGS+=-Wno-missing-prototypes
EXTRA_CFLAGS+=-Wno-undef
EXTRA_CFLAGS+=-Wno-strict-prototypes
EXTRA_CFLAGS+=-Wno-cast-qual
EXTRA_CFLAGS+=-Wno-parentheses
EXTRA_CFLAGS+=-Wno-redundant-decls
EXTRA_CFLAGS+=-Wno-missing-braces
EXTRA_CFLAGS+=-Wno-uninitialized
EXTRA_CFLAGS+=-Wno-unused
EXTRA_CFLAGS+=-Wno-inline
EXTRA_CFLAGS+=-Wno-switch
EXTRA_CFLAGS+=-Wno-pointer-arith
EXTRA_CFLAGS+=-Wno-overflow
EXTRA_CFLAGS+=-D_KERNEL
EXTRA_CFLAGS += -Wno-unused-variable #Added to avoid "defined but not used" warning
VPATH=$(PWD)
INC_DIR=$(PWD)/../../../zfs/sys
KBUILD_EXTRA_SYMBOLS += ${INC_DIR}/../../scst/scst/main/Module.symvers
endif

ifeq ($(shell basename $(PWD)), iser_main)
EXTRA_CFLAGS+=-std=gnu99 -Wno-declaration-after-statement #added for ISO C90 mixed declaration
EXTRA_CFLAGS+=-Wframe-larger-than=8192
EXTRA_CFLAGS+=-Wno-unknown-pragmas
EXTRA_CFLAGS+=-Wno-unused-function ## defined but not used warning
EXTRA_CFLAGS+=-Wno-missing-prototypes
EXTRA_CFLAGS+=-Wno-undef
EXTRA_CFLAGS+=-Wno-strict-prototypes
EXTRA_CFLAGS+=-Wno-cast-qual
EXTRA_CFLAGS+=-Wno-parentheses
EXTRA_CFLAGS+=-Wno-redundant-decls
EXTRA_CFLAGS+=-Wno-missing-braces
EXTRA_CFLAGS+=-Wno-uninitialized
EXTRA_CFLAGS+=-Wno-unused
EXTRA_CFLAGS+=-Wno-inline
EXTRA_CFLAGS+=-Wno-switch
EXTRA_CFLAGS+=-Wno-pointer-arith
EXTRA_CFLAGS+=-Wno-overflow
EXTRA_CFLAGS+=-D_KERNEL
EXTRA_CFLAGS += -Wno-unused-variable #Added to avoid "defined but not used" warning
VPATH=$(PWD)
INC_DIR=$(PWD)/../../../../zfs/sys
KBUILD_EXTRA_SYMBOLS +=$(PWD)/../main/Module.symvers
endif

ifeq ($(shell basename $(PWD)), main)
VPATH=$(PWD)
EXTRA_CFLAGS+=-std=gnu99 -Wno-declaration-after-statement #added for ISO C90 mixed declaration
EXTRA_CFLAGS+=-Wframe-larger-than=8192
EXTRA_CFLAGS+=-Wno-unknown-pragmas
EXTRA_CFLAGS+=-Wno-unused-function ## defined but not used warning
EXTRA_CFLAGS+=-Wno-missing-prototypes
EXTRA_CFLAGS+=-Wno-undef
EXTRA_CFLAGS+=-Wno-strict-prototypes
EXTRA_CFLAGS+=-Wno-cast-qual
EXTRA_CFLAGS+=-Wno-parentheses
EXTRA_CFLAGS+=-Wno-redundant-decls
EXTRA_CFLAGS+=-Wno-missing-braces
EXTRA_CFLAGS+=-Wno-uninitialized
EXTRA_CFLAGS+=-Wno-unused
EXTRA_CFLAGS+=-Wno-inline
EXTRA_CFLAGS+=-Wno-switch
EXTRA_CFLAGS+=-Wno-pointer-arith
EXTRA_CFLAGS+=-Wno-overflow
EXTRA_CFLAGS+=-D_KERNEL
EXTRA_CFLAGS += -Wno-unused-variable
ifneq ("$(wildcard $(PWD)/../../../zfs/sys)","")
INC_DIR = $(PWD)/../../../zfs/sys
endif
ifneq ("$(wildcard $(PWD)/../../../../zfs/sys)","")
INC_DIR = $(PWD)/../../../../zfs/sys
endif
KBUILD_EXTRA_SYMBOLS += ${INC_DIR}/../zfs-module/Module.symvers
KBUILD_EXTRA_SYMBOLS += ${INC_DIR}/../../scst/scst/main/Module.symvers
endif
