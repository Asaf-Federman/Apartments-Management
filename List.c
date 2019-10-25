#include "Header.h"

void makeEmptyList(List *lst)//gets a list and emptying the list.
{
	lst->head = lst->tail = NULL;
}
ListNode* createNode(char* address, Date toEnter,DateEntry addedToList, int serial,int price,short int numRooms,ListNode* next)
{
	ListNode *result;
	result = (ListNode *)malloc(sizeof(ListNode));
	if (!result)
	{
		printf("Memory allocation failed");
		return NULL;
	}
	result->apart.address = address;
	result->apart.num_of_rooms = numRooms;
	result->apart.price = price;
	result->apart.serial = serial;
	result->apart.added_to_list = addedToList;
	result->apart.date_to_enter = toEnter;
	result->next = next;

	return result;
}

void insertNodeToTail(List* lst, ListNode* newTail)
{
	newTail->next = NULL;

	if (lst->head == NULL)
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}
void printList(List *merge)//recieves a list and prints it.
{
	ListNode *p;
	p = merge->head;
	for (p = merge->head; p != NULL; p = p->next)
	{
			printf("Apt details:\n");
			printf("Code: %d\n", p->apart.serial);
			printf("Address: %s\n", p->apart.address);
			printf("Number of rooms: %d\n", p->apart.num_of_rooms);
			printf("Price: %d\n", p->apart.price);
			printf("Entry date: %d.%d.%d\n", p->apart.date_to_enter.day, p->apart.date_to_enter.month, p->apart.date_to_enter.year);
			printf("Database entry date: %d.%d.%d\n", p->apart.added_to_list.day, p->apart.added_to_list.month, p->apart.added_to_list.year);

	}
}
void makeEmptyListCom(comList *lst)//gets a list and emptying the list.
{
	lst->head = lst->tail = NULL;
}
comListNode* createNodeCom(comListNode* next,char* command, int serial, comListNode* prev)
{
	comListNode *result;
	result = (comListNode *)malloc(sizeof(comListNode));
	if (!result)
	{
		printf("Memory allocation failed");
		return NULL;
	}
	result->serial = serial;
	result->next = next;
	result->prev = prev;
	result->command = command;
	return result;
}

void insertNodeToTailCom(comList* lst, comListNode* newTail)
{
	newTail->next = NULL;

	if (lst->head == NULL)
	{
		lst->head = lst->tail = newTail;
		newTail->prev = NULL;
	}
	else
	{
		newTail->prev = lst->tail;
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void insertNodeToHeadCom(comList* lst, comListNode* newHead)
{
	if (lst->tail == NULL)
		lst->tail = newHead;
	newHead->prev = NULL;
	newHead->next = lst->head;
	if (lst->head != NULL)
	{
		lst->head->prev = newHead;
	}
	lst->head = newHead;
}