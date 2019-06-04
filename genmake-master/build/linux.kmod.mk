ifdef KMOD
ifeq ($(findstring ${KMOD}.c,${SRCS}),${KMOD}.c)		
KMOD:=z${KMOD}
endif
ifdef VPATH
ifdef ZFS_OBJS
TEMP=$(subst .o,.c,${ZFS_OBJS})
SRCS+=${TEMP}
endif #ZFS_OBJS
final_files:=$(foreach SRC, ${SRCS},$(foreach DIR_PATH, ${VPATH}, $(wildcard ${DIR_PATH}/${SRC})))
final_files:=$(foreach objs, ${final_files},$(shell realpath --relative-to=$(PWD) ${objs}))
moduleobjs:=$(shell echo ${moduleobjs} | tr -s ' ' )
moduleobjs:=$(subst .h,,${final_files})
moduleobjs:=$(subst .S,.o,${moduleobjs})
moduleobjs:=$(subst .c,.o,${moduleobjs})
endif #VPATH
endif #KMOD

obj-m += ${KMOD}.o
ifndef moduleobjs
${KMOD}-objs:=$(patsubst %.h,,$(SRCS:.c=.o))
${KMOD}-objs:=$(patsubst %.h,,$(${KMOD}-y:.S=.o))
else #!moduleobjs
${KMOD}-objs := ${moduleobjs}
endif #moduleobjs

default:
	echo $(EXTRA_CFLAGS)
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:  
	${RM} ${moduleobjs}
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
