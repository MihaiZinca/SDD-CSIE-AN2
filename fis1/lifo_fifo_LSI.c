#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

//LSI
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
};

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
	if ((*cap) == NULL)
		*cap = nou;
	else
	{
		Nod* aux = *cap;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nou;
	}
}

//TRAVERSARE //EXTRAGERE INCEPUT
Carte pop(Nod** stiva)
{
	if (*stiva == NULL)
		return initCarte(NULL, 0, 0);
	//shallow copy
	Carte c = (*stiva)->info;
	Nod* copie = *stiva;
	(*stiva) = (*stiva)->next;
	free(copie);
	return c;

	//deep copy
	Carte c = initCarte((*stiva)->info.titlu, );
	Nod* copie = *stiva;
	(*stiva) = (*stiva)->next;
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


void CoadaInVecotr(Nod** coada, Carte** vectorCarti, int nrCarti)
{
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*coada != NULL)
	{
		(*vectorCarti)[i] = pop(coada);
		i++;
	}
}

void VectorInStiva(Carte* vectorCarti, int nrCarti, Nod** stiva)
{
	for (int i = 0; i < nrCarti; i++)
		inserareInceput(stiva, vectorCarti[i]);
}

void StivaInCoada(Nod** stiva, Nod** coada)
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
		inserareSfarsit(coada, c);
	}
}

void CoadaInStiva(Nod** coada, Nod** stiva)
{
	while (*coada != NULL)
	{
		Carte c = pop(coada);
		inserareInceput(stiva, c);
	}
}