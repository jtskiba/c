#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct stack{ // from: https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
	int top;
	unsigned capacity;
	int *array;
};

void swap(int *, int *);
void insertion_sort(int s[], int n);
void selection_sort(int s[], int n);
void bubble_sort(int s[], int n);

struct stack *createStack(unsigned capacity);
void push(struct stack *this_stack, int item);
int pop(struct stack *this_stack);
int top(struct stack *this_stack);
int isNull(struct stack *this_stack);

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
	
	struct stack *my_stack = createStack(100);
	
	push(my_stack, 10);
	push(my_stack, 20);
	push(my_stack, 30);
	push(my_stack, 40);
	
	printf("%d popped from stack\n", pop(my_stack)); 
    printf("Top item is %d\n", top(my_stack)); 
 
	printf("%d popped from stack\n", pop(my_stack));
	printf("Top item is %d\n", top(my_stack)); 
	
	
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
	printf("%d pushed to stack\n", item);
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




