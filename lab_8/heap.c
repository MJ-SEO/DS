#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char * arr ;
	int capacity ;
	int size ;
	size_t usize ;

	int (* cmp)(void *e1, void *e2) ;

} heap_t ;

heap_t *
heap_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) ;

void
heap_free (heap_t * heap) ;

int
heap_size (heap_t * heap) ;

int
heap_top (heap_t * heap, void * buf) ;

int
heap_pop (heap_t * heap, void * buf) ;

int
heap_push (heap_t * heap, void * buf) ;

heap_t *
heap_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) 
{
	heap_t * h = malloc(sizeof(heap_t)) ;
	h->arr = calloc(capacity + 1, usize) ;
	h->capacity = capacity ;
	h->size = 0 ;
	h->usize = usize ;
	h->cmp = cmp ;
	return h ;
}

void
heap_free (heap_t * h) 
{
	free(h->arr) ;
	free(h) ;
}

int
heap_size (heap_t * h)
{
	return h->size ;
}

int
parent (int i) { return i / 2 ; }

int
left (int i) { return i * 2 ; }

int
right (int i) { return i * 2 + 1 ; }

void *
arr (heap_t * h, int i)
{
	return h->arr + h->usize * i ;
}

void
swap (heap_t * h, int a, int b)
{
	char * tmp = (char *) malloc(h->usize) ;
	memcpy(tmp, h->arr + a * h->usize, h->usize) ;
	memcpy(h->arr + a * h->usize, h->arr + b * h->usize, h->usize) ;
	memcpy(h->arr + b * h->usize, tmp, h->usize) ;
}

int
cmp (heap_t * h, int a, int b)
{
	return h->cmp(h->arr + a * h->usize, h->arr + b * h->usize) ;
}

int
heap_top (heap_t * h, void * buf)
{
	if (h->size == 0)
		return 1 ;
	memcpy(buf, arr(h, 1), h->usize) ;
}

int
heap_pop (heap_t * h, void * buf)
{
	if (h->size == 0)
		return 1 ;

	/*TODO*/

	return 0 ;
}

int
heap_push (heap_t * h, void * buf) 
{
	if (h->size == h->capacity) 
		return 1 ;

	h->size += 1 ;
	memcpy(arr(h, h->size), buf, h->usize) ;
	for (int i = h->size ; parent(i) > 0 ; ) {
		if (cmp(h, parent(i), i) < 0) {
			swap(h, parent(i), i) ;
			i = parent(i) ;
		}
		else {
			break ;
		}
	}
	return 0 ;
}

int 
string_cmp (void *e1, void *e2)
{
	char *s1 = *((char **)e1) ;
	char *s2 = *((char **)e2);
	return strcmp(s1, s2) ;
}

int 
main ()
{
	char * inputs[7] = {"necessary", "correct", "absent", "type", "because", "further", 0x0} ;
	int i ;

	heap_t * h = heap_create(5, sizeof(char *), string_cmp) ;

	for (i = 0 ; inputs[i] != 0x0 ; i++) {
		heap_push(h, &(inputs[i])) ;
		char * s ;
		heap_top(h, &s) ;
	}

	while (heap_size(h) > 0) {
		char * s = 0x0 ;
		heap_pop(h, &s) ;
		printf("%s\n", s) ;
	}

	return 0 ;
}
