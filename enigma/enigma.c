#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"enigma.h"
#include"rotors.h"

#define PRINTOUT 0
#define ALPHALEN 26
#define PRINT    1

typedef struct stateRep {
    int numRotors;
    int * rotorSelection;
    char * rotorState;
    //int plugboard[2][26] = {{ 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 },
    //                        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}};
} state;


//initialised the rotor selection and initala positions and returns a struct contaiing the information
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
    //plugboard TODO
    if( PRINTOUT ) printf("Plugboard (y/n):");
    do
        scanf("%c", &ch);
    while( toupper(ch) != 'Y' &&  toupper(ch) != 'N' );
    */

    return new;
}


//Prints out the state of the rotors
void showState( State s )
{
    printf("\nUsing %d rotors\n\n   ", s->numRotors);
    int i;
    for(i = 0; i < numRot( s ); i++){
        rotorName( s, s->rotorSelection[i]);
    }
    printf("\n   ");
    for(i = 0; i < numRot( s ); i++){
        printf("+---");
    }
    printf("+\n");
    int reflec = s->rotorSelection[numRot(s)];
    if( reflec == 12 || reflec == 10){
        printf(" b ");
    } else {
        printf(" c ");
    }
    for(i = 0; i < numRot( s ); i++){
        printf("| %c ", s->rotorState[i]);
    }
    printf("|\n   ");
    for(i = 0; i < numRot( s ); i++){
        printf("+---");
    }
    printf("+\n\n");
}


//overall function for encoding a single character
char encode( char ch, State state )
{
    step( state );

    int i;
    for( i = numRot( state ) - 1; i >= 0; i--){
        ch = encodeForwards( ch, state, i);
    }

    ch = reflect( ch, state );

    for( i = 0; i < numRot( state ); i++){
        ch = encodeBackwards( ch, state, i);
    }
    return ch;
}


//encoding forward to reflector
char encodeForwards( char ch, State s, int rotor)
{
    //from last rotor
    if( rotor == s->numRotors-1) ch = (((ch + (s->rotorState[rotor] - 'A')) - 'A' ) % ALPHALEN ) +'A';
    else ch = (((ch + (s->rotorState[rotor] - s->rotorState[rotor+1]) + 'A' )) % ALPHALEN ) +'A';
//    printf("\n[%c %c] %d \n", s->rotorState[rotor+1], s->rotorState[rotor], s->rotorState[rotor+1] - s->rotorState[rotor]);
    if( PRINT) printf("->%c", ch);
    //wiring through rotor
    ch = rotors[ s->rotorSelection[rotor]-1 ][ ch - 'A'];
    if( PRINT) printf("->*(%d)%c",rotor, ch);
    return ch;
}


//encoding through the reflector
char reflect( char ch, State s )
{
    //from last rotor
    //
    ch = (((ch + (s->rotorState[0] - 'A')) - 'A' ) % ALPHALEN ) +'A';//CHECK!!!
    if( PRINT) printf("->%c", ch);
    //Through reflector
    ch = rotors[ s->rotorSelection[numRot(s)] ][ ch - 'A' ];
    if( PRINT) printf("->||*%c||", ch);
    //to next rotor
    ch = (abs(ch - s->rotorState[0] ) % ALPHALEN ) +'A';//CHECK!!!
    if( PRINT) printf("->%c", ch);
    return ch;
}


//encoding back from the reflector
char encodeBackwards( char  ch, State s, int rotor)
{
    //wiring through rotor
    int i;
    for(i = 0; i < ALPHALEN; i++){
        if( ch == rotors[rotor][i]){
            ch = i + 'A';
            break;
        }
    }
    if( PRINT) printf("->*(%d)%c",rotor, ch);
    //getting to next rotor
    if( rotor == s->numRotors-1) ch = (((ch - (s->rotorState[rotor] - 'A')) + 'A' ) % ALPHALEN ) +'A';
    else ch = (((ch + (s->rotorState[rotor+1] - s->rotorState[rotor])) + 'A' ) % ALPHALEN ) +'A';
    if( PRINT) printf("->%c", ch);

    return ch;
}


//rototes the rotors
void step( State s )
{
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
    }
}


//returns 1 if the rotor will catch the next rotor when it next rotates
//and 0 otherwise
int isTip( int rotor, State s)
{
    int state = 0;
    char pos = s->rotorState[rotor];
    if( (pos == rotors[rotor][26]) || (pos == rotors[rotor][27]) ) state = 1;
    return state;
}


//rotates the rotors by updating the rotor state
void rotate( int rotor, State s){
    if(s->rotorState[rotor] == 'Z') s->rotorState[rotor] = 'A';
    else s->rotorState[rotor]++;
}


//returns the number of rotors in use
int numRot( State state)
{
    return( state->numRotors );
}


//free memory associated with state
void dropState( State state )
{
    free( state->rotorSelection);
    free( state->rotorState);
    free( state );
}

void rotorName( State s, int rotor)
{
   /* switch (rotor){
      case 0:
      printf("  I ");
      break;
case: 1;
      printf(" II ");
      break;
case: 2;
      printf(" III");
      break;
case: 3;
      printf(" IV ");
      break;
case: 4;
      printf("  V ");
      break;
case: 5;
      printf(" VI ");
      break;
case: 6;
      printf(" VII");
      break;
case: 7;
      printf("VIII");
      break;
    }*/
    if( rotor == 1){
        printf("  I ");
    } else if( rotor == 2 ){
        printf(" II ");
    } else if( rotor == 3 ){
        printf(" III");
    } else if( rotor == 4 ){
        printf(" IV ");
    } else if( rotor == 5 ){
        printf("  V ");
    } else if( rotor == 6 ){
        printf(" VI ");
    } else if( rotor == 7 ){
        printf(" VII");
    } else if( rotor == 8 ){
        printf("VIII");
    }
}
