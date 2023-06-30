
/* Please be aware that the code in its current state is in the initial phase and has undergone minimal testing. It is strongly recommended to thoroughly test and make any necessary modifications before utilizing it. */
/* I cannot be held responsible for any issues or difficulties arising from using the code without making appropriate modifications. */
/* Queue basic implementation in C */
#include <stdio.h>
#include <stdlib.h>

typedef enum{QUEUE_FULL=INT_MIN, QUEUE_EMPTY=-1, SUCCESS = 0, ERROR = -9999}qState_t;
typedef enum {INSERT_REAR = 1, GET_FRONT, GET_REAR, DELETE_FRONT, DISPLAY, QUIT_APP}functionality_t;
typedef enum {FALSE, TRUE}bool_t;

struct Queue {
	int rear;
	int front;
	int size;
	int* data;		//Holds data
};

struct Queue* createQueue(int queueSize) {
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->front = -1;
	q->rear = -1;
	q->size = queueSize;
	q->data = (int*)malloc(q->size*sizeof(int));
	return q;
}

bool_t isQueueFull(struct Queue* q) {
	if (q->front == 0 && q->rear == q->size - 1)
		return TRUE;
	if (q->rear + 1 == q->front)
		return TRUE;
	return FALSE;
}

bool_t isQueueEmpty(struct Queue* q) {
	if (q->front == -1 && q->rear == -1)
		return TRUE;
	return FALSE;
}

qState_t insertRear(struct Queue* q, int myData) {
	if (isQueueFull(q))
		return QUEUE_FULL;
	if (q->rear == -1 && q->front == -1) {
		q->rear = 0;
		q->front = 0;
		q->data[q->rear] = myData;
		return SUCCESS;
	}
	q->rear = (q->rear + 1) % q->size;
	q->data[q->rear] = myData;
	return SUCCESS;
}

int getFront(struct Queue* q) {
	if (isQueueEmpty(q))
		return QUEUE_EMPTY;
	return q->data[q->front];

}
int getRear(struct Queue* q) {
	if (isQueueEmpty(q))
		return QUEUE_EMPTY;
	return q->data[q->rear];
}
qState_t deleteFront(struct Queue* q) {
	if (isQueueEmpty(q))
		return QUEUE_EMPTY;
	if (q->rear == q->front) {
		q->rear = -1;
		q->front = -1;
		return SUCCESS;
	}
	q->front = (q->front++)%q->size;
	return SUCCESS;
}
qState_t display(struct Queue* q) {
	if (isQueueEmpty(q))
		return QUEUE_EMPTY;
	if (q->rear == q->front) {
		printf("%d ", q->data[q->rear]);
		return SUCCESS;
	}
	if (isQueueFull(q)) {
		int qElement;
		for (qElement = q->front; qElement != q->rear; qElement = (qElement+1)%q->size) 
			printf("%d ", q->data[qElement]);
		printf("%d ", q->data[qElement]);
		return SUCCESS;
	}
	int qElement;
	for (qElement = q->front; qElement != q->rear; qElement = (qElement + 1) % q->size) 
		printf("%d ",q->data[qElement]);
	printf("%d ", q->data[qElement]);
	return SUCCESS;
}
int main() {
	int choice;
	int qSize;
	int data;
	struct Queue* q;
	printf("Enter size for queue ");
	scanf("%d",&qSize);
	q = createQueue(qSize);
	while (TRUE) {
		printf("\n1. insertRear data\n");
		printf("2. getFront data\n");
		printf("3. getRear data\n");
		printf("4. deleteFront data\n");
		printf("5. display data\n");
		printf("6. queit Application\n");
		int a = scanf("%d", &choice);
		if (!a)
			printf("Couldn't read the input\n");
		switch (choice) {
		case INSERT_REAR:
			printf("Enter the data to be store in queue ");
			scanf("%d", &data);
			if (insertRear(q, data) == QUEUE_FULL)
				printf("\nqueue is full!\n");
			break;
		case GET_FRONT:
			data = getFront(q);
			if (data == QUEUE_EMPTY)
				printf("\nqueue is empty!\n");
			else
				printf("%d", data);
			break;
		case GET_REAR:
			data = getRear(q);
			if (data == QUEUE_EMPTY)
				printf("\nqueue is empty!\n");
			else
				printf("%d", data);
			break;
		case DELETE_FRONT:
			data = deleteFront(q);
			if (data == QUEUE_EMPTY)
				printf("\nqueue is empty!\n");
			break;
		case DISPLAY:
			data = display(q);
			if (data == QUEUE_EMPTY)
				printf("\nQueue is empty!\n");
			break;
		case QUIT_APP:
			exit(0);
		}
	}
	return 0;
}