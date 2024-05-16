#include "headers.h"


int IsAnInstruction( char *Test ){ /* Returns 1 if Test is an instruction, and 0 if not an instruction */

return		( 	! (
		 strcmp( Test, "ADD" )  &&
		 strcmp( Test, "AND" ) &&
		 strcmp( Test, "COMP" )  &&
		 strcmp( Test, "DIV" )  &&
		 strcmp( Test, "J" )  &&
		 strcmp( Test, "JEQ" )  &&
		 strcmp( Test, "JGT" )  &&
		 strcmp( Test, "JLT" )  &&
		 strcmp( Test, "JSUB" )  &&
		 strcmp( Test, "LDA" )  &&
		 strcmp( Test, "LDCH" )  &&
		 strcmp( Test, "LDL" )  &&
		 strcmp( Test, "LDX" )  &&
		 strcmp( Test, "MUL" )  &&
		 strcmp( Test, "OR" )  &&
		 strcmp( Test, "RD" )  &&
		 strcmp( Test, "RSUB" )  &&
		 strcmp( Test, "STA" )  &&
		 strcmp( Test, "STCH" )  &&
		 strcmp( Test, "STL" )  &&
		 strcmp( Test, "STSW" )  &&
		 strcmp( Test, "STX" )  &&
		 strcmp( Test, "SUB" )  &&
		 strcmp( Test, "TD" )  &&
		 strcmp( Test, "TIX" )  &&
		 strcmp( Test, "WD" )

		 ) ) ;
}

void InsertOpcode(char Name[7], int opcode) {
	int i = 0;
	while (Opcodes[i] != NULL) {
		i++;
	}
	struct opcode *temp;
	temp = malloc(sizeof(struct opcode));
	Opcodes[i] = temp;

	strcpy(temp->Name, Name);
	temp->OpCode = opcode;
}

bool InOpcodeTable(char *opcode) {
	int i = 0;
        bool answer = false;

        while (Opcodes[i] != NULL) {
                if (strcmp(Opcodes[i]->Name, opcode) == 0) {
                        answer = true;
                        break; // Opcode found
                }
                i++;
        }

	return answer;

}

void printOpcodeTable() {
	int i = 0;
	while(Opcodes[i] != NULL) {
		printf("%s\t%02x\t\n", Opcodes[i]->Name, Opcodes[i]->OpCode);
		i++;
	}
}

int getOpcode(char *opcode) {
	int i = 0;
	int opcodeValue = 0;
	while(Opcodes[i] != NULL) {
		if(strcmp(Opcodes[i]->Name, opcode) == 0) {
			opcodeValue = Opcodes[i]->OpCode;
			break;
		}
		i++;
	}
	return opcodeValue;
}

int ApplyInstruction(char *opcode, char *operand) {
	int returnAddress = 3;

	if (strcmp(opcode, "ADD") == 0) {
		const char *hexString = "18";
		int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
		if(!InOpcodeTable(opcode)) {
			InsertOpcode(opcode, code);
		}
	}
	else if (strcmp(opcode, "AND") == 0) {
		const char *hexString = "40";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "COMP") == 0) {
		const char *hexString = "28";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "DIV") == 0) {
		const char *hexString = "24";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "J") == 0) {
		const char *hexString = "3C";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "JEQ") == 0) {
		const char *hexString = "30";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "JGT") == 0) {
		const char *hexString = "34";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "JLT") == 0) {
		const char *hexString = "38";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "JSUB") == 0) {
		const char *hexString = "48";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "LDA") == 0) {
		const char *hexString = "00";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "LDCH") == 0) {
		const char *hexString = "50";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "LDL") == 0) {
		const char *hexString = "08";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "LDX") == 0) {
		const char *hexString = "04";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "MUL") == 0) {
		const char *hexString = "20";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "OR") == 0) {
		const char *hexString = "44";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "RD") == 0) {
		const char *hexString = "D8";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "RSUB") == 0) {
		const char *hexString = "4C";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "STA") == 0) {
		const char *hexString = "0C";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "STCH") == 0) {
		const char *hexString = "54";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "STL") == 0) {
		const char *hexString = "14";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "STSW") == 0) {
		const char *hexString = "E8";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "STX") == 0) {
		const char *hexString = "10";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "SUB") == 0) {
		const char *hexString = "1C";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "TD") == 0) {
		const char *hexString = "E0";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "TIX") == 0) {
		const char *hexString = "2C";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}
	else if (strcmp(opcode, "WD") == 0) {
		const char *hexString = "DC";
                int code = (int)strtol(hexString, NULL, 16); // Convert the string to an integer
                if(!InOpcodeTable(opcode)) {
                        InsertOpcode(opcode, code);
                }

	}

	return returnAddress;
}

