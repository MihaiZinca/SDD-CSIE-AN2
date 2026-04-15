#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

//LDI
//STIVA(LIFO) -INSEARE INCEPUT, EXTRAGERE INCEPUT
//COADA(FIFO) INSERARE FINAL,EXTRARE INCEPUT

typedef struct Carte
{
	char* titlu;
	int nrPagini;
	float pret;
}Carte;

typedef struct Nod Nod;
struct Nod {
	Carte info;
	Nod* next;
	Nod* prev;
};


void inserareInceput(Nod** cap, Nod** sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	nou->prev = NULL;
	if ((*cap) == NULL)
		*cap = *sfarsit = nou;
	else {
		(*cap)->prev = nou;
		*cap = nou;
	}
}

void inserareSfarsit(Nod** cap, Nod** sfarsit, Carte c)
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

//TRAVERSARE /EXTRAGER INCEPUT
Carte pop(Nod** cap, Nod** sfarsit)
{
	if (*cap == NULL)
		return initCarte(NULL, 0, 0);
	Carte c = (*cap)->info;
	Nod* copie = *cap;
	*cap = (*cap)->next;
	if (*cap != NULL)
		(*cap)->prev = NULL;
	else
		*sfarsit = NULL;
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

void afisareListaCarti(Nod* cap) {
	while (cap != NULL) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void coadainVector(Nod** coada, Carte** vectorCarti, int nrCarti) //idem pt stiva
{
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*coada != NULL)
	{
		(*vectorCarti)[i] = pop(coada, NULL);
		i++;
	}
}

Nod* vectorInStiva(Carte* vectorCarti, int nrCarti)
{
	Nod* stiva = NULL;
	Nod* sfarsit = NULL;

	for (int i = nrCarti - 1; i >= 0; i--)
	{
		inserareInceput(&stiva, &sfarsit, vectorCarti[i]);
	}

	return stiva;
}

void StivainCoada(Nod** stiva, Nod** coada)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	Nod* sfarsitCoada = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva, NULL);
		inserareSfarsit(&aux1, &aux2, c);
	}
	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2, c);
		inserareSfarsit(coada, &sfarsitCoada, c);
	}
}

void CoadainStiva(Nod** coada, Nod** stiva)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	Nod* sfarsitStiva = NULL;
	while (*coada != NULL)
	{
		Carte c = pop(coada, NULL);
		inserareSfarsit(&aux1, &aux2, c);
	}
	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inserareInceput(stiva, &sfarsitStiva, c);
	}
}