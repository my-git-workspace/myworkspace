KMOD:=msyschar
obj-m:=${KMOD}.o 
${KMOD}-objs:=chr_dev.o init.o
EXTRA_CFLAGS:=-I$(PWD)
all:userland
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf userland
userland:userland.c
	gcc userland.c -o userland
run:
	./userland
insmod:
	sudo insmod ${KMOD}.ko
rmmod:
	sudo rmmod ${KMOD}
