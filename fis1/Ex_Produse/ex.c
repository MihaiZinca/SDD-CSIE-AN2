#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct Produs
{
	char* denumire;
	int cantitate;
	float pret;
}Produs;

typedef struct Nod Nod;

struct Nod
{
	Produs info;
	Nod* next;
	Nod* prev;
};


void inseareInceput(Nod** cap, Produs p)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = *cap;
	*cap = nou;
}

void inserareSfarsit(Nod** cap, Produs p)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
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

void dezalocare(Nod** cap)
{
	while (cap != NULL)
	{
		free((*cap)->info.cantitate);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

void afisareProdus(Produs produs)
{
	printf("Denumire %s, canitate %d, pret %f", produs.denumire, produs.cantitate, produs.pret);
}

void afisareLista(Nod* cap)
{
	while (cap != NULL)
	{
		afisareProdus(cap->info);
		cap = cap->next;
	}
}

Nod* cautareDen(Nod* cap, const char* den)
{
	while (cap != NULL)
	{
		if (strcmp(cap->info.denumire, den) == 0)
		{
			return cap;
		}
	}
	return NULL;
}

Nod* stergereNoduriLSI(Nod* cap)
{
	Nod* aux = cap;
	if (cap->info.cantitate == 0)
	{
		aux = cap->next;
		free(cap->info.denumire);
		free(cap);
		return aux;
	}

	while (aux != NULL && aux->next != NULL)
	{
		if (cap->info.cantitate == 0)
		{
			Nod* sters = aux->next;
			aux->next = sters->next;
			free(sters->info.denumire);
			free(sters);
		}
		else
		{
			aux = aux->next;
		}
	}
	return cap;
}

int lsiToVector(Nod* cap, Produs p[])
{
	int n = 0;
	while (cap != NULL)
	{
		p[n++] = cap->info;
		cap = cap->next;
	}
	return n;
}

Nod* vectorToLsi(Produs p[], int n)
{
	Nod* cap = NULL;
	for (int i = n - 1; i >= 0; i--)
	{
		inseareInceput(&cap, p[i]);
	}
	return cap;
}

void inserareInceputLdi(Nod** cap, Nod** coada,Produs p)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = *cap;
	nou->prev = NULL;
	if ((*cap) == NULL)
	{
		*cap = *coada=nou;
	}
	else
	{
		(*cap)->prev = nou;
		*cap = nou;
	}
}

void inserareSfarsitLdi(Nod** cap, Nod** coada, Produs p)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = NULL;
	nou->prev = *coada;
	if ((*cap) == NULL)
	{
		*cap = *coada = nou;
	}
	else
	{
		(*coada)->next = nou;
		*coada = nou;
	}
}

//trv st dr
void afisareListaProdusLDI(Nod* cap)
{
	while (cap != NULL)
	{
		afisareProdus(cap->info);
		cap = cap->next;
	}
}

void afisareInversaListaProdusLDI(Nod* coada)
{
	while (coada != NULL)
	{
		afisareProdus(coada->info);
		coada = coada->prev;
	}
}


void inserareDupaPretLDI(Nod** cap, Nod** coada, Produs p)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = NULL;
	nou->prev = NULL;
	if (*cap == NULL)
		*cap = *coada = nou;
	else if (p.pret < (*cap)->info.pret)
	{
		nou->next = *cap;
		(*cap)->prev = nou;
		*cap = nou;
	}
	else if (p.pret >= (*coada)->info.pret)
	{
		nou->prev = *coada;
		(*coada)->next = nou;
		*coada = nou;
	}
	else
	{
		Nod* aux = *cap;
		while (aux->next != NULL && aux->next->info.pret < p.pret)
			aux = aux->next;

		nou->next = aux->next;
		nou->prev = aux;

		aux->next->prev = nou;
		aux->next = nou;
	}

}

Nod* stergereNodLDI(Nod* cap, Nod** coada, char* denum_c)
{
	Nod* aux = cap;
	while (aux != NULL)
	{
		if (strcmp(aux->info.denumire, denum_c) == 0)
		{
			if (aux->prev != NULL)
				aux->prev->next = aux->next;
			else
				cap = aux->next;

			if (aux->next != NULL)
				aux->next->prev = aux->prev;
			else
				*coada = aux->prev;
			free(aux->info.denumire);
			free(aux);
			break;
		}
		aux = aux->next;
	}
	return cap;
}


int  ldiToVector(Nod* cap, Produs p[])
{
	int n = 0;
	while (cap != NULL)
	{
		p[n++] = cap->info;
		cap = cap->next;
	}
	return n;
}

void lsiToLdi(Nod* lsi, Nod** cap, Nod** coada)
{
	*cap = *coada = NULL;
	while (lsi != NULL)
	{
		inserareSfarsitLdi(cap, coada, lsi->info);
		lsi = lsi->next;
	}
}

void ldiToLsi(Nod* cap, Nod** lsi)
{
	*lsi = NULL;
	while (cap != NULL)
	{
		inserareSfarsit(lsi, cap->info);
		cap = cap->next;
	}
}


//stiva(lifo) -inserare inceput,extragere inceput
//coada(fifo)-inseare final,extragere iceput

