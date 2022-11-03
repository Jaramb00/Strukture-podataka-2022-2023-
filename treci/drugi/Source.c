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
void Meni();
int BrisiMemoriju(Position head);
int DodajIza(Position head);
int DodajIspred(Position head);
int IspisiUDatoteku(Position head);
int UpisiIzDatoteke(Position head);
int UnesiSortirano(Position head, Position temp);


int main() {

	osoba head = { .ime = {0}, .prezime = {0}, .godrod = 0, .next = NULL };

	int odabir = 0;

	do {
		Meni();

		scanf("%d", &odabir);

		switch (odabir)
		{
		case 0:
			printf("Kraj programa!\n");
			break;

		case 1:
			DodajNaPocetak(&head);
			break;

		case 2:
			DodajNaKraj(&head);
			break;

		case 3:
			Ispis(head.next);
			break;
		case 4:
			IzbrisiPoPrezimenu(&head);
			break;
		case 5:
			BrisiMemoriju(&head);
			break;
		case 6:
			DodajIza(&head);
			break;
		case 7:
			DodajIspred(&head);
			break;
		case 8:
			IspisiUDatoteku(head.next);
			break;
		case 9:
			UpisiIzDatoteke(&head);
			break;
		default:
			printf("Krivi unos!\n");
			break;
		}

	} while (odabir != 0);



	Position temp = NULL;
	temp = PronadiPoPrezimenu(head.next);
	printf("Ime: %s, Prezime: %s, Godina rodenja: %d \n", temp->ime, temp->prezime, temp->godrod);



	return 0;
}

int UnesiSortirano(Position head, Position temp)
{
	if (head->next == NULL)
	{
		UnesiNakon(head, temp);
		return EXIT_SUCCESS;
	}

	Position first = head->next;

	if (strcmp(first->prezime, temp->prezime) > 0)
	{
		UnesiNakon(head, temp);
		return EXIT_SUCCESS;
	}

	while (strcmp(first->prezime, temp->prezime) > 0)
	{
		first = first->next;

		if (strcmp(first->prezime, temp->prezime) == 0)
		{
			free(temp);
			return EXIT_SUCCESS;
		}
	}

	UnesiNakon(first, temp);

	return EXIT_SUCCESS;
}

int UpisiIzDatoteke(Position head)
{
	Position temp = NULL;
	char ime_dat[MAXL] = { 0 };

	FILE* fp = NULL;

	printf("Unesite ime datoteke iz koje zelite ucitati listu: \n");
	scanf(" %s", ime_dat);

	fp = fopen(ime_dat, "r");
	if (!fp)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return EXIT_FAILURE;
	}

	while (!feof(fp))
	{
		temp = (Position)malloc(sizeof(osoba));
		if (!temp)
		{
			printf("Greska pri alokaciji memorije!\n");
			return EXIT_FAILURE;
		}

		fscanf(fp," %s %s %d", temp->ime, temp->prezime, &temp->godrod);

		UnesiSortirano(head, temp);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int IspisiUDatoteku(Position first)
{

	Position temp = first;
	char ime_dat[MAXL] = { 0 };
	printf("Kako zelite da se zove vasa datoteka?\n");
	scanf(" %s", ime_dat);

	FILE* fp = NULL;
	fp = fopen(ime_dat, "w");
	if (!fp)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return EXIT_FAILURE;
	}

	while (temp != NULL)					//Zasto ne moze while(temp->next != NULL)
	{
		fprintf(fp, "IME: %s PREZIME: %s GODINA_RODENJA: %d \n", temp->ime, temp->prezime, temp->godrod);
		temp = temp->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int DodajIspred(Position head)
{
	Position temp = NULL;
	Position NovaOsoba = NULL;
	char TrazenoPrezime[MAXL] = { 0 };

	NovaOsoba = StvoriNovuOsobu();


	printf("Ispred koga zelite unijeti u listu? \n");
	scanf(" %s", TrazenoPrezime);

	temp = PronadiPrethodni(head, TrazenoPrezime);

	UnesiNakon(temp, NovaOsoba);

	return EXIT_SUCCESS;
}

int DodajIza(Position head)
{
	Position temp = NULL;
	Position NovaOsoba = NULL;
	char TrazenoPrezime[MAXL] = { 0 };

	NovaOsoba = StvoriNovuOsobu();

	temp = PronadiPoPrezimenu(head->next);

	UnesiNakon(temp, NovaOsoba);

	return EXIT_SUCCESS;
}

int BrisiMemoriju(Position head)
{
	Position p = head;
	Position q = NULL;

	while (p->next != NULL)
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
	return EXIT_SUCCESS;
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

	return EXIT_SUCCESS;
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

	return EXIT_SUCCESS;
}

int DodajNaKraj(Position head)
{
	Position NovaOsoba = NULL;
	Position zadnji = NULL;

	NovaOsoba = StvoriNovuOsobu();

	zadnji = PronadiZadnjeg(head);

	UnesiNakon(zadnji, NovaOsoba);

	return EXIT_SUCCESS;
}

int Ispis(Position first)
{
	Position temp = NULL;
	temp = first;

	while (temp) {
		printf("Ime: %s, Prezime: %s, Godina rodenja: %d \n", temp->ime, temp->prezime, temp->godrod);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
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

	return EXIT_SUCCESS;
}

void Meni()
{
	printf("\n*******MENI*******\n");
	printf("Za kraj programa ->0:\n");
	printf("Za unijeti na pocetak unesite ->1:\n");
	printf("Za unijeti na kraj unesite->2:\n");
	printf("Za ispis osoba unesite ->3:\n");
	printf("Za izbrisati osobu unesite ->4:\n");
	printf("Za izbrisati memoriju unesite ->5\n");
	printf("Za unijeti iza osobe unesite ->6\n");
	printf("Za unijeti ispred osobe unesite ->7\n");
	printf("Za ispis liste u datoteku unesite ->8\n");
	printf("Za upis u listu iz datoteke unesite ->9\n");
	printf("\n*******************\n");

}