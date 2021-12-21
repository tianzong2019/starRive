#ifndef _U_ATOMIC_H_
#define _U_ATOMIC_H_

typedef int atomic_t;

#define ATOMIC_INIT(v)    __sync_and_and_fetch(v, 0)

#define atomic_read(v)    __sync_or_and_fetch(v, 0)

#define atomic_set(v, i)             \
	do {                             \
		__sync_and_and_fetch(v, 0);  \
		__sync_add_and_fetch(v, i);  \
	} while(0)

#define atomic_inc(v)     __sync_add_and_fetch(v, 1)

#define atomic_dec(v)     __sync_sub_and_fetch(v, 1)

#define atomic_add(v, i)  __sync_add_and_fetch(v, i)

#define atomic_sub(v, i)  __sync_sub_and_fetch(v, i)

#endif
