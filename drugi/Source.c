#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAXL 64

struct _Lista;
typedef struct _Lista* Position;
typedef struct _Lista {
	char ime[MAXL];
	char prezime[MAXL];
	int godrod;
	Position next;
}osoba;

Position StvoriNovuOsobu();
int DodajNaPocetak(Position p);
int Ispis(Position first);
int DodajNaKraj(Position head);
Position PronadiZadnjeg(Position head);
int UnesiNakon(Position zadnji, Position NovaOsoba);
Position PronadiPoPrezimenu(Position first);
int IzbrisiPoPrezimenu(Position head);
Position PronadiPrethodni(Position head, char* TrazenoPrezime);


int main() {

	osoba head = { .ime = {0}, .prezime = {0}, .godrod = 0, .next = NULL };

	DodajNaPocetak(&head);
	DodajNaPocetak(&head);
	Ispis(head.next);
	DodajNaKraj(&head);
	DodajNaKraj(&head); 
	Ispis(head.next);

	Position temp = NULL;
	temp = PronadiPoPrezimenu(head.next);
	printf("Ime: %s, Prezime: %s, Godina rodenja: %d \n", temp->ime, temp->prezime, temp->godrod);

	IzbrisiPoPrezimenu(&head);

	Ispis(head.next);

	return 0;
}

Position PronadiPrethodni(Position head, char* TrazenoPrezime)
{
	Position previous = NULL;
	Position current = NULL;

	previous = head;						//zaboravia si ih postavit na neke vrijednosti s kojima mozemo radit
	current = previous->next;

	while (current->next != NULL && (strcmp(current->prezime, TrazenoPrezime) != 0))
	{
		previous = current;
		current = previous->next;
	}
	if (current == NULL)
	{
		printf("Osoba nije upisana u listu! \n");
		return NULL;
	}
	
	return previous;
}

int IzbrisiPoPrezimenu(Position head)
{
	Position temp = head;
	Position current = NULL;
	Position previous = NULL;

	char TrazenoPrezime[MAXL] = { 0 };

	printf("Upisite prezime osobe koju zelite izbrisati: \n");
	scanf(" %s", TrazenoPrezime);

	previous = PronadiPrethodni(temp, TrazenoPrezime);

	current = previous->next;
	previous->next = current->next;

	free(current);

	return 0;
}

Position PronadiPoPrezimenu(Position first)
{
	Position temp = first;
	char TrazenoPrezime[MAXL] = { 0 };

	printf("Upisite prezime osobe koju zelite pronaci: \n");
	scanf(" %s",TrazenoPrezime);

	while (temp !=  NULL) {
		if (strcmp(temp->prezime,TrazenoPrezime) == 0) {
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

Position PronadiZadnjeg(Position head)
{
	Position temp = head;

	while (temp->next != NULL) {
		temp = temp->next;
	}

	return temp;
}

int UnesiNakon(Position zadnji, Position NovaOsoba)
{
	NovaOsoba->next = zadnji->next;
	zadnji->next = NovaOsoba;

	return 0;
}

int DodajNaKraj(Position head)
{
	Position NovaOsoba = NULL;
	Position zadnji = NULL;

	NovaOsoba = StvoriNovuOsobu();

	zadnji = PronadiZadnjeg(head);

	UnesiNakon(zadnji, NovaOsoba);

	return 0;
}

int Ispis(Position first)
{
	Position temp = NULL;
	temp = first;

	while (temp) {
		printf("Ime: %s, Prezime: %s, Godina rodenja: %d \n", temp->ime, temp->prezime, temp->godrod);
		temp = temp->next;
	}

	return 0;
}

Position StvoriNovuOsobu()
{
	char ime[MAXL] = { 0 };
	char prezime[MAXL] = { 0 };
	int godrod = 0;

	Position NovaOsoba = NULL;
	NovaOsoba = (Position)malloc(sizeof(osoba));
	if (!NovaOsoba) {
		printf("Neuspjesna alokacija memorije!\n");
		return NULL;
	}

	printf("Unesite ime: \n");
	scanf(" %s",ime);
	printf("Unesite prezime: \n");
	scanf(" %s",prezime);
	printf("Unesite godinu rodenja: \n");
	scanf("%d",&godrod);


	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime);
	NovaOsoba->godrod = godrod;
	NovaOsoba->next = NULL;

	return NovaOsoba;
}

int DodajNaPocetak(Position head)
{
	Position NovaOsoba = NULL;

	NovaOsoba = StvoriNovuOsobu();

	NovaOsoba->next = head->next;
	head->next = NovaOsoba;

	return 0;
}
