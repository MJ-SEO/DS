#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arraylist {
	int capacity ;
	int length ;
	int unit ;
	void * elements ;
} ;

typedef struct arraylist arraylist_t ;

arraylist_t * 
arraylist_alloc (int unit) 
{
	arraylist_t * l ;

	l = (arraylist_t *) malloc(sizeof(arraylist_t)) ;
	l->capacity = 10 ;
	l->length = 0 ;
	l->unit = unit ;
	l->elements = (int *) calloc(l->capacity, l->unit) ;
	return l ;
}

void
arraylist_free (arraylist_t * l, void (* free_element)(void * e)) 
{
	if (free_element != 0x0) {
		int i ;
		for (i = 0 ; i < l->length ; i++) {
			void * elem = l->elements + l->unit * i ;
			free_element(elem) ;
		}
	}
	free(l->elements) ;
	free(l) ;
}

int 
arraylist_length (arraylist_t * l)
{
	return l->length ;
}

void
arraylist_print (arraylist_t * l, void (* print_element)(void * e)) 
{
	int i ;
	for (i = 0 ; i < l->length ; i++) {
		print_element(l->elements + l->unit * i) ;
	}
}

void
arraylist_insert_first (arraylist_t * l, void * e)
{
	if (l->length == l->capacity) {
		l->capacity *= 2 ;
		l->elements = (int *) realloc(l->elements, (size_t) l->capacity * l->unit) ;
	}
	int i ;
	for (i = l->length - 1 ; i >= 0 ; i--)
		memcpy(l->elements + (i + 1) * l->unit, l->elements + i, l->unit) ;
	memcpy(l->elements, e, l->unit) ;
	l->length += 1 ;
}

void
arraylist_insert_last (arraylist_t * l, void * e)
{
	if (l->length == l->capacity) {
		l->capacity *= 2 ;	
		l->elements = (int *) realloc(l->elements, (size_t) l->capacity * l->unit ) ;
	}
	memcpy(l->elements + l->length * l->unit, e, l->unit) ;
	l->length += 1 ;
}

int
arraylist_remove_first (arraylist_t * l, void * e) 
{
	if (l->length == 0)
		return 1 ;
	
	memcpy(e, l->elements, l->unit) ;
	int i ;
	for (i = 1 ; i < l->length ; i++) 
		memcpy(l->elements + (i - 1) * l->unit, l->elements + i, l->unit) ;
	l->length -= 1 ;
	return 0 ;
}

int
arraylist_remove_last (arraylist_t * l, void * e) 
{
	if (l->length == 0)
		return 1 ;
	
	memcpy(e, l->elements + (l->length - 1) * l->unit, l->unit) ;
	l->length -= 1 ;
	return 0 ;
}

int
arraylist_get (arraylist_t * l, int pos, void * e)
{
	if (l->length <= pos) 
		return 1 ;
	
	memcpy(e, l->elements + pos * l->unit, l->unit) ;
	return 0 ;
}

void
arraylist_sort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2))
{
	int i, j, m ;
	double * t = malloc(l->unit) ;

	for (i = 0 ; i < l->length - 1 ; i++) {
		m = i ;
		for (j = i + 1 ; j < l->length ; j++) {
			if (cmp_elements(l->elements + j * l->unit, l->elements  + m * l->unit) < 0)
				m = j ;
		}
		memcpy(t, l->elements + i * l->unit, l->unit) ;
		memcpy(l->elements + i * l->unit, l->elements + m * l->unit, l->unit) ;
		memcpy(l->elements + m * l->unit, t, l->unit) ;
	}
	free(t) ;
}

void
_arraylist_qsort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2), void * begin, void * end)
{
	if (begin >= end - l->unit)
		return ;

	int unit = l->unit ;
	void * t = malloc(sizeof(unit)) ;

	void * pivot = begin ;
	void * lbound = begin + unit ;
	void * rbound = end - unit ;
	
	while (lbound <= rbound) {
		while (lbound <= end - unit && cmp_elements(lbound, pivot) <= 0) 
			lbound += unit ;
			
		while (begin < rbound && cmp_elements(pivot, rbound) < 0) 
			rbound -= unit ;
		
		if (lbound <= rbound) {
			memcpy(t, lbound, unit) ;
			memcpy(lbound, rbound, unit) ;
			memcpy(rbound, t, unit) ;
			lbound += unit ;
			rbound -= unit ;
		}
	}
	memcpy(t, rbound, unit) ;
	memcpy(rbound, pivot, unit) ;
	memcpy(pivot, t, unit) ;
	free(t) ;

	_arraylist_qsort(l, cmp_elements, begin, rbound + unit) ;
	_arraylist_qsort(l, cmp_elements, rbound + unit, end) ;
}

void
arraylist_qsort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2))
{
	_arraylist_qsort(l, cmp_elements, l->elements, l->elements + l->length * l->unit) ;
}


void
free_string (void * p)
{ 
	char ** s = (char **) p ;
	free(*s) ;
}

int
cmp_string (void * e1, void * e2)
{
	char * s1 = *((char **) e1) ;
	char * s2 = *((char **) e2) ;

	while (*s1 != 0x0 && *s2 != 0x0 && *s1 == *s2) {
		s1++ ;
		s2++ ;
	}
	if (*s1 == 0x0 && *s2 != 0x0)
		return -1 ;
	
	if (*s1 != 0x0 && *s2 == 0x0)
		return 1 ;

	return (*s1 - *s2) ;
}

int
cmp_double (void *e1, void*e2){
	
	double s1 = *((double*)e1);
	double s2 = *((double*)e2);

	printf("[DEBUG] s1: %lf", s1);
	printf("       [DEBUG] s2: %lf\n", s2);;

	if((s1 - s2)<0){
		return -1;
	}
	else if((s1 - s2)>0){
		return 1;
	}
	else{
		return (s1 - s2);
	}
}

void
print_string (void * p) 
{
	char * s = *((char **) p) ;
	printf("%s\n", s) ;
}

int
cmp_value (void * e1, void * e2)
{
   interval_t * t1 = ((interval_t *) e1) ; 
   interval_t * t2 = ((interval_t *) e2) ; 
 
   if (0 < t1->value - t2->value)
       return 1 ;
   else if (0 == t1->value - t2->value){
       if(t2->position < t1->position) // t1은 끝점 t2는 시작점
           return -1 ;
       else
           return 1 ;
   }
   else
       return -1 ;
}

int
main()
{
   arraylist_t * l ;
   l = arraylist_alloc(sizeof(interval_t)) ;
  
   int n ;
   scanf("%d", &n) ;
 
   for (int i = 0 ; i < n ; i++) {
      
       float num1;
       float num2;
       char * end;
      
       scanf("%f %f", &num1, &num2) ;
 
       interval_t  t ;
 
       t.value = num1 ;
       t.position = 0 ;
       arraylist_insert_last(l, &t) ;
 
       t.value = num2 ;
       t.position = 1 ;
       arraylist_insert_last(l, &t) ;  
   }
   arraylist_qsort(l, cmp_value) ;
 
   int max = 0 ;
   int tmp_max = 0 ;
   interval_t t ;
   for(int i = 0 ; i < arraylist_length(l) ; i++ ) {
       arraylist_get(l, i, &t) ;
       if(t.position == 0) {
           tmp_max++ ;
       }
       else if(t.position == 1) { // 
           tmp_max-- ;
       }
       if(max <= tmp_max)
           max = tmp_max ;
   }
   printf("%d\n", max) ;

	return 0;
}

