#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include"enigma.h"

#define ALPHALEN    26
#define RED         "\x1b[31m"
#define BLUE        "\x1b[32m"
#define GREEN       "\x1b[34m"
#define RESET       "\x1b[0m"

int main(int argv, char * argc[]){

    State rotorSet = setup( argv, argc );
    assert( rotorSet != NULL );
    showState( rotorSet );

    char ch;
    while( (ch = getchar()) != EOF ){
        if( isalpha(ch) ){
            ch = encode( toupper(ch), rotorSet );
            showState( rotorSet );
        }
        printf("%c\n", ch);
    }

    dropState( rotorSet );

    return 0;
}
