#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

struct queue{ // from: https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
	int front, rear, size;
	unsigned capacity;
	int *array;
};

void swap(int *, int *);
void merge_sort(int s[], int low, int high);
void merging(int s[], int low, int middle, int high);
void CountSplitInv(int s[], int low, int middle, int high, int *inv);
void sort_and_count(int s[], int low, int high, int *inv);
struct queue *createQueue(unsigned capacity);
void enqueue(struct queue *this_queue, int item);
int dequeue(struct queue *this_queue);
int front(struct queue *this_queue);
int rear(struct queue *this_queue);

int main(void){
	
	int i, j; /*for iterations*/ 
	int inversions; /* count inversions*/
	int n=6; /*array length*/
	//int s[6] = {1, 3, 5, 2, 4, 6}; /*array*/
	int s[6] = {6, 5, 4, 3, 2, 1}; /*array*/
	inversions = 0;
	
	//for (i=0; i<n; ++i) // generate an array of n random numbers
	//	s[i] = n-i;        //rand(); // random int generator from <stdlib.h> 
	
	for (i=0; i< n; ++i) // print unsorted array elements
		printf("%d\n",s[i]);
	printf("\n");
	
	sort_and_count(s,0,5, &inversions);
		
	for (i = 0; i < n; ++i) //print sorted array elements
		printf("%d\n",s[i]);
	
	printf("Inversions total = %d\n", inversions);

	return 0;
}

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

void merge_sort(int s[], int low, int high){  // see Skiena Algorithm Design Manual, p.122
	int i;      //counter
	int middle; //index of middle element
	
	if (low < high){
		middle = round((low + high) / 2);
		merge_sort(s, low, middle);
		merge_sort(s, middle+1, high);
		merging(s, low, middle, high);
	}
}

void merging(int s[], int low, int middle, int high){  // see Skiena Algorithm Design Manual, p.123
	int i; // counter	
	struct queue *buffer1 = createQueue(20);
	struct queue *buffer2 = createQueue(20);

	for (i=low; i<=middle; i++) enqueue(buffer1, s[i]);
	for (i=middle+1; i<=high; i++) enqueue(buffer2, s[i]);
	
	i = low;
	while (!isEmpty(buffer1) && !isEmpty(buffer2)){ // updated as found bug in the Skiena's version or copied incorrectly
		if (front(buffer1) <= front(buffer2))
			s[i++] = dequeue(buffer1);
		else
			s[i++] = dequeue(buffer2);
	}
	
	while (!isEmpty(buffer1)) s[i++] = dequeue(buffer1);
	while (!isEmpty(buffer2)) s[i++] = dequeue(buffer2);

}

void sort_and_count(int s[], int low, int high, int *inv){  // see Skiena Algorithm Design Manual, p.122
	int i;      //counter
	int middle; //index of middle element
	
	if (low < high){
		middle = round((low + high) / 2);
		sort_and_count(s, low, middle, inv);
		sort_and_count(s, middle+1, high, inv);
		CountSplitInv(s, low, middle, high, inv);
	}
}

void CountSplitInv(int s[], int low, int middle, int high, int *inv){  // see Skiena Algorithm Design Manual, p.123
	int i; // counter	
	struct queue *buffer1 = createQueue(100);
	struct queue *buffer2 = createQueue(100);

	for (i=low; i<=middle; i++) enqueue(buffer1, s[i]);
	for (i=middle+1; i<=high; i++) enqueue(buffer2, s[i]);
	
	i = low;
	while (!isEmpty(buffer1) && !isEmpty(buffer2)){ // updated as found bug in the Skiena's version or copied incorrectly
		//printf("b1:%d b2:%d s1:%d s2:%d r1:%d r2:%d f1:%d f2:%d ",front(buffer1), front(buffer2), buffer1->size, buffer2->size, buffer1->rear, buffer2->rear, buffer1->front, buffer2->front);
		if (front(buffer1) <= front(buffer2)){
			s[i++] = dequeue(buffer1);
			//printf("\n");
		}
		else {
			*inv += buffer1->size;
			//printf("inv = %d\n",buffer1->size - buffer1->front);
			s[i++] = dequeue(buffer2);
			
		}
	}
	
	while (!isEmpty(buffer1)) {s[i++] = dequeue(buffer1);}
	while (!isEmpty(buffer2)) {s[i++] = dequeue(buffer2);}

}


