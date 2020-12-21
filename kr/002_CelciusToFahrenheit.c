// This code changes Celcius degrees (0 to 300, by 20) to Fahreheits

#include <stdio.h>
#include <stdlib.h>



int main(){
    int low, high, change, i;
    low = 0;
    high = 300;
    change = 20;

    for (i = low; i <= high; i += change){
        printf("%d %d \n", i, (9.0/5)*i+32);
    }
    return 0;
}
