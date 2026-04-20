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
	Nod* prev;
};

void inseareInceputLDI(Nod** cap, Nod** sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	nou->prev = NULL;
	if (*cap == NULL)
		*cap = *sfarsit = nou;
	else
	{
		(*cap)->prev = nou;
		*cap = nou;
	}
}

void inserareSfarsitLDI(Nod** cap, Nod** sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = *sfarsit;
	if (*cap == NULL)
		*cap = *sfarsit = nou;
	else
	{
		(*sfarsit)->next = nou;
		*sfarsit = nou;
	}
}

void inseareInceputCircular(Nod** cap, Nod** sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if (*cap == NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		*cap = *sfarsit = nou;
	}
	else
	{
		nou->next = *cap;
		nou->prev = *sfarsit;
		(*cap)->prev = nou;
		(*sfarsit)->next = nou;
		*cap = nou;
	}
}
void inseareSfarsitCircular(Nod** cap, Nod** sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if (*cap == NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		*cap = *sfarsit = nou;
	}
	else
	{
		nou->next = *cap;
		nou->prev = *sfarsit;
		(*cap)->prev = nou;
		(*sfarsit)->next = nou;
		*sfarsit = nou;
	}
}

char* cautareTitlu(Nod* cap, Nod** sfarsit, float pret)
{
	while (cap != NULL)
	{
		if (cap->info.pret == pret)
		{
			char* copie = (char*)malloc(sizeof(char) * strlen(cap->info.titlu) + 1);
			strcpy(copie, cap->info.titlu);
			return copie;
		}
		cap = cap->next;
	}
	return NULL;
}

void dezalocare(Nod** cap, Nod** sfarsit)
{
	while ((*cap) != NULL)
	{
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
	*sfarsit = NULL;
}

void dezalocare_faraTitlu(Nod** cap)
{
	while ((*cap) != NULL)
	{
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

Nod* stergereNoduri(Nod* cap, Nod** sfarsit, char const* titlu)
{
	Nod* aux = cap;
	while (aux != NULL)
	{
		if (strcmp(aux->info.titlu, titlu) == 0)
		{
			Nod* sters = aux;
			if (aux->prev != NULL)
				aux->prev->next = aux->next;
			else
			{
				cap = aux->next;
				if (cap)aux->prev = NULL;
			}

			if (aux->next != NULL)
				aux->next->prev = aux->prev;
			else
				*sfarsit = aux->prev;

			aux = aux->next;
			free(sters->info.titlu);
			free(sters);
		}
		else
		{
			aux = aux->next;
		}
	}
	return cap;
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
	printf("Titlu %s, pagini %d, pret%f", carte.titlu, carte.nrPagini, carte.pret);
}
//st dr
void afisareListaLDI(Nod* cap)
{
	while (cap != NULL)
	{
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

//dr st
void afisareInversaListaLDI(Nod* sfarsit)
{
	while (sfarsit != NULL)
	{
		afisareCarte(sfarsit->info);
		sfarsit = sfarsit->prev;
	}
}


int ldiToVector(Nod* ldi, Carte c[])
{
	int n = 0;
	while (ldi != NULL)
	{
		c[n++] = ldi->info;
		ldi = ldi->next;
	}
	return n;
}

Nod* vectorToLdi(Carte c[], int n)
{
	Nod* ldi = NULL;
	Nod* sfarsit = NULL;
	for (int i = 0; i < n; i++)
	{
		inserareSfarsitLDI(&ldi, &sfarsit, c[i]);
	}
	return ldi;
}

void lsiToLdi(Nod* lsi, Nod** cap,Nod** coada)
{
	*cap = *coada = NULL;
	while (lsi != NULL)
	{
		inserareSfarsitLDI(cap, coada, lsi->info);
		lsi = lsi->next;
	}
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

void ldiToLsi(Nod* ldi, Nod** cap)
{
	*cap = NULL;
	while (ldi != NULL)
	{
		inserareSfarsitLSI(cap, ldi->info);
		ldi = ldi->next;
	}
}

int main()
{
	Nod* ldi = NULL;
	Nod* sfarsit = NULL;

	Carte c1 = initCarte("Ion", 200, 30);
	Carte c2 = initCarte("Enigma", 300, 45);
	Carte c3 = initCarte("Morometii", 250, 40);
	Carte c4 = initCarte("Baltagul", 180, 25);

	inserareSfarsitLDI(&ldi, &sfarsit, c1);
	inserareSfarsitLDI(&ldi, &sfarsit, c2);
	inserareSfarsitLDI(&ldi, &sfarsit, c3);
	inserareSfarsitLDI(&ldi, &sfarsit, c4);
	
	afisareListaLDI(ldi);

	int x;
	scanf("%d", &x);

	char* titluGasit = cautareTitlu(ldi, &sfarsit, 40);
	if (titluGasit != NULL)
	{
		printf("titlu %s", titluGasit);
		free(titluGasit);
	}

	ldi = stergereNoduri(ldi, &sfarsit,"Ion");
	afisareListaLDI(ldi);

	Carte v[10];
	int n = ldiToVector(ldi, v);
	for (int i = 0; i < n; i++)
		afisareCarte(v[i]);

	Nod* cap = vectorToLdi(v, n);
	afisareListaLDI(cap);

	Nod* lsi = NULL;
	ldiToLsi(ldi, &lsi);
	afisareListaLDI(lsi);

	Nod* lsii = NULL;
	Nod* coada = NULL;
	lsiToLdi(lsi, &lsii, &coada);

	dezalocare(&ldi, &sfarsit);
	dezalocare_faraTitlu(cap);
	dezalocare_faraTitlu(lsi);
	dezalocare_faraTitlu(lsii);

	return 0;
}