
str='NULL'
#ifeq ($(wildcard 'str'),)
	str='found'
#endif
ifeq ($(or (1,0)),  $(or(1,1)))
	str='or executed'
endif
#ifneq (${CFLAGS},)
#	str='empty'
#endif
all:
	echo ${str}
