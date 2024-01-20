#include <stdio.h>

int main() {

    int num;
    printf("Enter Number : ");
    scanf("%d", &num);

    int i=0;
    int count = 0;
    for(i=1; i<num; i++){
        if( num % i == 0) {
            count += i;
        }
    }

    if( count == num ) {
        printf("Perfect Number\n");
    } else {
        printf("Not Perfect Number\n");
    }


    return 0;
}