void ApplyInstructionPassTwo(char *opcode, char *operand, int LocationCounter, int num_tokens, int lineNumber, char *line) {
	char textRecordStart = 'T';
	int opcodeValue = getOpcode(opcode);
	int objectCodeLength = 3;
	char textRecordLine[70];
	int symbolAddress = 0;


	if (num_tokens == 1) {
		snprintf(
                textRecordLine,
                sizeof(textRecordLine),
                "%c%06X%02X%02X%04X",
                textRecordStart,
                LocationCounter,
                objectCodeLength,
                opcodeValue,
                symbolAddress
                );

                buildObjectFile(textRecordLine);
	}
	else {
		if (strcmp(opcode, "LDCH") == 0) {
			char *token; // To store the tokenized strings
                	char symbol[10]; // To store the first part of operand
                	char x[10]; // To store the second part of operand

                	token = strtok(operand, ",");
                	strcpy(symbol, token);
                	token = strtok(NULL, ",");
                	strcpy(x, token);

			bool validArgument = InSymbolTable(symbol);

			if (validArgument) {
				int indexedAddressValue = getSymbolAddress(symbol) + 0x8000;

                        	snprintf(
                        	textRecordLine,
                        	sizeof(textRecordLine),
                        	"%c%06X%02X%02X%X",
                        	textRecordStart,
                        	LocationCounter,
                        	objectCodeLength,
                        	opcodeValue,
                        	indexedAddressValue
                        	);

                        	buildObjectFile(textRecordLine);

			}
			else {
				printf("ASSEMBLY ERROR:\n");
                                printf("%s\r\n", line);
                                printf("On line %d, SIC Program containts invalid operand\r\n", lineNumber);
                                exit(1);
			}

		}
		else if (strcmp(opcode, "STCH") == 0) {
			char *token; // To store the tokenized strings
    			char symbol[10]; // To store the first part of operand
    			char x[10]; // To store the second part of operand

			token = strtok(operand, ",");
    			strcpy(symbol, token);
    			token = strtok(NULL, ",");
    			strcpy(x, token);

			bool validArgument = InSymbolTable(symbol);

			if (validArgument) {
				int indexedAddressValue = getSymbolAddress(symbol) + 0x8000;

                        	snprintf(
                        	textRecordLine,
                        	sizeof(textRecordLine),
                        	"%c%06X%02X%02X%X",
                        	textRecordStart,
                        	LocationCounter,
                        	objectCodeLength,
                        	opcodeValue,
                        	indexedAddressValue
                        	);

                        	buildObjectFile(textRecordLine);

			}
			else {
				printf("ASSEMBLY ERROR:\n");
                                printf("%s\r\n", line);
                                printf("On line %d, SIC Program containts invalid operand\r\n", lineNumber);
                                exit(1);
			}
		}
		else {
			bool validArgument = InSymbolTable(operand);
			if (validArgument) {
				symbolAddress = getSymbolAddress(operand);
                        	snprintf(
                        	textRecordLine,
                        	sizeof(textRecordLine),
                        	"%c%06X%02X%02X%X",
                        	textRecordStart,
                        	LocationCounter,
                        	objectCodeLength,
                        	opcodeValue,
                        	symbolAddress
                        	);

                        	buildObjectFile(textRecordLine);

			}
			else {
				printf("ASSEMBLY ERROR:\n");
                        	printf("%s\r\n", line);
                        	printf("On line %d, SIC Program containts invalid operand\r\n", lineNumber);
                        	exit(1);

			}
		}
	}

}
