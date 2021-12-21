
#cd;umount /mnt;mount -t nfs 10.106.36.29:/home/albter/codespace/qemu.arm64/app/yadichuli/user/test/zmq /mnt -o nolock;cd /mnt

all:
	aarch64-linux-gnu-gcc -o test test.c

.PHONY:clean
clean:
	rm -rf test *.o
