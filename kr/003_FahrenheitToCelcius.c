#include <stdio.h>
#include <stdlib.h>

#define LOW 0       // these are constants, not changeable
#define HIGH 300
#define CHANGE 20

int main(){
    short celc;
    celc = LOW;

    printf("Celcius\tFahrenheit\n");
    while (celc<=HIGH){
        printf("%d\t%.2f \n", celc, (celc-32)*(5.0/9));
        celc=celc+CHANGE;
    }
    celc = HIGH-CHANGE;
    while(celc>=LOW){
        printf("%d\t%.2f\n",celc,(celc-32)*(5/9.0));
        celc-=CHANGE;
    }
    return 0;
}
