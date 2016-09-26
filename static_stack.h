/**
 * @brief simple static stack demo for embedded systems
 */

#ifndef STATIC_STACK_H_
#define STATIC_STACK_H_

#include <stdbool.h>


/* static stack control structure */
typedef struct {
	unsigned char *data_buffer;
	int put_index;
	int get_index;
	int slot_size;
	int noof_elem;
	int slots_used;
}sstack_t;



/**
 * @brief insert data on top of queue
 */
int sstack_push(sstack_t *s, void *data, int size);

/**
 * @brief gets data on top of queue
 */
int sstack_pop(sstack_t *s, void *data, int *size);

/**
 * @brief check if stack is full
 */
bool sstack_full(sstack_t *s);

/**
 * @brief check if stack is empty
 */
bool sstack_empty(sstack_t *s);

/**
 * @brief flush the stack
 */
int sstack_flush(sstack_t *s);

/* declare a fully initialized stack control structure */
#define SSTACK_DECLARE(name, slot_len, elements) 									\
		unsigned char sstack_buffer_##name[(slot_len + sizeof(int)) * elements];	\
		sstack_t name = {															\
			.data_buffer = &sstack_buffer_##name[0],								\
			.put_index = 0,															\
			.get_index = elements - 1,												\
			.slot_size = slot_len + sizeof(int),									\
			.noof_elem = elements,													\
			.slots_used = 0															\
		}

#endif /* STATIC_STACK_H_ */
