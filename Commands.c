#include "Header.h"

void freeNode(List* lst,ListNode* freeNode)//freeing a specific node from the list
{
	if (lst->head == lst->tail)
		lst->head = lst->tail = NULL;
	free(freeNode->apart.address);
	free(freeNode);
}

void printArr(Apartment* arr, int size)//printing the array.
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("Apt details:\n");
		printf("Code: %d\n", arr[i].serial);
		printf("Address: %s\n", arr[i].address);
		printf("Number of rooms: %d\n", arr[i].num_of_rooms);
		printf("Price: %d\n", arr[i].price);
		printf("Entry date: %d.%d.20%d\n", arr[i].date_to_enter.day, arr[i].date_to_enter.month, arr[i].date_to_enter.year);
		printf("Database entry date: %d.%d.%d\n", arr[i].added_to_list.day, arr[i].added_to_list.month, arr[i].added_to_list.year);
	}
}

Apartment* dynArr(Apartment* arr, int* size)//increasing the array's size
{
	Apartment* temp;
	*size = *size * 2;
	temp = (Apartment *)realloc(arr, sizeof(Apartment)*(*size));//Increasing the array.
	if (temp)//checks if the realloc succeed
	{
		return temp;//after the realloc succeed.
	}
	else
	{
		printf("There's not enough space to allocate");
		return arr;
	}
}

void printApt(List* apt,int minRoom, int maxRoom, int maxPrice, int date, int flag)//printing the needed information out of the list.
{
	Apartment* arr;
	ListNode* curr;
	curr = apt->head;
	int day=0, month=0, year=0;
	int size=0,psize=2;
	arr = (Apartment*)malloc(sizeof(Apartment)*psize);
	int savedate = date;
	while (curr != NULL)
	{
		if (size == psize)
			arr = dynArr(arr, &psize);
		if (savedate != 0)
		{
			//getting year
			if (year == 0 && month==0 && day==0)
			{
				year = date % 10;
				date = date / 10;
				year += ((date % 10) * 10);
				date = date / 10;
				date = date / 10;
				date = date / 10;
				month = date % 10;
				date = date / 10;
				month += ((date % 10) * 10);
				date = date / 10;
				day = date % 10;
				date = date / 10;
				day += ((date % 10) * 10);
			}
			if (curr->apart.date_to_enter.year < year)
			{
				arr[size] = curr->apart;
				size++;
			}
			else if (curr->apart.date_to_enter.year == year&&curr->apart.date_to_enter.month < month)
			{
				arr[size] = curr->apart;
				size++;
			}
			else if (curr->apart.date_to_enter.year == year&&curr->apart.date_to_enter.month == month&&curr->apart.date_to_enter.day < day)
			{
				arr[size] = curr->apart;
				size++;
			}

		}
		else
		{
			if (minRoom == 0 && maxRoom == 0)
			{
				if (maxPrice != 0)
				{
					if (curr->apart.price <= maxPrice)
					{
						arr[size] = curr->apart;
						size++;
					}
				}
			}
			else if (minRoom != 0 && maxRoom == 0)
			{
				if (maxPrice == 0)
				{
					if (curr->apart.num_of_rooms >= minRoom)
					{
						arr[size] = curr->apart;
						size++;
					}
				}
				else
				{
					if (curr->apart.num_of_rooms >= minRoom&&curr->apart.price<=maxPrice)
					{
						arr[size] = curr->apart;
						size++;
					}
				}
			}
			else if (minRoom == 0 && maxRoom != 0)
			{
				if (maxPrice == 0)
				{
					if (curr->apart.num_of_rooms <=maxRoom)
					{
						arr[size] = curr->apart;
						size++;
					}
				}
				else
				{
					if (curr->apart.num_of_rooms <=maxRoom&&curr->apart.price <= maxPrice)
					{
						arr[size] = curr->apart;
						size++;
					}
				}
			}
			else if (minRoom != 0 && maxRoom != 0)
			{
				if (maxPrice == 0)
				{
					if (curr->apart.num_of_rooms >= minRoom&&curr->apart.num_of_rooms <= maxRoom)
					{
						arr[size] = curr->apart;
						size++;
					}
				}
				else
				{
					if (curr->apart.num_of_rooms >= minRoom&&curr->apart.num_of_rooms <= maxRoom&&curr->apart.price <= maxPrice)
					{
						arr[size] = curr->apart;
						size++;
					}
				}
			}
		}
		curr = curr->next;
	}
	if (flag == 2 || flag == 1)// 2 from high to low, 1 from low to high
	{
		mergeSort(arr, size, flag);
	}
	printArr(arr, size);
	free(arr);
}
void mergeSort(Apartment arr[], int n,int flag)//sorting the array.
{
	int  i;
	Apartment *temp;
	if (n <= 1)
		return;
	else
	{
		mergeSort(arr, n / 2,flag);
		mergeSort(arr + n / 2, n - n / 2,flag);
		temp = (Apartment*)malloc(sizeof(Apartment)*n);
		sortedMerge(arr, n / 2, arr + n / 2, n - n / 2, temp,flag);
		for (i = 0; i < n; i++)
		{
			arr[i] = temp[i];
		}
		free(temp);
	}
}

