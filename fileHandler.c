#include "headers.h"

void buildAssemblyFile(int lineNumber, int numberOfTokens, char *label, char *opcode, char *operand, int LocationCounter) {
	int i = 0;
	while(AssemblyProgram[i] != NULL) {
		i++;
	}
	struct assemblyLine *temp;
	temp = malloc(sizeof(struct assemblyLine));

	AssemblyProgram[i] = temp;

	if(numberOfTokens == 3) {
        	temp->lineNumber = lineNumber;
       		temp->numberOfTokens = numberOfTokens;

		temp->label = malloc(strlen(label) + 1);
		temp->opcode = malloc(strlen(opcode) + 1);
		temp->operand = malloc(strlen(operand) + 1);

		strcpy(temp->label, label);
		strcpy(temp->opcode, opcode);
		strcpy(temp->operand, operand);

		temp->LocationCounter = LocationCounter;
        }
	else if(numberOfTokens == 2) {
                temp->lineNumber = lineNumber;
        	temp->numberOfTokens = numberOfTokens;

		temp->opcode = malloc(strlen(opcode) + 1);
                temp->operand = malloc(strlen(operand) + 1);

		strcpy(temp->opcode, opcode);
                strcpy(temp->operand, operand);

		temp->LocationCounter = LocationCounter;
        }
	else if(numberOfTokens == 1) {
                temp->lineNumber = lineNumber;
        	temp->numberOfTokens = numberOfTokens;

		temp->opcode = malloc(strlen(opcode) + 1);
		strcpy(temp->opcode, opcode);

		temp->LocationCounter = LocationCounter;
        }


}

void makeHeaderRecord(char *programName, int startingAddress, int programLength) {
	char header[20]; //19 character plus null pointer
	char headerStart = 'H';
	// Format the header record using snprintf
    	snprintf(
        header,
        sizeof(header),
        "%c%-6s%06X%06X",  // Left-justify program name, and zero-pad addresses
	headerStart,     //H
        programName,     // Program name, left-justified
        startingAddress, // Starting address in hexadecimal, zero-padded to 6 digits
        programLength    // Program length in hexadecimal, zero-padded to 6 digits
    	);
	buildObjectFile(header); //adds header to object file
}


void makeTextRecord() {
	int i = 1;
	while(AssemblyProgram[i] != NULL) {
		if(AssemblyProgram[i]->numberOfTokens == 3) {
			char line[40];
			snprintf(line, sizeof(line), "%s\t%s\t%s\n", AssemblyProgram[i]->label, AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand);
			//opcode is an instruction
			if(IsAnInstruction(AssemblyProgram[i]->opcode) == 1) {
				//printf("%s\t%s\t%X\n", AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand, AssemblyProgram[i]->LocationCounter);
				ApplyInstructionPassTwo(AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand, AssemblyProgram[i]->LocationCounter, AssemblyProgram[i]->numberOfTokens, AssemblyProgram[i]->lineNumber, line);
				applyModification(AssemblyProgram[i]->LocationCounter, AssemblyProgram[0]->label);
			}
			//opcode is directive
			else {
				ApplyDirectivePassTwo(AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand, AssemblyProgram[i]->LocationCounter, line, AssemblyProgram[i]->lineNumber);
			}
		}
		else if(AssemblyProgram[i]->numberOfTokens == 2) {
			char line[40];
			snprintf(line, sizeof(line), "%s\t%s\t%s\n", AssemblyProgram[i]->label, AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand);
			//opcode is an instruction
                        ApplyInstructionPassTwo(AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand, AssemblyProgram[i]->LocationCounter, AssemblyProgram[i]->numberOfTokens, AssemblyProgram[i]->lineNumber, line);
			applyModification(AssemblyProgram[i]->LocationCounter, AssemblyProgram[0]->label);

		}
		else if(AssemblyProgram[i]->numberOfTokens == 1) {
			char line[40];
                        snprintf(line, sizeof(line), "%s\t%s\t%s\n", AssemblyProgram[i]->label, AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand);
			//opcode is instruction
			ApplyInstructionPassTwo(AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand, AssemblyProgram[i]->LocationCounter, AssemblyProgram[i]->numberOfTokens, AssemblyProgram[i]->lineNumber, line);
		}

		i++;
	}
}

