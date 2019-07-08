ifdef ZFS_COMMON_OBJS
SRCS+=$(subst .o,.c,${ZFS_COMMON_OBJS})
endif #ZFS_COMMON_OBJS

ifdef ZFS_SHARED_OBJS
SRCS+=$(subst .o,.c,${ZFS_SHARED_OBJS})
endif #ZFS_SHARED_OBJS

OBJS=$(SRCS:.c=.o)
PROG=lib${LIB}.so
CFLAGS+=${EXTRA_CFLAGS} ${LDADD}
all:${PROG}
${PROG}:${OBJS} 
	$(CC)  -shared ${LDFLAGS} ${CFLAGS} $^  -o $@ ${LIBS} 
%.o:%.c ${SRCS}
	$(CC) -fPIC ${CFLAGS}  -c $^

.PHONY:clean
clean:
	${RM} ${OBJS} ${PROG}
