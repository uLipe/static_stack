/**
 * @brief simple static stack demo for embedded systems
 */

#include <string.h>
#include "static_stack.h"

int sstack_push(sstack_t *s, void *data, int size){
	int ret = 0;
	unsigned char *ptr;

	if(s == NULL || data == NULL || size == 0) {
		/* check your parameters */
		ret = -1;
	} else {
		int mem_pos = s->put_index * s->slot_size;
		ptr = (unsigned char *)s->data_buffer;

		if(s->slots_used >= s->noof_elem|| size > s->slot_size) {
			/* stack full or not enough room for data*/
			ret = -1;
		} else {

			/* insert the size of byte stream */
			memcpy(&ptr[mem_pos], &size, sizeof(size));

			/* insert the byte stream on stack memory*/
			memcpy(&ptr[mem_pos + sizeof(size)], data, size);

			/* update memory indexes, a stack has
			 * policy based on LIFO data insertion and
			 * remotion, so both indexes walk, and always
			 * put_index is ahead of get_index by 1 slot
			 */
			s->put_index = (s->put_index + 1) % s->noof_elem;
			s->get_index = (s->put_index == 0 ?(s->noof_elem + ((s->put_index - 1) % s->noof_elem))
									:(s->put_index - 1) % s->noof_elem);
			++s->slots_used;
		}
	}

	return(ret);
}

int sstack_pop(sstack_t *s, void *data, int *size){
	int ret = 0;
	unsigned char *ptr;

	if(s == NULL || data == NULL || size == NULL) {
		/* check your parameters */
		ret = -1;
	} else {
		int mem_pos = s->get_index * s->slot_size;
		ptr = (unsigned char *)s->data_buffer;

		if(s->noof_elem == 0) {
			/* stack empty...*/
			ret = -1;
		} else {

			/* gets the size of byte stream */
			memcpy(size,&ptr[mem_pos], sizeof(int));

			/* remove the byte stream from stack memory*/
			memcpy(data,&ptr[mem_pos + sizeof(int)], *size);

			/* update memory indexes, a stack has
			 * policy based on LIFO data insertion and
			 * remotion, so both indexes walk, and always
			 * put_index is ahead of get_index by 1 slot
			 */
			s->put_index = (s->put_index == 0 ?(s->noof_elem + ((s->put_index - 1) % s->noof_elem))
									:(s->put_index - 1) % s->noof_elem);

			s->get_index = (s->put_index == 0 ?(s->noof_elem + ((s->put_index - 1) % s->noof_elem))
									:(s->put_index - 1) % s->noof_elem);
			--s->slots_used;
		}
	}

	return(ret);
}

bool sstack_full(sstack_t *s){
	bool ret = true;
	if(s == NULL) {
		/* check your parameters */
		ret = false;
	} else {
		ret = (s->slots_used >= s->noof_elem? true : false);
	}
	return(ret);
}

bool sstack_empty(sstack_t *s){
	bool ret = true;
	if(s == NULL) {
		/* check your parameters */
		ret = false;
	} else {
		ret = (s->slots_used == 0? true : false);
	}
	return(ret);
}

int sstack_flush(sstack_t *s){
	int ret = 0;
	if(s == NULL) {
		/* check your parameters */
		ret = -1;
	} else {
		s->slots_used = 0;
		s->get_index = s->noof_elem - 1;
		s->put_index = 0;
	}
	return(ret);
}
