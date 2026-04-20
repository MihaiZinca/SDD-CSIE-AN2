#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Carte
{
	char* titlu;
	int nrPagini;
	float pret;
}Carte;

typedef struct Nod Nod;
struct Nod
{
	Carte info;
	Nod* next;
	Nod* prev;
};

void inseareInceput(Nod** cap, Nod** sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	nou->prev = NULL;
	if (*cap == NULL)
		*cap = *sfarsit = nou;
	else
	{
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
	if (*cap == NULL)
		*cap = *sfarsit = nou;
	else
	{
		(*sfarsit)->next = nou;
		*sfarsit = nou;
	}
}

Carte initCarte(const char* titlu, int nrPagini, float pret)
{
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);
	return c;
}

void afisareCarte(Carte carte)
{
	printf("Titlu %s, pagini %d, pret%f", carte.titlu, carte.nrPagini, carte.pret);
}

void afisareLista(Nod* cap)
{
	while (cap != NULL)
	{
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void dezalocare(Nod** cap, Nod** sfarsit)
{
	while ((*cap) != NULL)
	{
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
	*sfarsit = NULL;
}

Carte pop(Nod** cap, Nod** sfarist)
{
	if (*cap == NULL)
	{
		Carte c;
		c.nrPagini = 0;
		c.pret = 0;
		c.titlu = NULL;
		return c;
	}
	Carte c = (*cap)->info;
	Nod* aux = *cap;
	*cap = (*cap)->next;

	if (*cap != NULL)
		(*cap)->prev = NULL;
	else
		*sfarist = NULL;
	free(aux);
	return c;
}

void stergereNodStiva(Nod** stiva, Nod** sfarsit, const char* titlu)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva, sfarsit);
		if (strcmp(c.titlu, titlu) != 0)
			inseareInceput(&aux1, &aux2, c);
		else
			free(c.titlu);
	}
	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inseareInceput(stiva, sfarsit, c);
	}
}

void stergereNodCoada(Nod** coada, Nod** sfarsit, const char* titlu)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	while (*coada != NULL)
	{
		Carte c = pop(coada, sfarsit);
		if (strcmp(c.titlu, titlu) != 0)
			inserareSfarsit(&aux1, &aux2, c);
		else
			free(c.titlu);
	}
	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inserareSfarsit(coada, sfarsit, c);
	}
}

int stivaToVector(Nod** stiva,Nod** sfarsit,Carte v[])
{
	int n = 0;
	while (stiva != NULL)
	{
		v[n++] = pop(stiva, sfarsit);
	}
	return n;
}

Nod* vectorToStiva(Carte v[], int n)
{
	Nod* stiva = NULL;
	Nod* sfarsit = NULL;
	for (int i = n - 1; i >= 0; i--)
		inseareInceput(&stiva, &sfarsit, v[i]);
	return stiva;
}

int coadaToVector(Nod**coada, Nod** sfarsit, Carte v[])
{
	int n = 0;
	while (*coada != NULL)
	{
		v[n++] = pop(coada, sfarsit);
	}
	return n;
}
Nod* vectorToCoada(Carte v[], int n)
{
	Nod* coada = NULL;
	Nod* sfarsit = NULL;
	for (int i = 0; i < n; i++)
		inserareSfarsit(&coada, &sfarsit, v[i]);
	return coada;
}

void stivaToCoada(Nod** stiva, Nod** coada, Nod** sfCoada)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva, sfCoada);
		inserareSfarsit(&aux1, &aux2, c);
	}
	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inserareSfarsit(coada, sfCoada, c);
	}
}

void coadaToStiva(Nod** coada, Nod** stiva, Nod** sfStiva)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	while (*coada != NULL)
	{
		Carte c = pop(coada, sfStiva);
		inserareSfarsit(&aux1, &aux2,c);
	}
	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inseareInceput(stiva, sfStiva, c);
	}
}


