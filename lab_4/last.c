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

void RemoveFirst(char *buf)
{
    int i = 0;
    for (i = 1; buf[i]; i++)
    {
        buf[i - 1] = buf[i];
    }
    buf[i - 1] = '\0';
}
typedef struct{
     char string[129];
     int m;
}task;

int main(){
        char re[128];
        char str[100];
        int tof[5] = {0};
        char output;
        int len =0;
        linkedlist_t *l;
        linkedlist_t *s;
        char dummy;
        char test;

        l = linkedlist_alloc(sizeof(char));
        s = linkedlist_alloc(sizeof(task));

        printf("RE 입력: ");
        scanf("%s", re);

        for(int i=0; i<5; i++){
                for(int i=0; i<strlen(re); i++){
                        linkedlist_insert_last(l, &re[i]);
                }
                printf("%d 번쨰 문장 입력: \n",i+1);
                scanf("%s", str);
                task first;
                strcpy(first.string, str);
                linkedlist_insert_first(s, &first);

                while(linkedlist_length(l) !=0){
                        char p;
                        linkedlist_remove_first(l, &p);

                        if(islower(p)){
                                int len = linkedlist_length(s);
                                for(int k=0; k<len; k++){
                                  task load;
                                  linkedlist_remove_first(s, &load);
                                  if(p == load.string[0]){
                                        task next;
                                        strcpy(next.string, load.string);
                                      	RemoveFirst(next.string);
                                      	linkedlist_insert_last(s, &next);
                                    }
                                }
                        }

                        else if(p == '?'){
                                int len = linkedlist_length(s);
					                      for(int k=0;k<len;k++){
                    				      task load;
                    				      linkedlist_remove_first(s,&load);
						
						                      task next;
						                      strcpy(next.string, load.string);
						                      RemoveFirst(next.string);	
                     				      linkedlist_insert_last(s, &next);		
						                  }
                        }
                        else if(p == '!'){
                               int len = linkedlist_length(s);
					                     for(int k=0; k<len; k++){
                    			    	task load;
                    				    linkedlist_remove_first(s,&load);
					                    	linkedlist_insert_last(s,&load);
						
                                if(strlen(load.string) != 0){
							                    task next;
							                    strcpy(next.string, load.string);
							                    RemoveFirst(next.string);
                        				  linkedlist_insert_last(s, &next);	
						                    }
               				        }
                        }
                        else if(p == '['){
                                char mem[129] = {0,};
				                      	int c_len = linkedlist_length(s);
					                      int index =0;
                                        while(1){
                                                char firstt;
                                                linkedlist_remove_first(l,&firstt);
                                          		  if(firstt==']')
                                                  		break;
                                                if(islower(firstt)){
							                                    mem[index] = firstt;
                                      		      	index++;
						                                    }
                                          }

					                                for(int k=0; k<c_len; k++){
					                                    task e;
						                                  linkedlist_remove_first(s,&e);
						                                      if(strchr(mem, e.string[0])){
							                                          task next;
                                                      	strcpy(next.string,e.string);
                                                       	RemoveFirst(next.string);
                                                       	linkedlist_insert_last(s, &next);
						                                      }
					                                  }	
                        }
                        else if(p == '*'){
                                int c_len = linkedlist_length(s);
				                          for(int k=0;k<c_len;k++){
                  				          task a;
                    				        linkedlist_remove_first(s, &a);
							                      if(strlen(a.string) == 0){
								                      linkedlist_insert_last(s, &a);
							                      }
							                      else{
								                      int length = strlen(a.string);
								                      int numm = 0;	
								                        while(numm < length+1){
									                        task next;
									                        strcpy(next.string, a.string);
									                        for(int z=0; z<length-numm; z++){
										                          next.string[z] = next.string[z+numm];
								                          }
								                          int d =1;
									                        while(d<numm+1){
									                          	next.string[strlen(a.string)-d] = '\0';
 									                          	d++; 
									                        }
								                          linkedlist_insert_last(s, &next);
								                          numm++;
								                        }
							                    }		
					                      }
                            }
                        else{
                                return 0;
                        }

                }  // for문끝(re 길이)

                task result;
                while(linkedlist_length(s) != 0){
			          linkedlist_remove_first(s,&result);
			              if(strlen(result.string) == 0){
				              tof[i] = 1;
			              }
		            }           
              
        } // for문 끝 (5번)

        for(int i=0; i<5; i++){
                if(tof[i] == 1)
                        printf("true\n");
                else
                        printf("false\n");
        }
        linkedlist_free(s);
        linkedlist_free(l);
        return 0;
}
