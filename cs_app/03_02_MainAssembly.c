
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 3 Machine-Level Representation of Programs
	//////////////////////////////////////////////////////////
	*/
	
	//gcc -O1 -o out 03_01_AccumAssembly.o 03_02_MainAssembly.c
	//objdump -d out
	
	int sum(int, int);
	
int main(){
	return sum(1,3);
}