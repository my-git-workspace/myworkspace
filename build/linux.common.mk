##################Common Functionallity#######################

#$(1) - Variables from which values needs to be removed
#$(2) - values that needs to be removed
define REMOVE_VALUES_FROM_VAR
        $(shell TEMP=""; ALL_LIBS=`echo $(1)`; \
for LIB in `echo $(2) | tr ' ' '\n'`; do \
        TEMP=`echo $$ALL_LIBS | sed "s/$$LIB//g"`; \
        ALL_LIBS=$$TEMP; \
        done; echo $$ALL_LIBS )
endef #REMOVE_VALUES_FROM_VAR

ifdef RM_EXTRA_CFLAGS
TEMP_EXTRA_CFLAGS:=$(call REMOVE_VALUES_FROM_VAR,${EXTRA_CFLAGS},${RM_EXTRA_CFLAGS})
EXTRA_CFLAGS:=${TEMP_EXTRA_CFLAGS}
endif #RM_EXTRA_CFLAGS

ifdef RM_LIB 
TEMP_LIBS:=$(call REMOVE_VALUES_FROM_VAR,${LIBADD},${RM_LIB})
LIBADD:=${TEMP_LIBS}						
endif #RM_LIB

ifdef RM_SRCS
TEMP_SRCS:=$(call REMOVE_VALUES_FROM_VAR,${SRCS},${RM_SRCS})
SRCS:=${TEMP_SRCS}						
endif #RM_SRCS

ifdef RM_DIRS
TEMP_DIRS:=$(call REMOVE_VALUES_FROM_VAR,${SUBDIR},${RM_DIRS})
SUBDIR:=${TEMP_DIRS}						
endif #RM_SRCS

ifdef LIBADD
LIBS+=$(shell echo ${LIBADD} | sed "s/ /\ -l/g" | sed "s/^/\ -l/g")
endif #LIBADD
