obj-m=sample_driver.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	rm -f ${obj-m}
clean:
	rm -f sample_driver
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
load:
	sudo insmod sample_driver.ko
unload:
	sudo rmmod sample_driver
