obj-m += signal-module.o
all:userland
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	${RM} userland
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
userland: common.h userland.c
	gcc userland.c -o userland
load:
	sudo insmod signal-module.ko
unload:
	sudo rmmod signal-module.ko
