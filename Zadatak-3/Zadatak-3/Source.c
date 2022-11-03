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
int UnesiNakon(Position prethodni, Position NovaOsoba);
Position PronadiPoPrezimenu(Position first);
int IzbrisiPoPrezimenu(Position head);
Position PronadiPrethodni(Position head, char* TrazenoPrezime);
int DodajIza(Position head);
int DodajIspred(Position head);
void Meni();
int BrisiMemoriju(Position p);
int UnesiUDatoteku(Position head);
int SortirajListuGlupo(Position head);
int ProcitajteIzDatoteke(Position head);
int UnesiUListu(Position head, char* ime, char* prezime, int godrod);



int main() {

	osoba head = { .ime = {0}, .prezime = {0}, .godrod = 0, .next = NULL };
	Position h = &head;
	char prezime[MAXL] = { 0 };
	char imedat[MAXL] = { 0 };
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
			DodajNaPocetak(h);
			break;

		case 2:
			DodajNaKraj(h);
			break;

		case 3:
			Ispis(h);
			break;
		case 4:
			IzbrisiPoPrezimenu(h);
			break;
		case 5:
			DodajIza(h);
			break;
		case 6:
			DodajIspred(h);
			break;
		case 7:
			BrisiMemoriju(h);
			break;
		case 8:
			UnesiUDatoteku(h);
			break;
		case 9:
			printf("Sortirali ste sad i nikad više\n");
			SortirajListuGlupo(h);
			break;
		case 10:
			ProcitajteIzDatoteke(h->next);
			break;


		default:
			printf("Krivi unos!\n");
			break;
		}

	} while (odabir != 0);


	return 0;
}

int DodajIspred(Position head)
{
	Position temp = NULL;
	Position NovaOsoba = NULL;
	char TrazenoPrezime[MAXL] = { 0 };

	printf("Dodajemo ispred! \n\n");


	printf("Ispred koga zelite unijeti u listu? \n");
	scanf(" %s", TrazenoPrezime);

	temp = PronadiPrethodni(head, TrazenoPrezime);

	NovaOsoba = StvoriNovuOsobu();


	UnesiNakon(temp, NovaOsoba);

	return EXIT_SUCCESS;
}

int DodajIza(Position head)
{
	Position temp = NULL;
	Position NovaOsoba = NULL;
	char TrazenoPrezime[MAXL] = { 0 };

	printf("Dodajemo iza! \n\n");

	temp = PronadiPoPrezimenu(head->next);
	NovaOsoba = StvoriNovuOsobu();

	UnesiNakon(temp, NovaOsoba);

	return EXIT_SUCCESS;
}

Position PronadiPrethodni(Position head, char* TrazenoPrezime)
{
	Position previous = NULL;
	Position current = NULL;

	previous = head; //zaboravia si ih postavit na neke vrijednosti s kojima mozemo radit
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
	scanf(" %s", TrazenoPrezime);

	while (temp != NULL) {
		if (strcmp(temp->prezime, TrazenoPrezime) == 0) {
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

int UnesiNakon(Position prethodni, Position NovaOsoba)
{
	NovaOsoba->next = prethodni->next;
	prethodni->next = NovaOsoba;

	return 0;
}


int DodajNaKraj(Position head)
{
	Position NovaOsoba = NULL;
	Position zadnji = NULL;

	printf("Dodajemo na kraj liste! \n\n");


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

	printf("Unesite ime: \n->");
	scanf(" %s", ime);
	printf("Unesite prezime: \n->");
	scanf(" %s", prezime);
	printf("Unesite godinu rodenja: \n->");
	scanf("%d", &godrod);


	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime);
	NovaOsoba->godrod = godrod;
	NovaOsoba->next = NULL;

	return NovaOsoba;
}

int DodajNaPocetak(Position head)
{
	Position NovaOsoba = NULL;

	printf("Dodajemo na pocetak liste! \n\n");

	NovaOsoba = StvoriNovuOsobu();

	UnesiNakon(head, NovaOsoba);

	return 0;
}
void Meni()
{
	printf("\n/////////MENI\\\\\\\\\n");
	printf("Za kraj programa ->0:\n");
	printf("Za unijeti na pocetak unesite ->1:\n");
	printf("Za unijeti na kraj unesite->2:\n");
	printf("Za ispis osoba unesite ->3:\n");
	printf("Za izbrisati osobu unesite ->4:\n");
	printf("Za unijeti osobu iza osobe unesite ->5:\n");
	printf("Za unijeti osobu ispred osobe unesite ->6:\n");
	printf("Za izbrisati memoriju unesite ->7\n");
	printf("Za unijeti listu u datoteku unesite ->8\n");
	printf("Za samo sortiranje studenata unesite ->9\n");
	printf("Za citanje studenata u listu unesite ->10\n");





}

int BrisiMemoriju(Position p) {

	Position q = NULL;

	while (p->next != NULL)
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
	}

	printf("Memorija izbrisana\n");

	return 0;

}
int UnesiUDatoteku(Position head) {

	FILE* f;
	char imedat[MAXL] = { 0 };
	printf("Kako zelite nazvati datoteku u koju cete upisat listu\n->");
	scanf(" %s", imedat);
	f = fopen(imedat, "w");
	if (f == NULL)
	{
		printf("Greska u stvaranju nove datoteke!\n");
		return -1;
	}
	fprintf(f, "\n %-25s %-25s %-25s \n\n", "IME", "PREZIME", "GODINA RODENJA");
	while (head != NULL)
	{

		fprintf(f, "\n %-25s %-25s %-25d", head->ime, head->prezime, head->godrod);
		head = head->next;
	}

	fclose(f);
	printf("Datoteka %s uspjesno kreireana!\n", imedat);

	return 0;

}

int SortirajListuGlupo(Position head) {

	Position i, j, prosli_j, pomoc, kraj;
	kraj = NULL;
	i = head;
	while (i->next != kraj)
	{
		prosli_j = i;
		j = i->next;
		while (j->next != kraj)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				pomoc = j->next;
				prosli_j->next = pomoc;
				j->next = pomoc->next;
				pomoc->next = j;
				j = pomoc;
			}
			prosli_j = j;
			j = j->next;
		}
		kraj = j;
	}
	return 0;
}
int ProcitajteIzDatoteke(Position head) {

	FILE* f;
	char imedat[MAXL] = { 0 };
	char ime[MAXL] = { 0 };
	char prezime[MAXL] = { 0 };
	int godrod = 0;

	printf("Koju datoteku zelite procitati\n->");
	scanf(" %s", imedat);
	f = fopen(imedat, "r");
	if (f == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}
	while (!feof(f)) {

		fscanf(f, " %s %s %d\n", ime, prezime, godrod);
		UnesiUListu(head, ime, prezime, godrod);

	}
	fclose(f);

	return 0;
}

int UnesiUListu(Position head, char* ime, char* prezime, int godrod) {

	Position q = NULL;

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->godrod = godrod;

	while (head->next != NULL)
	{
		if (strcmp(head->next->prezime, prezime) > 0)
			break;
		head = head->next;
	}
	q->next = head->next;
	head->next = q;

	return 0;
}



