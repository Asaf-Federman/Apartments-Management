#define _CRT_SECURE_NO_WARNINGS
#define N 7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

typedef struct date
{
	short int year;
	short int month;
	short int day;
}Date;
typedef struct dateentry
{
	short int year;
	short int month;
	short int day;
	uintmax_t time;
}DateEntry;
typedef struct apartment
{
	int serial;
	char *address;
	int price;
	short int num_of_rooms;
	Date date_to_enter;
	DateEntry added_to_list;
}Apartment;

typedef struct listNode 
{
	Apartment apart;
	struct listNode* next;
}ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
}List;

typedef struct comListNode
{
	int serial;
	struct comListNode* next;
	struct comListNode* prev;
	char* command;
}comListNode;

typedef struct comList
{
	comListNode* head;
	comListNode* tail;
}comList;

void getanEnter(List *lst, int day, int flag);
char * GetInput();
int check(char *str1, char *str2);
void manageIn(char * str);
int getNum(char *str, int * length);
void buildApt(char* str, List *lst);
void makeEmptyList(List *lst);
ListNode* createNode(char* address, Date toEnter, DateEntry addedToList, int serial, int price, short int numRooms, ListNode* next);
void insertNodeToTail(List *lst, ListNode* newTail);
void timeAnalyse(DateEntry* entryToData);
void buyApart(int num1,List *lst);
void freeNode(List* lst, ListNode* freeNode);
void printApt(List* apt, int minRoom, int maxRoom, int maxPrice, int date, int flag);
Apartment* dynArr(Apartment* arr, int* size);
void mergeSort(Apartment arr[], int n, int flag);
void sortedMerge(Apartment arr1[], int size1, Apartment arr2[], int size2, Apartment res[], int flag);
void printArr(Apartment* arr, int size);
void printList(List *merge);
int fromDayToSec(int day);
void deleteEnter(List *lst, int days);
void getanEnter(List *lst, int day, int flag);
comListNode* createNodeCom(comListNode* next, char* command, int serial, comListNode* prev);
void makeEmptyListCom(comList *lst);
void insertNodeToTailCom(comList* lst, comListNode* newTail);
void comManage(comList* oldComm, char** newCom, char* str,int *serial);
char* lastCom(char** short_term_history);
void printShortHis(char** short_term_history,int serial);
void printAllHis(char** short_term_history,comList oldCom);
char* getCom(char** short_term_history,comList oldCom,int serial,int comNum);
void getNewCom(char *replace, char **original);
void replacement(char ** original, int i, char * temp1, char * temp2);
void writeToTxt(char** short_term_history,comList oldCom);
void readFromTxt(char** short_term_history, comList* oldCom,int* serial);
void insertNodeToHeadCom(comList* lst, comListNode* newHead);
void writeToBin(List * lst);
void makeBin(Date date,short int numRooms,unsigned char* c1,unsigned char* c2,unsigned char* c3);
void makeBin2(DateEntry added, unsigned char* c1,unsigned char* c2);
void readFromBin(List* lst);
void byteAnalyse(unsigned char c1,unsigned char c2,unsigned char c3,short int* numRooms,int* day,int* month,int* year);
void byteAnalyse2(unsigned char c1,unsigned char c2, int* day, int* month, int* year);
void freeApt(List *lst);
void freeCmd(comList oldCom, char **short_term_history);
char * getLine(FILE *f1);
