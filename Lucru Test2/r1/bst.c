#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<string.h>

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
	Nod* stanga;
	Nod* dreapta;
};

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

void afisareCarte(Carte carte) {
	printf("Id:%d, Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.id, carte.titlu, carte.nrPagini, carte.pret);
}

//parcurgeri

void inordine(Nod* rad)
{
	if (rad)
	{
		//srd
		inordine(rad->stanga);
		afisareCarte(rad->info);
		inordine(rad->dreapta);
	}
}

void preordine(Nod* rad)
{
	if (rad)
	{
		//rsd
		afisareCarte(rad->info);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

void postordine(Nod* rad)
{
	if (rad)
	{
		//sdr
		postordine(rad->stanga);
		postordine(rad->dreapta);
		afisareCarte(rad->info);
	}
}

void dezalocare(Nod** rad)
{
	if (*rad != NULL)
	{
		dezalocare(&(*rad)->stanga);
		dezalocare(&(*rad)->dreapta);
		free((*rad)->info.titlu);
		free(*rad);
	}
}

Carte cautareDupaId(Nod* rad, int id)
{
	if (rad == NULL)
		return initCarte(-1, "necunoscut", 0, 0);
	else if (id == rad->info.id)
		return initCarte(rad->info.id, rad->info.titlu, rad->info.nrPagini, rad->info.pret);
	else if (id < rad->info.id)
		return cautareDupaId(rad->stanga, id);
	else
		return cautareDupaId(rad->dreapta, id);
}

void rotireStanga(Nod** rad)
{
	Nod* aux = (*rad)->dreapta;
	(*rad)->dreapta = aux->stanga;
	aux->stanga = *rad;
	*rad = aux;
}

void rotireDreapta(Nod** rad)
{
	Nod* aux = (*rad)->stanga;
	(*rad)->stanga = aux->dreapta;
	aux->dreapta = *rad;
	*rad = aux;
}

int maxim(int a, int b)
{
	return (a > b ? a : b);
}

int calculInaltimeArbore(Nod* rad)
{
	if (rad)
		return maxim(calculInaltimeArbore(rad->stanga), calculInaltimeArbore(rad->dreapta))+1;
	return 0;
}
int diferentaInaltimeSubarbori(Nod* rad)
{
	if (rad)
		return calculInaltimeArbore(rad->stanga) - calculInaltimeArborei(rad->dreapta);
	return 0;
}

void echilibare(Nod** radacina)
{
	if (*radacina == NULL)
		return;

	int dif = diferentaInaltimeSubarbori(*radacina);
	if (dif == 2)
	{
		if (diferentaInaltimeSubarbori((*radacina)->stanga) == -1)
			rotireStanga(&(*radacina)->stanga);
		rotireDreapta(radacina);
	}
	if (dif == -2)
	{
		if (diferentaInaltimeSubarbori((*radacina)->dreapta) == 1)
			rotireDreapta(&(*radacina)->dreapta);
		rotireStanga(radacina);
	}
}

void inseareInBST(Nod** radacina, Carte c)
{
	if (*radacina == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = c;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
	else if (c.id < (*radacina)->info.id)
		return inseareInBST(&(*radacina)->stanga, c);
	else
		return inseareInBST(&(*radacina)->dreapta, c);
	echilibare(radacina);
}

Nod* stergere(Nod* rad, int id)
{
	if (rad == NULL)
		return NULL;
	
	if (id < rad->info.id)
		rad->stanga = stergere(rad->stanga, id);
	else if (id > rad->info.id)
		rad->dreapta = stergere(rad->dreapta, id);
	else
	{
		if (rad->stanga == NULL || rad->dreapta == NULL)
		{
			Nod* aux;
			if (rad->stanga != NULL)
				aux = rad->stanga;
			else
				aux = rad->dreapta;
			free(rad->info.titlu);
			free(rad);
			return aux;
		}

		Nod* aux = rad->dreapta;
		while (aux->stanga != NULL)
			aux = aux->stanga;

		free(rad->info.titlu);
		rad->info = initCarte(aux->info.id, aux->info.titlu, aux->info.nrPagini, aux->info.pret);
		rad->dreapta = stergere(rad->dreapta, aux->info.id);
	}
	echilibare(&rad);
	return rad;
}