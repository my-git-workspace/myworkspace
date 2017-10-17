obj-m += myproc.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
load:
	sudo insmod myproc.ko
unload:
	sudo rmmod myproc	
show:
	dmesg

clear:
	sudo dmesg -c
	
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
