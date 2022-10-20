#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXL 60
#define EXIT_FAILURE_ -1

struct _Lista;
typedef struct _Lista* position;
typedef struct _Lista{

	char ime[MAXL], prezime[MAXL];
	double bodovi;
	position next;

}Studenti;

position Inicialisation(position p);
int OpenFile_CountStudents(char* ime_dat);
int OpenFile_ScanAll(position p, char* ime_dat);
int UnesiUListu(position p, char* ime, char* prezime, double bodovi);
double RelativniBodovi(double x, double y);
int Ispis(position p);
double pronadiMaxBodove(position p);
int BrisiMemoriju(position p);


int main() {

	position lista_studenata = NULL;
	int n = 0;
	char datoteka[MAXL] = { 0 };

	lista_studenata=Inicialisation(lista_studenata);

	printf("Unesite ime datoteke koju zelite otvoriti \n->");
	scanf(" %s", &datoteka);

	n = OpenFile_CountStudents(datoteka);

	if (n < 0) {

		printf("Nema studenata\n");

		return EXIT_FAILURE_;
	}
	else {
		printf("Broj zapisanih studenata u datoteci ( %s) je -> %d\n\n",datoteka,n);
	}

	OpenFile_ScanAll(lista_studenata, datoteka);

	Ispis(lista_studenata);
	BrisiMemoriju(position p);


	return 0;
}

int OpenFile_CountStudents(char* ime_dat){

	int br = 0;
	char red[MAXL]= { 0 }; //buffer

	FILE* f = NULL;
	f = fopen(ime_dat,"r");

	if (f == NULL) {

		printf("Greska u otvaranju datoteke -> %s \n",ime_dat);
		return EXIT_FAILURE_;
	}

	while (!feof(f)) {

		fgets(red, MAXL, f);
		if (*red == '\n') {
			continue;
		}
		else{
			br++;
		}
	}

	fclose(f);
	return br;
}

position Inicialisation(position p) {
	
		p = (position)malloc(sizeof(Studenti));

		if (p == NULL)
		{
			printf("Greska pri inicijalizaciji liste.\n");
			return NULL;
		}

		p->bodovi = 0.0;
		strcpy(p->ime, "");
		strcpy(p->prezime, "");
		p->next = NULL;

		return p;
	}

int OpenFile_ScanAll(position p,char* ime_dat) {

	char ime[MAXL], prezime[MAXL] = { 0 };
	double bodovi=0.0;

	FILE* f = NULL;
	f = fopen(ime_dat,"r");

	if (f == NULL) {

		printf("Greska u otvaranju datoteke -> %s \n", ime_dat);
		return EXIT_FAILURE_;
	}
	
	while (!feof(f)) {

		fscanf(f, " %s %s %d\n", ime, prezime, &bodovi); //trenutacni problem
		UnesiUListu(p, ime, prezime, bodovi);
	}

	fclose(f);

	return 0;

}
int UnesiUListu(position p, char* ime, char* prezime, double bodovi)
{
	position q = NULL;
	q = Inicialisation(q);
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->bodovi = bodovi;

	q->next = p->next;
	p->next = q;

	return 0;
}
double RelativniBodovi(double x, double y) {

	double rel_bod = 0.0;
	rel_bod = (x / y) * 100;


	return rel_bod;
}


int Ispis(position p) {

	double max = 0.0;
	max = pronadiMaxBodove(p);
	double rel = 0.0;

	printf("Max bodovi su ->%d\n\n", max);

	printf("IME PREZIME RELATIVNI-BODOVI\n");

		p = p->next;
		while (p!= NULL)
		{
			rel = RelativniBodovi(p->bodovi, max);
			printf("%s %s %f\n", p->ime, p->prezime,rel);
			p = p->next;
		}

		return 0;
	}

double pronadiMaxBodove(position p) {

	double max_bodovi = 0.0;

	p = p->next;
		while (p!= NULL)
		{
			if (p->bodovi > max_bodovi) {
				max_bodovi = p->bodovi;
			}
			p = p->next;
		}
		
		return max_bodovi;
}
int BrisiMemoriju(position p) {

	position q = NULL;

	while (p->next != NULL)
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
	return 0;

}

