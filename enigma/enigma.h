typedef struct stateRep {
    int numRotors;
    int * rotorSelection;
    int * rotorState;
    //int plugboard[2][26] = {{ 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 },
    //                        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}};
} * State;

State setup( int argv, char * argc[]);
char encode( char ch,  State state );
int numRot( State state);
void dropState( State state );
