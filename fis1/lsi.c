#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>

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
};

//LSI

void inserareLaInceput(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
}