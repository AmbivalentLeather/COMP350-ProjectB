
// Joe's Operating System Kernel
// kernel.c

void main()
{
	int startVidMem = 0xb800;
	int vidMemOffset = 0x0;
	int white = 0x7;
	char* letters = "Hello World\0";

	while (*letters != 0x0) {
		putInMemory(startVidMem, vidMemOffset, *letters);
		++vidMemOffset;
		putInMemory(startVidMem, vidMemOffset, white);
		++vidMemOffset;
		//advance letters pointer
		++letters;
	}

	char al = 'Q';
	char ah = 0xe;
	int ax = ah * 256 + al;
	interrupt(0x10, ax, 0, 0, 0);

	while(1);
}
