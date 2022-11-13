#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAX 64
#define MAXL 1024

struct _Stog;
typedef struct _Stog* Position;
typedef struct _Stog {
	float element;
	Position next;
}stog;

int ReadFromFile(Position head);
int Push(Position head, float broj);
int RacunanjeIzraza(Position head, char operator);
float Pop(Position head);


int main() {

	stog head = { .element = 0, .next = NULL };

	Position first = &head;

	ReadFromFile(&head);

	printf("Rezultat matematickih operacija je %f\n", first->next->element);

	return 0;
}

float Pop(Position head)
{
	float broj = 0.0;
	Position first = NULL;

	first = head->next;

	broj = first->element;
	head->next = first->next;

	free(first);

	return broj;
}

int RacunanjeIzraza(Position head, char operator)
{
	float br1 = 0.0;
	float br2 = 0.0;

	switch (operator)
	{
	case '+':
		br1 = Pop(head);
		br2 = Pop(head);
		Push(head, br1 + br2);
		break;

	case '-':
		br1 = Pop(head);
		br2 = Pop(head);
		Push(head, br2 - br1);
		break;

	case '*':
		br1 = Pop(head);
		br2 = Pop(head);
		Push(head, br2 * br1);
		break;

	case '/':
		br1 = Pop(head);
		br2 = Pop(head);
		if (br1 == 0)
			printf("Nije moguce dijeljenje sa 0\n");
		else
			Push(head, br2 / br1);
		break;
	}


	return EXIT_SUCCESS;
}


int Push(Position head, float broj)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(stog));
	if (!newElement)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	newElement->next = head->next;
	head->next = newElement;

	newElement->element = broj;

	return EXIT_SUCCESS;
}

int ReadFromFile(Position head)
{

	char imedat[MAX] = { 0 };
	char buffer01[MAXL] = { 0 };
	char* buffer1 = NULL;
	float broj = 0;
	int status = 0;
	int brojac = 0;
	char operator = 0;

	printf("Unedite ime datoteke koju zelite ucitati! \n");
	scanf(" %s", imedat);

	FILE* fp = NULL;

	fp = fopen(imedat, "r");
	if (!fp)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return EXIT_FAILURE;
	}

	fgets(buffer01, MAXL, fp);

	buffer1 = buffer01;

	while (strlen(buffer1) > 0)
	{
		status = sscanf(buffer1, " %f %n", &broj, &brojac);

		if (status == 1)
		{
			Push(head, broj);
			buffer1 += brojac;
		}
		else
		{
			sscanf(buffer1, " %c %n", &operator, &brojac);
			RacunanjeIzraza(head, operator);
			buffer1 += brojac;
		}
	}


	fclose(fp);

	return EXIT_SUCCESS;
}