# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-

modname:=hrtimer

ifneq  ($(KERNELRELEASE),)

obj-m:=${modname}.o

$(info "2nd")

else

KDIR :=${HOME}/codespace/qemu.arm64/kernel-proto
PWD:=$(shell pwd)

all:
	$(info "1st")
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.o *.symvers *.mod.c *.mod.o *.mod *.order .tmp_versions .${modname}*
endif
