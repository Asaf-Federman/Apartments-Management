#include"Header.h"
void writeToTxt(char** short_term_history, comList oldCom)//writing the data into text file.
{
	FILE* f1;
	int i;
	comListNode* curr=oldCom.tail;

	f1 = fopen("Commands.txt", "wt");
	for (i = N - 1; i >= 0; i--)
	{
		fprintf(f1, "%s\n", short_term_history[i]);
	}
	while (curr != NULL)
	{
		fprintf(f1, "%s\n", curr->command);
		curr = curr->prev;
	}
	fclose(f1);
}
char * getLine(FILE *f1)//getting a line from the file.
{
	int size = 0;
	char c;
	int psize=2;
	c = fgetc(f1);
	if (c == EOF)
		return NULL;
	char * str = (char *)malloc(sizeof(str)*psize);
	char * temp;
	while (c != '\n')
	{
		if (size == (psize-1))
		{
			psize = psize * 2;
			temp = (char *)realloc(str,sizeof(char)*(psize));
			if (temp == NULL)
				return NULL;
			str = temp;
		}
		str[size] = c;
		size++;
		c=fgetc(f1);
	}
	str[size] = '\0';
	temp = (char *)realloc(str, sizeof(char)*(size+1));
	if (temp == NULL)
		return NULL;
	str = temp;
	return str;
}
void readFromTxt(char** short_term_history,comList *oldCom,int* serial)//reading from text file, and transforming the data into needed data.
{
	FILE* f1;
	comListNode* p;
	char* str;
	int i,count=1;

	str = (char*)malloc(sizeof(char) * 101);
	f1 = fopen("Commands.txt", "rt");
	if (f1 == NULL)
		return;
	for (i = 6;i>=0;i--)
	{
		*serial = *serial + 1;
		str=getLine(f1);
		if (str == NULL)
			return;
		short_term_history[i] = str;
	}
	str = getLine(f1);
	while (str != NULL)
	{
		p = createNodeCom(NULL, str,0, NULL);//serial is set afterwards
		insertNodeToHeadCom(oldCom, p);
		str = getLine(f1);
	}
	free(str);//the last one doesnt contain anything
	p = oldCom->head;
	while (p != NULL)
	{
		p->serial = count;
		count++;
		p = p->next;
	}
	count--;
	*serial = *serial + count;
	fclose(f1);
}
void writeToBin(List * lst)//writing into binary file.
{
	FILE* f;
	ListNode* curr=lst->head;
	short int ser,len;
	int price;
	unsigned char c1,c2,c3;

	f = fopen("Apart.bin", "wb");
	if (f == NULL)
		return;
	while (curr != NULL)
	{
		c1 = 0x00; 
		c2 = 0x00;
		c3 = 0x00;
		ser = (short int)curr->apart.serial;
		fwrite(&ser, sizeof(short int), 1, f);
		len = (short int)strlen(curr->apart.address);
		fwrite(&len, sizeof(short int), 1, f);
		fwrite(curr->apart.address, sizeof(char), len, f);
		price = curr->apart.price;
		fwrite(&price, sizeof(int), 1, f);
		makeBin(curr->apart.date_to_enter, curr->apart.num_of_rooms, &c1, &c2, &c3);
		fwrite(&c1, sizeof(unsigned char), 1, f);
		fwrite(&c2, sizeof(unsigned char), 1, f);
		fwrite(&c3, sizeof(unsigned char), 1, f);
		c1 = 0x00;
		c2 = 0x00;
		makeBin2(curr->apart.added_to_list, &c1, &c2);
		fwrite(&c1, sizeof(unsigned char), 1, f);
		fwrite(&c2, sizeof(unsigned char), 1, f);
		curr = curr->next;
	}
	fclose(f);
}

void makeBin(Date date, short int numRooms, unsigned char* c1,unsigned  char* c2,unsigned char* c3)//transforming data into bytes
{
	unsigned char maskNum1 = 0x00;

	*c1 = ((maskNum1) | (numRooms))<<4;
	*c1 = (((maskNum1) | (date.day)) >> 1)|(*c1);
	*c2 = ((maskNum1) | (date.day)) << 7;
	*c2 = (((maskNum1) | (date.month)) << 3) | (*c2);
	*c2 = (((maskNum1) | (date.year)) >> 4) | (*c2);
	*c3 = ((maskNum1) | (date.year)) << 4;
}

