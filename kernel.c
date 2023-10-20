
// Joe's Operating System Kernel
// kernel.c

void printString(char*);

void main()
{
	char* letters = "Hello World\0";

	printString(letters);

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
