#include <stdio.h>

int main() {
	
	int money;
	printf("Please enter the amount of money: ");
	scanf("%d" , &money);

	int hundred = money / 100;
	money = money - (hundred*100);
	
	int fifty 	= money / 50;
	money = money - (fifty*50);
	
	int twenty  = money / 20;
	money = money - (twenty*20);
	
	int tenner  = money / 10;
	
	if( money % 10 == 0 ) {
		printf("\n\n%d pieces 100TL" , hundred);	
		printf("\n%d pieces 50TL" , fifty);	
		printf("\n%d pieces 20TL" , twenty);	
		printf("\n%d pieces 10TL" , tenner);
	} else {
		printf("\n\nThe smallest 10 TL note is available..!");	
	}

	
	return 0;
}
