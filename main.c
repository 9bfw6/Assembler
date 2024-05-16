#include "headers.h"

// Method that trims whitespace characters from the end of a string
void rtrim(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        str[--len] = '\0';
    }
}

int main( int argc, char* argv[]){

	FILE *fp;
	char objectFileExtension[] = ".obj";
	char line[1024];
	char fullline[1024];
	int LocationCounter = 0;
	int CurrentSourceLine = 0;
	const int MAX_MEMORY = 0x8000;
	char programName[7];
	int firstAddress = 0;
	int programLength = 0;
	int pass1Only = 0;  // Flag to determine if only pass 1 should be executed
	bool firstLine = true;

	if ( argc < 2 ) {
	printf("ERROR: Usage: %s filename\n", argv[0]);
	return 0;
	}

	// Determine if '--pass1only' was passed
    	if (argc == 3 && strcmp(argv[1], "--pass1only") == 0) {
        	pass1Only = 1;
        	argv[1] = argv[2];  // Shift the filename to the correct position
    	}


	fp = fopen( argv[1], "r");

	if ( fp == NULL ) {
	printf("ERROR: %s could not be opened for reading,\n", argv[1] );
	return 0;
	}

	//Create character array holding object file name
	size_t baseLength = strlen(argv[1]);
	size_t extensionLength = strlen(objectFileExtension);
	char objectFileName[baseLength + extensionLength + 1];
	snprintf(objectFileName, sizeof(objectFileName), "%s%s", argv[1], objectFileExtension);


	while(  (fgets( line , 1024 , fp ) != NULL) && (LocationCounter < MAX_MEMORY)   ) {
		strcpy(fullline, line);
		CurrentSourceLine++;
		char *token1 = NULL;
                char *token2 = NULL;
                char *token3 = NULL;

		if (line[0] == 35) {
			printf("COMMENT:%s", line);

			continue;
		}
		if (line[0] == '\n' || line[0] == '\r') {
			printf("ASSEMBLY ERROR:\n");
        		printf("%s\r\n", fullline);
			printf("On line %d, SIC Program contains a blank line\r\n", CurrentSourceLine);
        		return(0);
        	}
		// Trim trailing whitespace characters
    		rtrim(line);


		//Tokenize the line
		int num_tokens = 0; /* variable to keep track of each token */
		for (char *p = strtok(line, " \t "); p != NULL; p = strtok(NULL, "\t " )) {
			if (num_tokens == 0) {
				token1 = (char*) malloc(strlen(p) + 1);
				if (token1 == NULL) {
					printf("Error with allocating memory with the first token");
					return(0);
				}
				else {
					strcpy(token1, p);
					num_tokens++;
				}
			}
			else if (num_tokens == 1) {
				token2 = (char*) malloc(strlen(p) + 1);
				if (token2 == NULL) {
                                        printf("Error with allocating memory with the second token");
					return(0);
                                }
				else {
                                	strcpy(token2, p);
					num_tokens++;
				}
			}
			else if (num_tokens == 2){
				token3 = (char*) malloc(strlen(p) + 1);
                                if (token3 == NULL) {
                                        printf("Error with allocating memory with the third token");
					return(0);
                                }
				else {
                                	strcpy(token3, p);
					num_tokens++;
				}

				p = strtok(NULL, " \t");
                                while (p != NULL) {
                                        token3 = realloc(token3, strlen(token3) + strlen(p) + 1);
                                        strcat(token3, " ");
                                        strcat(token3, p);
                                        p = strtok(NULL, " \t");
                                }

			}

        	}

		//if there is a symbol
		if (num_tokens == 3) {

			//If the the first line is being read
			if (firstLine) {
				if (strcmp(token2, "START") == 0) {
					strcpy(programName, token1);
					firstAddress = (int)strtol(token3, NULL, 16);
					if (firstAddress >= MAX_MEMORY) {
						printf("ASSEMBLY ERROR:\n");
                        			printf("%s\r\n", fullline);
                        			printf("On line %d, SIC Program starts at hex %X. No room left in SIC memory\r\n", CurrentSourceLine, firstAddress);
						return(0);
					}
					LocationCounter = firstAddress;
                                	//Insert this symbol into the symbol table
					if (IsAValidSymbol(token1) == 1) {
						InsertSymbol( token1, LocationCounter, CurrentSourceLine );
						//Build assembly file for pass two
                        			buildAssemblyFile(CurrentSourceLine, num_tokens, token1, token2, token3, LocationCounter);
					}
					else {
						printf("ASSEMBLY ERROR:\n");
                        			printf("%s\r\n", fullline);
                        			printf("On line %d, SIC Program contains an invalid Symbol\r\n", CurrentSourceLine);
                        			return(0);
					}
					firstLine = false;
                                }
				else {
					printf("ASSEMBLY ERROR:\n");
					printf("%s\r\n", fullline);
					printf("On line %d, SIC Program missing START directive\r\n", CurrentSourceLine);
					return(0);
				}

			}
			//Insert symbol into symbol table
			else {
				if((IsAValidSymbol(token1) == 1) && (IsADirective(token1) == 0) && !(InSymbolTable(token1))) {
                                        InsertSymbol(token1, LocationCounter, CurrentSourceLine);

					//Build assembly file for pass two
                        		buildAssemblyFile(CurrentSourceLine, num_tokens, token1, token2, token3, LocationCounter);
                                }
				else {
					if (IsADirective(token1) == 1) {
						printf("ASSEMBLY ERROR:\n");
                        			printf("%s\r\n", fullline);
                        			printf("On line %d, SIC Program contains a Symbol that is a directive\r\n", CurrentSourceLine);
						return(0);
					}
					else if (InSymbolTable(token1)) {
						printf("ASSEMBLY ERROR:\n");
                        			printf("%s\r\n", fullline);
                        			printf("On line %d, SIC Program contains a Symbol that is already defined\r\n", CurrentSourceLine);
                        			return(0);
					}
					printf("ASSEMBLY ERROR:\n");
                        		printf("%s\r\n", fullline);
                        		printf("On line %d, SIC Program contains an invalid Symbol\r\n", CurrentSourceLine);
                                        return(0);
				}


				if (IsADirective(token2) == 1) {
					LocationCounter = LocationCounter + ApplyDirective(token2, token3, CurrentSourceLine, fullline);
				}
				else if (IsAnInstruction(token2) == 1) {
					LocationCounter = LocationCounter + ApplyInstruction(token2, token3);
				}
				else {
					printf("Not a valid directive nor instruction on line %d", CurrentSourceLine);
					return(0);
				}

			}
		}
		//if there is only an instruction/directive and operand
		else if (num_tokens == 2) {
			//Build assembly file for pass two
                        buildAssemblyFile(CurrentSourceLine, num_tokens, token3, token1, token2, LocationCounter);

			if (IsADirective(token1) == 1) {
                                LocationCounter = LocationCounter + ApplyDirective(token1, token2, CurrentSourceLine, fullline);
                        }
			else if (IsAnInstruction(token1) == 1) {
				LocationCounter = LocationCounter + ApplyInstruction(token1, token2);
			}
			else {
                              	printf("Not a valid directive nor instruction on line %d\n", CurrentSourceLine);
				return(0);
                        }

		}
		//if there is only an instruction
		else if (num_tokens == 1) {
			//Build assembly file for pass two
                        buildAssemblyFile(CurrentSourceLine, num_tokens, token2, token1, token3, LocationCounter);

			if (IsAnInstruction(token1) == 1) {
				LocationCounter = LocationCounter + ApplyInstruction(token1, token2);
			}
			else {
				printf("Not a valid instruction on line %d", CurrentSourceLine);
				return(0);
			}
		}
		free(token1);
		free(token2);
		free(token3);
		token1 = token2 = token3 = NULL;
   		num_tokens = 0;



	} /* End of while loop */




	fclose( fp );

	if (LocationCounter < MAX_MEMORY) {
		if (pass1Only == 1) {
			PrintSymbolTable();
                	return(0);
		}
	}
	else {
		printf("ASSEMBLY ERROR:\n");
        	printf("%s\r\n", fullline);
		printf("On line %d, SIC Program does not fit in SIC memeory\r\n", CurrentSourceLine);
		exit(1);
	}

	//start pass two
	programLength = LocationCounter - firstAddress;
	makeHeaderRecord(programName, firstAddress, programLength);
	makeTextRecord();
	makeModificationRecord();
	makeEndRecord();

	//If there are no problems with assembly, output the object file
	outputObjectFile(objectFileName);


}
