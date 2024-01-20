#include <stdio.h>

int main() {
	
	int day = 0;
	int count = 0;
	int i;
	for(i=10; count<=1000; i+=5) {
		count += i;
		day++;
	}
	
	printf("%d. day the book will be finished", day);
	
	return 0;
}