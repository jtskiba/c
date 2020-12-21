#include <stdio.h>
#include <string.h>

void print_array(int a[], int cnt){
	int i;
	for (i=0;i<cnt;i++)
		printf("%d ",a[i]);
	printf("\n");
}

/* Determine whether string s is longer than string t */
/* WARNING: This function is buggy */
int strlonger(char *s, char *t) {
	return strlen(s) - strlen(t) > 0;
} //strlen outputs unsigned int! per string.h

int strlonger2(char *s, char *t) {
	return strlen(s) > strlen(t);
} //strlen outputs unsigned int! per string.h

int main(void){
			
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	*/
	
	/*p.77 PP2.26*/
	char *s1 = "abcd";
	char *s2 = "abcde";
			
	printf("s1='abcd' longer than s2='abcde'? FALSE/0. Per strlonger = %d\n",strlonger(s1,s2));
	printf("s1='abcd' longer than s2='abcde'? FALSE/0. Per strlonger2 = %d\n",strlonger2(s1,s2));
	
	return 0;
}