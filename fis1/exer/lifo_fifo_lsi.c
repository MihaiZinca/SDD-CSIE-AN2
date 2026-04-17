#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


//STIVA(LIFO)- inseare inceput,extragere inceput
//Coada(FIFO)- inserare final,extragere inceput


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
};

//LSI


void inserareInceput(Nod** cap, Carte c) //PUSH
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}

void inserareFinal(Nod** cap, Carte c) //PUT
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
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

//traversrare
Carte pop(Nod** stiva)
{
	if (*stiva == NULL)
		return initCarte(NULL, 0, 0);
	//sw
	Carte c = (*stiva)->info;
	Nod* copie = *stiva;
	*stiva = (*stiva)->next;
	free(copie);
	return c;

	//dp
	Carte c = initCarte((*stiva)->info.titlu, (*stiva)->info.nrPagini, (*stiva)->info.pret);
	Nod* copie = *stiva;
	*stiva = (*stiva)->next;
	free(copie->info.titlu);
	free(copie);
	return c;
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
	printf("\nTitlu: %s, nrPagini: %d, pret: %.2f.", carte.titlu, carte.nrPagini, carte.pret);
}

void afisareListaCarti(Nod* cap)
{
	while (cap != NULL)
	{
		afisareCarte(cap->info);
		cap = cap->next;
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

void stergereNodStiva(Nod** stiva, const char* titlu)
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

void stergereNodCoada(Nod** coada, const char* titlu)
{
	Nod* aux = NULL;
	while (*coada != NULL)
	{
		Carte c = pop(coada);
		if (strcmp(c.titlu, titlu) != 0)
			inserareFinal(&aux, c);
		else
			free(c.titlu);
	}
	while (aux != NULL)
	{
		Carte c = pop(&aux);
		inserareFinal(coada, c);
	}
}


void stivaInVector(Nod** stiva, Carte** vectorCarti, int nrCarti)
{
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*stiva != NULL)
	{
		(*vectorCarti)[i] = pop(stiva);
		i++;
	}
}

Nod* vectorInStiva(Carte* vectorCarti, int nrCarti)
{
	Nod* stiva = NULL;
	for (int i = nrCarti - 1; i >= 0; i--)
		inserareInceput(&stiva, vectorCarti[i]);
	return stiva;
}

void coadaInVector(Nod** coada, Carte** vectorCarti, int nrCarti)
{
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*coada != NULL)
	{
		(*vectorCarti)[i] = pop(coada);
		i++;
	}
}

Nod* vectorInCoada(Carte* vectorCarti, int nrCarti)
{
	Nod* coada = NULL;
	for (int i = 0;i<nrCarti; i--)
		inserareFinal(&coada, vectorCarti[i]);
	return coada;
}

void stivaInCoada(Nod** stiva, Nod** coada)
{
	Nod* aux = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva);
		inserareFinal(&aux, c);

	}
	while (aux != NULL)
	{
		Carte c = pop(&aux);
		inserareFinal(coada, c);
	}
}

void coadaInStiva(Nod** coada, Nod** stiva)
{
	while (*coada != NULL)
	{
		Carte c = pop(coada);
		inserareInceput(stiva, c);
	}
}