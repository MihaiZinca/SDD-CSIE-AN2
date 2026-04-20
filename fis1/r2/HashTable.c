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

typedef struct HashTable HashTable;
struct HashTable
{
	Nod** vector; //vector de liste
	int size;
};

void inseareSfarsit(Nod** cap, Carte c)
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

Carte citireCarte(FILE* file)
{
	char buffer[30];
	Carte c;
	fscanf(file, "%s %d %f", buffer, &c.nrPagini, &c.pret);
	c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(c.titlu, buffer);
	return c;
}
Nod* citireCarti(const char* numeFisier)
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
		inseareSfarsit(&cap, c);
	}
	fclose(file);
	return cap;
}

void afisareCarte(Carte carte)
{
	printf("Titlu %s, pagini %d, pret%f", carte.titlu, carte.nrPagini, carte.pret);
}

void afisareLista(Nod* cap)
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
	for (int i = 0; i < tabela.size; i++)
		tabela.vector[i] = NULL;
	return tabela;
}

int hash(int nrPagini, int size)
{
	return nrPagini % size;
}

//tratare coliziunii
void inseareInHashTable(HashTable tabela,Carte c)
{
	if (tabela.size > 0)
	{
		int poz = hash(c.nrPagini, tabela.size);
		if (poz >= 0 && poz < tabela.size)
			inseareSfarsit(&(tabela.vector[poz]),c);
	}
}

void afisareHashTable(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		afisareLista(tabela.vector[i]);
}

void dezalocareHashTable(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		dezalocare(&(tabela.vector[i]));
	free(tabela.vector);
}

Carte cautareCarte(HashTable table, int nrPagini)
{
	Carte c;
	c.nrPagini = 0;
	c.pret = 0;
	c.titlu = NULL;

	int poz = hash(nrPagini, table.size);
	Nod* cap = table.vector[poz];
	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
			return cap->info;
		cap = cap->next;
	}
	return c;
}

float pretmediuCarteX(HashTable tabela, int nrPagini)
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

void stergereNoduri(HashTable tabela, int nrPagini)
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
	Carte* v = (Carte*)malloc(sizeof(Carte) * nr);
	int n = 0;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			v[n++] = cap->info;
			cap = cap->next;
		}
	}
	*nrElem = nr;
	return v;
}

HashTable vectorToHash(Carte v[], int n, int size)
{
	HashTable tabela = initTable(size);
	for (int i = 0; i < n; i++)
		inseareInHashTable(tabela, v[i]);
	return tabela;
}


HashTable lsiToHash(Nod* lsi, int size)
{
	HashTable tabela = initTable(size);
	while (lsi != NULL)
	{
		inseareInHashTable(tabela, lsi->info);
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
			inseareSfarsit(&lsi, cap->info);
			cap = cap->next;
		}
	}
	return lsi;
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


HashTable ldiToHash(Nod* ldi, int size)
{
	HashTable tabela = initTable(size);
	while (ldi != NULL)
	{
		inseareInHashTable(tabela, ldi->info);
		ldi = ldi->next;
	}
	return tabela;
}
Nod* hashToLdi(HashTable tabela)
{
	Nod* ldi = NULL;
	Nod* sfarsit = NULL;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			inserareSfarsitLDI(&ldi, &sfarsit, cap->info);
			cap = cap->next;
		}
	}
	return ldi;
}



void inserareInceput(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}

HashTable stivatoHash(Nod* stiva, int size)
{
	HashTable tabela = initTable(size);
	while (stiva != NULL)
	{
		inseareInHashTable(tabela, stiva->info);
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
		inseareInHashTable(tabela, coada->info);
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
			inseareSfarsit(&coada, cap->info);
			cap = cap->next;
		}
	}
	return coada;
}

int main()
{
	Nod* lsi = citireCarti("carti.txt");
	afisareLista(lsi);

	HashTable tabela = lsiToHash(lsi, 5);
}