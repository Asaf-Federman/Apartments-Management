#include "Header.h"

void main()
{
	printf("Please enter one of the following commands:\n");
	printf("add-an-apt, get-an-apt, buy-an-apt or delete-an-apt\n");
	printf("For reconstruction commands, please enter:\n");
	printf("!!, !num, history, short_history or !num^str1^str2\n");
	printf("To exit, enter exit.\n>> ");
	char * str;
	str = GetInput();
	manageIn(str);
}