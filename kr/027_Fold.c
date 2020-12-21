/* Write a Program Fold that folds long input ines into two or more shorter lines after the last
non blank character that occurs before the n-th column of input.
Make sure your program does something intelligent with very long lines lines, and if there are no
blanks or tabs before the specified column.
This is exercise 1-22 on p.34 in K&R
NB. it also converts different number of blanks (be it spaces or tabs) into a single space
*/

#include<stdio.h>
#define TABS 8 /* default number of spaces between two tab stops */
#define NEXT_LINE 10 /* this is max length of a row, ie e.g. 10 columns of length */
#define MAXLINE 1000 /* max number of characters that can be read and split between rows */
#define IN 1 /* are we in word or outside word */
#define OUT 0

int find_blank_between(char array[], int from, int to); /* this fn was not used in the end */

/* takes input line, and breaks it down into rows of same size, equal to NEXT_LINE
   It also removed >1 number of spaces before processing print */
int main(void)
  {
      int i, j, k, m, n, t0, t1, c, find, state;
      int count; /* counts position of cursor, taking into account tab stops */
      int last_break; /* shows cursor position of last space or tab before NEXT_LINE, not used */
      char line[MAXLINE];

      state = IN; /* first char [position = 1] is always non blank, thats how i wrote it */
      count = 0; /* cursor counter to zero */
      last_break = 0; /* not used, to initialise only */
      j = 0; /* this is so that we dont write char to sentence when double spacing used */
      line[0] = ' ';
      m = 1; /* current word starting position */
      t0 = 1; /* position of cursor for next line) */
      t1 = t0 + NEXT_LINE - 1; /* position of cursor for end of next line */

      /* reading input into my line array, removing any double or more spacings, i vs j used for that*/
      for (i = 0; ((c = getchar()) != EOF) && (c != '\n') && (i < MAXLINE - 1); i++)
      {
          if ((c == ' ') && (line[j] != ' ') && (line[j] != '\t'))
          {
              ++j;
              ++count;
              //last_break = j;
              line[j] = c;

          }
          else if ((c == ' ') && ((line[j] == ' ') || (line[j] != '\t')))
          {
              ++count;
          }
          else if ((c == '\t') && (line[j] != ' ') && (line[j] != '\t'))
          {
              ++j;
              count += TABS - (count % TABS);
              //last_break = j;
              line[j] = ' ';
          }
          else if ((c == '\t') && ((line[j] == ' ') || (line[j] == '\t')))
          {
              count += TABS - (count % TABS);
          }
          else
          {
              ++j;
              ++count;
              line[j] = c;
          }
      }
      line[++j] = '\0'; /* to finish each input with EOF mark */
      /* Below is reprinting the long line as it is, without splitting */
      printf("\nREPRINT:\n");
      for (n = 1; n <= j; ++n)
      {
          printf("%c",line[n]);
      }
      /* This splits the input between rows, as requested
         It goes through my line and checks if in or out of word
         if out of word, it then considers printing the last word
         m - start position of the last word
         n - 1 - end position of last word (as n is a blank)
         t0 - start of the row you are in
         t1 - end of the row you are in
         when the current word is spanning the end of row t1, then
         you need to move the word into new row and start printing then.
         When word is very long (longer than NEXT_LINE, then the word
         goes to next row and print NEXT_LINE of characters, then does '-'
         moves to next row, and then continues printing until all characters
         of the word are printed*/
      printf("\n\nSPLIT PRINT:\n");
        for (n = 1; n <= j; ++n)
      {
           if ((line[n] == ' ') || (line[n] == '\0'))
           {
               state = OUT;
               //find = find_blank_between(line, t0, t1);
               if ((n - 1)<= t1)
                  for (k = m; k <= n; ++k)
                      putchar(line[k]);
               else
               {
                   putchar('\n');
                   t0 = m;
                   t1 = t0 + NEXT_LINE - 1;
                   while (((n - 1) - t1 + 1) >= 0)
                   {
                       for (k = m; k <= t1 - 1; ++k)
                          putchar(line[k]);
                       putchar('-');
                       putchar('\n');
                       m = t1;
                       t0 = m;
                       t1 = t0 + NEXT_LINE - 1;
                   }
                   for (k = m; k <= n; ++k)
                        putchar(line[k]);
               }
           }
           else
           {
               if (state == OUT)
                   m = n;
               state = IN;
           }
      }
      return 0;
}

/* finds last blank ie space in an arrays elts from to
   this function proved not to be used in the end. but
   kept here for reference */
int find_blank_between(char array[], int from, int to)
{
    int i, sum;
    sum = 0;
    for (i = from; i <= to; i++)
        if (array[i] != ' ')
            ++sum;

    if (sum == (to - from + 1))
        return to;
    else if (sum == 0)
        return from;
    else
    {
        for (i = to; i >= from; i--)
            if (array[i] == ' ')
                return i;
    }

}



