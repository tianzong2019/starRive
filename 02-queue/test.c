#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ulist.h"
#if 0
#include "uqueue.h"
#else
#include "uqueue2.h"
#endif

void pr_list(struct ulist_head *hd)
{
	struct ulist_head *tmp = hd;

	if (list_empty(hd))
		return;

	do {
		tmp = tmp->next;
		if(tmp == hd)
			break;
		printf("%d, ", tmp->id);
	} while(1);

	printf("\n");
}

void destroy_list(struct ulist_head *hd)
{
	struct ulist_head *tmp = hd->next;

	while (!list_empty(hd)) {
		list_del(tmp);
		printf("%d, ", tmp->id);
		free(tmp);
		tmp = hd->next;
	}
	printf("\n\n");
}

void test_list(struct ulist_head *hd)
{
	int i = 0;
	struct ulist_head *tmp = NULL;
	//
	list_init(hd);
	//
	for (i = 0; i < 5; i++) {
		tmp = (struct ulist_head *)malloc(sizeof(struct ulist_head));
		bzero(tmp, sizeof(struct ulist_head));
		tmp->id = i;
		list_add(tmp, hd);
		pr_list(hd);
	}
	printf("----------\n");
	destroy_list(hd);
	//
	for (i = 0; i < 5; i++) {
		tmp = (struct ulist_head *)malloc(sizeof(struct ulist_head));
		bzero(tmp, sizeof(struct ulist_head));
		tmp->id = i;
		list_add_tail(tmp, hd);
		pr_list(hd);
	}
	printf("----------\n");
	destroy_list(hd);
}

void test_queue(struct queuelist *qh)
{
	int i = 0;
	struct sendmsg *tmp = NULL;

	queue_init(qh, 5);
	//
	for (i = 0; i <= 5; i++) {
		tmp = (struct sendmsg *)malloc(sizeof(struct sendmsg));
		bzero(tmp, sizeof(struct sendmsg));
		tmp->id = i;
		enqueue(qh, tmp);
		/** enqueue_tail(qh, tmp); */
	}
	tmp = NULL;
	do {
		if (qh->cur == 0) {
			printf("%s %d, queue empty\n", __func__, __LINE__);
			break;
		}
		dequeue(qh, tmp);
		//dequeue_tail(qh, tmp);
		free(tmp);
		tmp = NULL;
	} while(1);
}


int main(int argc, char const *argv[])
{
	/** struct ulist_head hd; */
	/** test_list(&hd); */

	struct queuelist qh;
	test_queue(&qh);

	return 0;
}
