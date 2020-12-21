/* Write a Program detab,which replaces tabs in the input with a proper
  number of blanks to space. This is exercise 1-20 on p.34 of K&R */

  #include <stdio.h>

  #define TABS 8
  #define FILL '#'

  main()
  {
      int i, c;
      int count; /* counts position of cursor */
      int spaces;

      count = spaces = 0;
      while ((c = getchar()) != EOF)
      {
          if (c == '\n')
              count = -1; /* Otherwise second line of input is messed up as newline is added to the count */

          count++;
          if (c == '\t')
          {
              spaces = TABS - ((count - 1) % TABS);
              count+=spaces-1;
              for (i = 1; i <= spaces; ++i)
              {
                  putchar(FILL);
              }
              i = 0;

          }
          else
          {
              putchar(c);
          }
      }
  }