void inserareInceputStiva(Nod** cap, Produs p)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = *cap;
	*cap = nou;
}

void inserareSfarsitCoada(Nod** cap, Produs p)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
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

Produs initProdus(const char* denumire, int cantitate, float pret)
{
	Produs p;
	p.cantitate = cantitate;
	p.pret = pret;
	p.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(p.denumire, denumire);
	return p;
}

//Traversare/Extragere inceput
Produs pop(Nod** stiva)
{
	if (*stiva == NULL)
		return initProdus(NULL, 0, 0);

	//sw
	Produs p = (*stiva)->info;
	Nod* copie = *stiva;
	*stiva = (*stiva)->next;
	free(copie);
	return p;

	//dp
	Produs p = initProdus((*stiva)->info.denumire, (*stiva)->info.cantitate, (*stiva)->info.pret);
	Nod* copie = *stiva;
	*stiva = (*stiva)->next;
	free(copie->info.denumire);
	free(copie);
	return p;

}

void stergeNodStiva(Nod** stiva, const char* den)
{
	Nod* aux = NULL;
	while (*stiva != NULL)
	{
		Produs p = pop(stiva);
		if (strcmp(p.denumire, den) != 0)
			inserareInceputStiva(&aux, p);
		else
			free(p.denumire);
	}

	while (aux != NULL)
	{
		Produs p = pop(&aux);
		inserareInceputStiva(stiva, p);
	}
}

void stergeNodCoada(Nod** coada, float pret)
{
	Nod* aux = NULL;
	while (*coada != NULL)
	{
		Produs p = pop(coada);
		if (p.pret < pret)
			inserareSfarsitCoada(&aux, p);
	}
	while (aux != NULL)
	{
		Produs p = pop(&aux);
		inserareSfarsitCoada(coada, p);
	}
}


void stivaToVector(Nod** stiva, Produs p[])
{
	int n = 0;
	while (*stiva != NULL)
	{
		p[n++] = pop(stiva);
		
	}
}

void coadaToVector(Nod** coada, Produs p[])
{
	int n = 0;
	while (*coada != NULL)
	{
		p[n++] = pop(coada);
	}
}

Nod* vectorToStiva(Produs* vectorP, int nrProd)
{
	Nod* stiva = NULL;
	for (int i = nrProd - 1; i >= 0; i--)
		inserareInceputStiva(&stiva, vectorP[i]);
	return stiva;
}

Nod* vectorToCoada(Produs* vectorP, int nrProd)
{
	Nod* coada = NULL;
	for (int i = 0; i < nrProd; i++)
		inserareSfarsitCoada(&coada, vectorP[i]);
	return coada;
}


typedef struct HashTable HashTable;
struct HashTable
{
	Nod** vector;
	int size;
};

HashTable initTable(int dim)
{
	HashTable tabela;
	tabela.size = dim;
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++)
		tabela.vector[i] = NULL;
	return tabela;
}

int hash(int cantitate, int size)
{
	return cantitate % size;
}

void inseareInTabela(HashTable tabela, Produs p)
{
	if (tabela.size > 0)
	{
		int pozitie = hash(p.cantitate, tabela.size);
		if (pozitie >= 0 && pozitie < tabela.size)
			inserareSfarsit(&(tabela.vector[pozitie]), p);
	}
}

void afisareTabela(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		afisareLista(tabela.vector[i]);
}

void dezalocareTabela(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		dezalocare(&(tabela.vector[i]));
	free(tabela.vector);
}

float calculPretMediu(HashTable tablea, int cantitate)
{
	int poz = hash(cantitate, tablea.size);
	Nod* cap = tablea.vector[poz];

	float s = 0;
	int nr = 0;
	while (cap != NULL)
	{
		if (cap->info.cantitate == cantitate)
		{
			s += cap->info.cantitate;
			nr++;
		}
		cap = cap->next;
	}
	return s / nr;
}

void stergereProduse(HashTable tabela, int cantitate)
{
	int poz = hash(cantitate, tabela.size);
	Nod* cap = tabela.vector[poz];
	Nod* prev = NULL;
	while (cap != NULL)
	{
		if (cap->info.cantitate == cantitate)
		{
			Nod* sters = cap;
			if (prev == NULL)
				tabela.vector[poz] = cap->next;
			else
				prev->next = cap->next;

			cap = cap->next;
			free(sters->info.denumire);
			free(sters);
		}
		else
		{
			prev = cap;
			cap = cap->next;
		}
	}
}

HashTable vectorToHash(Produs* p, int n, int size)
{
	HashTable tabela = initTable(size);
	for (int i = 0; i < n; i++)
		inseareInTabela(tabela, p[i]);
	return tabela;
}

Produs* hashToVector(HashTable tabela, int* nrElem)
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

	Produs* vector = (Produs*)malloc(sizeof(Produs) * nr);
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
		inseareInTabela(tabela, lsi->info);
		lsi = lsi->next;
	}
	return tabela;
}

HashTable ldiToHash(Nod* ldi, int size)
{
	HashTable tabela = initTable(size);
	while (ldi != NULL)
	{
		inseareInTabela(tabela, ldi->info);
		ldi = ldi->next;
	}
	return tabela;
}
