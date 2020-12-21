
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 3 Machine-Level Representation of Programs
	//////////////////////////////////////////////////////////
	*/
	
	//gcc -O1 -S 03_03_SimpleExample.c

int simple(int *xp, int y){
	int t = *xp + y;
	*xp = t;
	return t;
}