#include <stdio.h>

int main() {
	
	float weight = 100.0;
	float height = 20.0;
	int months = 0;
	
	int i;
	while(weight < 150.0 || height < 30.0) {
		
		weight = weight * 1.10;
		height = height * 1.05; 
		
		months++;
	}	
	
	printf("After %d months,\n" , months);
	printf("Height: %.2f cm\n", height);
    printf("Weight: %.2f kg\n", weight);
	
	return 0;
}