#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

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


void inserareLaInceput(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}

void inserareLaSfarist(Nod** cap, Carte c)
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

void inserareInceputCircular(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if (*cap == NULL)
	{
		nou->next = nou;
		*cap = nou;
	}
	else
	{
		Nod* aux = *cap;
		while (aux->next != *cap)
			aux = aux->next;

		nou->next = *cap;
		aux->next = nou;
		*cap = nou;
	}
}

void inserareSfarsitCircular(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if (*cap == NULL)
	{
		nou->next = nou;
		*cap = nou;
	}
	else
	{
		Nod* aux = *cap;
		while (aux->next != *cap)
			aux = aux->next;

		nou->next = *cap;
		aux->next = nou;
	}
}

void inserareDupaPret(Nod** cap, Carte c)
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
		if (c.pret < (*cap)->info.pret) //inserare la inceput
		{
			nou->next = *cap;
			*cap = nou;
		}
		else
		{
			Nod* aux = *cap;
			while (aux->next != NULL && aux->next->info.pret < c.pret)
				aux = aux->next;
			nou->next = aux->next;
			aux->next = nou;
		}
	}
}
Nod* stergereNod(Nod* p, char* titlu_cautat)
{
	Nod* t = p;
	//daca nodul cautat este primul
	if (strcmp(p->info.titlu, titlu_cautat) == 0)
	{
		t = p->next;
		free(p->info.titlu);
		free(p);

		return t;
	}

	while (t->next != NULL)
	{
		if (strcmp(t->next->info.titlu, titlu_cautat) == 0)
		{
			Nod* de_sters = t->next;
			t->next = de_sters->next;

			free(de_sters->info.titlu);
			free(de_sters);
		}

		t = t->next;
	}

	return p;
}


void afisareListaCirculara(Nod* cap)
{
	if (!cap)
	{
		return;
	}
	Nod* aux = cap;
	do
	{
		afisareCarte(cap->info);
		cap = cap->next;
	} while (cap != aux);
}

Carte citireCarte(FILE* file)
{
	char buffer[30];
	Carte c;
	fscanf(file, "%29s %d %f", buffer, &c.nrPagini,&c.pret);
	
	c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(c.titlu, buffer);
	return c;
}

void afisareCarte(Carte c)
{
	printf("Titlu:%s, nrPagini:%d, pret:%f\n", c.titlu, c.nrPagini, c.pret);
}

Nod* citireListaCarti(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	if (!file)
	{
		printf("eroare la deschiderea fis");
		return NULL;
	}

	Nod* cap = NULL;
	inserareLaInceput(&cap, citireCarte(file));
	fclose(file);
	return cap;
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

int main()
{
	Nod* cap = citireListaCarti("carti.txt");

	afisareListaCarti(cap);

	dezalocare(&cap);

	return 0;
}
