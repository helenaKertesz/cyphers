#include<stdio.h>
#include<ctype.h>

#define GRAPHLEN 40;

int main (void){

	double freq[26] = {0};
	int ch;
    double graphLen = 40;

	while((ch = getchar()) != EOF){
		if(isalpha(ch)){
			freq[ (toupper(ch) - 65) ]++;
		}
	}

	int i = 0;
	char letter = 'a';
	double n;
	int most = 0;

	while( i < 26 ){
		if( freq[i] > freq[most]){
			most = i;
		}
		i++;
	}

	printf("most frequent letter is %c with %.0f occurances\n", 'a' + most, freq[most]);

	double increment = freq[most]/graphLen;

	printf("increment is %f\n", increment);

	i = 0;

	while( i < 26 ){
		printf("%c - %5.0f | ", letter, freq[i]);
		for(n = 0; n < freq[i] ; (n = n + increment)){
			printf("*");
		}
		printf("\n");
		letter++;
		i++;
	}

	return(0);
}
