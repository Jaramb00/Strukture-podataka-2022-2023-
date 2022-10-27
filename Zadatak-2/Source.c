#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAXL 64

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba {
	char ime[MAXL];
	char prezime[MAXL];
	int godrod;
	Pozicija next;
}Osoba;

Pozicija Incijalizacija(Pozicija p);
int Stvori_Osobu(Pozicija p);
int Dodaj_na_pocetak(Pozicija p);
int Ispis(Pozicija p);
Pozicija Pronadi_zadnji(Pozicija p);
int Dodaj_na_kraj(Pozicija p);
Pozicija Pronadi_prethodni_po_prezimenu(Pozicija p, char* prezime);
int Brisi(Pozicija p, char* prezime);
int BrisiMemoriju(Pozicija p);
void Meni();



int main() {
	Osoba head = { .next = NULL, .ime = {0}, .prezime = {0}, .godrod = 0 };

	Pozicija h = &head;
	char prezime[MAXL] = { 0 };
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
			Dodaj_na_pocetak(h);
			break;

		case 2:
			Dodaj_na_kraj(h);
			break;

		case 3:
			Ispis(h);
			break;
		case 4:
			printf("Unesite prezime koje zelite izbrisati:\n->");
			scanf(" %s", prezime);
			Brisi(h, prezime);

			break;
		case 5:
			BrisiMemoriju(h);

		default:
			printf("Krivi unos!\n");
			break;
		}
		
	} while (odabir != 0);

	
	return 0;
}
int Stvori_Osobu(Pozicija p) {

	Pozicija q = NULL;
	q = Incijalizacija(q);

	
	printf("Unesite ime: \n->");
	scanf(" %s", q->ime);
	printf("Unesite prezime: \n->");
	scanf(" %s", q->prezime);
	printf("Unesite godinu rodenja: \n->");
	scanf("%d", &(q->godrod));

	q->next = p->next;
	p->next = q;

	return 0;

}
Pozicija Incijalizacija(Pozicija p) {

	p = (Pozicija)malloc(sizeof(Osoba));

	if (!p) {
		printf("Greska pri alokaciji memorije");

		return NULL;
	}

	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	p->godrod = 0;
	p->next = NULL;

	return p;
}
int Dodaj_na_pocetak(Pozicija p) {

	Stvori_Osobu(p);

	return 0;
}
int Ispis(Pozicija p) {

	if (p->next == NULL)
	{
		printf("\nU listi nema elemenata!\n");
		return -1;
	}

	printf("IME PREZIME GODINA_RODENJA\n\n");
	p = p->next;
	while (p != NULL) {
		printf(" %s %s %d\n", p->ime, p->prezime, p->godrod);
		p = p->next;
	}
	return 0;
}
Pozicija Pronadi_zadnji(Pozicija p) {

	Pozicija z = NULL;

	while (p->next != NULL) {
		p = p->next;
	}
	z = p;

	return z;

}
int Dodaj_na_kraj(Pozicija p) {

	Pozicija zadnji = NULL;
	zadnji = Pronadi_zadnji(p);
	Stvori_Osobu(zadnji);

	return 0;
}
/*
Pozicija Pronadi_po_prezimenu(Pozicija p,char* prezime) {

	Pozicija pom = NULL;

	while (p->next != NULL) {
		if (strcmp(p->next->prezime,prezime)==0) {
			pom = p->next;
		}
		p = p->next;
	}

		return pom;
	
*/
int Brisi(Pozicija p,char*prezime) {

	Pozicija prosli = NULL;
	Pozicija trenutni = NULL;
	prosli = Pronadi_prethodni_po_prezimenu(p,prezime);

	if (prosli == NULL)
	{
		return -1;
	}

	trenutni = prosli->next;
	prosli->next = trenutni->next;

	free(trenutni);


	return 0;
}

Pozicija Pronadi_prethodni_po_prezimenu(Pozicija p,char*prezime) {

	Pozicija prosli = NULL;
	Pozicija trenutni = NULL;
	prosli = p;
	trenutni = prosli->next;

	while (trenutni != NULL &&(strcmp(trenutni->prezime, prezime) != 0)) {

			prosli = trenutni;

			trenutni = prosli->next;
	}

	if (trenutni == NULL)
	{
		printf("\nOsoba nije upuisana u listu\n");
		return NULL;
	}

	return prosli;
}
int BrisiMemoriju(Pozicija p) {

	Pozicija q = NULL;

	while (p->next != NULL)
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
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
	printf("Za izbrisati memoriju unesite ->5\n");
}
