############################################### Auto Generated ###########################################
########################## sg.mk contains ${SOURCE_FILES} ${HEADER_FILES} ${LIBS} ${INCLUDES} ############################
PWD=$(shell pwd)
SG.MK=${PWD}/sg.mk
include ${SG.MK}
EXT=$(shell echo ${SOURCE_FILES} | grep -o ".cpp")
CXX=gcc
EXE=$(shell basename ${PWD})
RM=rm
OBJS+=""
CFLAGS=${PKG}
ifneq "${EXT}" ""
	OBJS=$(patsubst %.cpp, %.o, ${SOURCE_FILES})
	CXX=g++
else
	EXT=.c
	CXX=gcc
	OBJS=$(patsubst %.c, %.o, ${SOURCE_FILES})
endif
EXTPAT=%"${EXT}"
FIRST_SOURCE_FILE=$(firstword ${SOURCE_FILES})
#EXE=$(basename ${FIRST_SOURCE_FILE} ${EXT})
all:${EXE}
${EXE}:${OBJS} ${HEADER_FILES}
	${CXX} -o $@ $^ ${LIBS} ${INCLUDES} ${PKG}
#%.o:${EXTPAT}
#	${CXX} -c -w ${SOURCE_FILES} -o $@ ${LIBS} ${INCLUDES}
.PHONY: clean run

run:
	@./${EXE}
clean:
	${RM} -rf ${EXE} ${OBJS} 

