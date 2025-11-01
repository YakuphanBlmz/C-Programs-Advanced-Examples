#include <stdio.h>

int main() {
	
	int i;
	int oddCount = 0;
	printf("Odd Numbers\n");
	for(i=1; i<=100; i+=2) {
		printf("%d  " , i );
		oddCount++;
	}
	printf("\nTotal Odd Numbers : %d" , oddCount);
	
	
	int evenCount = 0;
	printf("\n\n\nEven Numbers\n");
	for(i=0; i<=100; i+=2) {
		printf("%d  " , i );
		evenCount++;
	}
	printf("\nTotal Even Numbers : %d" , evenCount);
	
	return 0;
}