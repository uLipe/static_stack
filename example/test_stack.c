#include <stdio.h>
#include <string.h>
#include "../static_stack.h"

/* creates a 4 byte wide x 32 slots stack */
SSTACK_DECLARE(test, sizeof(int), 32);


int main (int argc, char **argv)
{
	unsigned int data = 0;

	/* insert data until the stack is filled up */
	while(sstack_full(&test) == false) {
		printf("Data pushed to stack %d \n\r", data);
		sstack_push(&test, &data, sizeof(data));
		data += 2;
	}

	/* remove all the data pushed to stack */
	while(sstack_empty(&test) == false) {
		int size;
		sstack_pop(&test, &data, &size);
		/* keeps the compiler quiet*/
		(void)size;
		printf("Data popped from stack %d \n\r", data);
	}


	return 0;
}
