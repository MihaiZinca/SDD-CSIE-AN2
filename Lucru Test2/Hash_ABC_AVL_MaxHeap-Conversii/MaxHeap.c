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

typedef struct MaxHeap MaxHeap;
struct MaxHeap
{
	Carte* vector;
	int size;
};

Carte initCarte(int prioritate,int id, const char* titlu, int nrPagini, float pret)
{
	Carte c;
	c.prioritate = prioritate;
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

void afisareMaxHeap(MaxHeap heap)
{
	for (int i = 0; i < heap.size; i++)
		afisareCarte(heap.vector[i]);
}

void heapify(MaxHeap heap, int index)
{
	if (heap.size > 0)
	{
		int pozMax = index;
		int pozSt = 2 * index + 1;
		int pozDr = 2 * index + 2;

		if (pozSt < heap.size && heap.vector[pozMax].prioritate < heap.vector[pozSt].prioritate)
			pozMax = pozSt;

		if (pozDr < heap.size && heap.vector[pozMax].pret < heap.vector[pozDr].prioritate)
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

void extragere(MaxHeap* heap, Carte* c)
{
	*c = initCarte(heap->vector[0].prioritate, heap->vector[0].id, heap->vector[0].titlu, heap->vector[0].nrPagini, heap->vector[0].pret);

	Carte aux = heap->vector[0];
	heap->vector[0] = heap->vector[heap->size - 1];
	heap->vector[heap->size - 1] = aux;

	heap->size--;
	heapify(*heap, 0);
}

void dezalocareMaxHeap(MaxHeap* heap)
{
	for (int i = 0; i < heap->size; i++)
		free(heap->vector[i].titlu);
	free(heap->vector);
	heap->size = 0;
}