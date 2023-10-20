
// Joe's Operating System Kernel
// kernel.c

void printString(char*);
void printChar(char*);

void main()
{
	char* letters = "Hello World\n\0";
	char* c = "c";

	printString(letters);
	printChar(c);

	while(1);
}

void printString(char* chars)
{	
	int i = 0;
	while (chars[i] != 0x0) {
		char al = chars[i];
		char ah = 0xe;
		int ax = ah * 256 + al;
		interrupt(0x10, ax, 0, 0, 0);
		++i;
	}
}

void printChar(char* c)
{
	char al = *c;
	char ah = 0xe;
	int ax = ah * 256 + al;
	interrupt(0x10, ax, 0, 0, 0);

}
