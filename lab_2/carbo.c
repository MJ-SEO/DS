#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef
struct {
	void* buffer;
	int unit;
	int capacity;
	int top;
}
stack;

stack*
create_stack(int capacity, int unit)
{
	stack* st = malloc(sizeof(stack));
	st->capacity = capacity;
	st->unit = unit;
	st->top = 0;
	st->buffer = calloc(capacity, unit);
	return st;
}

void
delete_stack(stack* st)
{
	if (st->buffer != 0x0)
		free(st->buffer);
	free(st);
}

int
push(stack* st, void* elem)
{
	if (is_full(st))
		return 1;

	memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit);
	st->top += 1;

	return 0;
}

int
pop(stack* st, void* elem)
{
	if (is_empty(st))
		return 1;

	memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit);
	st->top -= 1;
	return 0;
}

int
is_empty(stack* st)
{
	return (st->top == 0);
}

int
is_full(stack* st)
{
	return (st->top == st->capacity);
}

int
get_size(stack* st)
{
	return st->top;
}

int
get_element(stack* st, int index, void* elem)
{
	if (st->top <= index)
		return 1;

	memcpy(elem, st->buffer + index * st->unit, st->unit);
	return 0;
}

int convert(char ch){
	if(ch=='C')
		return 12;
	else if(ch=='O')
		return 16;
	else if(ch=='H')
		return 1;
	else
		return 1111;
}


int
main(){
	stack* st;
	st = create_stack(200, sizeof(int));
	
	char car[100]={0x0};
	int sum=0;
	int i=0;
	int one =1;

	scanf("%s", car);

	while(car[i] != '\0'){
		if(car[i]=='C'||car[i]=='H'||car[i]=='O'){
			if(car[i] =='C'){
				int n =	convert('C');
				push(st, &n);
				push(st, &one);
			}
			else if(car[i] == 'O'){
				int n =	convert('O');
				push(st, &n);
				push(st, &one);
			} 
			else if(car[i] == 'H'){
				int n =	convert('H');
				push(st, &n);
				push(st, &one);
			}	
		}
		else if(isdigit(car[i])){
			int dummy;
			int n = car[i]-48;
			pop(st, &dummy);
			push(st, &n);	
		}
		else if(car[i] == '('){
			int n = -1;
			push(st, &n);  
		}
		else if(car[i] == ')'){
			int n, dummy;
			int in_sum=0;
			int n1, n2;
			while(1){
			        get_element(st,st->top-1,&n);
				if(n==-1){
					break;
				}
				pop(st, &n1);
				pop(st, &n2);
				in_sum = in_sum + (n1*n2);
			}
			pop(st, &dummy);
			push(st, &in_sum);
			push(st, &one);
		}
		else{}
		i++;
	}

	while(get_size(st)!=0){
		int n1, n2;
		pop(st, &n1);
		pop(st, &n2);
		sum = sum + (n1*n2);
	}

	
	printf("%d\n", sum);
	return 0;
}	
