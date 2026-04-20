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
};


//STIVA(LIFO) -INSERARE INCEPUT,EXTRAGERE INCEPUT 
//COADA(FIFO) -INSERARE FINAL, EXTRAGERE INCEPUT


void inserareInceput(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}

void inserareSfarsit(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	if (*cap == NULL)
		*cap = nou;
	else
	{
		Nod* aux = *cap;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nou;
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

void afisareStiva(Nod* stiva)
{
	while (stiva != NULL)
	{
		afisareCarte(stiva->info);
		stiva = stiva->next;
	}
}

void dezalocare(Nod** cap)
{
	while ((*cap) != NULL)
	{
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

//traversare/extragere inceput
Carte pop(Nod** stiva)
{
	if (*stiva == NULL)
	{
		Carte c;
		c.nrPagini = 0;
		c.pret = 0;
		c.titlu = NULL;
		return c;
	}

	//sw 
	Carte c = (*stiva)->info;
	Nod* aux = *stiva;
	*stiva = (*stiva)->next;
	free(aux);
	return c;

	//dp
	Carte c = initCarte((*stiva)->info.titlu, (*stiva)->info.nrPagini, (*stiva)->info.pret);
	Nod* aux = *stiva;
	*stiva = (*stiva)->next;
	free(aux->info.titlu);
	free(aux);
	return c;
}

void stergereNoduriStiva(Nod** stiva, const char* titlu)
{
	Nod* aux = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva);
		if (strcmp(c.titlu, titlu) != 0)
			inserareInceput(&aux, c);
		else
			free(c.titlu);
	}
	while (aux != NULL)
	{
		Carte c = pop(&aux);
		inserareInceput(stiva, c);
	}
}

void stergereNoduriCoada(Nod** coada, const char* titlu)
{
	Nod* aux = NULL;
	while (*coada != NULL)
	{
		Carte c = pop(coada);
		if (strcmp(c.titlu, titlu) != 0)
			inserareSfarsit(&aux, c);
		else
			free(c.titlu);
	}
	while (aux != NULL)
	{
		Carte c = pop(&aux);
		inserareSfarsit(coada, c);
	}
}


int stivaToVector(Nod** stiva, Carte c[])
{
	int n = 0;
	while (*stiva != NULL)
	{
		c[n++] = pop(stiva);
	}
	return n;
}

Nod* vectorToStiva(Carte c[], int n)
{
	Nod* stiva = NULL;
	for (int i = n - 1; i >= 0; i++)
		inserareInceput(&stiva, c[i]);
	return stiva;
}


int coadaToVector(Nod** coada, Carte c[])
{
	int n = 0;
	while (*coada != NULL)
	{
		c[n++] = pop(coada);
	}
	return n;
}
Nod* vectorToCoada(Carte c[], int n)
{
	Nod* coada = NULL;
	for (int i = 0; i < n; i++)
		inserareSfarsit(&coada, c[i]);
	return coada;
}

void stivaToCoada(Nod** stiva, Nod** coada)
{
	Nod* aux = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva);
		inserareSfarsit(&aux, c);
	}
	while (aux != NULL)
	{
		Carte c = pop(&aux);
		inserareSfarsit(stiva, c);
	}
}

void coadaToStiva(Nod** coada, Nod** stiva)
{
	while (*coada != NULL)
	{
		Carte c = pop(coada);
		inserareInceput(stiva, c);
	}
}


