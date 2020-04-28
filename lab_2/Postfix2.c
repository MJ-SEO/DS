#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int top ;
	} 
	stack ;

stack * 
create_stack (int capacity, int unit) 
{
	stack * st = malloc(sizeof(stack)) ;
	st->capacity = capacity ;
	st->unit = unit ;
	st->top = 0 ;
	st->buffer = calloc(capacity, unit) ;
	return st ;
}

void
delete_stack (stack * st) 
{
	if (st->buffer != 0x0)
		free(st->buffer) ;
	free(st) ;
}

int 
push (stack * st, void * elem)
{
	if (is_full(st))
		return 1 ;

	memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit) ;
	st->top += 1 ;

	return 0 ;
}

int
pop (stack * st, void * elem)
{
	if (is_empty(st)) 
		return 1 ;
	
	memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit) ;
	st->top -= 1 ;
	return 0;
}

int 
is_empty (stack * st) 
{
	return (st->top == 0) ;
}

int 
is_full (stack * st) 
{
	return (st->top == st->capacity) ;
}

int
get_size (stack * st) 
{
	return st->top ;
}

int
get_element (stack * st, int index, void * elem)
{
	if (st->top <= index)
		return 1 ;

	memcpy(elem, st->buffer + index * st->unit, st->unit) ;
	return 0 ;
}


void
print_stack (stack * st)
{
	int i ;
	for (i = 0 ; i < get_size(st) ; i++) {
		int num ;
		get_element(st, i, &num) ;
		printf("[%d]", num) ;
	}
	printf(".\n") ;
}


int
main ()
{
	stack * st ;
	st = create_stack(100, sizeof(int)) ;
	int invalid=0, undefined=0;

	char tok[16] ;
	do {
		print_stack(st) ;

		scanf("%s", tok) ;

		if (tok[0] == ';') 
			break ;

		if (isdigit(tok[0])) {
			int num = atoi(tok) ;
			push(st, &num) ;
		}
		else {
			switch (tok[0]) {
				case '+' : {
					if(get_size(st)<2){
						invalid = 1;
					}
					int n1, n2, res ;
					pop(st, &n2) ;
					pop(st, &n1) ;
					res = n1 + n2 ;
					push(st, &res) ;
					break ;
				} 

				case '-' : {
					if(get_size(st)<2){
						invalid = 1;
					}
					int n1, n2, res ;
					pop(st, &n2) ;
					pop(st, &n1) ;
					res = n1 - n2 ;
					push(st, &res) ;
					break ;
				}

				case '*' : {
					if(get_size(st)<2){
						invalid = 1;
					}
					int n1, n2, res ;
					pop(st, &n2) ;
					pop(st, &n1) ;
					res = n1 * n2 ;
					push(st, &res) ;
					break ;
				}

				case '/' : {
					if(get_size(st)<2){
						invalid = 1;
					}
					int n1, n2, res ;
					pop(st, &n2) ;
					pop(st, &n1) ;
					if(n2==0){
						undefined =1;
					}
					else{
					res = n1 / n2 ;
					push(st, &res) ;
					}
					break ;
				}
				case '^' :{
					if(get_size(st)<2){
						invalid = 1;
					}
					int n1, n2;
					int res =1;
					pop(st, &n2);
					pop(st, &n1);
					if(n2<0){
						undefined =1;
					}
					for(int i=0; i<n2; i++){
						res *= n1;
					}
					push(st, &res);
					break;
				} 
				case '~' :{
					if(get_size(st)<2){
						invalid = 1;
					}
					int n1, res;
					pop(st, &n1);
					res = -n1;
					push(st, &res);
					break;
				}
				default:
					invalid = 1;
					break;
			}
		}
	} while (tok[0] != ';') ;

	if(invalid ==1){
		printf("invalid");
	}
	else if(undefined ==1){
		printf("undefiend");
	}
	else{
	int result ;
	if(get_size(st)>2){
		printf("invalid");
		return 0;
	}
	pop(st, &result) ;
	printf("%d\n", result) ;
	
	delete_stack(st) ;
	}
	
	return 0 ;
}
