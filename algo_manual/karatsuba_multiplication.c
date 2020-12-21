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

struct stack *createStack(unsigned capacity){
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

//subtracts two numbers in queue representation (a >=b!) 
struct queue *subtractq(struct queue *a, struct queue *b){ //assumes a>=b
	
	int carry, out, i, max, deqA, deqB, same_inputs;
	int len1 = a->size;
	int len2 = b->size;
	if (len1>len2) max=len1; else max=len2;
	struct queue* totalq = createQueue(max+1);
	if (a==b) same_inputs=1; else same_inputs=0; 
	
	carry = 0;
	for(i=0;i<max;i++){
		//printf("i=%d\n",i);
		out = 0;
		if (same_inputs == 0){ // not the same inputs a and b
			deqA = dequeue(a); //printf(" deqA=%d\n",deqA);
			deqB = dequeue(b); //printf(" deqB=%d\n",deqB);
			out = deqA - deqB - carry;
			carry = 0;
		}
		else {
			deqA = dequeue(a); //same inputs a and b
			out = 0 - carry; // deqA - deqA - carry;
			carry = 0;
		}
		if (out < 0){
			out += 10;
			carry = 1;
		}
		enqueue(totalq, out);
	}
	if (same_inputs == 0){ // not the same inputs a and b
		a->size = a->size+len1;
		a->front = a->front-len1;
		b->size = b->size+len2;
		b->front = b->front-len2;
	}
	else {
		a->size = a->size+len1;
		a->front = a->front-len1;
	}
	//printf("\ntotq size=%d front=%d rear=%d array[f]=%d\n", totalq->size, totalq->front, totalq->rear, totalq->array[totalq->front]);
	
	while ((totalq->array[totalq->rear]) == 0){ // make sure that 12-8=4 not 04
		totalq->rear = totalq->rear - 1;
		totalq->size = totalq->size - 1;
	}
	return totalq;
}

// multiplies a number in queue representation by 10 to the power n  (number * 10^n)
struct queue *x10powerNq(struct queue *a, int power){
	
	int remainder, carry, out, i, j, max, deqA, deqB, same_inputs;
	int len = a->size;
	struct queue* totalq = createQueue(len+power+1); 
	
	for(i=0;i<power;i++){
		enqueue(totalq,0);
	}
	
	for(i=0;i<len;i++){
		//printf("i=%d\n",i);
		out = 0;
		enqueue(totalq,dequeue(a));
	}
	a->size = a->size+len;
	a->front = a->front-len;

	while (((totalq->array[totalq->rear]) == 0) && (totalq->size >1)){ // make sure no leading zero 
		totalq->rear = totalq->rear - 1;
		totalq->size = totalq->size - 1;
	}	
	return totalq;
}

//adds two numbers in queue representation
struct queue *addq(struct queue *a, struct queue *b){
	//adds two numbers in queue representation
	int remainder, carry, out, i, j, max, deqA, deqB, same_inputs;
	int len1 = a->size;
	int len2 = b->size;
	if (len1>len2) max=len1; else max=len2;
	//printf("\na: size= %d cap= %d\n",a->size, a->capacity);
	//printf("\nb: size= %d cap= %d\n",b->size, b->capacity);
	struct queue* totalq = createQueue(max+2); 
	if (a==b) same_inputs=1; else same_inputs=0; 
	//printf("same=%d\n", same_inputs);	
	remainder = 0;
	carry = 0;
	for(i=0;i<max;i++){
		//printf("i=%d\n",i);
		out = 0;
		if (same_inputs == 0){ // not the same inputs a and b (i.e. e.g. a and a, b and b - does not mean a=21 and b=21 are same, only if 2 same letters
			deqA = dequeue(a); //printf(" deqA=%d\n",deqA);
			deqB = dequeue(b); //printf(" deqB=%d\n",deqB);
			out = deqA + deqB + carry;
		}
		else {
			deqA = dequeue(a); //same inputs a and b
			out = deqA + deqA + carry;
		}					
		remainder = out%10;
		//printf(" rem: %d\n", remainder);
		carry = (out-remainder)/10;
		enqueue(totalq, remainder);
	}
	if (same_inputs == 0){ // not the same inputs a and b
		a->size = a->size+len1;
		a->front = a->front-len1;
		b->size = b->size+len2;
		b->front = b->front-len2;
	}
	else {
		a->size = a->size+len1;
		a->front = a->front-len1;
	}
	//printf("-%d",carry);
	
