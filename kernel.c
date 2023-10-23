
// Joe's Operating System Kernel
// kernel.c

void printString(char*);

void printChar(char*);
char* readString(char*);
char* readSector(char*, int);

void main()
{
	char* letters = "Hello World\0";

//	printString(letters);

//	readString(input);

//	printString(input);

	char buffer[512];
	readSector(buffer, 30);
	printString(buffer);

	while(1);
}

void printString(char* chars)
{	
	/*
	int startVidMem = 0xb800;
	int vidMemOffset = 0x0;
	int white = 0x7;
	*/

	int i = 0;
	while (chars[i] != 0x0) {
		char al = chars[i];
		char ah = 0xe;
		int ax = ah * 256 + al;
		interrupt(0x10, ax, 0, 0, 0);
		++i;
	}
	/*
	char al = *chars;
	char ah = 0xe;
	int ax = ah * 256 + al;
	interrupt(0x10, ax, 0, 0, 0);
	*/
}

char* readSector(char* buffer, int sector){
    int AH = 2; // this number tells BIOS to read a sector as opposed to write
    int AL = 1; // numbers of sectors to read
    char* BX = buffer; // address where the data should be stored to
    int CH = 0; // track number
    int CL = sector+1; // relative sector number
    int DH = 0; // head number
//    interrupt(0x13, AH, AL, BX, CH, CL, DH, 0x80);
    interrupt(0x13, AH*256+AL, BX, CH*256+CL, DH*256+0x80); //Notes version  

    return buffer;
}
