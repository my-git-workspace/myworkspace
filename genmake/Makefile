#IFEQ=ifeq
#ELSE=else
#ENDIF=endif
#MSG="None"
#MSG_1="None"
#${IFEQ} (1, 1)
#	MSG="hello"
#${ENDIF}
#ifeq (1,1)
#	MSG_1='Hello'
#endif
#SUBDIR=a b c d e f
#SUB=$(SUBDIR:' '='\n')
ARCH=i382
OS='WIN'
#arch=$(shell if [ ${ARCH} = "i386" ] && [ ${OS} = "LINUX" ];then \
	echo true; \
	fi )
arch=$(shell if [ ${ARCH} = "i386" ] || [ ${OS} = "LINUX" ];then \
	echo true; else echo false;\
	fi )

#ifneq ($(shell if [ $(ARCH) = "win32" ] || \
#     [ $(ARCH) = "win64" ] || \
#     [ $(ARCH) = "linux" ] || \
#     [ $(ARCH) = "android" ]; \
#     then echo true;else echo false;fi),true)
#
#$(error \
#	please specify a valid architecture by passing ARCH= parameter   \
#	Valid architectures are win32, win64, linux, android \
#	)
#endif
LIBADD= md pthread umem util m nvpair zfs_core
#LIBS+=$(LIBADD: : -l)
LIBS+=$(shell echo ${LIBADD} | sed "s/ /\ -l/g" | sed "s/^/\ -l/g")

all:
	@#echo "${arch}"
	@#make -C a	
	@echo "LIBADD::${LIBADD}"
	@echo "LIBS::${LIBS}"

