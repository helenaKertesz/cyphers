#include<stdio.h>
#include<ctype.h>

int main (void){
	
	int freq[26] = {0};
	int ch;
	
	while((ch = getchar()) != EOF){
		if(isalpha(ch)){
			freq[ (toupper(ch) - 65) ]++;
			//printf("adding %c\n", ch);
		}
	}	
	
	int i = 0;
	char letter = 'a';
	int n;
	int most = 0;
	
	while( i < 26 ){
		if( freq[i] > freq[most]){
			most = i;
		}
		i++;
	}
	
	printf("most is %d at %d\n", most, freq[most]);
	
	double increment = freq[most]/40;
	
	printf("increment is %f\n", increment);
	
	i = 0;
	
	while( i < 26 ){
		printf("%c - %5d | ", letter, freq[i]);
		for(n = 0; n < freq[i] ; (n = n + increment)){
			printf("*");
		}
		printf("\n");
		letter++;
		i++;
	}
	
	return(0);
}
