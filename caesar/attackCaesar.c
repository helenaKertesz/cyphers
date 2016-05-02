#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define ALPHALEN

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

    for( i = 0; i < 26; i++){
        if( freq[i] > freq[most]){
            most = i;
        }
    }

    int rot = 'e' - 'a';
    printf("rot = %d (4)\n", rot);
    printf("most = %d\n", most);

    return 0;

}
