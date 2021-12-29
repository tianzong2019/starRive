#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ulist2.h"

struct ulist_head dh;

void destorylist(struct ulist_head *dh)
{
	struct ulist_head *tmp;
	while(!list_empty(dh)) {
		tmp = dh->next;
		list_del(tmp);
		free(tmp);
	}
}

void prlist(struct ulist_head *head)
{
	struct ulist_head *tmp = head;
	do {
		printf("%d, ", tmp->id);
		tmp = tmp->next;
	} while (tmp != head);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int i = 0;
	struct ulist_head *tmp = NULL;
	//
	list_init(&dh);
	// 初始化链表
	for (i=0; i<10; i++) {
		tmp = (struct ulist_head *)malloc(sizeof(struct ulist_head));
		bzero(tmp, sizeof(struct ulist_head));
		tmp->id = i;
		list_add(tmp, &dh);
		prlist(&dh);
	}
	//
	destorylist(&dh);
	printf("---------------------\n");
	//
	for (i=0; i<10; i++) {
		tmp = (struct ulist_head *)malloc(sizeof(struct ulist_head));
		bzero(tmp, sizeof(struct ulist_head));
		tmp->id = i;
		list_add_tail(tmp, &dh);
		prlist(&dh);
	}
	//
	destorylist(&dh);
	//
	return 0;
}
