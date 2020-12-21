#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

struct queue{ // from: https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
	int front, rear, size;
	unsigned capacity;
	int *array;
};

struct stack{ // from: https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
	int top;
	unsigned capacity;
	int *array;
};

// function to create a queue of given capacity.  
// It initializes size of queue as 0 
struct queue *createQueue(unsigned capacity)
{
	struct queue *this_queue = (struct queue *) malloc(sizeof(struct queue));
	this_queue->capacity = capacity;
	this_queue->front = this_queue->size = 0;
	this_queue->rear = capacity - 1; //important - see enqueue
	this_queue->array = (int *) malloc(this_queue->capacity * sizeof(int));
	return this_queue;
}

// queue becomes full when size becomes equal to the capacity
int isFull(struct queue *this_queue){
	return(this_queue->size == this_queue->capacity);
}

// queue is empty when size is 0
int isEmpty(struct queue *this_queue){
	return (this_queue->size == 0);
}

//Function to add item to a queue, it changes rear and size
void enqueue(struct queue *this_queue, int item){
	if (isFull(this_queue))
		return;
	this_queue->rear = (this_queue->rear + 1)%this_queue->capacity;
	this_queue->array[this_queue->rear] = item;
	this_queue->size = this_queue->size + 1;
	//printf("%d enqueued to queue\n", item);
}

int dequeue(struct queue *this_queue){
	if (isFull(this_queue))
		return INT_MIN;
	if (isEmpty(this_queue)) //added for this multiplication
		return 0;
	int item = this_queue->array[this_queue->front];
	this_queue->front = (this_queue->front + 1)%this_queue->capacity;
	this_queue->size = this_queue->size - 1;
	return item;
}

//Function to get front of queue
int front(struct queue *this_queue){
	if(isEmpty(this_queue))
		return INT_MIN;
	return (this_queue->array[this_queue->front]);
}

//Function to get rear of queue
int rear(struct queue *this_queue){
	if(isEmpty(this_queue))
		return INT_MIN;
	return (this_queue->array[this_queue->rear]);
}

void swap(int *px, int *py){ /*interchange *px and *py - see K&R*/
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;	
}

struct stack *createStack(unsigned capacity)
{
	struct stack *this_stack = (struct stack *) malloc(sizeof(struct stack));
	this_stack->capacity = capacity;
	this_stack->top = -1;
	this_stack->array = (int *) malloc(capacity * sizeof(int));
	return this_stack;
}


// stack is empty when top is -1
int isNull(struct stack *this_stack){
	return (this_stack->top == -1);
}

//Function to add item to a queue, it changes rear and size
void push(struct stack *this_stack, int item){
	this_stack->top = (this_stack->top + 1);
	this_stack->array[this_stack->top] = item;
	//printf("%d pushed to stack\n", item);
}

int pop(struct stack *this_stack){
	if (isNull(this_stack))
		return INT_MIN;
	int item = this_stack->array[this_stack->top];
	this_stack->top = (this_stack->top - 1);
	return item;
}

//Function to get front of queue
int top(struct stack *this_stack){
	if(isNull(this_stack))
		return INT_MIN;
	return (this_stack->array[this_stack->top]);
}

void int_mult(char *str1, char *str2){
	int i, j, k, m; // counters
	int size_s1, size_s2; //size of arrays s1 and s2
	int out, carry, remainder, temp;
	int s1[size_s1 = strlen(str1)], s2[size_s2 = strlen(str2)];
	struct queue *subsums[size_s2];
	for (i=0; i<size_s2; i++){
		subsums[i] = createQueue(size_s1 * size_s2 + 1);
	}
	struct stack *total = createStack(size_s1 * size_s2 + 1);

	//convert each char from str1 and str2 into arrays of integers
	for (i=0;i<size_s1;i++){
		s1[i] = (int)str1[i]-48;
	}
	for (i=0;i<size_s2;i++){
		s2[i] = (int)str2[i]-48;
	}
	
	k=0;
	for (j=size_s2-1; j>=0; j--){
		carry=0;
		for (m=0; m<k; m++){
				enqueue(subsums[k],0);
			}
		for (i=size_s1-1; i>=0; i--){
			out = (s1[i]*s2[j]) + carry;
			remainder = out%10;
			carry = (out-remainder)/10;
			enqueue(subsums[k],remainder);
			if ((i==0) && (carry != 0)){
				enqueue(subsums[k],carry);
			}
		}
	    k++;
	}
	
	remainder = 0;
	carry = 0;
	for(i=0;i<(size_s1*size_s2+1);i++){ //size_s1+size_s2
		out = 0;
		for (j=0;j<size_s2;j++){ //size_s2
			temp = dequeue(subsums[j]);
			out += temp;
		}
		out += carry;
		remainder = out%10;
		carry = (out-remainder)/10;
		push(total, remainder);
	}
	if (carry != 0){
		push(total,carry);
	}
	
	while ((out = pop(total)) == 0) //remove any leading zero
		;
	printf("%d", out); //read one number which is non-zero, so print it first
	while ((out = pop(total)) != INT_MIN){ // print remaining numbers
		printf("%d",out);
	}
}

int main(void){
	
	char str1[100],str2[100];
	
	printf("Integer muliplication (algo from high school)\n");
	printf("Enter 1st number: "), gets(str1);
	printf("Enter 2nd number: "), gets(str2);
	printf("Result\t\t: "), int_mult(str1, str2);
		
	return 0;
}

