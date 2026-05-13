#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte {
	int id;
	char* titlu;
	int nrPagini;
	float pret;
} Carte;

typedef struct Nod Nod;
struct Nod {
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
	printf("Id:%d, Titlu: %s, nrPagini: %d, pret: %.2f. \n",carte.id, carte.titlu, carte.nrPagini, carte.pret);
}

void inserareInABC(Nod** radacina, Carte c)
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
	{
		inserareInABC(&(*radacina)->stanga, c);
	}
	else
	{
		inserareInABC(&(*radacina)->dreapta, c);
	}
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
	{
		return initCarte(rad->info.id, rad->info.titlu, rad->info.nrPagini, rad->info.pret);
	}
	else if (id < rad->info.id)
	{
		return cautareDupaId(rad->stanga, id);
	}
	else
	{
		return cautareDupaId(rad->dreapta, id);
	}
}

void afisareFrunze(Nod* rad)
{
	if (rad != NULL)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL)
		{
			afisareCarte(rad->info);
		}
		afisareFrunze(rad->stanga);
		afisareFrunze(rad->dreapta);
	}
}

Nod* stergere(Nod* rad, int id)
{
	if (rad == NULL)
		return NULL;

	if (id < rad->info.id)
	{
		rad->stanga = stergere(rad->stanga, id);
	}
	else if(id>rad->info.id)
	{ 
		rad->dreapta = stergere(rad->dreapta, id);
	}
	else
	{
		// 0 sau 1 copil
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

		//2 copii
		Nod* aux = rad->dreapta;
		while (aux->stanga != NULL) //cautam minim din dreapta
		{
			aux = aux->stanga;
		}

		free(rad->info.titlu);
		rad->info = initCarte(aux->info.id, aux->info.titlu, aux->info.nrPagini, aux->info.pret);
		rad->dreapta = stergere(rad->dreapta, aux->info.id);
	}
	return rad;
}

