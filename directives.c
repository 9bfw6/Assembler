#include "headers.h"

const int MAX_WORD_MEMORY = 8388607; //max value for a signed one word constant in hex 

int IsADirective( char *Test ){

return		( 	! ( 
		 strcmp( Test, "START" )  &&
		 strcmp( Test, "END" )   &&
		 strcmp( Test, "RESB" )  &&
		 strcmp( Test, "RESW" )  &&
		 strcmp( Test, "RESR" )  &&
		 strcmp( Test, "BYTE" )  &&
		 strcmp( Test, "WORD" )  &&
		 strcmp( Test, "EXPORTS" )   

		 ) ) ;
}

bool ValidHexNumber(char *value) {
	// Iterate through each character of the string
    	for (int i = 0; value[i] != '\0'; i++) {
        	if (!((value[i] >= '0' && value[i] <= '9') ||
              		(value[i] >= 'A' && value[i] <= 'F') ||
              		(value[i] >= 'a' && value[i] <= 'f'))) {
            	// return false if not hex
            	return false;
		}
    	}
    // All characters are valid hexadecimal digits
    return true;
}

int EndDirective(char *directive, char *operand, int lineNumber, char *line) {
	int returnAddress = 0;

	return returnAddress;
}

int ResbDirective(char *directive, char *operand, int lineNumber, char *line) {
	int returnAddress = atoi(operand);

	return returnAddress;
}

int ReswDirective(char *directive, char *operand, int lineNumber, char *line) {
	int operandAsInt = atoi(operand);
	int returnAddress = 3 * operandAsInt;

	return returnAddress;
}

int ResrDirective(char *directive, char *operand, int lineNumber, char *line) {
	int returnAddress = 3;

	return returnAddress;
}

int ByteDirective(char *directive, char *operand, int lineNumber, char *line) {
	int returnAddress = 0;
	char type[2];
	char *value;
	int numberOfHexChars = 0;
	int numberOfBytes = 0;


	// Extracting type
        *type = operand[0];
        type[1] = '\0';


        // Extracting value
        char *token = strtok(operand, "\'");
        token = strtok(NULL, "\'");
        if (token != NULL) {
            // Extracted value is the token after the opening quote
		//printf("%ld, %s\n", strlen(token), token);
            	value = (char*) malloc(strlen(token) + 2);
            	strcpy(value, token);
        }




	if (type[0] == 'X') {
		bool isHex = ValidHexNumber(value);
		if (isHex) {
			numberOfHexChars = strlen(value);
			numberOfBytes = (numberOfHexChars/2);
			returnAddress = numberOfBytes;
		}
		else {
			printf("ASSEMBLY ERROR:\n");
        		printf("%s\r\n", line);
			printf("On line %d, SIC Program contains an invalid hex constant\r\n", lineNumber);
			exit(EXIT_FAILURE);
		}
	}
	else if (type[0] == 'C') {
		int numberOfBytes = strlen(value);
		returnAddress = numberOfBytes;

	}

	return returnAddress;
}

int WordDirective(char *directive, char *operand, int lineNumber, char *line) {
	int returnAddress = 3;
	int integerConstant = atoi(operand);

	if (integerConstant <= MAX_WORD_MEMORY) {
	}
	else  {
		printf("ASSEMBLY ERROR:\n");
       	        printf("%s\r\n", line);
        	printf("On line %d, SIC Program contains a WORD Constant that Exceeds 24 bit limitation\r\n", lineNumber);
		exit(EXIT_FAILURE);
	}

	return returnAddress;
}

int ExportsDirective(char *directive, char *operand, int lineNumber, char *line) {
	int returnAddress = 3;

	return returnAddress;
}

