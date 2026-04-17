#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct Produs
{
	char* denumire;
	int cantitate;
	float pret;
}Produs;

typedef struct Nod Nod;

struct Nod
{
	Produs info;
	Nod* next;
};


void inseareInceput(Nod** cap, Produs p)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = *cap;
	*cap = nou;
}

void inserareSfarsit(Nod** cap, Produs p)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = NULL;
	if ((*cap) == NULL)
	{
		*cap = nou;
	}
	else
	{
		Nod* aux = *cap;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nou;
	}
}

void dezalocare(Nod** cap)
{
	while (cap != NULL)
	{
		free((*cap)->info.cantitate);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

void afisareProdus(Produs produs)
{
	printf("Denumire %s, canitate %d, pret %f", produs.denumire, produs.cantitate, produs.pret);
}

void afisareLista(Nod* cap)
{
	while (cap != NULL)
	{
		afisareProdus(cap->info);
		cap = cap->next;
	}
}

Nod* cautareDen(Nod* cap, const char* den)
{
	while (cap != NULL)
	{
		if (strcmp(cap->info.denumire, den) == 0)
		{
			return cap;
		}
	}
	return NULL;
}

Nod* stergereNoduri(Nod* cap)
{
	Nod* aux = cap;
	if (cap->info.cantitate == 0)
	{
		aux = cap->next;
		free(cap->info.denumire);
		free(cap);
		return aux;
	}

	while (aux != NULL && aux->next != NULL)
	{
		if (cap->info.cantitate == 0)
		{
			Nod* sters = aux->next;
			aux->next = sters->next;
			free(sters->info.denumire);
			free(sters);
		}
		else
		{
			aux = aux->next;
		}
	}
	return cap;
}

int lsiToVector(Nod* cap, Produs p[])
{
	int n = 0;
	while (cap != NULL)
	{
		p[n++] = cap->info;
		cap = cap->next;
	}
	return n;
}

Nod* vectorToLsi(Produs p[], int n)
{
	Nod* cap = NULL;
	for (int i = n - 1; i >= 0; i--)
	{
		inseareInceput(cap, p[i]);
	}
	return cap;
}