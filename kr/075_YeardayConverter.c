/*
K&R Ch5.7
Let us define two functions to do the conversions: day_of_year converts the month and day
into the day of the year, and month_day converts the day of the year into the month and day.
Since this latter function computes two values, the month and day arguments will be pointers:

month_day(1988, 60, &m, &d)
sets m to 2 and d to 29 (February 29th).
*/

#include <stdio.h>
#include <string.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};


/* sort input lines */
int main(void)
{
	
	int year, month, day, yearday;
	int pmo; 
	int pda;
	
	printf("Let's convert year/month/day to yearday\n");
	printf("Enter year:\n");
	scanf("%d", &year);
	printf("Enter month:\n");
	scanf("%d", &month);
	printf("Enter day:\n");
	scanf("%d", &day);
	printf("\t this is: %d\n",day_of_year(year,month,day));
	
	printf("Let's convert year/yearday to month/day\n");
	printf("Enter year:\n");
	scanf("%d", &year);
	printf("Enter yearday:\n");
	scanf("%d", &yearday);
	month_day(year,yearday,&pmo,&pda);
	printf("\t this is: month - %d, day - %d\n",pmo,pda);
	
	
	
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