int ApplyDirective(char *directive, char *operand, int lineNumber, char *line) {
	int returnAddress = 0;

	if (strcmp(directive, "END") == 0) {
		returnAddress = EndDirective(directive, operand, lineNumber, line);
	}
	else if (strcmp(directive, "RESB") == 0) {
		returnAddress = ResbDirective(directive, operand, lineNumber, line);
	}
	else if (strcmp(directive, "RESW") == 0) {
		returnAddress = ReswDirective(directive, operand, lineNumber, line);
	}
	else if (strcmp(directive, "RESR") == 0) {
		returnAddress = ResrDirective(directive, operand, lineNumber, line);
	}
	else if (strcmp(directive, "BYTE") == 0) {
		returnAddress = ByteDirective(directive, operand, lineNumber, line);
	}
	else if (strcmp(directive, "WORD") == 0) {
		returnAddress = WordDirective(directive, operand, lineNumber, line);
	}
	else if (strcmp(directive, "EXPORTS") == 0) {
		returnAddress = ExportsDirective(directive, operand, lineNumber, line);
	}

	return returnAddress;
}

char* convertToAscii(char* characterConstant) {
	int len = strlen(characterConstant); // Length of the input text
	char *hexOutput = (char*)malloc((len * 2) + 1); // Allocate enough memory
    	int offset = 0;

	for (int i = 0; i < len; i++) {
        	// Convert each character's ASCII value to hexadecimal and append to hexOutput
        	snprintf(&hexOutput[offset], 3, "%02X", (unsigned char)characterConstant[i]);
        	offset += 2; // Move the offset by 2 for the next hex representation
    	}

	// Null-terminate the output array
    	hexOutput[offset] = '\0';
	return hexOutput;
}

void ByteDirectivePassTwo(char *opcode, char *operand, int LocationCounter) {
        char type[2];
        char *value;
        int numberOfHexChars = 0;
        int numberOfBytes = 0;
	char textRecordStart = 'T';
	char textRecordLine[70];
	int hexValue = 0;


	// Extracting type
        *type = operand[0];
        type[1] = '\0';


        // Extracting value
        char *token = strtok(operand, "\'");
        token = strtok(NULL, "\'");
        if (token != NULL) {
            // Extracted value is the token after the opening quote
            value = (char*) malloc(strlen(token) + 1);
            strcpy(value, token);
        }

	if (type[0] == 'X') {
                bool isHex = ValidHexNumber(value);
                if (isHex) {
                        numberOfHexChars = strlen(value);
                        numberOfBytes = (numberOfHexChars/2);
			hexValue = (int)strtol(value, NULL, 16);
                }

		snprintf(
                textRecordLine,
                sizeof(textRecordLine),
                "%c%06X%02X%06X",
                textRecordStart,
                LocationCounter,
                numberOfBytes,
                hexValue
                );
                buildObjectFile(textRecordLine);
        }
	else if (type[0] == 'C') {
                numberOfBytes = strlen(value);
		char *asciiChars = convertToAscii(value);

		snprintf(
                textRecordLine,
                sizeof(textRecordLine),
                "%c%06X%02X%s",
                textRecordStart,
                LocationCounter,
                numberOfBytes,
                asciiChars
                );
                buildObjectFile(textRecordLine);

        }


}

void ApplyDirectivePassTwo(char *opcode, char *operand, int LocationCounter, char *line, int lineNumber) {
	char textRecordStart = 'T';
	int objectCodeLength = 0;
        char textRecordLine[70];
        int objectCode = 0;

	if(strcmp(opcode, "WORD") == 0) {
		objectCodeLength = 3;
		objectCode = atoi(operand);

		snprintf(
                textRecordLine,
                sizeof(textRecordLine),
                "%c%06X%02X%06X",
                textRecordStart,
                LocationCounter,
                objectCodeLength,
                objectCode
                );
		buildObjectFile(textRecordLine);
	}
	else if(strcmp(opcode, "BYTE") == 0) {
		ByteDirectivePassTwo(opcode, operand, LocationCounter);
	}
	else if(strcmp(opcode, "END") == 0) {
		if (InSymbolTable(operand)) {
			int startingAddress = getSymbolAddress(operand);
			addEndRecord(startingAddress);
		}
		else {
			printf("ASSEMBLY ERROR:\n");
                        printf("%s\r\n", line);
                        printf("On line %d, not a valid first instruction for END directive.\r\n", lineNumber);
                        exit(EXIT_FAILURE);
		}
	}

}
