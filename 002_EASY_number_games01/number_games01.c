#include <stdio.h>

int main(){
	
	int i;
	int a,b,c;
	int count = 0;
	/*
        a = hundreds digit
        b = tens digit
        c = ones digit
    */

	for(i=102; i<1000; i++) {
		a = i / 100;
		b = (i/10)%10;
		c = i % 10;
		if ( a != b && a != c && b!=c) {
			printf("%d - " , i);
			count++;
		}
	}
	
	printf("\n\nTotal Number : %d" , count);
	
	return 0;
}