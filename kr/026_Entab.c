/* Write a Program entab that replaces strings of blanks by the minimum
    number of tabs and blanks to acheive the same spacing.
   Use the same tab stops as for detab.
   This is exercise 1-21 on p.34 in K&R
*/
#include<stdio.h>
#define TABS 8

int main(void)
  {
      int i, c;
      int count; /* counts position of cursor */
      int spaces; /* no of blanks to next tab stop, max 7 */
      int cons_blanks; /* counts the number of consecutive blanks */
      int x1,x2,x3,y1,y2,y3;  /*this is to track what i typed and what i print- a proof (space,tab,other)*/

      x1 = x2 = x3 = y1 = y2 = y3 = 0;
      count = spaces = cons_blanks = 0;
      while ((c = getchar()) != EOF)
      {
          if (c == '\n')
              count = -1; /* Otherwise second line of input is messed up as newline is added to the count */
          count++;
          if (c == ' ')
          {
              ++cons_blanks;
              --count;
              ++x1;
          }
          else
          {
              if (c == '\t')
              {
                  ++x2;
                  count = (TABS * ((count - 1) / TABS)) + ((count - 1) % TABS);
              }
              else
                  ++x3;

              spaces =  (TABS * (((count - 1) / TABS)  + 1)) - (count - 1);
              spaces = spaces % TABS;
              if (cons_blanks <= spaces)
              {
                  for (i = 1; i <= cons_blanks; ++i)
                  {
                      putchar(' ');
                      ++y1;
                  }
                  count = count + cons_blanks;
              }
              else
              {
                  for (i = 1; i <= spaces; ++i)
                  {
                      putchar(' ');
                      ++y1;
                  }
                  for (i = 1; i <= ((cons_blanks - spaces) / TABS); i++)
                  {
                      putchar('\t');
                      ++y2;
                  }
                  for (i = 1; i <= ((cons_blanks - spaces) % TABS); i++)
                  {
                      putchar(' ');
                      ++y1;
                  }
                  count = count + cons_blanks;
              }
              cons_blanks = 0;
              if (c == '\t')
                  ++y2;
              putchar(c);
          }
      }
      printf("OLD: space:%2d\ttab:%2d\tother:%2d\n",x1, x2, x3);
      printf("NEW: space:%2d\ttab:%2d\tother:%2d\n",y1, y2, y3 = x1 + x2 + x3 - y1 - y2);
      return 0;
}



