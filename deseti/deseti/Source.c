#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MAXL 1024

struct _gradovi;
typedef struct _gradovi* PositionS;
typedef struct _gradovi {
	char imegrada[MAXL];
	int brojstanovnika;
	PositionS left;
	PositionS right;
}gradovi;

struct _drzave;
typedef struct _drzave* PositionL;
typedef struct _drzave {
	char imedrzave[MAXL];
	char imedat[MAXL];
	PositionL next;
	PositionS root;
}drzave;

int OpenFile(PositionL head);
PositionL CreateNovaDrzava();
int UnesiSortirano(PositionL novadrzava, PositionL head);
int IspisiListu(PositionL first);
int UcitajGradove(PositionL first);
PositionS StvoriNoviGrad();
PositionS UnesiSortiranoGrad(PositionS root, PositionS novigrad);
int IspisiGradove(PositionS root);
int Pretraga(PositionL head);
int PronadiDrzavu(PositionL head, char* imedrzave);
int PronadiGradove(PositionL drzava);
int IspisGradovaPoMin(PositionS root, int minBrojStanovnika);


int main() {

	drzave Head = { .imedrzave = {0}, .imedat = {0}, .next = NULL, .root = NULL };
	PositionL head = &Head;
	OpenFile(head);

	UcitajGradove(head->next);
	
	//IspisiListu(head->next);

	Pretraga(head);


	return 0;
}

int Pretraga(PositionL head)
{
	char imedrzave[MAXL] = { 0 };

	do
	{
		printf("\n***********************");
		printf("\nUnesite ime drzave kojoj zelite pretraziti gradove po broju stanovnika: ");
		printf("\nZa prekid pretrazivanja upisite exit");
		scanf(" %s", imedrzave);
		PronadiDrzavu(head, imedrzave);
	} while (strcmp(imedrzave, "exit") != 0);

	return EXIT_SUCCESS;
}

int PronadiDrzavu(PositionL head, char* imedrzave)
{
	PositionL temp = NULL;
	temp = head->next;

	while (temp)
	{
		if (strcmp(temp->imedrzave, imedrzave) == 0)
		{
			PronadiGradove(temp);

			break;
		}
		else
		{
			temp = temp->next;
		}
	}

	if (!temp)
	{
		printf("\n %s ne postoji u listi!\n", imedrzave);
	}

	return EXIT_SUCCESS;
}

int PronadiGradove(PositionL drzava)
{
	int minBrojStanovnika = 0;
	PositionS root = NULL;
	root = drzava->root;

	printf("\n %s", drzava->imedrzave);
	printf("\nUnesite minimalan broj stanovnika gradova u odabranoj drzavi : \n");
	scanf(" %d", &minBrojStanovnika);

	IspisGradovaPoMin(root, minBrojStanovnika);

	return EXIT_SUCCESS;
}

int IspisGradovaPoMin(PositionS root, int minBrojStanovnika)
{
	PositionS temp = NULL;
	temp = root;

	if (temp)
	{
		if (temp->brojstanovnika <= minBrojStanovnika)
		{
			IspisGradovaPoMin(temp->right, minBrojStanovnika);
		}
		else
		{
			IspisGradovaPoMin(temp->left, minBrojStanovnika);
			printf("\n %s -> broj stanovnika: %d", temp->imegrada, temp->brojstanovnika);
			IspisGradovaPoMin(temp->right, minBrojStanovnika);
		}
	}

	return EXIT_SUCCESS;
}

int UcitajGradove(PositionL first)
{

	PositionL temp = NULL;
	temp = first;

	while (temp)
	{
		FILE* fp = NULL;
		fp = fopen(temp->imedat, "r");
		if (!fp)
		{
			printf("Nesupjesno otvaranje datoteke %s\n", temp->imedat);
			return EXIT_FAILURE;
		}

		while (!feof(fp))
		{
			PositionS novigrad = NULL;
			novigrad = StvoriNoviGrad();
			
			fscanf(fp, " %s %d", novigrad->imegrada, &novigrad->brojstanovnika);

			temp->root = UnesiSortiranoGrad(temp->root, novigrad); 
		}

		fclose(fp);

		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

PositionS UnesiSortiranoGrad(PositionS root, PositionS novigrad)
{
	if (root == NULL)
	{
		return novigrad;
	}

	if (root->brojstanovnika < novigrad->brojstanovnika)
	{
		root->right = UnesiSortiranoGrad(root->right, novigrad);

		return root;
	}
	else if (root->brojstanovnika > novigrad->brojstanovnika)
	{
		root->left = UnesiSortiranoGrad(root->left, novigrad);

		return root;
	}
	else
	{
		if (strcmp(root->imegrada, novigrad->imegrada) < 0)
		{
			root->right = UnesiSortiranoGrad(root->right, novigrad);

			return root;
		}
		else if (strcmp(root->imegrada, novigrad->imegrada) > 0)
		{
			root->left = UnesiSortiranoGrad(root->left, novigrad);

			return root;
		}
		else
		{
			free(novigrad);

			return root;
		}
	}

}

PositionS StvoriNoviGrad()
{
	PositionS novigrad = NULL;

	novigrad = (PositionS)malloc(sizeof(gradovi));
	if (!novigrad)
	{
		printf("Neuspjesna alokacija memorije za novi grad! \n");
		return NULL;
	}

	novigrad->left = NULL;
	novigrad->right = NULL;

	return novigrad;
}

int OpenFile(PositionL head)
{
	char filename[MAXL] = { 0 };
	char imedrzave[MAXL] = { 0 };
	char imedat[MAXL] = { 0 };

	PositionL novadrzava = NULL;

	printf("Unesite ime datoteke: \n");
	scanf(" %s", filename);

	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (!fp)
	{
		printf("\nNeuspjesno otvaranje datoteke!\n");
		return EXIT_FAILURE;
	}

	while (!feof(fp)) {
		novadrzava = CreateNovaDrzava();
		fscanf(fp, " %s %s", imedrzave, imedat);
		strcpy(novadrzava->imedrzave, imedrzave);
		strcpy(novadrzava->imedat, imedat);

		UnesiSortirano(novadrzava, head);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

PositionL CreateNovaDrzava()
{
	PositionL novadrzava = NULL;
	novadrzava = (PositionL)malloc(sizeof(drzave));
	if (!novadrzava)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return NULL;
	}

	novadrzava->next = NULL;
	novadrzava->root = NULL;

	return novadrzava;
}

int UnesiSortirano(PositionL novadrzava, PositionL head)
{
	while (head->next != NULL)
	{
		if (strcmp(head->next->imedrzave, novadrzava->imedrzave) > 0)
			break;
		head = head->next;
	}

	novadrzava->next = head->next;
	head->next = novadrzava;


	return EXIT_SUCCESS;
}

int IspisiListu(PositionL first)
{

	while (first)
	{
		printf("\n IME DRZAVE: %s  IME DATOTEKE: %s \n", first->imedrzave, first->imedat);
		IspisiGradove(first->root);
		//printf("\n");

		first = first->next;
	}

	return EXIT_SUCCESS;
}

int IspisiGradove(PositionS root)
{
	PositionS temp = NULL;
	temp = root;

	if (temp)
	{
		IspisiGradove(temp->left);
		printf("\n %s -> broj stanovnika: %d", temp->imegrada, temp->brojstanovnika);
		IspisiGradove(temp->right);
		printf("\n");
	}

	return EXIT_SUCCESS;
}