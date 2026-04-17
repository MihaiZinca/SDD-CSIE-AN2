#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

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

void inseareInceput(Nod** cap, Nod** sfarist, Carte c) //PUSH
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	nou->prev = NULL;
	if ((*cap) == NULL)
		*cap = *sfarist = nou;
	else
	{
		(*cap)->prev = nou;
		*cap = nou;
	}
}

void inserareFinal(Nod** cap, Nod** sfarsit, Carte c) //PUT
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

//traversare/extragere inecput
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

Carte initCarte(const char* titlu, int nrPagini, float pret)
{
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);
	return c;
}

void afisareCarte(Carte carte) {
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

void stergeNodStiva(Nod** cap, Nod** sfasrit, const char* titlu)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	while (*cap != NULL)
	{
		Carte c = pop(cap, sfasrit);
		if (strcmp(c.titlu, titlu) != 0)
			inseareInceput(&aux1, &aux2, c);
		else
			free(c.titlu);
	}

	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inseareInceput(cap, sfasrit, c);
	}
}

void steregereNodCoada(Nod** cap, Nod** sfarsit, const char* titlu)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	while (*cap != NULL)
	{
		Carte c = pop(cap, sfarsit);
		if (strcmp(c.titlu, titlu) != 0)
			inserareFinal(&aux1, &aux2, c);
		else
			free(c.titlu);
	}

	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inserareFinal(cap, sfarsit, c);
	}
}


void stivaInVector(Nod** stiva,Nod**sfarsit,Carte** vectorCarti, int nrCarti)
{
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*stiva != NULL)
	{
		(*vectorCarti)[i] = pop(stiva, sfarsit);
		i++;
	}

}

Nod* vectorInStiva(Carte* vectorCarti, int nrCarti)
{
	Nod* stiva = NULL;
	Nod* sfarsit = NULL;
	for (int i = nrCarti - 1; i >= 0; i--)
		inseareInceput(&stiva, &sfarsit, vectorCarti[i]);

	return stiva;
}

void coadaInVector(Nod** coada,Nod** sfarsit, Carte** vectorCarti, int nrCarti)
{
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*coada != NULL)
	{
		(*vectorCarti)[i] = pop(coada, sfarsit);
		i++;
	}
}

Nod* vectorInCoada(Carte* vectorCarti, int nrCarti)
{
	Nod* coada = NULL;
	Nod* sfarsit = NULL;
	for (int i = 0; i < nrCarti; i++)
		inserareFinal(&coada, &sfarsit, vectorCarti[i]);
	return coada;
}


void stivaInCoada(Nod** stiva, Nod** coada,Nod** sfCoada)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	
	while (*stiva != NULL)
	{
		Carte c = pop(stiva, sfCoada);
		inserareFinal(&aux1, &aux2, c);
	}
	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inserareFinal(coada, sfCoada, c);
	}
}

void coadaInStiva(Nod** coada, Nod** stiva, Nod** sfStiva)
{
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	while (*coada != NULL)
	{
		Carte c = pop(coada, sfStiva);
		inserareFinal(&aux1, &aux2, c);
	}

	while (aux1 != NULL)
	{
		Carte c = pop(&aux1, &aux2);
		inseareInceput(stiva, sfStiva, c);
	}
}