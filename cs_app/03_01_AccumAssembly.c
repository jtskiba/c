
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 3 Machine-Level Representation of Programs
	//////////////////////////////////////////////////////////
	*/
	
	//p.162 3.2.2 Code example
	//to see assembly output run as follows:
	//gcc -O1 -S NameOfSourceFile.c  //-O1 is the first level of optimisation (higher levels may generate assembly which is hard to decipher) -S to give assembly

	//gcc -O1 -c 03_01_AccumAssembly.c
	// to get the object file in binary 
	
	// then use the following to decode it (this is invoking disassembler)
	//objdump -D 03_01_AccumAssembly.o

	// or as per p.163, use run gdb on the .o file i.e. gdb 03_01_AccumAssembly.o
	// and in there, type: x/17xb sum
	// this means examine (x), 17 hex (x) formatted bytes (b)

int accum = 0;

int sum(int x, int y){
	int t = x + y;
	accum += t;
	return t;
}