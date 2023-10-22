/* Written by: Nick Young, Chase Simao
 * Date: October 2023 */

void printString(char*);
void printChar(char*);
char* readString(char*);

void main()
{
	char* letters = "Aunter a string: \0";
	char input[80];

	printString(letters);

	readString(input);

	printString(input);

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

/*
For every element in a given array
	Call interrupt 0x16
	Save result in array
	Print to screen
	Exit loop if ENTER key is pressed (ASCII 0xd)
Add 0xa (line feed) and 0x0 (end of string) as the last two characters in the array
Print 0xd and 0xa characters (since the user pressed enter)
Return the array

If i = 0x8 (backspace), 
	Print to screen w/o storing in array
	Decrease the array index

If i = 0 && i = 0x8
	Do nothing

(Make sure the array index does not go below zero). 
!!To erase the character from the screen, print out a space and a second backspace.
I don't know how exactly to do the above other than literally trying it so thats what I'll do
*/

char* readString(char* inputArray) // I'm not sure why it wants a pointer here, array?
{
	char* registered = " Input registered ";
	char in = 0x0;

	int i = 0;
	while (i != 79) {
		in = (char) interrupt(0x16, 0, 0, 0, 0);
		if (in == 0xd)
			break;	// Break out of the loop if the user presses enter
		if (i == 0 && in == 0x8)
			;	// Don't print backspace if array index == 0
		if (in == 0x8){
			char space = ' ';
			interrupt(0x10, 0xe * 256 + in, 0, 0, 0);
			interrupt(0x10, 0xe * 256 + space, 0, 0, 0);
			//interrupt(0x10, 0xe * 256 + in, 0, 0, 0);
			--i;
			;	// Print backspace character, decrement array index
		}

		inputArray[i] = in;
		interrupt(0x10, 0xe * 256 + in, 0, 0, 0);
//		printString(registered);
		++i;
	}
	inputArray[i] = 0xa;
	inputArray[i + 1] = 0x0;

	interrupt(0x10, 0xe * 256 + 0xd, 0, 0, 0); // Print 0xd
	interrupt(0x10, 0xe * 256 + 0xa, 0, 0, 0); // Print 0xa

	return inputArray;
}
