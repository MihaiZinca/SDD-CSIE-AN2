#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Carte
{
	int id;
	char* titlu;
	int nrPagini;
	float pret;
	int prioritate; //pt maxheap
}Carte;

typedef struct Nod Nod;
struct Nod
{
	Carte info;
	Nod* next;
	Nod* stanga; //pt ABC
	Nod* dreapta;//PT ABC
};

typedef struct HashTable HashTable;
struct HashTable
{
	Nod** vector; ///vector de liste
	int size;
};

void inserareSfarsit(Nod** cap, Carte c)
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

Carte initCarte(int id,const char* titlu, int nrPagini, float pret)
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
	printf("Id:%d, Titlu: %s, nrPagini: %d, pret: %.2f. \n",carte.id, carte.titlu, carte.nrPagini, carte.pret);
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

void afisareListaCarti(Nod* cap)
{
	while (cap != NULL)
	{
		afisareCarte(cap->info);
		cap = cap->next;
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

//tratare coliziune
void inserareInHash(HashTable tabela, Carte c)
{
	if (tabela.size > 0)
	{
		int poz = hash(c.nrPagini, tabela.size);
		if (poz >= 0 && poz < tabela.size)
			inserareSfarsit(&(tabela.vector[poz]), c);
	}
}

void afisareHashTable(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		afisareListaCarti(tabela.vector[i]);
}

void dezalocareHashTable(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		dezalocare(&(tabela.vector[i]));
	free(tabela.vector);
}

Carte cautareCarte(HashTable tabela, int nrPagini)
{
	Carte c;
	c.nrPagini = 0;
	c.pret = 0;
	c.titlu = NULL;

	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz];
	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
			return cap->info;
		cap = cap->next;
	}
	return c;
}

//pt conversii

void echilibrare(Nod** radacina)
{
	if (*radacina == NULL)
		return;

	int difH = diferentaInaltimeSubarbori(*radacina);
	if (difH == 2)
	{
		if (diferentaInaltimeSubarbori((*radacina)->stanga) == -1)
			rotireStanga(&(*radacina)->stanga);
		rotireDreapta(radacina);
	}

	if (difH == -2)
	{
		if (diferentaInaltimeSubarbori((*radacina)->dreapta) == 1)
			rotireDreapta(&(*radacina)->dreapta);
		rotireStanga(radacina);
	}
}

void inserareInBST(Nod** radacina, Carte c)
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
		inserareInBST(&(*radacina)->stanga, c);
	}
	else
	{
		inserareInBST(&(*radacina)->dreapta, c);
	}
	echilibrare(radacina);

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

void hashToABC(HashTable tabela, Nod** abc)
{
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap)
		{
			inserareInABC(abc, cap->info);
			cap = cap->next;
		}
	}
}

void abcToHash(Nod* abc, HashTable* tabela)
{
	if (abc)
	{
		abcToHash(abc->stanga, tabela);
		int poz = hash(abc->info.nrPagini, tabela->size);
		inserareSfarsit(&(tabela->vector[poz]), abc->info);
		abcToHash(abc->dreapta, tabela);
	}
}

void hashTOAVL(HashTable tabela, Nod** avl)
{
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap)
		{
			inserareInBST(avl, cap->info);
			cap = cap->next;
		}
	}
}

void avlToHash(Nod* avl, HashTable* tabela)
{
	if (avl)
	{
		avlToHash(avl->stanga, tabela);
		int poz = hash(avl->info.nrPagini, tabela->size);
		inserareSfarsit(&(tabela->vector[poz]), avl->info);
		avlToHash(avl->dreapta, tabela);
	}
}




typedef struct MaxHeap MaxHeap;
struct MaxHeap {
	Carte* vector;
	int size;
};

void heapify(MaxHeap heap, int index)
{
	if (heap.size > 0)
	{
		int pozMax = index;
		int pozSt = 2 * index + 1;
		int pozDr = 2 * index + 2;

		if (pozSt < heap.size && heap.vector[pozMax].prioritate < heap.vector[pozSt].prioritate)
			pozMax = pozSt;

		if (pozDr < heap.size && heap.vector[pozMax].prioritate < heap.vector[pozDr].prioritate)
			pozMax = pozDr;

		if (pozMax != index)
		{
			Carte aux = heap.vector[pozMax];
			heap.vector[pozMax] = heap.vector[index];
			heap.vector[index] = aux;
		}

		if (pozMax <= heap.size / 2 - 1)
			heapify(heap, pozMax);
	}
}

void hashToMaxHeap(HashTable tabela, MaxHeap* heap)
{
	heap->size = 0;
	for (int i = 0; i < heap->size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap)
		{
			heap->vector[heap->size] = cap->info;
			heap->size++;
			cap = cap->next;
		}
	}

	for (int i = heap->size / 2 - 1; i >= 0; i--)
	{
		heapify(*heap, i);
	}
}

void maxheapToHash(MaxHeap heap, HashTable* tabela)
{
	for (int i = 0; i < heap.size; i++)
	{
		int poz = hash(heap.vector[i].id, tabela->size);
		inserareSfarsit(&(tabela->vector[poz]), heap.vector[i]);
	}
}




