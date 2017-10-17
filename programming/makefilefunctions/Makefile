RM_LIB=geom
LIBADD=geom pthread val
SRCS=	sha256acc.c hello.c
SRCS+=	sha256-ssse3-asm.S sha256acc.c
RM_SRCS=sha256-ssse3-asm.S sha256acc.c
EXTRA_CFLAGS += -no-integrated-as -v
EXTRA_CFLAGS+=-I$(PWD)/../sys
EXTRA_CFLAGS+=-DDEBUG=1
RM_EXTRA_FLAGS=-no-integrated-as -v -DDEBUG=1
#$(1) - Variables from which values needs to be removed
#$(2) - values that needs to be removed 
define REMOVE_VALUES_FROM_VAR
	$(shell TEMP=""; ALL_LIBS=`echo $(1)`; \
for LIB in `echo $(2) | tr ' ' '\n'`; do \
        TEMP=`echo $$ALL_LIBS | sed "s/$$LIB//g"`; \
        ALL_LIBS=$$TEMP; \
        done; echo $$ALL_LIBS )
endef 
#remaining=$(call REMOVE_VALUES_FROM_VAR, ${LIBADD},${RM_LIB})
#remaining=$(call REMOVE_VALUES_FROM_VAR, ${SRCS},${RM_SRCS})
remaining=$(call REMOVE_VALUES_FROM_VAR, ${EXTRA_CFLAGS},${RM_EXTRA_FLAGS})
all:
	@echo ${remaining}
