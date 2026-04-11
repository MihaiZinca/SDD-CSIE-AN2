#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


//LDI
//stiva(lifo) - inseare la inceput,extragere inceput
//coada(fifo)-inseare final,extragere inceput

typedef struct Nod Nod;

typedef struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
} Carte;

struct Nod {
	Carte info;
	Nod* next;
	Nod* prev;
};


void inserareLaInceput(Nod** cap, Nod** sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	nou->prev = NULL;
	if ((*cap) == NULL)
		*cap = *sfarsit = nou;
	else
	{
		(*cap)->prev = nou;
		*cap = nou;
	}
}

void inserareLaSfarsti(Nod** cap, Nod** sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = *sfarsit;
	if ((*cap) == NULL)
		*cap = *sfarsit = nou;
	else
	{
		(*sfarsit)->next = nou;
		*sfarsit = nou;
	}
}
//EXTRAGERE/TRAVERSARE INCEPUT
Carte pop(Nod** cap, Nod** sfarist)
{
	if (*cap == NULL)
		return initCarte(NULL, 0, 0);

	Carte c = (*cap)->info;
	Nod* copie = *cap;
	*cap = (*cap)->next;
	if (*cap != NULL)
		(*cap)->prev = NULL;
	else
		*sfarist = NULL;
	free(copie);
	return c;
}

Carte initCarte(const char* titlu, int nrPag, float pret)
{
	Carte c;
	c.nrPagini = nrPag;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);
	return c;
}

void afisareCarte(Carte carte) {
	printf("\nTitlu: %s, nrPagini: %d, pret: %.2f.", carte.titlu, carte.nrPagini, carte.pret);
}

void StivaInCoada(Nod** stiva, Nod** coada)
{
	Nod* aux1= NULL;
	Nod* aux2 = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva, coada);
		inserareLaInceput(&aux1, &aux2, c);
	}
	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inserareLaInceput(stiva, coada, c);
	}
}

void CoadaInStiva(Nod** coada, Nod** stiva)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	while (*coada != NULL)
	{
		Carte c = pop(coada, stiva);
		inserareLaInceput(&aux1, &aux2, c);
	}
}

