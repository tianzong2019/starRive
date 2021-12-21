#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "zmq.h"

int main(void)
{
        void *ctx, *sock;
        int ret = 0;
        char data[1024];
        int i = 0;

        ctx = zmq_ctx_new();
        sock = zmq_socket(ctx,ZMQ_PUB);
		//
		int sndhwm =0, rcvhwm = 0;
		size_t rcvhwm_size = sizeof (rcvhwm), sndhwm_size = sizeof (sndhwm);
		zmq_getsockopt(sock, ZMQ_SNDHWM, &sndhwm, &sndhwm_size);
		zmq_getsockopt(sock, ZMQ_RCVHWM, &rcvhwm, &rcvhwm_size);
		//
		sndhwm = 10;
		rcvhwm = 10;
		//使用高水位标记ZMQ_SNDHWM（High-Water Marks，HWM）来定义缓冲区的大小
		ret = zmq_setsockopt(sock, ZMQ_SNDHWM, &sndhwm, sndhwm_size);
		ret = zmq_setsockopt(sock, ZMQ_RCVHWM, &rcvhwm, rcvhwm_size);
		//
		printf("%s %d, rcv %d snd %d\n", __func__, __LINE__, rcvhwm, sndhwm);  //动态生效
        ret = zmq_bind(sock,"tcp://*:5555");
        while(1)
        {
                sprintf(data,"[%d]PUB: Hello World",i++);
				printf("to client %s\n", data);
                ret = zmq_send(sock,data,strlen(data),0);
                sleep(1);
        }
        zmq_close(sock);
        zmq_ctx_destroy(ctx);
        return 0;
}