void makeBin2(DateEntry added, unsigned char* c1, unsigned char* c2)//transforming data into bytes
{
	int year = added.year - 2000;
	unsigned char maskNum = 0x00;
	*c1 = (((maskNum) | (added.day)) << 3);
	*c1 = (((maskNum) | (added.month)) >> 1) | (*c1);
	*c2 = (((maskNum) | (added.month)) << 7);
	*c2 = ((maskNum) | (year)) | (*c2);
}

void readFromBin(List* lst)//reading the binary file and transforming it into needed data
{
	FILE* f;
	int size;
	Date date;
	DateEntry date2;
	short int s,len,numRooms;
	int serial,price,day,month,year;
	char* str;
	unsigned char c1, c2, c3;
	ListNode* p;
	struct tm info;
	time_t time_raw;
	f = fopen("Apart.bin", "rb");
	if (f == NULL)
		return;
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	rewind(f);
	while (ftell(f) < size)
	{
		c1 = c2 = c3 = 0x00;
		serial = price = 0;
		numRooms = len = s = 0;
		day = month = year = 0;
		fread(&s, sizeof(short int), 1, f);
		serial = (int)s;
		fread(&len, sizeof(short int), 1, f);
		str = (char*)malloc(sizeof(char)*(len + 1));
		fread(str, sizeof(char), len, f);
		str[len] = '\0';
		fread(&price, sizeof(int), 1, f);
		fread(&c1, sizeof(unsigned char), 1, f);
		fread(&c2, sizeof(unsigned char), 1, f);
		fread(&c3, sizeof(unsigned char), 1, f);
		byteAnalyse(c1, c2, c3, &numRooms, &day, &month, &year);
		date.day = day;
		date.month = month;
		date.year = year;
		day = month = year = 0;
		fread(&c1, sizeof(unsigned char), 1, f);
		fread(&c2, sizeof(unsigned char), 1, f);
		byteAnalyse2(c1, c2, &day, &month, &year);
		date2.day = day;
		date2.month = month;
		date2.year = year+2000;
		info.tm_year = date2.year-1900;
		info.tm_mon = month-1;
		info.tm_mday = day;
		info.tm_hour = 0;
		info.tm_min = 0;
		info.tm_sec = 1;
		info.tm_isdst = 0;
		time_raw = mktime(&info);
		date2.time = time_raw;
		p = createNode(str, date,date2, serial, price, numRooms, NULL);
		insertNodeToTail(lst, p);
	}
	fclose(f);
}
void byteAnalyse(unsigned char c1, unsigned char c2,unsigned  char c3, short int* numRooms, int* day, int* month, int* year)//analysing the date structure from bytes.
{
	unsigned char mask1 = 0x00;
	unsigned char day1 = 0x0F;
	unsigned char day2 = 0x80;
	unsigned char month1 = 0x78;
	unsigned char year1 = 0x07;
	unsigned char year2 = 0xF0;
	*numRooms = (short int)((c1) >> 4);
	*day= ((day1)&c1) << 1;
	*day = (((day2)&c2) >> 7) | (*day);
	*month = (((month1)&(c2)) >> 3);
	*year = (((year1)&(c2)) << 4);
	*year = (((year2)&c3) >> 4) | (*year);
}

void byteAnalyse2(unsigned char c1, unsigned char c2, int* day, int* month, int* year)//analysing the added time structure from bytes.
{
	unsigned char day1 = 0xF8;
	unsigned char month1 = 0x07;
	unsigned char month2 = 0x80;
	unsigned char year1 = 0x7F;
	*day = (((c1)&(day1)) >> 3);
	*month = (((c1)&(month1)) << 1);
	*month = (((c2)&(month2)) >> 7) | (*month);
	*year = ((c2)&(year1));
}