/*
K&R Ch5.8
function month_name(n), which returns a pointer to a
character string containing the name of the n-th month.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);
char *month_name(int n);

static char daytab[2][13] = {
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};


/* sort input lines */
int main(void)
{
	
	int year, month, day, yearday, out;
	int pmo; 
	int pda;
	
	do {
		printf("Let's convert year/month/day to yearday\n");
		printf("Enter year:\n");
		scanf("%d", &year);
		printf("Enter month:\n");
		scanf("%d", &month);
		printf("Enter day:\n");
		scanf("%d", &day);
		yearday = day_of_year(year,month,day);
		if (yearday == -1)
			printf("\t One of the inputs is incorrect, try again..\n");
	} while (yearday == -1);
	
	printf("\t this is: %d yearday\n",yearday);
	
	
	
	do {
		printf("Let's convert year/yearday to month/day\n");
		printf("Enter year:\n");
		scanf("%d", &year);
		printf("Enter yearday:\n");
		scanf("%d", &yearday);
		out = month_day(year,yearday,&pmo,&pda);
		if (out == -1)
			printf("\t Your yearday figure is negative or too high, try again..\n");
	} while (out == -1);
			
	printf("\t this is: %s, %d\n", month_name(pmo),pda);
	
	
	
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	// error checking below
	if ((month < 1) || (month > 12) ){
		printf("month\n");
		return -1; //error will be flagged by negative 1
	}
	if ((day < 1) || (day > daytab[leap][month]))
	{
		printf("day\n");
		return -1; //error will be flagged by negative 1
	}
	

	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap, max_days_in_year;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	
	
	if (leap)
		max_days_in_year = 366;
	else
		max_days_in_year = 365;
	
	//error checking below
	if (yearday > max_days_in_year)
		return -1;
	
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
	return 1;
}


/* month_name: return name of n-th month */
char *month_name(int n)
{
	static char *name[] = {
		"Illegal month",
		"January", "February", "March",
		"April", "May", "June",
		"July", "August", "September",
		"October", "November", "December"
	};
	return (n < 1 || n > 12) ? name[0] : name[n];
}