void sortedMerge(Apartment arr1[], int size1, Apartment arr2[], int size2,Apartment res[],int flag)//sorting the array.
{
	int read1 = 0, read2 = 0, write = 0;
	if (flag == 1)
	{
		while ((read1 < size1) && (read2 < size2))
		{
			if (arr1[read1].price <= arr2[read2].price)
			{
				res[write] = arr1[read1];
				read1++;
			}
			else //arr1>arr2
			{
				res[write] = arr2[read2];
				read2++;
			}
			write++;
		}
	}
	if (flag == 2)
	{
		while ((read1 < size1) && (read2 < size2)) 
		{
			if (arr1[read1].price >= arr2[read2].price)
			{
				res[write] = arr1[read1];
				read1++;
			}
			else //arr1>arr2
			{
				res[write] = arr2[read2];
				read2++;
			}
			write++;
		}
	}
	while (read1 < size1)             
	{
		res[write] = arr1[read1];
		read1++;
		write++;
	}
	while (read2 < size2)
	{
		res[write] = arr2[read2];
		read2++;
		write++;
	}
}
void buyApart(int num1, List *lst)//removing the apart from the list
{
	ListNode* curr, *prev;
	prev=curr = lst->head;
	int i=1;
	if (lst->head->apart.serial == num1)
	{
		lst->head = lst->head->next;
		freeNode(lst,lst->head);
		return;
	}
	while (curr != NULL)
	{
		if (curr->apart.serial == num1)
		{
			prev->next = curr->next;
			freeNode(lst, curr);
			return;
		}
		if (curr == lst->tail&&lst->tail->apart.serial == num1)
		{
			lst->tail = prev;
			freeNode(lst, curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

char* lastCom(char** short_term_history)//this function is getting the short term history arr and return the last command
{
	int i;
	char* temp=NULL;
	for (i = 0; i < 7; i++)
	{
		if (short_term_history[i] != NULL)
		{
			temp = short_term_history[i];
		}
		else
			break;
	}
	return temp;
}

void printShortHis(char** short_term_history,int serial)//this function is printing the short term command history
{
	int i;
	if (serial > 7)
	{
		for (i = 1; i <= 7; i++)
		{
			if (short_term_history[i - 1] != NULL)
				printf("%d: %s\n", serial - 7 + i, short_term_history[i - 1]);
		}
	}
	else
	{
		for (i = 1; i <= 7; i++)
		{
			if (short_term_history[i - 1] != NULL)
				printf("%d: %s\n", i, short_term_history[i - 1]);
		}
	}
}

void printAllHis(char** short_term_history, comList oldCom)//this function is printing all the command history
{
	int i;
	int s=1;
	comListNode* curr;
	curr = oldCom.head;
	//printing the old commands
	while (curr != NULL)
	{
		printf("%d: %s\n", curr->serial, curr->command);
		curr = curr->next;
		s++;
	}
	//printing the new commands
	for (i = 1; i <= 7; i++)
	{
		if (short_term_history[i-1] != NULL)
		{
			printf("%d: %s\n", s, short_term_history[i - 1]);
		}
		s++;
	}
}

char* getCom(char** short_term_history, comList oldCom, int serial,int comNum)//Gets a command using the command number entered.
{
	comListNode* curr = oldCom.head;
	if (serial - 7 < comNum)//if the command is now in the short term arr
	{
		return short_term_history[6 - (serial - comNum)];
	}
	else//if the command is in the old com list
	{
		while (curr != NULL)
		{
			if (curr->serial == comNum)
			{
				return curr->command;
			}
			curr = curr->next;
		}
	}
	return NULL;
}

void timeAnalyse(DateEntry* entryToData)//builds a time structure.
{
	int i=0;
	char* str;//time as string
	time_t curtime;
	time(&curtime);//gets the time from the pc
	str = ctime(&curtime);//get the time and returns it as string

	while (str[0] == ' ')
		str++;
	while (str[0] != ' ')
		str++;
	while (str[0] == ' ')
		str++;
	//update the month
	if (check(str, "Jan") == 1)
		entryToData->month = 1;
	else if (check(str, "Feb") == 1)
		entryToData->month = 2;
	else if (check(str, "Mar") == 1)
		entryToData->month = 3;
	else if (check(str, "Apr") == 1)
		entryToData->month = 4;
	else if (check(str, "May") == 1)
		entryToData->month = 5;
	else if (check(str, "Jun") == 1)
		entryToData->month = 6;
	else if (check(str, "Jul") == 1)
		entryToData->month = 7;
	else if (check(str, "Aug") == 1)
		entryToData->month = 8;
	else if (check(str, "Sep") == 1)
		entryToData->month = 9;
	else if (check(str, "Oct") == 1)
		entryToData->month = 10;
	else if (check(str, "Nov") == 1)
		entryToData->month = 11;
	else if (check(str, "Dec") == 1)
		entryToData->month = 12;
	while (str[0] != ' ')
		str++;
	while (str[0] == ' ')
		str++;
	while (str[0] != ' ')
	{//update the day
		entryToData->day = entryToData->day * 10 + (int)(str[0] - '0');
		str++;
	}
	while (str[0] == ' ')
		str++;
	while (str[0] != ' ')
		str++;
	while (str[0] == ' ')
		str++;
	for(i=0;i<4;i++)
	{//update the year
		entryToData->year = entryToData->year * 10 + (int)(str[0] - '0');
		str++;
	}
	time_t result = time(NULL);
	uintmax_t time = (uintmax_t)result;
	time = time / 86400;//transforming into a day
	time = time * 86400;//transforming back into seconds.
	entryToData->time = time;
}

void buildApt(char* str,List *lst)//building an apartment node.
{
	ListNode *p = lst->head;
	ListNode* res;
	int serial = 0;
	Date dateToEnter;
	DateEntry entryToDatabase;
	entryToDatabase.day = entryToDatabase.month = entryToDatabase.year = 0;
	dateToEnter.day = 0;
	dateToEnter.month = 0;
	dateToEnter.year = 0;
	int i = 0, j, price = 0;
	short numRooms=0;
	char* address;//an array that saves the address
	while (p != NULL)
	{
		serial=p->apart.serial;
		p = p->next;
	}
	serial++;
	while (str[0] == ' ')
		str++;
	str++;
	while (str[i] != '"')//i-how many chars in the string.
	{
		i++;
	}
	address = (char*)malloc(sizeof(char)*(i+1));
	for (j = 0; j < i; j++)
	{//gets the address from the string
		address[j] = str[0];
		str++;
	}
	address[j] = '\0';
	str++;
	while (str[0] == ' ')
		str++;
	while (str[0] != ' ')
	{//gets the price from the string
		price = price * 10 + (int)(str[0] - '0');
		str++;
	}
	while (str[0] == ' ')
		str++;
	while (str[0] != ' ')
	{//gets the num of rooms from the string
		numRooms = numRooms * 10 + (int)(str[0] - '0');
		str++;
	}
	while (str[0] == ' ')
		str++;
	while (str[0] != ' ')
	{//gets the enter date-day
		dateToEnter.day = dateToEnter.day * 10 + (int)(str[0] - '0');
		str++;
	}
	while (str[0] == ' ')
		str++;
	while (str[0] != ' ')
	{//gets the enter date-month
		dateToEnter.month = dateToEnter.month * 10 + (int)(str[0] - '0');
		str++;
	}
	while (str[0] == ' ')
		str++;
	while (str[0] != ' '&&str[0]!='\0')
	{//gets the enter date-year
		dateToEnter.year = dateToEnter.year * 10 + (int)(str[0] - '0');
		str++;
	}
	timeAnalyse(&entryToDatabase);
	res = createNode(address, dateToEnter, entryToDatabase, serial, price, numRooms, NULL);
	insertNodeToTail(lst, res);
}

char * GetInput()//places the input inside an array.
{
	char c;
	int size = 0;
	int psize = 2;
	char *temp;
	c = getchar();
	char *str = (char *)malloc(sizeof(char)*(psize));//Temporary array for absorbing the input.
	if (str)//checking if the malloc succeed.
	{
		while (c != '\n')// if the user didn't press "enter" to finish the absorb of inputs.
		{
			if (size == psize-1)// checking if the array is full
			{
				psize = psize * 2;
				temp = (char *)realloc(str, sizeof(char)*(psize));//Increasing the array.
				if (temp)//checks if the realloc succeed
				{
					str = temp;//after the realloc succeed.
				}
				else
				{
					printf("There's not enough space to allocate");
				}
			}
			str[size] = c;
			size++;
			c = getchar();
		}
		str[size] = '\0';
	}
	return str;
}
int fromDayToSec(int day)
{
	int seconds;
	seconds = day * 24 * 60 * 60;
	return seconds;
}
void getanEnter(List *lst, int day, int flag)//Gets all the apartments inserted using the day parameter.
{
	time_t result = time(NULL);
	uintmax_t curtime= (uintmax_t)result;
	curtime = curtime / 86400;//transforming into a day
	curtime = curtime * 86400;//transforming back into seconds.
	int seconds;
	int size = 0, psize = 2;
	ListNode *curr;
	Apartment *arr = (Apartment*)malloc(sizeof(Apartment)*psize);
	seconds = fromDayToSec(day);
	curtime = curtime - (uintmax_t)seconds;
	for (curr = lst->head; curr != NULL; curr = curr->next)
	{
		if (size == psize)
			arr = dynArr(arr, &psize);
		if (curr->apart.added_to_list.time >= curtime)
		{
			arr[size] = curr->apart;
			size++;
		}
	}
	if (flag == 2 || flag == 1)// 2 from high to low, 1 from low to high
	{
		mergeSort(arr, size, flag);
	}
	printArr(arr, size);
	free(arr);
}
void deleteEnter(List *lst, int days)//Delete the apartments entered using the days parameter.
{
	ListNode *curr = lst->head;
	int seconds;
	time_t result = time(NULL);
	uintmax_t curtime = (uintmax_t)result;
	curtime = curtime / 86400;//transforming into a day
	curtime = curtime * 86400;//transforming back into seconds.
	seconds = fromDayToSec(days);
	curtime = curtime - (uintmax_t)seconds;
	ListNode *prev = lst->head;
	while(curr!=NULL)
	{
		if (curr->apart.added_to_list.time >= curtime)
		{
			if (curr == lst->head)
			{
				prev = prev->next;
				freeNode(lst, curr);
				lst->head = prev;
				if (lst->head == NULL)
					lst->tail = NULL;
				curr = prev;
			}
			else if (lst->tail == curr)
			{
				lst->tail = prev;
				freeNode(lst, curr);
				break;
			}
			else
			{
				prev->next = curr->next;
				freeNode(lst, curr);
				curr = prev->next;
			}
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
int check(char *str1, char *str2)//checks if the first string is a match to second one.
{
	int num = strlen(str2);
	int i = 0;
	while (str2[0] != '\0' && str1[0]!='\0')
	{
		if (str1[0] == str2[0])
		{
			i++;
			str1++;
			str2++;
		}
		else
		{
			return 0;
		}
	}
	if (i == num)
		return 1;
	else
		return 0;
}

int getNum(char *str, int * length)//Calculates a number out of a string.
{
	*length = 0;
	int num=0;
	while (str[0] == ' ')
	{
		str++;
		*length = *length + 1;
	}
	while (str[0] != ' ' && str[0] != '\0' && str[0]!='^')
	{
		num = num * 10 + (int)(str[0] - '0');
		str++;
		*length = *length + 1;
	}
	return num;
}

void comManage(comList* oldComm, char** newCom, char* str,int *serial)//getting the commands and storing them in the correct database
{
	int i;
	*serial = *serial + 1;
	comListNode* res;
	if (*serial <= 7)
	{//enter to the newCom arr
		newCom[(*serial)-1] = str;
	}
	else
	{//enter to the listcom
		res = createNodeCom(NULL, newCom[0], (*serial) - 7,NULL);
		insertNodeToTailCom(oldComm, res);
		//moving arr to the left
		for (i = 1; i < 7; i++)
			newCom[i - 1] = newCom[i];
		//putting the new com in the arr
		newCom[6] = str;
	}
}

void getNewCom(char *replace, char **original)//Gets a new command using old command.
{
	char * temp1 = (char *)malloc(sizeof(char)*strlen(replace));
	int index1=0;
	char * temp2 = (char *)malloc(sizeof(char)*strlen(replace));
	int index2=0;
	int i = 0;
	replace = replace + 1;
	while (replace[0] != '\0' && replace[0] != '^')
	{
		temp1[index1] = replace[0];
		index1++;
		replace=replace+1;
	}
	temp1[index1] = '\0';
	replace = replace + 1;
	while (replace[0] != '\0' && replace[0] != '^')
	{
		temp2[index2] = replace[0];
		index2++;
		replace = replace + 1;
	}
	temp2[index2] = '\0';
	while ((*original)[i] != '\0')
	{
		if (check((*original) + i, temp1) == 1)
		{
			replacement(original,i, temp1,temp2);
			i = i + strlen(temp2);
			i--;
		}
		i++;
	}
	free(temp1);
	free(temp2);
}
void replacement(char ** original, int i, char * temp1,char * temp2)//Replacing the sub string with another sub string.
{
	int j = 0;
	int length = 0;
	length = strlen(*original) + 1 - strlen(temp1) + strlen(temp2);
	char * newstr = (char *)malloc(sizeof(char)*length);
	while (j != i)
	{
		newstr[j] = (*original)[j];
		j++;
	}
	while (temp2[0] != '\0')
	{
		newstr[j] = temp2[0];
		temp2 = temp2 + 1;
		j++;
	}
	i = i + strlen(temp1);
	while ((*original)[i] != '\0')
	{
		newstr[j] = (*original)[i];
		j++;
		i++;
	}
	newstr[j] = '\0';
	free(*original);
	*original = newstr;
}
void freeApt(List *lst)//freeing the apartments.
{
	ListNode *p=lst->head;
	ListNode *temp = lst->head;
	while(p!=NULL)
	{
		free(p->apart.address);
		p = p->next;
		free(temp);
		temp = p;
	}
	free(lst);
}
void freeCmd(comList oldCom, char **short_term_history)//freeing the commands.
{
	comListNode *p = oldCom.head;
	comListNode *temp = oldCom.head;
	int i;
	while (p != NULL)
	{
		free(p->command);
		p = p->next;
		free(temp);
		temp = p;
	}
	for (i = 0; i < N; i++)
	{
		if (short_term_history[i] != NULL)
			free(short_term_history[i]);
	}
}

void manageIn(char * str)//Gets the input and summon functions.
{
	char *temp;
	int flag = 0;
	char * str2;
	char *makeNew;
	int serial = 0;//Serial of commands.
	comList oldCom;//List of Commands
	makeEmptyListCom(&oldCom);//Emptying the list.
	char *short_term_history[N];//Command arr
	int i;
	int maxPrice,minRoom,maxRoom,date,enter,comNum;//number of the command
	int length = 0;//length of the number
	int extra = 0;//flag for -s/-sr
	int num1 = 0;
	char *strloc;//saves the original address of the string
	List * lst;//List of apartments.
	lst = (List*)malloc(sizeof(List));
	makeEmptyList(lst);//Emptying the apartments.

	//setting all pointers to NULL
	for (i = 0; i < N; i++)
		short_term_history[i] = NULL;
	readFromTxt(short_term_history, &oldCom,&serial);
	readFromBin(lst);
	while (strcmp(str, "exit") != 0)
	{
		if (check(str, "!!") == 1)
		{
			free(str);
			str = lastCom(short_term_history);
			makeNew = (char *)malloc(sizeof(char)*(strlen(str) + 1));
			if (makeNew == NULL)
				return;
			strcpy(makeNew, str);
			str = makeNew;
		}
		else if (check(str, "short_history")==1)
		{
			printShortHis(short_term_history,serial);
			printf(">> ");
			free(str);
		}
		else if (check(str, "history")==1)
		{
			printAllHis(short_term_history, oldCom);
			printf(">> ");
			free(str);
		}
		else if (check(str,"!")==1)
		{
			temp = str;
			str=str+1;
			comNum = getNum(str, &length);
			str = str + length;
			if (str[0] == '\0')
			{
				flag = 1;
				free(temp);
				str = getCom(short_term_history, oldCom, serial,comNum);
				makeNew = (char *)malloc(sizeof(char)*(strlen(str) + 1));
				if (makeNew == NULL)
					return;
				strcpy(makeNew, str);
				str = makeNew;
				comManage(&oldCom, short_term_history, str, &serial);
			}
			else
			{
				str2 = str;
				str = getCom(short_term_history, oldCom, serial, comNum);
				makeNew = (char *)malloc(sizeof(char)*(strlen(str) + 1));
				if (makeNew == NULL)
					return;
				strcpy(makeNew, str);
				str = makeNew;
			    getNewCom(str2, &str);
				free(temp);
			}
		}
		strloc = str;
		if (check(str, "get-an-apt") == 1)
		{
			extra = 0;
			maxPrice = 0;
			minRoom = 0;
			maxRoom = 0;
			date = 0;
			enter = 0;
			if(flag==0)
			     comManage(&oldCom, short_term_history, strloc, &serial);
			str = str + strlen("get-an-apt");
			while (str[0] != '\0')
			{
				//get-an-apt
				if (check(str, " -MaximumPrice") == 1)
				{
					str = str + strlen(" -MaximumPrice");
					maxPrice = getNum(str, &length);
					str = str + length;
					length = 0;
					if (check(str, " -sr") == 1)
					{
						str = str + strlen(" -sr");
						extra = 2;
					}
					else if (check(str, " -s") == 1)
					{
						str = str + strlen(" -s");
						extra = 1;
					}
					//maxPrice
				}
				else if (check(str, " -MinimumNumRooms") == 1)
				{
					str = str + strlen(" -MinimumNumRooms");
					minRoom = getNum(str, &length);
					str = str + length;
					length = 0;
					if (check(str, " -sr") == 1)
					{
						str = str + strlen(" -sr");
						extra = 2;
					}
					else if (check(str, " -s") == 1)
					{
						str = str + strlen(" -s");
						extra = 1;
					}
					//MinimumNumRooms
				}
				else if (check(str, " -MaximumNumRooms") == 1)
				{
					str = str + strlen(" -MaximumNumRooms");
					maxRoom = getNum(str, &length);
					str = str +length;
					length = 0;
					if (check(str, " -sr") == 1)
					{
						str = str + strlen(" -sr");
						extra = 2;
					}
					else if (check(str, " -s") == 1)
					{
						str = str + strlen(" -s");
						extra = 1;
					}

					//MaximumNumRooms
				}
				else if (check(str, " -Date") == 1)
				{
					str = str + strlen(" -Date");
					date = getNum(str, &length);
					str = str + length;
					length = 0;
					if (check(str, " -sr") == 1)
					{
						str = str + strlen(" -sr");
						extra = 2;
					}
					else if (check(str, " -s") == 1)
					{
						str = str + strlen(" -s");
						extra = 1;
					}
					//Date
				}
				else if (check(str, " -Enter") == 1)
				{
					str = str + strlen(" -Enter");
					enter = getNum(str, &length);
					str = str + length;
					length = 0;
					if (check(str, " -sr") == 1)
					{
						str = str + strlen(" -sr");
						extra = 2;
					}
					else if (check(str, " -s") == 1)
					{
						str = str + strlen(" -s");
						extra = 1;
					}
					
					getanEnter(lst, enter,extra);
				}
			}
			if (enter == 0)
			{
				printApt(lst, minRoom, maxRoom, maxPrice, date, extra);
			}
			printf(">> ");
			flag = 0;
		}
		else if (check(str, "add-an-apt") == 1)
		{
			if (flag == 0)
				comManage(&oldCom, short_term_history, strloc, &serial);
			str = str + strlen("add-an-apt");
			buildApt(str, lst);
			printf(">> ");
			flag = 0;
		}
		else if (check(str, "buy-an-apt") == 1)
		{
			if (flag == 0)
				comManage(&oldCom, short_term_history, strloc, &serial);
			str = str + strlen("buy-an-apt");
			num1 = getNum(str, &length);
			str = str + length;
			length = 0;
			buyApart(num1, lst);
			printf(">> ");
			flag = 0;
		}
		else if (check(str, "delete-an-apt") == 1)
		{
			if (flag == 0)
				comManage(&oldCom, short_term_history, strloc, &serial);
			str = str + strlen("delete-an-apt");
			str = str + strlen(" -Enter");
			num1 = getNum(str, &length);
			str = str + length;
			length = 0;
			deleteEnter(lst, num1);
			printf(">> ");
			flag = 0;
		}
		str = GetInput();
	}
	writeToTxt(short_term_history, oldCom);
	writeToBin(lst);
	freeApt(lst);
	freeCmd(oldCom, short_term_history);
	printf("Good Bye!\n");
}