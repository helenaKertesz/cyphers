#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"enigma.h"
#include"rotors.h"

#define PRINTOUT 0
#define ALPHALEN 26

typedef struct stateRep {
    int numRotors;
    int * rotorSelection;
    char * rotorState;
    //int plugboard[2][26] = {{ 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 },
    //                        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}};
} state;

State setup( int argv, char * argc[]){

    if( !( (argv == 9 && atoi(argc[1]) == 3 ) || ( argv == 11 && atoi(argc[1]) == 4) ) ){
        printf("Usage: [num rotors (3 or 4)] [rotors to be used (1-8)] [reflector (a or b)] [initial rotor setting (A-Z)]\n");
        return NULL;
    }

    int i; //increment
    int n = 1;
    State new = malloc(sizeof( state ));
    new->numRotors = atoi( argc[n] );
    int * rotorSelection = malloc(sizeof(int) * ( new->numRotors + 1));
    char * rotorState = malloc(sizeof(char) * ( new->numRotors));
    n++;
    for(i = 0; i < new->numRotors; i++, n++){
        rotorSelection[i] = atoi( argc[n] );
    }
    rotorSelection[i] = 4 + toupper( *argc[n] ) - 'B' + (new->numRotors) * 2;
    n++;
    new->rotorSelection = rotorSelection;
    for(i = 0; i < new->numRotors; i++, n++){
        rotorState[i] = toupper(*argc[n]);
    }
    new->rotorState = rotorState;
    /*
    //plugboard
    if( PRINTOUT ) printf("Plugboard (y/n):");
    do
        scanf("%c", &ch);
    while( toupper(ch) != 'Y' &&  toupper(ch) != 'N' );
    */

    return new;
}


void showState( State s ){
    printf("\nUsing %d rotors\n", s->numRotors);
    int i;
    for(i = 0; i < numRot( s ); i++){
        printf("|%c", s->rotorState[i]);
    }
    printf("|\n\n");
}


char encode( char ch, State state ){

    step( state );

    int i;
    for( i = numRot( state ) - 1; i <= 0; i--){
        ch = encodeForwards( ch, state, i);
    }

    ch = reflect( ch, state );

    for( i = 0; i < numRot( state ); i++){
        ch = encodeBackwards( ch, state, i);
    }
    return ch;
}

int numRot( State state){
    return( state->numRotors );
}

void dropState( State state ){
    free( state->rotorSelection);
    free( state->rotorState);
    free( state );
}

char encodeForwards( char ch, State s, int rotor){
    //from last rotor

    if( rotor == s->numRotors) ch = (((ch + s->rotorState[rotor]) - 'A') % ALPHALEN ) + 'A';

    ch = ch; //s->rotorState[i] - 'A' something
    //wiring through rotor
    ch = rotors[ s->rotorSelection[rotor] ][ ch - 'A'];
    return ch;
}

char reflect( char ch, State s ){

    //from last rotor

    ch = rotors[ s->rotorSelection[numRot(s)] ][ ch - 'A' ];

    //to next rotor
    return ch;
}

char encodeBackwards( char  ch, State s, int rotor){

    //wiring through rotor
    ch = rotors[ s->rotorSelection[rotor] ][ ch - 'A'];

    //getting to next rotor
    ch = ch; //s->rotorState[i] - 'A' something

    return ch;
}

void step( State s ){
    int nR = s->numRotors;
    if( nR == 4 ){
        if( isTip( nR-3, s) &&  isTip( nR-2, s) &&  isTip( nR-1, s) ){
            rotate( nR-4, s);
            rotate( nR-3, s);
            rotate( nR-2, s);
            rotate( nR-1, s);
        }
    }
    if ( isTip( nR-2, s) &&  isTip( nR-1, s) ){
        rotate( nR-3, s);
        rotate( nR-2, s);
        rotate( nR-1, s);
    } else if( isTip( nR-1, s) ){
        rotate( nR-2, s);
        rotate( nR-1, s);
    } else {
        rotate( nR-1, s);
        printf("rotated %d\n", nR-1);
    }
}

int isTip( int rotor, State s)
{
    int state = 0;
    char pos = s->rotorState[rotor];
    if( (pos == rotors[rotor][26]) || (pos == rotors[rotor][27]) ) state = 1;
    return state;
}

void rotate( int rotor, State s){
    if(s->rotorState[rotor] == 'Z') s->rotorState[rotor] = 'A';
    else s->rotorState[rotor]++;
}
