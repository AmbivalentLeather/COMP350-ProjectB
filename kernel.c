/* Written by: Nick Young, Chase Simao
 * Date: October 2023 */

void printString(char*);
void printChar(char*);
char* readString(char*);

void main()
{
	char* letters = "Aunter a string: \0";
	char input[80];
	char* testing = "c\0";

	//printString(testing);

	printString(letters);
	//printString(testing);

	readString(input);
	//printString(testing);

	printString(input);
	//printString(testing);

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
	char* testing = "Input registered";

	interrupt(0x16, 0, 0, 0, 0);
	printString(testing);
	return inputArray;
}
