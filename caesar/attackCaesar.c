#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define ALPHALEN 26

int main(){

    int freq[ALPHALEN] = {0};
    char ch;

    while((ch = getchar()) != EOF){
        if(isalpha(ch)){
            freq[ (toupper(ch) - 'A') ]++;
        }
    }

    int i;
    int most = 0;

    for( i = 0; i < ALPHALEN; i++){
        if( freq[i] > freq[most]){
            most = i;
        }
    }

    int rot = 'e' - 'a';
    rot  = (most - 4 + ALPHALEN) % ALPHALEN;

    printf("rot = %d\n", rot);

    return 0;

}
