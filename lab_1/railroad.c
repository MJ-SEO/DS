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
	int rail=0, station=0;
	int num=1;
	int dummy;
	int pre;

	printf("rail의 수와 station의 수:");
	scanf("%d %d", &rail, &station);
	
	int rail_input[rail];
	int rail_arr[rail];
	
	stack* st = create_stack(station, sizeof(int));

	printf("원하는 rail의 의 배열 입력: ");	

	for(int i=0; i<rail; i++){
		rail_arr[i] = num;
		num+=1;                          
	}

	for(int i=0; i<rail; i++){
		scanf("%d", &rail_input[i]);    
	}

	int i=0;
	int n=0;
	while(1){

		if(n==rail){
			printf("true");			
			break;
		}

		printf("현재n: %d\n", n);
		printf("현재i: %d\n", i);
		printf("현재stack수: %d\n", get_size(st));
			
		get_element(st,st->top-1,&pre);	
		printf("현재top 값: %d\n", pre);

		if(i>rail){
			printf("false");
			break;
		}
		
		if(rail_input[n] == pre){
			pop(st,&dummy);
			n++;
		continue; 
		}
	
		if(rail_input[n] != rail_arr[i]){
			push(st, &rail_arr[i]);
			if(get_size(st)>station){
				printf("false");
				break;
			}
		}
		else{
			n++;
		}	
		i++;
	}

/*
	for(int i=0; i<rail; i++){
		int getnum = 0;
		push(st,&rail_arr[i]);
		printf("스택 수: %d", get_size(st));

		if(get_size(st)>station){
			printf("false");
			return 0;
		
		}
		printf("top: %d", st->top);
		
		get_element(st,st->top-1,&dummy);
		
		printf("더미 %d", dummy);
		
		if(dummy == rail_input[getnum]){
			pop(st,&hugi);
			getnum++;
		}
	}



	for(int i=0; i<rail; i++){
		for(int j=0; j<rail-2; j++){
			
			if(rail_input[i] == i+1){
				push(out_stack, &rail_arr[i]);
				
				
			}
			else{
				if(rail_input[i] == j+2){
					for(int k=0; k<j+1; k++)
						push(st, &rail_arr[k]);
				  push(out_stack, &rail_arr[j+1]);	
				}
			}
		}
	}	

	if(arr_input[0] = 1){
		arr_output[0] = 1;

		if(arr_input[1] = 2){
			arr_output[1] =2;

			if(arr_input[2] =3){
				arr_output[2] =3;	

			}
			else{
				
			}
		else{
			if(arr_input[1] ==3){	
				push(st, &arr[1]);
				arr_output[1] =3;	
			}
			else if(arr_input[1] ==4){	
				push(st, &arr[1]);
				push(st, &arr[2]);
				arr_output[1] =4;	
			}
		}
		} 
		
	}	
	else{
		if(arr_input[0] == 2){
			push(st, &arr[0]);
			arr_output[0]=2;
		}
		else if(arr_input[0] == 3){
			push(st, &arr[0]);
			push(st, &arr[1]);
			arr_output[0]=3;
		}
		else if(arr_input[0] == 4){
			push(st, &arr[0]);
			push(st, &arr[1]);
			push(st, &arr[2]);
			arr_output[0]=4;
		}
	}
	}	*/
		
	return 0;
}

