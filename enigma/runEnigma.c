#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"enigma.h"

#define ALPHALEN    26
#define RED         "\x1b[31m"
#define BLUE        "\x1b[32m"
#define GREEN       "\x1b[34m"
#define RESET       "\x1b[0m"

int main(int argv, char * argc[]){

    State rotorSet = setup( argv, argc );

    char ch;
    while( (ch = getchar()) != EOF ){
        if( isalpha(ch) )
            ch = encode( ch, rotorSet );
        printf("%c", ch);
    }

    dropState( rotorSet );

    return 0;
}
