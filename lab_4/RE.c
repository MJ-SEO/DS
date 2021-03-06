
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
	char str[128];
	int tof[5];
	char output;
	int len =0;
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

	for(int i=0; i<5; i++){
		printf("%d 번쨰 문장 입력: \n",i+1);
		scanf("%s", str);
		int index =0;		
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
					printf("debug\n");
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
					if(re[n] == ']')
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
				int c_len = linkedlist_length(l);
				for(int i=0; i<c_len+1; i++){
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
			
	/*		if(linkedlist_length(task)<1){
				tof[i] = 0;
				break;
			}
	*/		
			printf("현재linkedlist task : ");
			for(int t=0; t<linkedlist_length(task); t++){
				char test;
				linkedlist_get(task,t,&test);
				printf("%c ", test);
			}			
			printf("//  re[n]: %d\n",n);		
	
						

			for(int m=0; m<linkedlist_length(l); m++){
				linkedlist_remove_first(l, &dummy);
			}

			for(int z=0; z<linkedlist_length(task); z++){
				char a;
				linkedlist_remove_first(task, &a);
				linkedlist_insert_last(l, &a);
			}
		
			printf("현재linkedlist l : ");
			for(int t=0; t<linkedlist_length(l); t++){
				char test;
				linkedlist_get(l,t,&test);
				printf("%c ", test);
			}			
			printf("//  re[n]: %d\n",n);		
			printf("\n");
		
		}  // for문끝(re 길이)
		
		if(linkedlist_length(task)<2){
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
