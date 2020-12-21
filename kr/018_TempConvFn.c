#include <stdio.h>
#include <stdlib.h>

#define LOW 0       // these are constants, not changeable
#define HIGH 300
#define CHANGE 20

int main(){
    short celc;

    float Celc_to_Fahr(int ce);

    celc = LOW;
    printf("Celcius\tFahrenheit\n");
    while (celc<=HIGH){
        printf("%d\t%.2f \n", celc, Celc_to_Fahr(celc));
        celc = celc + CHANGE;
    }
    celc = HIGH-CHANGE;
    while(celc>=LOW){
        printf("%d\t%.2f\n",celc,(celc-32)*(5/9.0));
        celc-=CHANGE;
    }
    return 0;
}

float Celc_to_Fahr(int celcius)
{
    return (celcius-32)*(5/9.0);
}

