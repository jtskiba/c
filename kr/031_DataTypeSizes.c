/*
K&R Ex 2-1, p.36.
Determine the rnages of char, short, int, long variables both signed and unsigned
by printing standard headers and by direct computation
*/
#include<stdio.h>
#include<math.h>
#include<limits.h>

#define BIT 8

int main(void)
{
    int i = 1 ;
    int temp;
    short int hi = 1;
    unsigned short int hu = 1;
    long int li = 1;
    unsigned long int lu = 1;
    unsigned int ui = 1;
    char c = 1;
    unsigned char uc = 1;

    /* INT - compute (takes 5 seconds)*/
    //while (i > 0)
    //    i++;
    //printf("int is from i= %d to i=%d\n", i, i-1);

    /* INT - standard headers*/
    printf("Storage size of int is %d, therefore max number: 2^(%d * 8bits)\n", sizeof(int), sizeof(int));
    printf("int is from i= %d to i= %d\n",
           (int)pow(2,(sizeof(int)*BIT))+1,
           (int)pow(2,(sizeof(int)*BIT)));
            // you need math.h for pow(a,b)
    printf("int is from i= %d to i= %d\n", INT_MIN, INT_MAX); // you need limits.h
    printf("int is from i= %d to i= %d\n\n", -INT_MAX-1, INT_MAX);


    /* UNSIGNED INT - compute */
    printf("unsigned int is from ui= %u to ui= %u\n", 0, -1);

    /* UNSIGNED INT - standard headers*/
    printf("Storage size of unsigned int is %u, therefore max number: 2^(%u * 8bits)\n",
           sizeof(unsigned int), sizeof(unsigned int));
    printf("unsigned int is from i= %u to i= %u\n",
           (unsigned int)pow(2,(sizeof(unsigned int)*BIT))+1,
           (unsigned int)pow(2,(sizeof(unsigned int)*BIT)));
             // you need math.h for pow(a,b)
    printf("unsigned int is from ui= %u to ui= %u\n\n", 0, UINT_MAX); // you need limits.h,
            // note: no such thing as UINT_MIN - this is just zero



    /* CHAR - compute (takes = 0 sec)*/
    while (c > 0)
        c++;
    printf("char is from c= %d to c= %d\n", c, -(c+1));
            // note that you cannot use c - 1 in the latter as this will yield -129 due to %d

    /* CHAR - standard headers */
    printf("Storage size of char is %d, therefore max number: 2^(%d * 8bits) = \n", sizeof(char), sizeof(char));
    printf("char is from c= %d to c= %d\n",
           -(int)pow(2,(sizeof(char)*BIT))/2,
           -1+(int)pow(2,(sizeof(char)*BIT))/2);
            // you need math.h for pow(a,b)
    printf("char is from c= %d to c= %d\n", CHAR_MIN, CHAR_MAX); // you need limits.h
    printf("char is from c= %d to c= %d\n\n", -CHAR_MAX-1, CHAR_MAX);

    /* UNSIGNED CHAR - compute*/
    while (uc > 0){
        temp = uc;
        uc++;
    }
    printf("unsigned char is from uc= %d to uc= %d\n", 0, temp);
            // harder to retrieve that final positive char number, thats why created temp

    /* UNSIGNED CHAR - standard headers */
    printf("Storage size of unsigned char is %d, therefore max number: 2^(%d * 8bits) = \n",
           sizeof(unsigned char), sizeof(unsigned char));
    printf("unsigned char is from uc= %d to uc= %d\n",
           0,
           (int)pow(2,(sizeof(unsigned char)*BIT))-1);
            // you need math.h for pow(a,b)
    printf("unsigned char is from uc= %d to uc= %d\n\n", 0, UCHAR_MAX); // you need limits.h


    /* SHORT - compute*/
    while (hi > 0)
        hi++;
    printf("short int is from hi= %hi to hi= %hi\n", hi, hi-1);

    /* SHORT INT - standard headers */
    printf("Storage size of short int is %d, therefore max number: 2^(%d * 8bits)\n",
           sizeof(short int), sizeof(short int));
    printf("short int is from hi= %hi to hi= %hi\n",
           (short int)pow(2,(sizeof(short int)*BIT))+1,
           (short int)pow(2,(sizeof(short int)*BIT)));
            // you need math.h for pow(a,b)
    printf("short int is from hi= %d to hi= %d\n", SHRT_MIN, SHRT_MAX); // you need limits.h
    printf("short int is from hi= %d to hi= %d\n\n", -SHRT_MAX-1, SHRT_MAX);

    /* UNSIGNED SHORT - compute*/
    printf("unsigned short int is from hu= %hu to hu= %hu\n", 0, -1);

    /* UNSIGNED SHORT INT - standard headers */
    printf("Storage size of unsigned short int is %d, therefore max number: 2^(%d * 8bits)\n",
           sizeof(unsigned short int), sizeof(unsigned short int));
    printf("unsigned short int is from hu= %hu to hi= %hu\n",
           0,
           (unsigned short int)pow(2,(sizeof(unsigned short int)*BIT)));
            // you need math.h for pow(a,b)
    printf("unsigned short int is from hu= %d to hu= %d\n\n", 0, USHRT_MAX); // you need limits.h


    /* LONG - compute*/
    while (li > 0)
        li++;
    printf("long int is from li= %li to li= %li\n", li, li-1);

    /* LONG INT - standard headers */
    printf("Storage size of long int is %d, therefore max number: 2^(%d * 8bits)\n",
           sizeof(long int), sizeof(long int));
    printf("long int is from li= %li to li= %li\n",
           (long int)pow(2,(sizeof(long int)*BIT))+1,
           (long int)pow(2,(sizeof(long int)*BIT)));
            // you need math.h for pow(a,b)
    printf("long int is from li= %d to li= %d\n", LONG_MIN, LONG_MAX); // you need limits.h
    printf("long int is from li= %d to li= %d\n\n", -LONG_MAX-1, LONG_MAX);

    /* UNSIGNED LONG INT- compute*/
    printf("unsigned long int is from lu= %lu to lu= %lu\n", 0, -1);

    /* UNSIGNED LONG INT - standard headers */
    printf("Storage size of unsigned long int is %d, therefore max number: 2^(%d * 8bits)\n",
           sizeof(unsigned long int), sizeof(unsigned long int));
    printf("unsigned long int is from lu= %lu to lu= %lu\n",
           0,
           (unsigned long int)pow(2,(sizeof(unsigned long int)*BIT)));
            // you need math.h for pow(a,b)
    printf("unsigned long int is from lu= %d to lu= %u\n\n", 0, ULONG_MAX); // you need limits.h


}