	if (carry != 0){
		//printf("i=%d\n",i);
		//printf(" car: %d\n", carry);
		enqueue(totalq, carry);
		//printf("%d",carry);
	}
	//printf("\ntotq: size= %d cap= %d\n",totalq->size, totalq->capacity);
	while ((totalq->array[totalq->rear]) == 0){ // make sure that 04+2=6 not 06
		totalq->rear = totalq->rear - 1;
		totalq->size = totalq->size - 1;
	}
	
	return totalq;
}


//multiplies two numbers in queue representation (KARATSUBA!)
struct queue *multq(struct queue *a, struct queue *b){
	void printq(struct queue *a);
	int remainder, out, i, j, max, deqA, deqB, same_inputs;
	//A, B, C, D, AxC, BxD, ApB, CpD, ApBxCpD, AxDpBxC;
	int len1 = a->size;
	int len2 = b->size;
	if (len1>len2) max=len1; else max=len2;
	struct queue* totalq = createQueue((len1*len2)+2);
	struct queue*      A = createQueue((len1*len2)+2); 	
	struct queue*      B = createQueue((len1*len2)+2); 
	struct queue*      C = createQueue((len1*len2)+2); 
	struct queue*      D = createQueue((len1*len2)+2); 
	struct queue*    ApB = createQueue((len1*len2)+2); 
	struct queue*    CpD = createQueue((len1*len2)+2); 
	struct queue*    AxC = createQueue((len1*len2)+2); 
	struct queue*    BxD = createQueue((len1*len2)+2); 
	struct queue* ApBxCpD= createQueue((len1*len2)+2); 
	struct queue* AxDpBxC= createQueue((len1*len2)+2); 
	

	if (a==b) same_inputs=1; else same_inputs=0; 
	
	
	//if (len1 < 1) {enqueue(a,0); multq(a,b);}
	//if (len2 < 1) {enqueue(b,0); multq(a,b);}
	
	if ((len1 <= 1) && (len2 <= 1)){
		if (same_inputs == 0){
			
			deqA = dequeue(a); 
			deqB = dequeue(b);
			out = deqA * deqB;
			if (out<10){
				enqueue(totalq,out);
			}
			else {
				//printf("\nout=%d\n",out);
				remainder = out%10;
				//printf("\nrem=%d\n",remainder);
				enqueue(totalq,remainder);
				out =(out-remainder)/10;
				enqueue(totalq, out);
			}
			a->size = a->size+len1;
			a->front = a->front-len1;
			b->size = b->size+len2;
			b->front = b->front-len2;
		}
		else {
			deqA = dequeue(a);
			out = deqA * deqA;
			if (out<10){
				enqueue(totalq,out);
			}
			else {
				remainder = out%10;
				enqueue(totalq,remainder);
				enqueue(totalq,(out-remainder)/10);
			}
			a->size = a->size+len1;
			a->front = a->front-len1;
		}
	}
	else {
		
		//A, B, C, D, AxC, BxD, ApB, CpD, ApBxCpD, AxDpBxC;
		
		for (i=0; i<max/2; i++){
			deqA = dequeue(a);
			enqueue(B, deqA);
		}
		for (i=max/2; i<max; i++){
			deqA = dequeue(a);
			enqueue(A, deqA);
		}
		for (i=0; i<max/2; i++){
			deqB = dequeue(b);
			enqueue(D, deqB);
		}
		for (i=max/2; i<max; i++){
			deqB = dequeue(b);
			enqueue(C, deqB);
		}
		
		a->size = a->size+len1;
		a->front = a->front-len1;
		b->size = b->size+len2;
		b->front = b->front-len2;
		
		ApB = addq(A, B);
		CpD = addq(C, D);
		
		// step1
		AxC = multq(A, C);
		//printq(AxC);
		
		// step2
		BxD = multq(B, D);
		//printq(BxD);
		
		// step3
		ApBxCpD = multq(ApB, CpD);
		//printq(ApBxCpD);
		
		// step4
		AxDpBxC = subtractq(subtractq(ApBxCpD, BxD), AxC);
		//printq(AxDpBxC);
		
		// step5
		totalq = addq(addq(x10powerNq(AxC,2*(max/2)),BxD), x10powerNq(AxDpBxC,max/2));
		//printq(totalq);
	}
	/*
	printf("\n");
	printq(a);
	printq(b);
	printq(A);
	printq(B);
	printq(C);
	printq(D);
	printq(ApB);
	printq(CpD);
	printf("\n");
	printq(AxC);
	printq(BxD);
	*/
	
	

