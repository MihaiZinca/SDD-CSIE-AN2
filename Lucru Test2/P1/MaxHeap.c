#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Carte {
	int id;
	char* titlu;
	int nrPagini;
	float pret;
	int prioritate;
} Carte;

//pt conversie abc/avl
typedef struct Nod Nod;
struct Nod {
	Carte info;
	Nod* stanga;
	Nod* dreapta;
};

typedef struct MaxHeap MaxHeap;
struct MaxHeap {
	Carte* vector;
	int size;
};

Carte initCarte(int prioritate, int id,const char* titlu, int nrPagini, float pret) {
	Carte c;
	c.prioritate = prioritate;
	c.id = id;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);

	return c;
}

void afisareCarte(Carte carte) {
	printf("%d. ,Id:%d ,Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.prioritate,carte.id, carte.titlu, carte.nrPagini, carte.pret);
}

void traversareMaxHeap(MaxHeap heap)
{
	for (int i = 0; i < heap.size; i++)
	{
		afisareCarte(heap.vector[i]);
	}
}

//ordonare
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

void extragereCarte(MaxHeap* heap, Carte* c)
{
	*c = initCarte(heap->vector[0].prioritate, heap->vector[0].id,heap->vector[0].titlu, heap->vector[0].nrPagini, heap->vector[0].pret);
	//interschimbare primu cu ultimul
	Carte aux = heap->vector[0];
	heap->vector[0] = heap->vector[heap->size - 1];
	heap->vector[heap->size - 1] = aux;

	heap->size--;
	heapify(*heap, 0);
}

void dezalocareHeap(MaxHeap* heap)
{
	for (int i = 0; i < heap->size; i++)
	{
		free(heap->vector[i].titlu);
	}
	free(heap->vector);
	heap->size = 0;
}


//conversie

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

void MaxHeapToABC(MaxHeap heap, Nod** abc) //pt AVL la fel
{
	for (int i = 0; i < heap.size; i++)
		inserareInABC(abc, heap.vector[i]);
}

void abctoMaxHeap(Nod* rad, MaxHeap* heap) //pt avl la fel
{
	if (rad)
	{
		heap->vector[heap->size] = rad->info;
		heap->size++;

		abctoMaxHeap(rad->stanga, heap);
		abctoMaxHeap(rad->dreapta, heap);
	}

	for (int i = heap->size / 2 - 1; i >= 0; i--)
	{
		heapify(*heap, i);
	}
}

 
