#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


//LSI
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
};


//inserare la inceput push

void inserareLaInceput(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}
//inseare la Sfarsit put

void inseareLaSfarsit(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	if ((*cap) == NULL)
		*cap = nou;
	else
	{
		Nod* aux = *cap ;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nou;
	}
}

//Traversare /extaragere inceput
Carte pop(Nod** stiva)
{
	if (*stiva == NULL)
		return initCarte(NULL, 0, 0);
	
	//sw
	Carte c = (*stiva)->info;

	//dp
	//Carte c=initCarte((*stiva)->info.titlu,,,)
	Nod* copie = *stiva;
	(*stiva) = (*stiva)->next;
	//free(copie.info.titlu);
	free(copie);
	return c;
}

Carte initCarte(const char* titlu, int nrPagini, float pret)
{
	Carte c ;
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

void CoadaInVector(Nod** coada, Carte** vectorCarti, int nrCarti)
{
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*coada != NULL)
	{
		(*vectorCarti)[i] = pop(coada);
		i++;
	}
}

void VectorInStiva(Carte* vectorCarti, int nrCarti,Nod** stiva)
{
	for (int i = 0; i < nrCarti; i++)
	{
		inserareLaInceput(stiva, vectorCarti[i]);
	}
}

void StivaInCoada(Nod** stiva, Nod** coada)
{
	Nod* aux = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva);
		inseareLaSfarsit(&aux, c);
	}
	while (aux != NULL)
	{
		Carte c = pop(&aux);
		inserareLaInceput(coada, c);
	}
}

void CoadainStiva(Nod** coada, Nod** stiva)
{
	while (*coada != NULL)
	{
		Carte c = pop(coada);
		inserareLaInceput(stiva, c);
	}
}

