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
	Nod* prev;
};

//LISTA DUBLA INL
void inserareLaInceput(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	nou->prev = NULL;
	if ((*cap) == NULL)
		*cap = *coada = nou;
	else
	{
		(*cap)->prev = nou;
		*cap = nou;
	}
}
void inseareLaSfarsit(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = *coada;
	if ((*cap) == NULL)
		*cap = *coada = nou;
	else
	{
		(*coada)->next = nou;
		*coada = nou;
	}
}

void inserareIntre(Nod* aux, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = NULL;
	if (aux->next == NULL)
	{
		aux->next = nou;
		nou->prev = aux;
		*coada = nou;
	}
	else
	{
		nou->next = aux->next;
		nou->prev = aux;
		
		aux->next->prev = nou;
		aux->next = nou;
	}

}

void inseareDupaPret(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = NULL;
	if ((*cap) == NULL)
		*cap = *coada = nou;
	else if (c.pret < (*cap)->info.pret)
	{
		nou->next = *cap;
		(*cap)->prev = nou;
		*cap = nou;
	}
	else if (c.pret >= (*coada)->info.pret)
	{
		nou->prev = *coada;
		(*coada)->next = nou;
		*coada = nou;
	}
	else
	{
		Nod* aux = *cap;
		while (aux->next != NULL && aux->next->info.pret < c.pret)
			aux = aux->next;
		
		nou->next = aux->next;
		nou->prev = aux;

		aux->next->prev = nou;
		aux->next = nou;
	}
}

Nod* stergereNod(Nod* cap, Nod** coada, char* titlu_c)
{
	Nod* aux = cap;
	while (aux != NULL)
	{
		if (strcmp(aux->info.titlu, titlu_c) == 0)
		{
			//daca nodul nu e primul
			if (aux->prev!=NULL)
				aux->prev->next = aux->next; //sarim peste nodul de sters
			else
				cap = aux->next; //mutam capul listei

			//daca nodul nu e ultimul
			if (aux->next!=NULL)
				aux->next->prev = aux->prev; //legam nodul urmator la cel anterior
			else
				*coada = aux->prev; 

			free(aux->info.titlu);
			free(aux);
			break;
		}
		aux = aux->next;
	}
	return cap;
}



Nod* stergerePoz(Nod* cap, Nod** coada, int poz)
{
	if (cap==NULL)return NULL;
	Nod* aux = cap;
	int i = 0;
	while (aux != NULL && i < poz)
	{
		aux = aux->next;
		i++;
	}
	
	if (aux == NULL)return cap;
	
	if (aux->prev != NULL)
		aux->prev->next = aux->next;
	else
		cap = aux->next; 

	if (aux->next != NULL)
		aux->next->prev = aux->prev;
	else
		*coada = aux->prev;
	free(aux->info.titlu);
	free(aux);

	return cap;
}

void inseareInceputCiruclar(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if ((*cap) == NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		*cap = *coada = nou;
	}
	else
	{
		nou->next = *cap;
		nou->prev = *coada;

		(*cap)->prev = nou;
		(*coada)->next = nou;
		*cap = nou;
	}
}

void inseareSfarsitCircular(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if ((*cap) == NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		*cap = *coada = nou;
	}
	else
	{
		nou->next = *cap;
		nou->prev = *coada;

		(*cap)->prev = nou;
		(*coada)->next = nou;
		*coada = nou;
	}
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
	printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);

}

//de la st la dr
void afisareListaCarti(Nod* cap)
{
	while (cap != NULL)
	{
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

//de la dr la stanga
void afisareinveraListaCarti(Nod* coada)
{
	while (coada != NULL)
	{
		afisareCarte(coada->info);
		coada = coada->prev;
	}
}

void afisareListaCirculara(Nod* cap)
{
	if (!cap)return;
	Nod* aux = cap;
	do
	{
		afisareCarte(cap->info);
		cap = cap->next;
	} while (cap != aux);
}

void dezalocare(Nod** cap, Nod** coada)
{
	while ((*cap) != NULL)
	{
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
	*coada = NULL;
}

float pretMediuCarte(Nod* cap)
{
	int nr = 0;
	float s = 0;
	while (cap != NULL)
	{
		s += cap->info.pret;
		nr++;
		cap = cap->next;
	}
	return s / nr;

}

float pretMaxim(Nod* cap)
{
	if (!cap)return 0;
	float max = cap->info.pret;
	Nod* aux = cap->next;
	while (aux != NULL)
	{
		if (aux->info.pret > max)
		{
			max = aux->info.pret;
		}
		aux = aux->next;
	}
	return max;
}

//CONVERSIE VECTOR ->LSI
Nod* vectorTOLSI(Carte v[], int n)
{
	Nod* cap = NULL;
	for (int i = n - 1; i >= 0; i--)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = v[i];
		nou->next = cap;
		cap = nou;
	}
	return cap;
}

int lsiToVector(Nod* cap, Carte v[])
{
	int n = 0;
	while (cap != NULL)
	{
		v[n++] = cap->info;
		cap = cap->next;
	}
	return n;
}

void lsiTOLDI(Nod* lsi, Nod** cap, Nod** coada)
{
	*cap = *coada = NULL;
	while (lsi != NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = lsi->info;
		nou->next = NULL;
		nou->prev = *coada;

		if ((*coada) != NULL)
			(*coada)->next = nou;
		else
			*cap = nou;
		*coada = nou;
		lsi = lsi->next;
	}
}

Nod* lditoLSI(Nod* cap)
{
	Nod* h = NULL;
	Nod* t = NULL;
	while (cap != NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = cap->info;
		nou->next = NULL;
		if (t != NULL)
			t->next = nou;
		else
			h = nou;
		t = nou;
		cap = cap->next;
	}
	return h;
}