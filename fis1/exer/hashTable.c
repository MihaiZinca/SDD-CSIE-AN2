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
	Nod* prev; //pt ldi
};

typedef struct HashTable HashTable;
struct HashTable
{
	Nod** vector;
	int size;
};

void inserareSfarsit(Nod** cap, Carte c)
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
	printf("Titlu %s, nrPaigni: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
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
	for (int i = 0; i < dim; i++)
		tabela.vector[i] = NULL;
	return tabela;
}

int hash(int nrPagini, int size)
{
	return nrPagini % size;
}
//tratare coliziunii
void inserareinTabela(HashTable tabela, Carte c)
{
	if (tabela.size > 0)
	{
		int pozitie = hash(c.nrPagini, tabela.size);
		if (pozitie >= 0 && pozitie < tabela.size)
			inserareSfarsit(&(tabela.vector[pozitie]), c);
	}
}

void parcurgereTabela(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		afisareListaCarti(tabela.vector[i]);
}

void dezalocareTabela(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		dezalocare(&(tabela.vector[i]));
	free(tabela.vector);
}

float calculPretMediu(HashTable tabela, int nrPagini)
{
	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz];

	float s = 0;
	int nr = 0;
	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
		{
			s += cap->info.pret;
			nr++;
		}
		cap = cap->next;
	}
	return s / nr;
}

void stergere(HashTable tabela, int nrPagini)
{
	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz];
	Nod* prev = NULL;
	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
		{
			if (prev == NULL)
				tabela.vector[poz] = cap->next;
			else
				prev->next = cap->next;
			free(cap->info.titlu);
			free(cap);
			return;
		}
		prev = cap;
		cap = cap->next;
	}
}

void steregeTot(HashTable tabela, int nrPagini)
{
	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz];
	Nod* prev = NULL;
	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
		{
			Nod* sters = cap;
			if (prev == NULL)
				tabela.vector[poz] = cap->next;
			else
				prev->next = cap->next;

			cap = cap->next;
			free(sters->info.titlu);
			free(sters);
			
		}
		else
		{
			prev = cap;
			cap = cap->next;
		}
	}
}


HashTable vectorToHash(Carte* v, int n, int size)
{
	HashTable tabela = initTable(size);
	for (int i = 0; i < n; i++)
		inserareinTabela(tabela, v[i]);
	return tabela;
}

Carte* hashToVector(HashTable tabela, int* nrElem)
{
	int nr = 0;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			nr++;
			cap = cap->next;
		}
	}
	Carte* vector = (Carte*)malloc(sizeof(Carte) * nr);
	int n = 0;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			vector[n++] = cap->info;
			cap = cap->next;
		}
	}
	*nrElem = nr;
	return vector;
}


HashTable lsiToHash(Nod* lsi, int size)
{
	HashTable tabela = initTable(size);
	while (lsi != NULL)
	{
		inserareinTabela(tabela, lsi->info);
		lsi = lsi->next;
	}
	return tabela;
}

Nod* hashToLsi(HashTable tabela)
{
	Nod* lsi = NULL;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			inserareSfarsit(&lsi, cap->info);
			cap = cap->next;
		}
	}
	return lsi;
}


HashTable ldiToHash(Nod* ldi, int size)
{
	HashTable tabela = initTable(size);
	while (ldi != NULL)
	{
		inserareinTabela(tabela, ldi->info);
		ldi = ldi->next;
	}
	return tabela;
}

Nod* hashToLdi(HashTable tabela)
{
	Nod* cap = NULL;
	Nod* coada = NULL;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* p = tabela.vector[i];
		while (p != NULL)
		{
			Nod* nou = (Nod*)malloc(sizeof(Nod));
			nou->info = p->info;
			nou->next = NULL;
			nou->prev = coada;
			
			if (cap == NULL)
				cap = nou;
			else
				coada->next = nou;

			coada = nou;
			p = p->next;
		}
	}
	return cap;
}

void inserareInceput(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}

HashTable stivaToHash(Nod* stiva, int size)
{
	HashTable tabela = initTable(size);
	while (stiva != NULL)
	{
		inserareinTabela(tabela, stiva->info);
		stiva = stiva->next;
	}
	return tabela;
}

Nod* hashToStiva(HashTable tabela)
{
	Nod* stiva = NULL;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			inserareInceput(&stiva, cap->info);
			cap = cap->next;
		}
	}
	return stiva;
}

HashTable coadaToHash(Nod* coada, int size)
{
	HashTable tabela = initTable(size);
	while (coada != NULL)
	{
		inserareinTabela(tabela, coada->info);
		coada = coada->next;
	}
	return tabela;
}

Nod* hashToCoada(HashTable tabela)
{
	Nod* coada = NULL;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			inserareSfarsit(&coada, cap->info);
			cap = cap->next;
		}
	}
	return coada;
}

int main()
{
	// creare vector de carti
	Carte v[5];
	v[0] = initCarte("Ion", 300, 45.5);
	v[1] = initCarte("Morometii", 400, 50);
	v[2] = initCarte("Baltagul", 300, 35);
	v[3] = initCarte("Enigma Otiliei", 500, 60);
	v[4] = initCarte("Amintiri", 300, 25);

	// creare tabela hash
	HashTable tabela = vectorToHash(v, 5, 3);

	printf("\n--- Tabela initiala ---\n");
	parcurgereTabela(tabela);

	// calcul medie pret
	float medie = calculPretMediu(tabela, 300);
	printf("\nPret mediu pentru 300 pagini: %.2f\n", medie);

	// stergere un element
	stergere(tabela, 400);
	printf("\n--- Dupa stergere (400 pagini) ---\n");
	parcurgereTabela(tabela);

	// stergere toate cu 300 pagini
	steregeTot(tabela, 300);
	printf("\n--- Dupa stergere toate (300 pagini) ---\n");
	parcurgereTabela(tabela);

	// conversie in vector
	int nrElem = 0;
	Carte* vector = hashToVector(tabela, &nrElem);

	printf("\n--- Vector rezultat ---\n");
	for (int i = 0; i < nrElem; i++)
	{
		afisareCarte(vector[i]);
	}
	dezalocareTabela(tabela);
	free(vector);

	Nod* stiva = NULL;
	inserareInceput(&stiva, initCarte("Ion", 300, 45.5));
	inserareInceput(&stiva, initCarte("Morometii", 400, 50));
	inserareInceput(&stiva, initCarte("Baltagul", 300, 35));
	inserareInceput(&stiva, initCarte("Enigma Otiliei", 500, 60));

	HashTable tabela1 = stivaToHash(stiva, 3);
	parcurgereTabela(tabela1);
	

	return 0;
}