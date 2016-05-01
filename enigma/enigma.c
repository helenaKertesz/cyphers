#include<stdio.h>

char encode( char ch, char R1, char R2, char R3, char R4, char reflec);

int main(){

	char ch;
	
	char R1, R2, R3, R4;
	
	char reflec;
	
	
	
	printf("Setting of rotor 1 (from left): ");
	while(isalpha(ch = getchar())){
		R1 = toupper( ch );
	}
	printf("Setting of rotor 2: ");
	while(isalpha(ch = getchar())){
		R2 = toupper( ch );
	}
	printf("Setting of rotor 3: ");
	while(isalpha(ch = getchar())){
		R3 = toupper( ch );
	}
	printf("Setting of rotor 4: ");
	while(isalpha(ch = getchar())){
		R4 = toupper( ch );
	}
	printf("Reflector (b or c): ");
	while((ch = toupper(getchar())) == 'C' || (ch  == 'D')){
		reflec = ch;
		printf("%c", ch);
	}
	
	printf("Enter phrase to be encoded letter by letter:\n");
	
	while((ch = getchar()) != EOF){
		if( ch != '\n' && isalpha(ch)){
			printf(" -> ");
			ch = encode(toupper( ch ), R1, R2, R3, R4, reflec);
			if(R4 == 'Z'){
				R4 = 'A';
			} else {
				R4++;
			}
			printf("%c\n", ch);
		}
	}
	
	return (0);
}

char encode( char ch, char R1, char R2, char R3, char R4, char reflec){
	
	int Rotor_I[26] = {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'};
	
	int Rotor_II[26] = {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H', 'W', 'T', 'M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'};
	
	int Rotor_III[26] = {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'};
	
	int Rotor_IV[26] = {'E', 'S', 'O', 'V', 'P', 'Z', 'J', 'A', 'Y', 'Q', 'U', 'I', 'R', 'H', 'X', 'L', 'N', 'F', 'T', 'G', 'K', 'D', 'C', 'M', 'W', 'B'};
	
	int Rotor_V[26] = {'V', 'Z', 'B', 'R', 'G', 'I', 'T', 'Y', 'U', 'P', 'S', 'D', 'N', 'H', 'L', 'X', 'A', 'W', 'M', 'J', 'Q', 'O', 'F', 'E', 'C', 'K'};
	
	int Rotor_VI[26] = {'J', 'P', 'G', 'V', 'O', 'U', 'M', 'F', 'Y', 'Q', 'B', 'E', 'N', 'H', 'Z', 'R', 'D', 'K', 'A', 'S', 'X', 'L', 'I', 'C', 'T', 'W'};
	
	int Rotor_VII[26] = {'N', 'Z', 'J', 'H', 'G', 'R', 'C', 'X', 'M', 'Y', 'S', 'W', 'B', 'O', 'U', 'F', 'A', 'I', 'V', 'L', 'P', 'E', 'K', 'Q', 'D', 'T'};
	
	int Rotor_VIII[26] = {'F', 'K', 'Q', 'H', 'T', 'L', 'X', 'O', 'C', 'B', 'J', 'S', 'P', 'D', 'Z', 'R', 'A', 'M', 'E', 'W', 'N', 'I', 'U', 'Y', 'G', 'V'};
	
	int Rotor_Beta[26] = {'L', 'E', 'Y', 'J', 'V', 'C', 'N', 'I', 'X', 'W', 'P', 'B', 'Q', 'M', 'D', 'R', 'T', 'A', 'K', 'Z', 'G', 'F', 'U', 'H', 'O', 'S'};
	
	int Rotor_Gamma[26] = {'F', 'S', 'O', 'K', 'A', 'N', 'U', 'E', 'R', 'H', 'M', 'B', 'T', 'I', 'Y', 'C', 'W', 'L', 'Q', 'P', 'Z', 'X', 'V', 'G', 'J', 'D'};
	
	int reflec_b[26] = {'E', 'N', 'K', 'Q', 'A', 'U', 'Y', 'W', 'J', 'I', 'C', 'O', 'P', 'B', 'L', 'M', 'D', 'X', 'Z', 'V', 'F', 'T', 'H', 'R', 'G', 'S'};
	
	int reflec_c[26] = {'R', 'D', 'O', 'B', 'J', 'N', 'T', 'K', 'V', 'E', 'H', 'M', 'L', 'F', 'C', 'W', 'Z', 'A', 'X', 'G', 'Y', 'I', 'P', 'S', 'U', 'Q'};
	
	int n;
	
	//from stationary to rotor 4
	n = R4 - 'A';
	
	if( (ch + n) <= 'Z'){
		ch = ch + n;
	} else {
		ch = ch - ( 26 - n);
	}
	
	printf("%c ->", ch);
	
	//rotor 4 wiring
	ch = Rotor_IV[ ch - 'A' ];
	
	printf("%c ->", ch);
	
	//from r4 to r3
	if((n = R4 - R3) >= 0){
		if( (ch + n) <= 'Z'){
			ch = ch + n;
		} else {
			ch = ch - ( 26 - n);
		}
	} else {
		n = R3 - R4;
		if( (ch + n) <= 'Z'){
			ch = ch + n;
		} else {
			ch = ch - ( 26 - n);
		}
	}
	
	printf("%c ->", ch);
	
	//r3 wiring
	ch = Rotor_III[ ch - 'A' ];
	
	printf("%c ->", ch);
	
	//from r3 to r2
	if((n = R2 - R3) >= 0){
		if( (ch + n) <= 'Z'){
			ch = ch + n;
		} else {
			ch = ch - ( 26 - n);
		}
	} else {
		n = R3 - R2;
		if( (ch + n) <= 'Z'){
			ch = ch + n;
		} else {
			ch = ch - ( 26 - n);
		}
	}
	
	printf("%c ->", ch);
	
	//r2 wiring
	ch = Rotor_II[ ch - 'A' ];
	
	printf("%c ->", ch);
	
	//from r2 to r1
	if((n = R1 - R2) >= 0){
		if( (ch + n) <= 'Z'){
			ch = ch + n;
		} else {
			ch = ch - ( 26 - n);
		}
	} else {
		n = R2 - R1;
		if( (ch + n) <= 'Z'){
			ch = ch + n;
		} else {
			ch = ch - ( 26 - n);
		}
	}
	
	printf("%c noot ->", ch);
	
	//r1 wiring
	ch = Rotor_I[ ch - 'A' ];
	
	printf("%c ->", ch);
	
	//from r1 to reflector
	n = R1 - 'A';
	
	if( (ch + (26-n)) <= 'Z'){
		ch = ch + n;
	} else {
		ch = ch - n;
	}
	
	printf("%c ->", ch);
	
	//reflector wiring
	
	ch = Rotor_I[ ch - 'A' ];
	
	printf("%c ->", ch);
	
	//from r1 to reflector
	
	
	//r1 wiring
	
	
	//from r1 to r2
	
	
	//r2 wiring
	
	
	//from r2 to r3
	
	
	//r3 wiring
	
	
	//from r3 to r4
	
	
	// r4 wiring
	
	//from r4 to stationary
	
	//plugboard
	
	
	return ( ch );
	
}
