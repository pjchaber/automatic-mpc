#include <sys/types.h>
#include <errno.h>

caddr_t _sbrk(int size){
	extern char __heap_start;
	extern char __heap_end;
	static char *current_heap_end = &__heap_start;
	char *previous_heap_end;

	previous_heap_end = current_heap_end;

	if(current_heap_end + size > &__heap_end){
		errno = ENOMEM;
		return (caddr_t) -1;
	}

	current_heap_end += size;
	return (caddr_t) previous_heap_end;
}