#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define MAX 64
#define MAXL 1024

struct _Polinom;
typedef struct _Polinom* Position;
typedef struct _Polinom {
	int koeficijent;
	int eksponent;
	Position next;
}polinom;

int ReadFromFile(Position head1, Position head2);
int UnesiUListu(Position head, int koeficijent, int eksponent);
int IspisiPolinom(Position head);
int ZbrojiPolinome(Position head1, Position head2, Position head);


int main() {

	polinom head = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	polinom head1 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	polinom head2 = { .koeficijent = 0, .eksponent = 0, .next = NULL };

	ReadFromFile(&head1, &head2);
	ZbrojiPolinome(&head1, &head2, &head);

	IspisiPolinom(&head);

	/*IspisiPolinom(&head1);
	printf("\n");
	IspisiPolinom(&head2);*/


	return 0;
}

int ZbrojiPolinome(Position head1,Position head2,Position head)
{
	while (head1->next != NULL && head2->next != NULL)
	{
		UnesiUListu(head, head1->koeficijent, head1->eksponent);
		UnesiUListu(head, head2->koeficijent, head2->eksponent);

		if (head1->next == NULL)
		{
			while (head2->next != NULL)
			{
				UnesiUListu(head, head2->koeficijent, head2->eksponent);
				head2 = head2->next;
			}
		}

		if (head2->next == NULL)
		{
			while (head1->next != NULL)
			{
				UnesiUListu(head, head1->koeficijent, head1->eksponent);
				head1 = head1->next;
			}
		}
		
		head1 = head1->next;
		head2 = head2->next;
	}

	return EXIT_SUCCESS;
}

int IspisiPolinom(Position head)
{
	Position first = NULL;
	first = head->next;

	if (first->next == NULL)
	{
		printf("Lista je prazna, polinom ne postoji!\n");
		return EXIT_SUCCESS;
	}

	while (first != NULL)
	{

		if (first->eksponent > 0)
		{
			printf(" %dx^%d ", first->koeficijent, first->eksponent);
		}

		if (first->eksponent < 0)
		{
			printf(" %dx^(%d) ", first->koeficijent, first->eksponent);
		}

		if (first->eksponent == 0)
		{
			printf(" %d ", first->koeficijent);
		}

		first = first->next;
	}

	return EXIT_SUCCESS;
}

int ReadFromFile(Position head1, Position head2)
{
	char buffer01[MAXL] = { 0 };
	char buffer02[MAXL] = { 0 };
	char* buffer1 = NULL;
	char* buffer2 = NULL;

	int koeficijent = 0;
	int eksponent = 0;
	int brojac = 0;
	int status = 0;

	char imedat[MAX] = { 0 };
	FILE* fp = NULL;

	printf("Unesite ime datoteke koju zelite otvoriti!\n");
	scanf(" %s", imedat);

	fp = fopen(imedat, "r");
	if (!fp)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return EXIT_FAILURE;
	}

	fgets(buffer01, 1024, fp);
	buffer1 = buffer01;

	fgets(buffer02, 1024, fp);
	buffer2 = buffer02;

	while (strlen(buffer1) > 0)
	{
		status = sscanf(buffer1, " %d %d %n", &koeficijent, &eksponent, &brojac);
		if (status != 2)
		{
			printf("Greska pri ucitavanju podataka iz datoteke");
			return EXIT_FAILURE;
		}

		UnesiUListu(head1, koeficijent, eksponent);

		buffer1 += brojac;

	}

	while (strlen(buffer2) > 0)
	{
		status = sscanf(buffer2, " %d %d %n", &koeficijent, &eksponent, &brojac);
		if (status != 2)
		{
			printf("Greska pri ucitavanju podataka iz datoteke");
			return EXIT_FAILURE;
		}

		UnesiUListu(head2, koeficijent, eksponent);

		buffer2 += brojac;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int UnesiUListu(Position head, int koeficijent, int eksponent)
{
	Position temp = NULL;
	Position pol = NULL;

	pol = (Position)malloc(sizeof(polinom));
	if (!pol)
	{
		printf("Neuspjesna alokacija memorije za polinom!\n");
		return EXIT_FAILURE;
	}

	pol->koeficijent = koeficijent;
	pol->eksponent = eksponent;
	pol->next = NULL;

	if (head->next == NULL)
	{
		pol->next = head->next;
		head->next = pol;

		return EXIT_SUCCESS;
	}

	while (head->next != NULL && head->next->eksponent > eksponent)
	{
		head = head->next;
	}


	if (head->next == NULL && head->eksponent > eksponent)
	{
		pol->next = head->next;			//Unesi nakon 
		head->next = pol;
	}
	else if (head->next != NULL && head->next->eksponent == eksponent)
	{
		head->next->koeficijent += koeficijent;		//nadodajemo eksponent na onaj u listi

		if (head->next->koeficijent == 0)			//ako je zbroj 0 prebacujemo pokazivace i brisemo iz liste
		{
			temp = head->next;
			head->next = head->next->next;
			free(temp);
		}

		free(pol);
	}
	else
	{
		pol->next = head->next;			//eskponent je najveci pa ga unosimo iza heada
		head->next = pol;
	}


	return EXIT_SUCCESS;
}