void addEndRecord(int startingAddress) {
	char ending = 'E';
        char endingRecord[12];

        snprintf(
        endingRecord,
        sizeof(endingRecord),
        "%c%06X",
        ending,
        startingAddress
        );

        buildEndRecord(endingRecord); //adds ending record to end record list



}

void buildEndRecord(char *endRecord) {
	int i = 0;
	while(EndingRecord[i] != NULL) {
		i++;
	}

	struct endingRecordLine *temp;
        temp = malloc(sizeof(struct endingRecordLine));
        EndingRecord[i] = temp;
        strcpy(temp->line, endRecord);

}

void makeEndRecord() {
	int i = 0;
        while(EndingRecord[i] != NULL) {
                char *line  = malloc(sizeof(struct endingRecordLine));
                strcpy(line, EndingRecord[i]->line);
                buildObjectFile(line);
                i++;
        }


}

void applyModification(int LocationCounter, char *programName) {
	char modificationCharacter = 'M';
	char modificationRecord[18];
	int startingModifiedAddress = LocationCounter + 0x1;
	int numberOfHalfBytes = 0x4;
	char displacementSign = '+';

	snprintf(
        modificationRecord,
        sizeof(modificationRecord),
        "%c%06X%02X%c%s",
        modificationCharacter,
        startingModifiedAddress,
	numberOfHalfBytes,
	displacementSign,
	programName
        );
	buildModificationRecord(modificationRecord);
}

void buildModificationRecord(char *line) {
	int i = 0;
        while(ModificationRecord[i] != NULL) {
                i++;
        }
	struct modificationRecordLine *temp;
        temp = malloc(sizeof(struct modificationRecordLine));
        ModificationRecord[i] = temp;
        strcpy(temp->line, line);

}

void makeModificationRecord() {
	int i = 0;
	while(ModificationRecord[i] != NULL) {
		char *line  = malloc(sizeof(struct modificationRecordLine));
		strcpy(line, ModificationRecord[i]->line);
		buildObjectFile(line);
		i++;
	}

}

void buildObjectFile(char *line) {
	int i = 0;
	while(ObjectFile[i] != NULL) {
		i++;
	}
	struct objectFileLine *temp;
        temp = malloc(sizeof(struct objectFileLine));
	ObjectFile[i] = temp;
	strcpy(temp->line, line);

}

void outputObjectFile(char *objectFileName) {
	FILE *file = fopen(objectFileName, "w");
	// Check if the file opened successfully
    	if (file == NULL) {
        	fprintf(stderr, "Error: Could not open object file '%s' for writing.\n", objectFileName);
        	return;
    	}
	int i = 0;
	while(ObjectFile[i] != NULL) {
		fprintf(file, "%s\n", ObjectFile[i]->line);  // Write objectFileLine to object file
		i++;
	}
	fclose(file);

}

void printObjectFile() {
	int i = 0;
	while(ObjectFile[i] != NULL) {
		printf("%s\n", ObjectFile[i]->line);
		i++;
	}
}


void printOriginalAssembly() {
	int i = 0;
	while(AssemblyProgram[i] != NULL) {
		if(AssemblyProgram[i]->numberOfTokens == 3) {
			printf("%s\t%s\t%s\t%x\n", AssemblyProgram[i]->label, AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand, AssemblyProgram[i]->LocationCounter);
			i++;
		}
		else if(AssemblyProgram[i]->numberOfTokens == 2) {
			printf("\t%s\t%s\t%X\n", AssemblyProgram[i]->opcode, AssemblyProgram[i]->operand, AssemblyProgram[i]->LocationCounter);
			i++;
		}
		else if(AssemblyProgram[i]->numberOfTokens == 1) {
			printf("\t%s\t%X\n", AssemblyProgram[i]->opcode, AssemblyProgram[i]->LocationCounter);
                        i++;
		}
	}
}

