#define ONE 1

int sum(int *a, int n);

int array[2] = {ONE, 2};

int main(void){
	int val = sum(array, 2);
	return val;
}