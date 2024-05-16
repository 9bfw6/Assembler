#include "headers.h"



int IsAValidSymbol( char *TestSymbol ){  /* Validates that TestSymbol is a valid symbol */

	int Result = 1;
	int index =0;
	int maxlength = 6;
	int done;
	done = 0 ;
	bool constraintOne = (TestSymbol[0] >= 65);
	bool constraintTwo = (TestSymbol[0] <= 90);

	//Returns false if first character isn't alphabetical 
	if (!(constraintOne) || !(constraintTwo)) {
                Result = 0;
        }

	while( !done ) {
		if ( TestSymbol[index] == '\0' ) {
			break;
			}

		if ( index == maxlength ) {
			done = 1;
			Result = 0;
		}
		index++;

	}


	return Result;

}

bool InSymbolTable(char *symbol) {
	int i = 0;
	bool answer = false;

	while (Symbols[i] != NULL) {
		if (strcmp(Symbols[i]->Name, symbol) == 0) {
           		answer = true;
            		break; // Symbol found, no need to continue searching
        	}
		i++;
	}

	return answer;
}


void InsertSymbol( char Name[7], int SymbolAddress, int SourceLine ){  /* Inserts symbol into symbol table */

        int i =0;
        while( Symbols[i] != NULL ) { i++; }
        struct symbol *temp;

        temp = malloc( sizeof( struct symbol ));

        Symbols[i] = temp;

        temp->SourceLine = SourceLine;
        temp->SymbolAddress = SymbolAddress;
        strcpy( temp->Name               , Name      );

}

void PrintSymbolTable(){

        int i =0;
        while( Symbols[i] != NULL ) {
                printf("%s\t%x\t\n", Symbols[i]->Name, Symbols[i]->SymbolAddress);
                i++;
                }

}

int getSymbolAddress(char *symbol) {
	int i = 0;
	int symbolAddress = 0;
	while(Symbols[i] != NULL) {
		if(strcmp(Symbols[i]->Name, symbol) == 0) {
			symbolAddress = Symbols[i]->SymbolAddress;
			break;
		}
		i++;
	}
	return symbolAddress;
}


