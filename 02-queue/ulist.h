#ifndef _U_LIST_H_
#define _U_LIST_H_

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

struct ulist_head {
	struct ulist_head *next, *prev;
	int id;
};

static inline void list_init(struct ulist_head *head)
{
	head->next = head;
	head->prev = head;
	head->id = -1;
}

static inline void __list_add(struct ulist_head *entry, struct ulist_head *prev, struct ulist_head *next)
{
	prev->next = entry;
	entry->prev = prev;
	entry->next = next;
	next->prev = entry;
}

static inline void list_add(struct ulist_head *entry, struct ulist_head *head)
{
	__list_add(entry, head, head->next);
}

static inline void list_add_tail(struct ulist_head *entry, struct ulist_head *head)
{
	__list_add(entry, head->prev, head);
}

static inline void __list_del(struct ulist_head *prev, struct ulist_head *next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(struct ulist_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->prev = entry;
	entry->next = entry;
}

static inline int list_empty(struct ulist_head *head)
{
	return head->prev == head;
}

#endif
