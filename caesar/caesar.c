#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define ALPHALEN 26

char encode( char ch, int rot);
char decode( char ch, int rot);


int main( int argc, char * argv[] ){

    if( argc != 3 ){
        printf("USAGE: ./caesar [encode or decode (E  or D) ] [rotation ( between 0 and 26) ]\n"); //TODO look up automatic error messages
        return 0;
    }

    int rot = atoi(argv[2]);
    char ch;

    while( (ch = getchar()) != EOF ){
        if( isalpha(ch)){

            if( *argv[1] == 'E' ){
                ch  = encode(ch, rot);
            } else if( *argv[1] == 'D' ){
                ch = decode(ch, rot);
            }

        }

        printf("%c", ch);
    }

    return 0;

}

//encodes a character given a rotation
char encode( char ch, int rot){

    if( isupper(ch) ){
        ch = (((ch - 'A') + rot) % ALPHALEN) + 'A';
    } else {
        ch = (((ch - 'a') + rot) % ALPHALEN) + 'a';
    }

    return ch;
}

//decodes a character given a rotation
char decode( char ch, int rot){

    if( isupper(ch) ){
        ch = ((ch - rot) % 'A') + 'A';
    } else {
        ch = ((ch - rot) % 'a') + 'a';
    }

    return ch;
}
