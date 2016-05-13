
typedef struct stateRep * State;

State setup( int argv, char * argc[]);
char encode( char ch,  State state );
void showState( State s );
int numRot( State state);
void dropState( State state );
char encodeForwards( char  ch, State s, int rotor);
char reflect( char ch, State s );
char encodeBackwards( char  ch, State s, int rotor);
void step( State s );
void rotate( int rotor, State s);
int isTip( int rotor, State s);
