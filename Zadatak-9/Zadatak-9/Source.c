#define _CRT_SECURE_NO_WARNINGS
#define MAX (100)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct _BinStabloCvor;
typedef struct _BinStabloCvor* StabloPos;
typedef struct _BinStabloCvor
{
	int data;
	StabloPos left;
	StabloPos right;
}BinStabloCvor;

struct _VezanaListaEl;
typedef struct _VezanaListaEl* Position;
typedef struct _VezanaListaEl {
	int data;
	Position next;
}VezanaListaEl;

StabloPos CreateNewCvor(int broj);
Position CreateListEl(int broj);
StabloPos Insert(StabloPos root, int broj);
int Replace(StabloPos root);
int InOrderToList(StabloPos root, Position head);
int InsertToEndOfList(Position current, StabloPos root);
int PrintList(Position head);
int DeleteAfter(Position P);
int DeleteList(Position P);
//int InputFileName(char* file);
int InsertListToFile(Position head);
int InOrder(StabloPos root);
int InsertAfter(Position current, Position newEl);

int main() {

	time_t t;
	srand((unsigned)time(&t));

	StabloPos root = NULL;
	VezanaListaEl Head = { .data = 0, .next = NULL };
	Position head = &Head;
	//char datoteka[MAX] = { 0 };
	int opcija, broj;
	//InputFileName(datoteka);

	do {
		printf("MENI ZA BINARNO STABLO:\n\n");
		printf("0.Izlaz\n");
		printf("1.Unesi random element u stablo(raspon <10,90>)\n");
		printf("2.Unesi element u stablo\n");
		printf("3.Replace\n");
		printf("4.Unesi u datoteku\n");
		printf("5.Ispisi listu\n");
		printf("6.InOrder ispis\n");
		printf("Upisite vasu opciju:");
		do {
			scanf("%d", &opcija);
			if (opcija < 0 || opcija > 7) {
				printf("ta opcija nepostoji, pokusajte ponovo...\n");
			}
		} while (opcija < 0 || opcija > 7);

		switch (opcija) {
		case 0:
			printf("Izlaz...\n");
			break;
		case 1:
			broj = (rand() % (90 - 10 + 1)) + 10;
			printf("Random broj je: %d\n", broj);
			root = Insert(root, broj);
			break;
		case 2:
			printf("Unesite broj koji zelite pohranit:\n");
			scanf("%d", &broj);
			root = Insert(root, broj);
			break;
		case 3:
			Replace(root);
			break;
		case 4:
			InOrderToList(root, head);
			InsertListToFile(head);
			DeleteList(head);
			break;
		case 5:
			PrintList(head);
			break;
		case 6:
			InOrder(root);
			printf("\n");
			break;
		}
		if (opcija != 0) {
			printf("pritisnite neku tipku za nastavak...");
			getch();
		}
		printf("\n");
	} while (opcija != 0);
	return 0;
}

StabloPos CreateNewCvor(int broj)
{
	StabloPos q = NULL;
	q = (StabloPos)malloc(sizeof(BinStabloCvor));
	if (!q) {
		perror("pogreska u alokaciji memorije\n");
		return NULL;
	}
	q->data = broj;
	q->left = NULL;
	q->right = NULL;
	return q;
}

Position CreateListEl(int broj)
{
	Position q = NULL;
	q = (Position)malloc(sizeof(VezanaListaEl));
	if (!q) {
		perror("pogreska u alokaciji memorije\n");
		return NULL;
	}
	q->data = broj;
	q->next = NULL;
	return q;
}

StabloPos Insert(StabloPos root, int broj)
{
	StabloPos node = root;
	if (node == NULL) {
		StabloPos temp = NULL;
		temp = CreateNewCvor(broj);
		return temp;

	}
	else if (node->data < broj) {
		node->left = Insert(node->left, broj);

	}
	else if (node->data > broj) {
		node->right = Insert(node->right, broj);

	}
	else {
		node->left = Insert(node->left, broj);
	}
	return root;
}

int Replace(StabloPos root)
{
	int leftSum = 0, rightSum = 0, prev;
	if (root == NULL)
	{
		return 0;
	}
	prev = root->data;
	leftSum += Replace(root->left);
	rightSum += Replace(root->right);
	root->data = leftSum + rightSum;
	return root->data + prev;
}

int InOrderToList(StabloPos root, Position head)
{
	StabloPos temp = root;
	if (temp == NULL)
		return 0;
	InOrderToList(temp->left, head);
	InsertToEndOfList(head, temp);
	InOrderToList(temp->right, head);
}

int InsertToEndOfList(Position head, StabloPos node)
{
	Position current = head;
	Position newEl = CreateListEl(node->data);
	if (newEl == NULL)
		return -1;

	while (current->next != NULL)
		current = current->next;
	InsertAfter(current, newEl);
	return 0;
}

int PrintList(Position head)
{
	Position current = head->next;
	while (current != NULL)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

int DeleteAfter(Position P) {

	Position temp = NULL;
	temp = P->next;
	P->next = P->next->next;
	free(temp);
}

int DeleteList(Position P)
{
	if (P->next = NULL) {
		printf("lista je prazna\n");
	}
	while (P->next != NULL)
	{
		DeleteAfter(P);
	}
	return 0;
}

int InOrder(StabloPos root)
{
	StabloPos temp = root;
	if (temp != NULL) {
		InOrder(temp->left);
		printf("%d ", temp->data);
		InOrder(temp->right);
	}
	return 0;
}

int InsertAfter(Position head, Position newEl)
{
	newEl->next = head->next;
	head->next = newEl;
	return 0;
}

/*int InputFileName(char* file)
{
	printf("Unesite ime datoteke:\n");
	fgets(file, MAX, stdin);

	if (file[strlen(file) - 1] == '\n')
		file[strlen(file) - 1] = '\0';
	return 0;
}
*/
int InsertListToFile(Position head)
{
	FILE* fp;
	char imedat[MAX] = { 0 };
	printf("Kako zelite nazvati datoteku u koju cete upisat listu\n->");
	scanf(" %s", imedat);
	fp = fopen(imedat, "w");
	if (fp == NULL)
	{
		printf("Greska u stvaranju nove datoteke!\n");
		return -1;
	}
	Position temp = head->next;
	while (temp != NULL) {
		fprintf(fp, "%d ", temp->data);
		temp = temp->next;
	}
	fprintf(fp, "\n");
	fclose(fp);
	return 0;
}