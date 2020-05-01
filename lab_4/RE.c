#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
	void * element ;
	struct node * left ; 
	struct node * right ;
} ;

typedef struct node node_t ;
typedef struct node linkedlist_t ;

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
linkedlist_free (linkedlist_t * l)
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		next = curr->right ;
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

int main(){
	char re[128];
	char str[100];
	int tof[5];
	char output;
	int len =0;
	int index =0;
	linkedlist_t *l;
	linkedlist_t *task;
	char dummy;
	char test;

	l = linkedlist_alloc(sizeof(char));
	task = linkedlist_alloc(sizeof(char));
	
	printf("RE 입력: ");
	scanf("%s", re);

	while(re[len] != '\0'){
                len++;
        }
/*	
	for(int i=0; i<len; i++){
		linkedlist_insert_last(l, &re[i]);
	}
	printf("현재 링크드리스트:");
		
	while (linkedlist_length(l) > 0) {
		linkedlist_remove_first(l, &test) ;
		printf("%c ", test) ;
	}		

	printf("\n");

	for(int i=0; i<len; i++){
		linkedlist_insert_last(l, &re[i]);
	}

	linkedlist_remove_first(l, &dummy);

	printf("맨앞 지운 링크드리스트:");		

	while (linkedlist_length(l) > 0) {
		int i=0;
		linkedlist_remove_first(l, &test) ;
		str[i] = test;
		printf("%c", str[i]);
	}		
	printf("\n");

*/	

	for(int i=0; i<5; i++){
		printf("%d 번쨰 문장 입력: \n",i+1);
		scanf("%s", str);
		
		while(str[index] != '\0'){
			linkedlist_insert_last(l, &str[index]);
                	index++;
        	}
		for(int n =0; n<len; n++ ){			
			if(islower(re[n])){
				char data;
				linkedlist_remove_first(l, &data);
				if(re[n] == data){
					for(int i=0; i<linkedlist_length(l); i++){
						char s_prime;
						linkedlist_get(l,i,&s_prime);
						linkedlist_insert_last(task, &s_prime);
					}
				}
				else{
					tof[i] = 0;
					break;
				}
               	 	}
                	else if(re[n] == '?'){	
				char data;
				linkedlist_remove_first(l, &data);
				for(int i=0; i<linkedlist_length(l); i++){		
					char s_prime;
					linkedlist_get(l,i,&s_prime);	
					linkedlist_insert_last(task, &s_prime);	
				}
                	}
                	else if(re[n] == '!'){	
				for(int i=0; i<linkedlist_length(l); i++){		
					char s_prime;
					linkedlist_get(l,i,&s_prime);	
					linkedlist_insert_last(task, &s_prime);	
				}

				char data;
				linkedlist_remove_first(l, &data);
				for(int i=0; i<linkedlist_length(l); i++){		
					char s_prime;
					linkedlist_get(l,i,&s_prime);	
					linkedlist_insert_last(task, &s_prime);	
				}
                	}

                	else if(re[n] == '['){		
				char data;
				linkedlist_remove_first(l, &data);
				while(1){
					n = n+1;
					if(re[i] == ']')
						break;
					if(re[n] == data){
						for(int i=0; i<linkedlist_length(l); i++){
							char s_prime;
							linkedlist_get(l,i,&s_prime);
							linkedlist_insert_last(task, &s_prime);
						}
					}
				}
               	 	}

                	else if(re[n] == '*'){ 
				for(int i=0; i<linkedlist_length(l)+1; i++){
					for(int j=0; j<linkedlist_length(l); j++){
						char s_prime;
						linkedlist_get(l,j,&s_prime);
						linkedlist_insert_last(task, &s_prime);	
					}
						linkedlist_remove_first(l, &dummy);
				}
                	}
			else{
				return 0;
			}
		}  // for문끝(re 길이)
		
		
		for(int i=0; i<linkedlisk_length(task); i++){
			// l = task
		}
		
		if(strlen(str)<5){
			tof[i] = 1;
		}
		else{
			tof[i] = 0 ;
		}
	} // for문 끝 (5번)

	for(int i=0; i<5; i++){
		if(tof[i] == 1)
			printf("true\n");
		else
			printf("false\n");
	}



	printf("입력받은 re: %s\n", re);
	printf("length: %d\n", len);
	
	return 0;
}
