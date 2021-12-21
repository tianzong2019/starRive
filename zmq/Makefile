
#cd;umount /mnt;mount -t nfs 10.106.36.29:/home/albter/codespace/qemu.arm64/app/yadichuli/user/test/zmq /mnt -o nolock;cd /mnt

all:
	aarch64-linux-gnu-gcc -o publish publish.c -L./lib -lzmq -I ./inc
	gcc -o subscribe subscribe.c -lzmq
	gcc -o client client.c -lzmq    # 编译client
	gcc -o server server.c -lzmq    # 编译server

.PHONY:clean
clean:
	rm -rf publish subscribe client server
