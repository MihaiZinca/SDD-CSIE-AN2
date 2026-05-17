#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Produs
{
	int cod;
	char* denumire;
	float pret;
}Produs;


typedef struct Nod Nod;
struct Nod
{
	Produs info;
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

typedef struct MaxHeap MaxHeap;
struct MaxHeap
{
	Produs* vector;
	int size;
};

void inserareSfarsit(Nod** cap, Produs p)
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

Produs initProdus(int cod, const char* denumire, float pret)
{
	Produs p;
	p.cod = cod;
	p.pret = pret;
	p.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(p.denumire, denumire);
	return p;
}

void afisareProdus(Produs p)
{
	printf("Cod:%d,Denumire:%s,Pret:%f", p.cod, p.denumire, p.pret);
}

void afisareListaProduse(Nod* cap)
{
	while (cap)
	{
		afisareProdus(cap->info);
		cap = cap->next;
	}
}
void dezalocare(Nod** cap)
{
	while (*cap != NULL)
	{
		free((*cap)->info.denumire);
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

int hash(int cod, int size)
{
	return cod % size;
}

void inseareInHash(HashTable tabela, Produs p)
{
	if (tabela.size > 0)
	{
		int poz = hash(p.cod, tabela.size);
		inserareSfarsit(&(tabela.vector[poz]), p);
	}
}

void afisareHash(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		afisareListaProduse(tabela.vector[i]);
}

void dezalocareHash(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		dezalocare(&(tabela.vector[i]));
	free(tabela.vector);
}

Produs cautareProdus(HashTable tabela, int cod)
{
	Produs p;
	p.cod = 0;
	p.pret = 0;
	p.denumire = NULL;

	int poz = hash(cod, tabela.size);
	Nod* cap = tabela.vector[poz];
	while (cap)
	{
		if (cap->info.cod == cod)
			return cap->info;
		cap = cap->next;
	}
	return p;
}

void inseareInABC(Nod** rad, Produs p)
{
	if (*rad == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = p;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*rad = nou;
	}
	else if (p.cod < (*rad)->info.cod)
	{
		inseareInABC(&(*rad)->stanga, p);
	}
	else
		inseareInABC(&(*rad)->dreapta, p);
}

void inordine(Nod* rad)
{
	if (rad)
	{
		//srd
		inordine(rad->stanga);
		afisareProdus(rad->info);
		inordine(rad->dreapta);
	}
}

void afisareFrunze(Nod* rad)
{
	if (rad)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL)
			afisareProdus(rad->info);
		afisareFrunze(rad->stanga);
		afisareFrunze(rad->dreapta);
	}
}

void hashToAVL(HashTable tabela, Nod** abc)
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


int maxim(int a, int b)
{
	return(a > b ? a : b);
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


void echilibare(Nod** rad)
{
	if (*rad == NULL)
		return;

	int dif = diferentaInaltimeSubarbori((*rad));
	if (dif == 2)
	{
		if (diferentaInaltimeSubarbori((*rad)->stanga) == -1)
			rotireStanga(&(*rad)->stanga);
		rotireDreapta(rad);
	}

	if (dif ==-2)
	{
		if (diferentaInaltimeSubarbori((*rad)->dreapta) == 1)
			rotireDreapta(&(*rad)->dreapta);
		rotireStanga(rad);
	}
}

void inseareInAVL(Nod** rad, Produs p)
{
	if (*rad == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = p;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*rad = nou;
	}
	else if (p.cod < (*rad)->info.cod)
	{
		inseareInAVL(&(*rad)->stanga, p);
	}
	else
		inseareInAVL(&(*rad)->dreapta, p);
	echilibare(rad);
}

void abcToAVL(Nod* abc, Nod** avl)
{
	if (abc)
	{
		abcToAVL(abc->stanga, avl);
		inseareInAVL(avl, abc->info);
		abcToAVL(abc->dreapta, avl);
	}
}

void afisareHeap(MaxHeap heap)
{
	for (int i = 0; i < heap.size; i++)
		afisareProdus(heap.vector[i]);
}
void heapify(MaxHeap heap, int index)
{
	if (heap.size > 0)
	{
		int pozMax = index;
		int pozSt = 2 * index + 1;
		int pozDr = 2 * index + 2;
		
		if (pozSt < heap.size && heap.vector[pozMax].pret < heap.vector[pozSt].pret)
			pozMax = pozSt;
		if (pozDr < heap.size && heap.vector[pozMax].pret < heap.vector[pozDr].pret)
			pozMax = pozDr;

		if (pozMax != index)
		{
			Produs aux = heap.vector[pozMax];
			heap.vector[pozMax] = heap.vector[index];
			heap.vector[index] = aux;
		}
		if (pozMax <= heap.size / 2 - 1)
			heapify(heap, pozMax);
	}
}

void extragereMaxim(MaxHeap* heap, Produs* p)
{
	*p = initProdus(heap->vector[0].cod, heap->vector[0].denumire, heap->vector[0].pret);

	Produs nou = heap->vector[0];
	heap->vector[0] = heap->vector[heap->size - 1];
	heap->vector[heap->size - 1] = nou;
	
	heap->size--;
	heapify(*heap, 0);
}

void avlToMaxHeap(Nod* avl,MaxHeap* heap)
{
	if (avl)
	{
		heap->vector[heap->size] = avl->info;
		heap->size++;

		avlToMaxHeap(avl->stanga, heap);
		avlToMaxHeap(avl->dreapta, heap);
	}
	
}


int main()
{

	Produs p1 = initProdus(10, "Lapte", 5.5);
	Produs p2 = initProdus(22, "Paine", 3.2);
	Produs p3 = initProdus(5, "Apa", 2.0);
	Produs p4 = initProdus(18, "Suc", 6.7);
	Produs p5 = initProdus(30, "Cafea", 15.0);

	HashTable tabela = initTable(5);
	inseareInHash(tabela, p1);
	inseareInHash(tabela, p2);
	inseareInHash(tabela, p3);
	inseareInHash(tabela, p4);
	inseareInHash(tabela, p5);
	
	printf("\nHASH:\n");
	afisareHash(tabela);
	
	Produs ok = cautareProdus(tabela, 18);
	if (ok.denumire)
		afisareProdus(ok);
	else
		printf("Nu exista\n");

	Nod* abc = NULL;
	hashToAVL(tabela, &abc);
	printf("\nABC inordine:\n");
	inordine(abc);
	printf("\nAfisare frunze abc\n");
	afisareFrunze(abc);

	Nod* avl = NULL;
	abcToAVL(abc, &avl);
	printf("\nAfisare AVl\n");
	inordine(avl);

	MaxHeap heap;
	heap.size = 0;
	heap.vector = (Produs*)malloc(sizeof(Produs) * 10);
	avlToMaxHeap(avl, &heap);
	for (int i = heap.size / 2 - 1; i >= 0; i--)
		heapify(heap, i);
	printf("\nHeap:\n");
	afisareHeap(heap);

	Produs max;
	extragereMaxim(&heap, &max);
	afisareProdus(max);

	printf("\nAfisare dupa extragere:\n");
	afisareHeap(heap);

	dezalocareHash(tabela);
	free(heap.vector);
	return 0;
}