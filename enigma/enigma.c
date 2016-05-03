#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"enigma.h"
#include"rotors.h"

#define PRINTOUT 1

State setup( int argv, char * argc[]){

    State new = malloc(sizeof(State));
    //number of rotors
    if( PRINTOUT ) printf("Enter number of rotors (3 or 4):");
    do
        scanf("%d", &new->numRotors);
    while( new->numRotors  != 3 && new->numRotors != 4);

    //rotor choices
    int * rotorSelection = malloc(sizeof(int) * ( new->numRotors + 1));
    new->rotorSelection = rotorSelection;

    //rotor positions
    int * rotorState = malloc(sizeof(int) * ( new->numRotors + 1));
    new->rotorState = rotorState;

    //plugboard

    return new;
}

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
