#ifndef _U_LIST2_H_
#define _U_LIST2_H_

struct ulist_head {
	int id;
	struct ulist_head *next, *prev;
};

#define list_init(h) \
	({ \
		(h)->next = (h); \
		(h)->prev = (h); \
		(h)->id = -1; \
	 })

#define __list_add(w, p, n) \
	({ \
		(n)->prev = (w); \
		(w)->next = (n); \
		(w)->prev = (p); \
		(p)->next = (w); \
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

#endif
