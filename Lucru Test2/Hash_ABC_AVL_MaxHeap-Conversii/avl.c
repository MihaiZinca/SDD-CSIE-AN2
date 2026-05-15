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
	Nod* stangda;
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

void afisareCarte(Carte carte)
{
	printf("Id:%d, Titlu:%s, nrPagini:%d, pret:%f", carte.id, carte.titlu, carte.nrPagini, carte.pret);
}

//parcurgeri
void inordine(Nod* rad)
{
	if (rad)
	{
		//srd
		inordine(rad->stangda);
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
		preordine(rad->stangda);
		preordine(rad->dreapta);
	}
}

void postordine(Nod* rad)
{
	if (rad)
	{
		//sdr
		postordine(rad->stangda);
		postordine(rad->dreapta);
		afisareCarte(rad->info);
	}
}

void dezalocare(Nod** rad)
{
	if (*rad != NULL)
	{
		dezalocare(&(*rad)->stangda);
		dezalocare(&(*rad)->dreapta);
		free((*rad)->info.titlu);
		free(*rad);
	}
}

Carte cautareDupaId(Nod* rad, int id)
{
	if (rad == NULL)
		return initCarte(-1, "ne", 0, 0);
	else if (id == rad->info.id)
		return initCarte(rad->info.id, rad->info.titlu, rad->info.nrPagini, rad->info.pret);
	else if (id < rad->info.id)
		return cautareDupaId(&(*rad).stangda, id);
	else
		return cautareDupaId(&(*rad).dreapta, id);
}

void rotireStanga(Nod** rad)
{
	Nod* aux = (*rad)->dreapta;
	(*rad)->dreapta = aux->stangda;
	aux->stangda = *rad;
	*rad = aux;
}

void rotireDreapta(Nod** rad)
{
	Nod* aux = (*rad)->stangda;
	(*rad)->stangda = aux->dreapta;
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
		return maxim(calculInaltimeArbore(rad->stangda),calculInaltimeArbore(rad->dreapta))+1;
	return 0;
}

int diferentaInaltimeSubarbori(Nod* rad)
{
	if (rad)
		return calculInaltimeArbore(rad->stangda) - calculInaltimeArbore(rad->dreapta);
	return 0;
}

void echilibare(Nod** rad)
{
	if (*rad == NULL)
		return;
	
	int dif = diferentaInaltimeSubarbori((*rad));
	if (dif == 2)
	{
		if (diferentaInaltimeSubarbori((*rad)->stangda) == -1)
			rotireStanga(&(*rad)->stangda);
		rotireDreapta(rad);
	}

	if (dif == -2)
	{
		if (diferentaInaltimeSubarbori((*rad)->dreapta) == 1)
			rotireDreapta(&(*rad)->dreapta);
		rotireStanga(rad);
	}
}

void inserareInBST(Nod** rad, Carte c)
{
	if (*rad == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = c;
		nou->stangda = NULL;
		nou->dreapta = NULL;
		*rad = nou;
	}
	else if (c.id < (*rad)->info.id)
		inserareInBST(&(*rad)->stangda, c);
	else
		inserareInBST(&(*rad)->dreapta, c);
	echilibare(rad);
}

Nod* stergereNoduri(Nod* rad, int id)
{
	if (rad == NULL)
		return;
	if (id < rad->info.id)
		rad->stangda = stergereNoduri(rad->stangda, id);
	else if (id > rad->info.id)
		rad->dreapta = stergereNoduri(rad->dreapta, id);
	else
	{
		if (rad->stangda == NULL || rad->dreapta == NULL)
		{
			Nod* aux;
			if (rad->stangda != NULL)
				aux = rad->stangda;
			else
				aux = rad->dreapta;
			free(rad->info.titlu);
			free(rad);
			return aux;
		}

		Nod* aux = rad->dreapta;
		while (aux->stangda != NULL)
			aux = aux->stangda;

		free(rad->info.titlu);
		rad->info = initCarte(aux->info.id, aux->info.titlu, aux->info.nrPagini, aux->info.pret);
		rad->dreapta = stergereNoduri(rad->dreapta, aux->info.id);
	}
	echilibare(&rad);
	return rad;
}
