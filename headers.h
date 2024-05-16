#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct symbol {
	int	SourceLine;
	int	SymbolAddress;
	char	Name[7];
};

struct symbol * Symbols[1024]; /* Array of symbol pointers to hold symbols */


struct opcode {
	int	OpCode;
	char	Name[8];
};

struct opcode * Opcodes[32]; /* Array of opcode pointers to hold opcodes */


struct assemblyLine {
	int lineNumber;  // Line number for reference
	int numberOfTokens;  //number of tokens
    	char *label;  // Label
    	char *opcode; // Opcode
    	char *operand; // Operand
	int LocationCounter; //location counter associated with line
};

struct assemblyLine * AssemblyProgram[50]; /* Array of assembly line pointers to hold original sic file */



struct modificationRecordLine {
	char line[19];
};

struct modificationRecordLine * ModificationRecord[50];


struct endingRecordLine {
	char line[12];
};

struct endingRecordLine * EndingRecord[1];


struct objectFileLine {
	char line[71];
};

struct objectFileLine * ObjectFile[100]; /* Array of objectFileLine pointers to hold the object file */


/* Function declarations */
int IsAValidSymbol( char *TestSymbol );
int IsADirective( char *Test );
int IsAnInstruction( char *Test ); /* Returns 1 if Test is an instruction, and 0 if not an instruction */
void InsertSymbol( char Name[7], int SymbolAddress, int SourceLine );
int getSymbolAddress(char *symbol);
void InsertOpcode(char Name[7], int opcode);
int getOpcode(char *opcode);
void PrintSymbolTable();
int EndDirective(char *directive, char *operand, int lineNumber, char *line);
int ResbDirective(char *directive, char *operand, int lineNumber, char *line);
int ReswDirective(char *directive, char *operand, int lineNumber, char *line);
int ResrDirective(char *directive, char *operand, int lineNumber, char *line);
int ByteDirective(char *directive, char *operand, int lineNumber, char *line);
int WordDirective(char *directive, char *operand, int lineNumber, char *line);
int ExportsDirective(char *directive, char *operand, int lineNumber, char *line);
int ApplyDirective(char *directive, char *operand, int lineNumber, char *line);
int ApplyInstruction(char *opcode, char *operand);
void rtrim(char *str);
bool InSymbolTable(char *symbol);
bool InOpcodeTable(char *opcode);
void printOpcodeTable();
bool ValidHexNumber(char *number);
void buildAssemblyFile(int lineNumber, int numberOfTokens, char *label, char *opcode, char *operand, int LocationCounter);
void ApplyInstructionPassTwo(char *opcode, char *operand, int LocationCounter, int num_tokens, int lineNumber, char *line);
void ApplyDirectivePassTwo(char *opcode, char *operand, int LocationCounter, char *line, int lineNumber);
void makeHeaderRecord(char *programName, int startingAddress, int programLength);
void makeTextRecord();
void addEndRecord(int startingAddress);
void buildEndRecord(char *endRecord);
void makeEndRecord();
void applyModification(int LocationCounter, char *programName);
void buildModificationRecord(char *line);
void makeModificationRecord();
void buildObjectFile(char *line);
void printObjectFile();
void printOriginalAssembly();
void outputObjectFile(char *objectFileName);
char* convertToAscii(char* characterConstant);
void ByteDirectivePassTwo(char *opcode, char *operand, int LocationCounter);
