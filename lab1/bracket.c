#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct {
		char * buffer ;
		int unit ;
		int capacity ;
		int top ;
	} 
	stack ;

stack * 
create_stack (int capacity, int unit) 
{
	stack * stack = malloc(sizeof(stack)) ;
	stack->capacity = capacity ;
	stack->unit = unit ;
	stack->top = 0 ;
	stack->buffer = (char *) calloc(capacity, unit) ;
	return stack ;
}

void
delete_stack (stack * stack) 
{
	if (stack->buffer != 0x0)
		free(stack->buffer) ;
	free(stack) ;
}

int 
push (stack * stack, void * elem)
{
	if (is_full(stack))
		return 1 ;
	
	memcpy(stack->buffer + stack->top * stack->unit, elem, stack->unit) ;
	stack->top += 1 ;
	return 0 ;
}

int
pop (stack * stack, void * elem)
{
	if (is_empty(stack)) 
		return 1 ;
	
	memcpy(elem, stack->buffer + (stack->top - 1) * stack->unit, stack->unit) ;
	stack->top -= 1 ;
	return 0;
}

int 
is_empty (stack * stack) 
{
	return (stack->top == 0) ;
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

int main(){
 
	stack * st ;
	char bak[100];
	int index=0;
	int max=0;
	int maximum=0;
	char arr[100];
	char mmmm[100];

	printf("입력:");
	scanf("%s", bak);

	while(bak[index] != '\0'){
		index++;
	}
	
	if(index%2==1){
		printf("invalid \n");
		return 0;
	}

	st = create_stack(index, sizeof(char));	

	for(int i=0; i<index; i++){
		if(bak[i] == '(' || bak[i] == '[' || bak[i] == '<' || bak[i] =='{'){ 
			push(st, &bak[i]);
			max = get_size(st);
			if(maximum<max){
				maximum = max;		
			}
			continue;
		}
		else if(bak[i] == ')' || bak[i] == ']' || bak[i] == '>' || bak[i] =='}'){
		 	if(bak[i] == ')'){		
				get_element(st,st->top-1,&arr[i]);
				if((arr[i]) == '('){
					pop(st, &mmmm[i]);
				}
				else{
					printf("invalid");
					break;
				}
				}
		
		 	if(bak[i] == ']'){
				get_element(st,st->top-1,&arr[i]);
				if((arr[i]) == '['){
					pop(st, &mmmm[i]);
				}
				else{
					printf("invalid");
					break;
				}
				}
			if(bak[i] == '>'){
				get_element(st,st->top-1,&arr[i]);
				if((arr[i]) == '<'){
					pop(st, &mmmm[i]);
				}
				else{
					printf("invalid");
					break;
				}
				}
		 	if(bak[i] == '}'){
				get_element(st,st->top-1,&arr[i]);
				if((arr[i]) == '{'){
					pop(st, &mmmm[i]);
				}
				else{
					printf("invalid");
					break;
				}
				}
		}
		}
		if(get_size(st)==0){
			printf("%d \n",maximum);
		} 	
	return 0;
}
	




