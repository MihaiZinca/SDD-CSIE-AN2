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
struct Nod {
	Carte info;
	Nod* next;
};

//LSI

void inserareInceput(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}

void inserareSfarsit(Nod** cap, Carte c)
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

void inserareInceputCiruclar(Nod** cap, Carte c)
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

void inserareSfarsitCiruclar(Nod** cap, Carte c)
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
		*cap = nou;
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
			while (aux->next != NULL && aux->next->info.pret < c.pret)
				aux = aux->next;

			nou->next = aux->next;
			aux->next = nou;
		}
	}
}

Nod* stergereNoduri(Nod* cap, char* titlu)
{
	Nod* aux = cap;
	if (strcmp(cap->info.titlu, titlu) == 0)
	{
		aux = cap->next;
		free(cap->info.titlu);
		free(cap);
		return aux;
	}

	while (aux!=NULL && aux->next != NULL)
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
		aux = aux->next; i++;
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
	if (!file)
	{
		printf("eroare deschiere");
		return NULL;
	}
	Nod* cap = NULL;
	citireCarte(&cap, citireCarte(file));
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

void modificarePret(Nod* cap, const char* titlu, float pretNou)
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

Nod* vectorToLsi(Carte v[], int n)
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

int main()
{
	Nod* cap=NULL;

	Carte c1;
	c1.titlu = (char*)malloc(strlen("Ion") + 1);
	strcpy(c1.titlu, "Ion");
	c1.nrPagini = 300;
	c1.pret = 45.5;

	Carte c2;
	c2.titlu = (char*)malloc(strlen("Morometii") + 1);
	strcpy(c2.titlu, "Morometii");
	c2.nrPagini = 250;
	c2.pret = 60;

	Carte c3;
	c3.titlu = (char*)malloc(strlen("Ion") + 1);
	strcpy(c3.titlu, "Ion");
	c3.nrPagini = 200;
	c3.pret = 35;

	inserareInceput(&cap, c1);
	inserareInceput(&cap, c2);

	inserareSfarsit(&cap, c3);

	printf("\nLista initiala:\n");
	afisareListaCarti(cap);

	
	Carte c4;
	c4.titlu = (char*)malloc(strlen("Enigma") + 1);
	strcpy(c4.titlu, "Enigma");
	c4.nrPagini = 400;
	c4.pret = 50;

	inserareDupaPret(&cap, c4);

	printf("\n\nDupa inserare dupa pret:\n");
	afisareListaCarti(cap);

	// Stergere dupa titlu
	cap = stergereNod(cap, "Ion");

	printf("\n\nDupa stergere 'Ion':\n");
	afisareListaCarti(cap);

	// Stergere dupa pozitie
	cap = stergerePoz(cap, 1);

	printf("\n\nDupa stergere pozitia 1:\n");
	afisareListaCarti(cap);

	// Pret maxim
	float max = pretMax(cap);
	printf("\n\nPret maxim: %.2f\n", max);

	char* titluGasit = afisareTitlu(cap, max);
	if (titluGasit)
	{
		printf("titlu cu pret max", titluGasit);
		free(titluGasit);
	}

	Carte v[10];
	int n = lsiToVector(cap, v);

	for (int i = 0; i < n; i++)
	{
		afisareCarte(v[i]);
	}
	Nod* cap2 = vectorToLsi(v, n);
	afisareListaCarti(cap2);

	dezalocare(&cap);
	dezalocare(&cap2);

	return 0;
}
