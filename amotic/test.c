#include <stdio.h>
#include <stdlib.h>

#include "uatomic.h"

int main(int argc, char const *argv[])
{
	atomic_t var = 65;
	printf("%s %d, var %d\n", __func__, __LINE__, var);

	ATOMIC_INIT(&var);
	printf("%s %d, var %d\n", __func__, __LINE__, var);

	printf("%s %d, var %d\n", __func__, __LINE__, atomic_read(&var));

	atomic_set(&var, 100);
	printf("%s %d, var %d\n", __func__, __LINE__, atomic_read(&var));

	atomic_inc(&var);
	printf("%s %d, var %d\n", __func__, __LINE__, atomic_read(&var));

	atomic_dec(&var);
	printf("%s %d, var %d\n", __func__, __LINE__, atomic_read(&var));

	atomic_add(&var, 9);
	printf("%s %d, var %d\n", __func__, __LINE__, atomic_read(&var));

	atomic_sub(&var, 9);
	printf("%s %d, var %d\n", __func__, __LINE__, atomic_read(&var));

	return 0;
}
