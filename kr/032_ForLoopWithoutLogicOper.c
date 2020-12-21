/*
K&R Ex 2-2, p.42.
Write loop equivalent to the for loop without using the && and ||
*/

#include<stdio.h>

int main(void)
{
    int lim = 1000;
    int c, i; 
    char s[lim];
    /*Re-write the first one without the logic operators*/
    /*
    for(i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;
            
    */
    // Replacement starts here
    for(i=0; i<lim-1; ++i){
        if ((c=getchar()) != '\n'){
            if (c != EOF){
                s[i] = c;
            }
            else
                break;
        }
        else
            break;     
    }
    // replacement ends here
    
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    
    s[i] = '\0';
            
        
    printf("%s",s);
    
    return 0;

}

