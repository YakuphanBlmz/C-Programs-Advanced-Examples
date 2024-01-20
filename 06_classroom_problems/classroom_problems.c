#include <stdio.h>
#define MAX 20

int main() {
	
	int arr[MAX];
	int i;
	int sum = 0;
	
	for(i=0; i<MAX; i++) {
		printf("Enter %d grade : " , i+1 );
		scanf("%d" , &arr[i]);
		sum += arr[i];
	}
	
	float avg = (float)sum / MAX;
	
	int max = arr[0];
	int min = arr[0];
	for(i=0; i<MAX; i++) {
		if( arr[i] > max ) {
			max = arr[i];
		}
		if( arr[i] < min ) {
			min = arr[i];
		}
	}
	
	printf("\n\nAverage Grade  : %.2f" , avg);
	printf("\nMaximum  Grade : %d" , max);
	printf("\nMinimum Grade  : %d" , min);
	
	return 0;
}