	/*
	remainder = 0;
	carry = 0;
	for(i=0;i<max;i++){
		//printf("i=%d\n",i);
		out = 0;
		if (same_inputs == 0){ // not the same inputs a and b
			deqA = dequeue(a); //printf(" deqA=%d\n",deqA);
			deqB = dequeue(b); //printf(" deqB=%d\n",deqB);
			out = deqA + deqB + carry;
		}
		else {
			deqA = dequeue(a); //same inputs a and b
			out = deqA + deqA + carry;
		}					
		remainder = out%10;
		//printf(" rem: %d\n", remainder);
		carry = (out-remainder)/10;
		enqueue(totalq, remainder);
	}
	if (same_inputs == 0){ // not the same inputs a and b
		a->size = a->size+len1;
		a->front = a->front-len1;
		b->size = b->size+len2;
		b->front = b->front-len2;
	}
	else {
		a->size = a->size+len1;
		a->front = a->front-len1;
	}
	//printf("-%d",carry);
	
	if (carry != 0){
		//printf("i=%d\n",i);
		//printf(" car: %d\n", carry);
		enqueue(totalq, carry);
		//printf("%d",carry);
	}
	*/
	
	while (((totalq->array[totalq->rear]) == 0) && (totalq->size >1)){ // make sure no leading zeros (just in case)
		totalq->rear = totalq->rear - 1;
		totalq->size = totalq->size - 1;
	}
	
	return totalq;
}


// prints number in queue representation
void printq(struct queue *a){
	int i;
	int len = a->size;
	struct stack* total = createStack(len+1);
	//printf("\nin print a: size= %d cap= %d\n",a->size, a->capacity);
	for (i=0;i<len;i++){
		push(total,dequeue(a));
	}
	//printf(">>len=%d, i=%d\n",len, i);
	a->size = a->size+len;
	a->front = a->front-len;
	//printf("\nin print a: size= %d cap= %d\n",a->size, a->capacity);
	for (i=0;i<len;i++){
		printf("%d",pop(total));
	}
	printf("\n");
	//free(total);
}

// below is katsuba mult but only for 2x2 (depracated!) - used to take string input
void karatsuba_mult(char *str1, char *str2){
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
	int size_s1, size_s2, i;
	char str1[100],str2[100];
	struct queue* q1 = createQueue(100);
	struct queue* q2 = createQueue(100);
	struct queue* q3 = createQueue(100);
	struct queue* q4 = createQueue(100);
	struct queue* q5 = createQueue(100);
		
	//printf("Karatsuba muliplication\n");
	printf("Enter 1st number: "), gets(str1);
	printf("Enter 2nd number: "), gets(str2);
	//printf("Result\t\t: "), karatsuba_mult(str1, str2);
	
	//convert each char from str1 and str2 into queues of integers
	size_s1 = strlen(str1), size_s2 = strlen(str2);
	
	for (i=size_s1-1; i>=0; i--){
		enqueue(q1, (int)str1[i]-48);
	}
	for (i=size_s2-1; i>=0; i--){
		enqueue(q2, (int)str2[i]-48);
	}
	
	// Karatsuba muliplication
	printf("Multipl result\t: ");
	q3 = multq(q1,q2);
	printq(q3);
	
	return 0;
}

