#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


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

//LSI

void inserareLaInceput(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}

void inserareLaSfarsit(Nod** cap, Carte c)
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

void inserareInceputCircular(Nod** cap, Carte c)
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

void inserareSfarsitCircular(Nod** cap, Carte c)
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
		if (c.pret < (*cap)->info.pret)
		{
			nou->next = *cap;
			*cap = nou;
		}
		else
		{
			Nod* aux = *cap;
			while (aux->next != NULL && (*cap)->info.pret < c.pret)
				aux = aux->next;

			nou->next = aux->next;
			aux->next = nou;
		}
	}
}

Nod* stergereNod(Nod* cap, char* titlu)
{
	Nod* aux = cap;
	if (strcmp(cap->info.titlu, titlu) == 0)
	{
		aux = cap->next;
		free(cap->info.titlu);
		free(cap);
		return aux;
	}
	while (aux->next != NULL)
	{
		if (strcmp(aux->next->info.titlu, titlu) == 0)
		{
			Nod* sters = aux->next;
			aux->next = sters->next;
			free(sters->info.titlu);
			free(sters);
		}
		aux = aux->next;
	}
	return cap;
}

Nod* stergerePoz(Nod* cap, int poz)
{
	Nod* aux = cap;
	if (cap && poz == 0)
	{
		aux = cap->next;
		free(cap->info.titlu);
		free(cap);
		return aux;
	}
	int i = 0;
	while (aux->next != NULL && i < poz - 1)
	{
		aux = aux->next;
		i++;
	}
	if (aux->next != NULL)
	{
		Nod* sters = aux->next;
		aux->next = sters->next;
		free(sters->info.titlu);
		free(sters);
	}
	return cap;

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

Nod* citireListaCarti(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	if (!file)printf("eroare");
	Nod* cap = NULL;
	inserareLaInceput(&cap, citireCarte(file));
	fclose(file);
	return cap;
}

void afisareCarte(Carte carte)
{
	printf("Titlu %s, pagini %d, pret %f", carte.titlu, carte.nrPagini, carte.pret);
}

void afisareListaCarti(Nod* cap)
{
	while (cap != NULL)
	{
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void afisareListaCirculara(Nod* cap)
{
	if (!cap)return;
	Nod* aux = cap;
	do {
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
float pretMax(Nod* cap)
{
	if (!cap)return 0;
	float max = cap->info.pret;
	Nod* aux = cap->next;
	while (aux != NULL)
	{
		if (aux->info.pret > max)
			max = aux->info.pret;
		aux = aux->next;
	}
	return max;
}

char* afisareTitlu(Nod* cap, float _pret)
{
	while (cap != NULL)
	{
		if (cap->info.pret == _pret)
		{
			char* copie = (char*)malloc(sizeof(char) * (strlen(cap->info.titlu) + 1));
			strcpy(copie, cap->info.titlu);
			return copie;
		}
		cap = cap->next;
	}
	return NULL;
}

void modifcarePret(Nod* cap, const char* titlu, float pretNou)
{
	while (cap != NULL)
	{
		if (strcmp(cap->info.titlu, titlu) == 0)
		{
			cap->info.pret = pretNou;
			return;
		}
		cap = cap->next;
	}
}