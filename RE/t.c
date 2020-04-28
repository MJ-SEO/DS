#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	typedef
	struct {
	void* buffer;
	int unit;
	int capacity;
	int front;
	int rear;
	int full;
}
queue;

queue*
create_queue(int capacity, int unit)
{
	queue* que = malloc(sizeof(queue));
	que->capacity = capacity;
	que->unit = unit;
	que->buffer = calloc(capacity, unit);
	que->front = 0;
	que->rear = 0;
	que->full = 0;
	return que;
}

void
delete_queue(queue* que)
{
	if (que->buffer != 0x0)
		free(que->buffer);
	free(que);
}

int
enqueue(queue* que, void* elem)
{
	if (is_full(que))
		return 1;

	memcpy(que->buffer + ((que->rear) * (que->unit)), elem, que->unit);
	que->rear = (que->rear + 1) % que->capacity;

	if (que->rear == que->front)
		que->full = 1;

	return 0;
}

int
dequeue(queue* que, void* elem)
{
	if (is_empty(que))
		return 1;

	memcpy(elem, que->buffer + que->front * que->unit, que->unit);
	que->front = (que->front + 1) % que->capacity;
	if (que->front == que->rear)
		que->full = 0;

	return 0;
}

int
is_empty(queue* que)
{
	return (que->front == que->rear) && (que->full == 0);
}

int
is_full(queue* que)
{
	return que->full;
}

void
print_queue(queue* que, void (*print_element)(void* elem))
{
	int i;
	if (que->front == que->rear && que->full == 0)
		return;

	for (i = que->front; i != que->rear; i = (i + 1) % (que->capacity)) {
		printf("[");
		print_element(que->buffer + i * que->unit);
		printf("] ");
	}
	printf("\n");
}

typedef struct {
	int x;
	int y;
} task;

const int d[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

int visited[20][20];

int main() {
	int i_num = 0;
	int max_s = 0;
	int min_s = 400;
	int scale;
	queue* tasks = create_queue(200, sizeof(task));
	int width, height;
	scanf("%d %d", &height, &width);
	int map[height][width];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			scanf("%1d", &map[i][j]);
		}
	}
	
	printf("your map\n");

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%1d", map[i][j]);
		}
		printf("\n");
	}

	printf("your visited map\n");

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%1d", visited[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j] == 1 && visited[i][j] != 1) {
				i_num++;
				task island;
				island.x = i;
				island.y = j;
				enqueue(tasks, &island); visited[i][j] = 1;
				scale = 0;
				while (!is_empty(tasks)) {
					task iisland;
					dequeue(tasks, &iisland);
					scale+=1;
					int i_d;
					for (i_d = 0; i_d < 4; i_d++) {
						task near;
						near.x = iisland.x + d[i_d][0];
						near.y = iisland.y + d[i_d][1];
						if (0 <= near.x && near.x < height) {
							if (0 <= near.y && near.y < width) {
								if (visited[near.x][near.y] != 1) {
										if (map[near.x][near.y] == 1) {
											enqueue(tasks, &near);
											visited[near.x][near.y] = 1;
									}
								}
							}
						}
					}
				}
				if (scale > max_s) {
					max_s = scale;
					printf("max: %d\n", max_s);
				}
				if (scale < min_s) {
					min_s = scale;
					printf("min: %d\n", min_s);
				}
			}
		}
	}

	printf("%d %d %d\n", i_num, min_s, max_s);
	return 0;
}
