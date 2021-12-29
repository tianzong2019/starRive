#ifndef _U_LIST_H_
#define _U_LIST_H_

struct ulist_head {
	struct ulist_head *next, *prev;
};

#define list_init(h) \
	({ \
		(h)->next = (h); \
		(h)->prev = (h); \
	 })

#define __list_add(w, p, n) \
	({ \
		(w)->prev = (p); \
		(w)->next = (n); \
		(p)->next = (w); \
		(n)->prev = (w); \
	 })

#define list_add(w, h)  ({__list_add((w), (h), (h)->next);})

#define list_add_tail(w, h) ({__list_add((w), (h)->prev, (h));})

#define list_del(w)  \
	({ \
		(w)->prev->next = (w)->next; \
		(w)->next->prev = (w)->prev; \
		(w)->prev = (w); \
		(w)->next = (w); \
	 })

static inline int list_empty(struct ulist_head *head)
{
	return head->prev == head;
}

// queue
struct queuelist {
	int max;
	int cur;
	struct ulist_head head;
};

static inline void queue_init(struct queuelist )
{
}

#endif
