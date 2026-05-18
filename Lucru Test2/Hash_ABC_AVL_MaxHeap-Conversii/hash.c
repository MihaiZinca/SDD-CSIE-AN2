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
	int prioritate;
}Carte;

typedef struct Nod Nod;
struct Nod
{
	Carte info;
	Nod* next;
	Nod* stanga;
	Nod* dreapta;
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
	for (int i = 0; i < tabela.size; i++)
		tabela.vector[i] = NULL;
	return tabela;
}

int hash(int nrPagini, int size)
{
	return nrPagini % size;
}

//tratarea coliziunii
void inseareInHash(HashTable tabela, Carte c)
{
	if (tabela.size > 0)
	{
		int poz = hash(c.nrPagini, tabela.size);
		if (poz >= 0 && poz < tabela.size)
			inserareSfarsit(&(tabela.vector[poz]), c);
	}
}

void afisareHash(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		afisareListaCarti(tabela.vector[i]);
}

void dezalocareHash(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		dezalocare(&(tabela.vector[i]));
	free(tabela.vector);
}

Carte cautareCarte(HashTable tabela, int nrPagini)
{
	Carte c;
	c.id = 0;
	c.nrPagini = 0;
	c.pret = 0;
	c.titlu = NULL;

	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz];
	while (cap)
	{
		if (cap->info.nrPagini == nrPagini)
			return cap->info;
		cap = cap->next;
	}
	return c;
}


//conversii

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
		return maxim(calculInaltimeArbore(rad->stanga), calculInaltimeArbore(rad->dreapta)) + 1;
	return 0;
}
int diferentaInaltimeSubarbori(Nod* rad)
{
	if (rad)
		return calculInaltimeArbore(rad->stanga) - calculInaltimeArbore(rad->dreapta);
	return 0;
}
void echilibare(Nod** rad)
{
	if (*rad == NULL)
		return;
	int dif = diferentaInaltimeSubarbori(*rad);
	if (dif == 2)
	{
		if (diferentaInaltimeSubarbori((*rad)->stanga) == -1)
			rotireStanga(&(*rad)->stanga);
		rotireDreapta(rad);
			
	}
	if (dif == -2)
	{
		if (diferentaInaltimeSubarbori((*rad)->dreapta) == 1)
			rotireDreapta(&(*rad)->dreapta);
		rotireStanga(rad);
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
		inserareInBST(&(*radacina)->stanga, c);
	else
		inserareInBST(&(*radacina)->dreapta, c);
	echilibare(radacina);
}

void inseareInABC(Nod** radacina, Carte c)
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
		inseareInABC(&(*radacina)->stanga, c);
	else
		inseareInABC(&(*radacina)->dreapta, c);
}

void hashToABC(HashTable tabela, Nod** abc)
{
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap)
		{
			inseareInABC(abc, cap->info);
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

void hashToAVL(HashTable tabela, Nod** avl)
{
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap)
		{
			inserareInBST(avl, cap->info);
			cap=cap->next;
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

void abcToAvl(Nod* abc, Nod** avl)
{
	if (abc)
	{
		inserareInBST(avl, abc->info);
		abcToAvl(abc->stanga, avl);
		abcToAvl(abc->dreapta, avl);
	}
}

void avlToABC(Nod* avl, Nod** abc)
{
	if (avl)
	{
		inseareInABC(abc, avl->info);
		avlToABC(avl->stanga, abc);
		avlToABC(avl->dreapta, abc);
	}
}

typedef struct MaxHeap MaxHeap;
struct MaxHeap
{
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
	for (int i = 0; i < tabela.size; i++)
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
		heapify(*heap, i);
}

void maxHeapToHash(MaxHeap heap, HashTable* tabela)
{
	for (int i = 0; i < heap.size; i++)
	{
		int poz = hash(heap.vector[i].nrPagini, tabela->size);
		inserareSfarsit(&(tabela->vector[poz]), heap.vector[i]);
	}
}

void abcToHeap(Nod* abc, MaxHeap* heap) //la fel si pt avl
{
	
	if(abc)
	{
		heap->vector[heap->size] = abc->info;
		heap->size++;

		abcToHeap(abc->stanga, heap);
		abcToHeap(abc->dreapta, heap);
	}
	//in main
	//for (int i = heap->size / 2 - 1; i >= 0; i--)
		//heapify(*heap, i);
}

void MaxHeapToABC(MaxHeap heap, Nod** abc) // la fel si pt avl
{
	for (int i = 0; i < heap.size; i++)
		inseareInABC(abc, heap.vector[i]);
}

