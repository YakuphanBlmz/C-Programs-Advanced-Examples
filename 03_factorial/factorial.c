#include <stdio.h>

int main() {
	
	int num;
	printf("Enter Number: ");
	scanf("%d" , &num);
	
	int i;
	int factorial = 1;
	for(i=num; i>=1; i--){
		factorial *= i;
	}
	
	printf("Factorial: %d\n", factorial);

    return 0;
}