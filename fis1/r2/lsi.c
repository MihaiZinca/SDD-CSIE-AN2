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

void inserareInceputLSI(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}

void inserareSfarsitLSI(Nod** cap, Carte c)
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
void inseareInceputCircular(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if ((*cap) == NULL)
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

void inseareSfarsitCircular(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if ((*cap) == NULL)
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

void afisarelistaCirculara(Nod* cap)
{
	if (!cap)return;
	Nod* aux = cap;
	do
	{
		afisareCarte(cap->info);
		cap = cap->next;

	} while (cap != aux);
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
void cautareTitlu(Nod* cap, const char* titlu)
{
	while (cap != NULL)
	{
		if (strcmp(cap->info.titlu, titlu) == 0)
		{
			printf("%s", cap->info.titlu);
		}
		cap = cap->next;
	}
	return NULL;
}

float pretMax(Nod* cap)
{
	if (!cap)return 0;
	float max = cap->info.nrPagini;
	Nod* aux = cap->next;
	while (aux != NULL)
	{
		if (aux->info.pret > max)
			max = aux->info.pret;
		aux = aux->next;
	}
	return max;
}

void stergereNoduri(Nod* cap, const char* titlu)
{
	while (cap != NULL && strcmp(cap->info.titlu, titlu) == 0)
	{
		Nod* t = cap;
		cap = cap->next;
		free(t->info.titlu);
		free(t);
	}
	Nod* aux = cap;
	while (aux != NULL && aux->next != NULL)
	{
		if (strcmp(aux->next->info.titlu, titlu) == 0)
		{
			Nod* sters = aux->next;
			aux->next = sters->next;
			free(sters->info.titlu);
			free(sters);
		}
		else
		{
			aux = aux->next;
		}
	}
}

Carte citireCarte(FILE* file)
{
	char buffer[30];
	Carte c;
	fscanf(file, "%s %d %f", buffer, &c.nrPagini, &c.pret);
	c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(c.titlu, buffer);
	return c;
}

Nod* afisareListaCarti(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	if (!file)
	{
		printf("eroare");
		return;
	}
	Nod* cap = NULL;
	while (!feof(file))
	{
		Carte c = citireCarte(file);
		inserareInceput(&cap, c);
	}
	fclose(file);
	return cap;
}

void afisareCarte(Carte carte)
{
	printf("Titlu %s, pagini %d, pret%f", carte.titlu, carte.nrPagini, carte.pret);
}

void afisareListaCarti(Nod* cap)
{
	while (cap != NULL)
	{
		afisareCarte(cap->info);
		cap = cap->next;
	}
}


int lsiToVector(Nod* lsi, Carte v[])
{
	int n = 0;
	while (lsi != NULL)
	{
		v[n++] = lsi->info;
		lsi = lsi->next;
	}
}

Nod* vectorToLsi(Carte v[], int n)
{
	Nod* lsi = NULL;
	for (int i = n - 1; i >= 0; i++)
		inserareInceputLSI(&lsi, v[i]);
	return lsi;
}

