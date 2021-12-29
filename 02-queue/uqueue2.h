#ifndef _U_QUEUE_H_
#define _U_QUEUE_H_
#include "ulist.h"

struct queuelist {
	struct ulist_head head;
	int max;
	int cur;
};

struct sendmsg {
	struct ulist_head node;
	int id;
	int size;
	void *vaddr;
};

#define queue_init(q, m) \
	do {\
		list_init(&(q)->head);  \
		(q)->max = (m); \
		(q)->cur = 0;   \
	} while(0)

#define enqueue(q, n) \
	({\
		int ret = 0; \
		if ((q)->max <= (q)->cur) { \
			printf("%s %d, queue full\n", __func__, __LINE__); \
			ret = -1; \
		} else { \
			list_add(&(n)->node, &(q)->head); \
			(q)->cur++; \
			printf("%s %d, nd %p %d, p.c.n %p %p %p\n", __func__, __LINE__, &(n)->node, (n)->id, (q)->head.prev, &(q)->head, (q)->head.next); \
		}\
		ret; \
	 })

#define enqueue_tail(q, n) \
	({\
		int ret = 0; \
		if ((q)->max <= (q)->cur) { \
			printf("%s %d, queue full\n", __func__, __LINE__); \
			ret = -1; \
		} else {\
			list_add_tail(&(n)->node, &(q)->head); \
			(q)->cur++; \
			printf("%s %d, nd %p %d, p.c.n %p %p %p\n", __func__, __LINE__, &(n)->node, (n)->id, (q)->head.prev, &(q)->head, (q)->head.next); \
		}\
		ret; \
	 })

#define dequeue(q, n) \
	({\
		int ret = 0; \
		typeof((q)->head) *__qh_tmp = (q)->head.next;\
		if ((q)->cur == 0) {\
			printf("%s %d, queue empty\n", __func__, __LINE__);\
			ret = -1;\
		}\
		(q)->cur--;\
		n = (typeof(n))(__qh_tmp - (size_t)&(((typeof(n))0)->node)); \
		printf("%s %d, nd %p %d, p.c.n %p %p %p\n", __func__, __LINE__, &n->node, n->id, qh->head.prev, &qh->head, qh->head.next); \
		list_del(__qh_tmp); \
		ret;\
	})

#define dequeue_tail(q, n) \
	({\
		int ret = 0; \
		typeof((q)->head) *__qh_tmp = (q)->head.prev;\
		if ((q)->cur == 0) {\
			printf("%s %d, queue empty\n", __func__, __LINE__);\
			ret = -1;\
		}\
		(q)->cur--;\
		n = (typeof(n))(__qh_tmp - (size_t)&(((typeof(n))0)->node)); \
		printf("%s %d, nd %p %d, p.c.n %p %p %p\n", __func__, __LINE__, &n->node, n->id, qh->head.prev, &qh->head, qh->head.next); \
		list_del(__qh_tmp); \
		ret;\
	})

#endif
