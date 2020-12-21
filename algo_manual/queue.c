#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct queue{ // from: https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
	int front, rear, size;
	unsigned capacity;
	int *array;
};

void swap(int *, int *);
void insertion_sort(int s[], int n);
void selection_sort(int s[], int n);
void bubble_sort(int s[], int n);
struct queue *createQueue(unsigned capacity);
void enqueue(struct queue *this_queue, int item);
int dequeue(struct queue *this_queue);
int front(struct queue *this_queue);
int rear(struct queue *this_queue);

int main(void){
	
	int i, j; /*for iterations*/ 
	int n=10; /*array length*/
	int s[n]; /*array*/
	
	/*
	for (i=0; i<n; ++i) // generate an array of n random numbers
		s[i]=rand(); // random int generator from <stdlib.h> 
	
	for (i=0; i< n; ++i) // print unsorted array elements
		printf("%d\n",s[i]);
	printf("\n");
	
	
	//insertion_sort(s, n); // performance is n^2 
    //selection_sort(s, n); // performance is n^2 	
	//bubble_sort(s, n); // performance is n^2 	

	//printf("\nsize: %d\n\n",sizeof(s)/sizeof(int)); //prints size of array i.e. 40 / 4 = 10

		
	for (i = 0; i < n; ++i) //print sorted array elements
		printf("%d\n",s[i]);
	*/
	
	struct queue *my_queue = createQueue(1000);
	
	enqueue(my_queue, 10);
	enqueue(my_queue, 20);
	enqueue(my_queue, 30);
	enqueue(my_queue, 40);
	
	printf("%d dequeued from queue\n\n", dequeue(my_queue)); 
  
    printf("Front item is %d\n", front(my_queue)); 
    printf("Rear item is %d\n", rear(my_queue)); 
	
	
	return 0;
}

void swap(int *px, int *py){ /*interchange *px and *py - see K&R*/
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;	
}

void insertion_sort(int s[], int n){
	int i, j;		
	for (i=1; i<n; i++){ /* insertion sort */
		j=i;
		while ((j>0) && (s[j] < s[j-1])){
			swap(&s[j],&s[j-1]);
			j--;
		}
	}	
}

void selection_sort(int s[], int n){
	int i, j; //counters
	int min; //index of minimum
	for (i=0; i<n; i++){
		min=i;
		for (j=i+1;j<n;j++)
			if (s[j] < s[min]) min=j;
		swap(&s[i],&s[min]);
	}
}

void bubble_sort(int s[], int n){  // https://en.wikipedia.org/wiki/Bubble_sort
	int i, j; //counters
	for (i=n; i>0; i--){
		for (j=1;j<n;j++)
			if (s[j] < s[j-1])
				swap(&s[j],&s[j-1]);
	}
}
/*
void merge_sort(int s[], int low, int high){  // see Skiena Algorithm Design Manual, p.122
	int i;      //counter
	int middle; //index of middle element
	
	if (low < high){
		middle = (low + high) / 2;
		merge_sort(s, low, middle);
		merge_sort(s, middle+1, high);
		merging(s, low, middle, high);
	}
}

void merging(int s[], int low, int middle, int high){  // see Skiena Algorithm Design Manual, p.123
	int i; // counter	
	
}
*/


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
	printf("%d enqueued to queue\n", item);
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


