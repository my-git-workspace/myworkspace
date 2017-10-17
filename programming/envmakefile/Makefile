#hello="hello"
#SOMNATH=${hello}
#ifndef SOMNATH
#	$(info SOMANTH defined)
#endif
#all:
#	@echo ${hello}


#abc="abc"
#ifeq "Makefile"   "1"
#	abc="abc"
#endif
#
#all:
#ifdef abc
#	echo abc defined
#endif

#hello="hello"
#ifeq "1" "2"
#
#	hello="neq"
#
#else ifeq "1" "3"
#	hello="eq"	
#else
#	hello='diff'
#endif

hello="hello"
ifeq ($(wildcard makefile),)
	hello="Makefile"
endif

all:
	echo ${hello}
		
