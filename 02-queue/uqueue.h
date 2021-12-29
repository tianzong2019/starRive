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

static inline void queue_init(struct queuelist *qh, int max)
{
	list_init(&qh->head);
	qh->max = max;
	qh->cur = 0;
}

static inline int enqueue(struct queuelist *qh, struct sendmsg *nd)
{
	int ret = 0;
	if (qh->max <= qh->cur) {
		printf("%s %d, queue full\n", __func__, __LINE__);
		ret = -1;
	} else {
		list_add(&nd->node, &qh->head);
		qh->cur++;
		printf("%s %d, nd %p %d, p.c.n %p %p %p\n", __func__, __LINE__, 
				&nd->node, nd->id, qh->head.prev, &qh->head, qh->head.next);
	}
	return ret;
}


static inline int enqueue_tail(struct queuelist *qh, struct sendmsg *nd)
{
	int ret = 0;
	if (qh->max <= qh->cur) {
		printf("%s %d, queue full\n", __func__, __LINE__);
		ret = -1;
	} else {
		list_add_tail(&nd->node, &qh->head);
		qh->cur++;
		printf("%s %d, nd %p %d, p.c.n %p %p %p\n", __func__, __LINE__, 
				&nd->node, nd->id, qh->head.prev, &qh->head, qh->head.next);
	}
	return ret;
}

#if 0
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

#else

#undef offsetof2
#define offsetof2(TYPE, MEMBER) ((size_t) &((TYPE)0)->MEMBER)

#define container_of2(ptr, type, member) ({                      \
        const typeof( ((type)0)->member ) *__mptr = (ptr);    \
        (type)( (char *)__mptr - offsetof2(type, member) );})

static inline int dequeue(struct queuelist *qh, struct sendmsg *nd)
{
	int ret = 0;
	struct ulist_head *tmp = qh->head.next;

	if (qh->cur == 0) {
		printf("%s %d, queue empty\n", __func__, __LINE__);
		ret = -1;
	} else {
		qh->cur--;
		nd = container_of2(tmp, typeof(nd), node);
		printf("%s %d, nd %p %d, p.c.n %p %p %p\n", __func__, __LINE__, 
				&nd->node, nd->id, qh->head.prev, &qh->head, qh->head.next);
		list_del(tmp);
	}
	return ret;
}

static inline int dequeue_tail(struct queuelist *qh, struct sendmsg *nd)
{
	int ret = 0;
	struct ulist_head *tmp = qh->head.prev;

	if (qh->cur == 0) {
		printf("%s %d, queue empty\n", __func__, __LINE__);
		ret = -1;
	} else {
		qh->cur--;
		nd = container_of2(tmp, typeof(nd), node);
		printf("%s %d, nd %p %d, p.c.n %p %p %p\n", __func__, __LINE__, 
				&nd->node, nd->id, qh->head.prev, &qh->head, qh->head.next);
		list_del(tmp);
	}
	return ret;
}
#endif
#endif
