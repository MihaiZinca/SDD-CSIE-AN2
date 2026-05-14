#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carte
{
	int id;
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

typedef struct HashTable HashTable;
struct HashTable
{
	Nod** vector;//vector de liste
	int size;
};

void inserareSfarist(Nod** cap, Carte c)
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

Carte initCarte(int id, const char* titlu, int nrPagini, float pret)
{
	Carte c;
	c.id = id;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);
	return c;
}

void afisareCarte(Carte carte)
{
	printf("Id:%d, Titlu:%s, nrPagini:%d, pret:%f", carte.id, carte.titlu, carte.nrPagini, carte.pret);
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

HashTable initTable(int dim)
{
	HashTable tabela;
	tabela.size = dim;
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < tabela.size; i++)
		tabela.vector[i] = NULL;
	return tabela;
}

int hash(int nrPagini, int size)
{
	return nrPagini % size;
}

//tratarea coliziunii
void inserareInHash(HashTable tabela, Carte c)
{
	if (tabela.size > 0)
	{
		int poz = hash(c.nrPagini, tabela.size);
		if (poz >= 0 && poz < tabela.size)
			inserareSfarist(&(tabela.vector[poz]), c);
	}
}

void afisareHash(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		afisareListaCarti(tabela.vector[i]);

}

void dezalocareHash(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		dezalocare(&(tabela.vector[i]));
	free(tabela.vector);
}

Carte cautareCarte(HashTable tabela, int nrPagini)
{
	Carte c;
	c.id = 0;
	c.nrPagini = 0;
	c.pret = 0;
	c.titlu = NULL;

	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz];
	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
			return cap->info;
		cap = cap->next;
	}
	return c;
}