#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	void * element ;
	struct node * left ; 
	struct node * right ;
} ;

typedef struct node node_t ;
typedef struct node linkedlist_t ;

linkedlist_t * 
linkedlist_alloc (int unit)  ;

void
linkedlist_free (linkedlist_t * l, void (* free_element)(void * e)) ;

int 
linkedlist_length (linkedlist_t * l) ;

void
linkedlist_print (linkedlist_t * l, void (* print_element)(void * e)) ;

void
linkedlist_insert_first (linkedlist_t * l, void * e) ;

void
linkedlist_insert_last (linkedlist_t * l, void * e) ;

int
linkedlist_remove (linkedlist_t * l, node_t * n) ;

int
linkedlist_remove_first (linkedlist_t * l, void * e) ;

int
linkedlist_remove_last (linkedlist_t * l, void * e) ;

int
linkedlist_get (linkedlist_t * l, int pos, void * e) ;

void
linkedlist_sort (linkedlist_t * l, int ( cmp_elements)(void * e1, void * e2)) ;

void
linkedlist_qsort (linkedlist_t * l, int ( cmp_elements)(void * e1, void * e2)) ;


linkedlist_t * 
linkedlist_alloc (int unit) 
{
	linkedlist_t * l = (linkedlist_t *) malloc(sizeof(linkedlist_t)) ;
	l->left = l  ;	
	l->right = l ;
	l->element = malloc(sizeof(int)) ;
	int * u = (int *) l->element ;
	*u = unit ;

	return l ;
}

void
linkedlist_free (linkedlist_t * l, void (* free_element)(void * e))
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		next = curr->right ;
		if (free_element != 0x0)
			free_element(curr->element) ;
		free(curr->element) ;
		free(curr) ;
		curr = next ;
	}
	free(l->element) ;
	free(l) ;
}

int 
linkedlist_length (linkedlist_t * l)
{
	int len = 0 ;

	node_t * curr = l->right ;
	while (curr != l) {
		len += 1 ;
		curr = curr->right ; 
	}
	return len ; 
}

void
linkedlist_print (linkedlist_t * l, void (* print_element)(void * e))
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		print_element(curr->element) ;
		curr = curr->right ;
	}
}

void 
linkedlist_insert (node_t * left, void * e, int unit)
{
	node_t * _new = (node_t *) malloc(sizeof(node_t)) ;
	_new->element = malloc(unit) ;
	memcpy(_new->element, e, unit) ;

	node_t * right = left->right ;

	_new->left = left ;
	_new->right = right ;

	left->right = _new ;
	right->left = _new ;
}

void
linkedlist_insert_first (linkedlist_t * l, void * e)
{
	linkedlist_insert(l, e, *((int *)(l->element))) ;
}

void
linkedlist_insert_last (linkedlist_t * l, void * e)
{
	linkedlist_insert(l->left, e, *((int *)(l->element))) ;
}

int
linkedlist_remove (linkedlist_t * l, node_t * n)
{
	if (l->left == l)
		return 1 ;

	n->left->right = n->right ;
	n->right->left = n->left ;

	free(n->element) ;
	free(n) ;
	return 0 ;
}

int 
linkedlist_remove_first (linkedlist_t * l, void * e)
{
	if (l->right == l)
		return 1 ;

	memcpy(e, l->right->element, *((int *)(l->element))) ;
	linkedlist_remove(l, l->right) ;
	return 0 ;
}

int
linkedlist_remove_last (linkedlist_t * l, void * e)
{
	if (l->left == l)
		return 1 ;

	memcpy(e, l->left->element, *((int *)(l->element))) ;
	linkedlist_remove(l, l->left) ;
	return 0 ;
}

int 
linkedlist_get (linkedlist_t * l, int pos, void * e)
{
	if (pos < 0)
		return 1 ;

	int unit = *((int *) l->element) ;
	int i = 0 ;
	node_t * curr = l->right ;
	while (i < pos && curr != l) {
		curr = curr->right ;
		i += 1 ;
	}
	if (i != pos)
		return 1 ;

	memcpy(e, curr->element, unit) ;
	return 0 ;
}

void
linkedlist_sort (linkedlist_t * l, int ( cmp_elements)(void * e1, void * e2)) 
{
	node_t * i, * j, * m ;

	int unit = *((int *)(l->element)) ;

	for (i = l->right ; i != l ; i = i->right) {
		m = i ;
		for (j = i->right ; j != l ; j = j->right) {
			if (cmp_elements(j->element, m->element) < 0)
				m = j ;
		}

		void * t = i->element ;
		i->element = m->element ;
		m->element = t ;
	}
}

void
linkedlist_qsort (linkedlist_t * l, int ( cmp_elements)(void * e1, void * e2))
{
	/* TODO */
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

void
print_string (void * p) 
{
	char * s = *((char **) p) ;
	printf("%s\n", s) ;
}

int 
main () 
{
	linkedlist_t * l ; 
	l = linkedlist_alloc(sizeof(char *)) ;

	FILE * fp = fopen("wordset.txt", "r") ;
	if (fp == 0x0) {
		perror("failed to open wordset.txt") ;
		exit(1) ;
	}

	while (!feof(fp)) {
		char s[256] ;

		int i = 0 ;
		int c ;
		while ((c = fgetc(fp)) != '\n' && c != EOF) {
			s[i] = c ;
			i++ ;
		}
		if (i != 0) {
			s[i] = 0x0 ;
			char * str = strdup(s) ;
			linkedlist_insert_last(l, &str) ;
		}
	}
	fclose(fp) ;

//	linkedlist_qsort(l, cmp_string) ;
	linkedlist_sort(l, cmp_string) ;

	int n ; 
	char * s ;
	scanf("%d", &n) ;
	linkedlist_get(l, n, &s) ;
	printf("%s\n", s) ;

	//linkedlist_print(l, print_string) ;
	linkedlist_free(l, free_string) ;
}

