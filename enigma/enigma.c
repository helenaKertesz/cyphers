#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include"enigma.h"
#include"rotors.h"

#define PRINTOUT 0

State setup( int argv, char * argc[]){
    printf("argv = %d ", argv);
/*
    //check for valid arguments
    if( argv < 9 || ( ( atoi(argc[1]) == 3 && argv != 9 ) || ( atoi(argc[1]) == 4 && argv != 11 ) ) ){
        printf("Invalid Settings");
    }
*/
    assert( argv == 9  && argc[1] == 3 || argv == 11 && argc[1] == 4);

    if( !(argv == 9 && argc[1] == 3 || argv == 11 && argc[1] == 4) ){
        printf("invalid settings");
        return 1;
    }

    int i; //increment
    int n = 1;

    State new = malloc(sizeof(State));
    int * rotorSelection = malloc(sizeof(int) * ( new->numRotors + 1));
    char * rotorState = malloc(sizeof(char) * ( new->numRotors));
    new->numRotors = atoi( argc[n] );
    n++;
    for(i = 0; i < new->numRotors; i++, n++){
        rotorSelection[i] = atoi( argc[n] );
    }
    rotorSelection[i] = 4 + toupper( *argc[n] ) - 'B' + (new->numRotors) * 2;
    for(i = 0; i < new->numRotors; i++, n++){
        rotorState[i] = *argc[n];
    }

    /*
    char ch;

    //number of rotors
    if( PRINTOUT ) printf("Enter number of rotors (3 or 4):");
    do
        scanf("%d", &new->numRotors);
    while( new->numRotors  != 3 && new->numRotors != 4);
    if( PRINTOUT ) printf("Number of rotors is %d\n", new->numRotors);

    //rotor choices
    int * rotorSelection = malloc(sizeof(int) * ( new->numRotors + 1));
    new->rotorSelection = rotorSelection;
    if( PRINTOUT ) printf("Enter rotor selection ( right to left )\n");
    for(i = 0; i < new->numRotors; i++){
        if( PRINTOUT ) printf("Rotor %d:", i + 1);
        do
            scanf("%d", &new->rotorSelection[i]);
        while( new->rotorSelection[i] <= 0 || new->rotorSelection[i] >= 9);
    }

    if( PRINTOUT ) printf("Reflector ( b or c ):");
    do
        scanf("%c", &ch);
    while( toupper(ch) != 'B' &&  toupper(ch) != 'C' );
    rotorSelection[i] = 4 + toupper(ch) - 'B' + (new->numRotors) * 2;

    //rotor positions
    char * rotorState = malloc(sizeof(char) * ( new->numRotors + 1));
    new->rotorState = rotorState;
    if( PRINTOUT ) printf("Enter rotor state ( right to left )\n");
    for(i = 0; i < new->numRotors; i++){
        if( PRINTOUT ) printf("Rotor %d:", i + 1);
        do {
            scanf("%c", &ch);
            new->rotorState[i] = toupper(ch);
        } while( new->rotorState[i]  < 'A' || new->rotorState[i] > 'Z');
    }

    //plugboard
    if( PRINTOUT ) printf("Plugboard (y/n):");
    do
        scanf("%c", &ch);
    while( toupper(ch) != 'Y' &&  toupper(ch) != 'N' );
    */

    return new;
}

/*
void showState( State s ){
    printf("Using %d rotorsi\n\n", s->numRotors);
    for(){
        printf("|%c");
    }
}
*/

char encode( char ch, State state ){
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
