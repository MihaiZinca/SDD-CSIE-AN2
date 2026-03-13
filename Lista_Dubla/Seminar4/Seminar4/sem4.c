#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//LISTA DUBLA INLANTUITA -LDI
//de la stanga la dr si de la dreapta la stanga (parcurgere inversa, ce la LSI nu avem)
//mai adaugam un alt nod nou -prev, previous(nodul din stanga)
//introducem nodul coada



typedef struct Nod Nod;

typedef struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
} Carte;

struct Nod {
	Carte info;
	Nod* next;
	Nod* prev;
};

//de cate ori se modifica nodul coada intr o inserare la inceput R:o singura data la incput
void inserareLaInceput(Nod** cap,Nod**coada, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; //shallow copy util
	nou->next = *cap;
	nou->prev = NULL; 
	if (*cap == NULL)
	{
		*cap = *coada=nou;
	}
	else
	{
		(*cap)->prev = nou;
		*cap = nou;
	}


}

//de cate ori se modifica nodul coada intr o inserare la sfarsit R:o singura data 
void inserareLaSfarsit(Nod** cap,Nod** coada,Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; //shallow copy util
	nou->next = NULL;
	nou->prev = *coada; //de la dr la stanga
	if ((*cap) == NULL) {
		*cap =*coada= nou;
	}
	else {
		(*coada)->next = nou;
		*coada = nou;
	
	}
}

Carte initCarte(const char* titlu,int nrPagini,float pret)  //pun const ca nu l modific  un fel de CONSTRUCTOR CA LA POO , aici nu mai folosim din fisier
{
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);
	return c;
}

void afisareCarte(Carte carte) {
	printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
}

//de la st la dr
void afisareListaCarti(Nod* cap) {
	while (cap != NULL) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}
//de la dr la stanga
void afisareInversaListaCarti(Nod* coada) {
	while (coada != NULL) {
		afisareCarte(coada->info);
		coada = coada->prev;
	}
}

void dezalocare(Nod** cap,Nod** coada) {
	while ((*cap) != NULL) {
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
	*coada = NULL;
}

float pretMediuCarte(Nod* coada) {
	int nrCarti = 0;
	float sumaPreturi = 0;
	while (coada != NULL) {
		sumaPreturi += coada->info.pret;
		nrCarti++;
		coada = coada->prev;
	}

	if (nrCarti != 0) {
		return sumaPreturi / nrCarti;
	}
	else {
		return 0;
	}
}

void afisareListaCircularaCarti(Nod* cap)
{
	//dc lista e goala
	if (!cap)
	{
		return;
	}
	Nod* aux = cap; //declar o copie
	do
	{
		afisareCarte(cap->info);
		cap = cap->next;

	} while (cap != aux);

}

float pretMaximCircular(Nod* cap) {
	if (!cap) {
		return 0;
	}

	float maxim = cap->info.pret;
	Nod* aux = cap->next;

	while (aux != cap) 
	{
		if (aux->info.pret > maxim) 
			maxim = aux->info.pret;

		aux = aux->next;
	}

	return maxim;
}

int main() {
	Nod* cap = NULL,*coada=NULL; //marchez inceptul listei(codului)

	inserareLaSfarsit(&cap,&coada,initCarte("MiculPrint",132,35.2));
	inserareLaSfarsit(&cap, &coada,initCarte("Nuntasii", 122, 46.9));
	inserareLaSfarsit(&cap,&coada, initCarte("Confess", 126, 34.3));


	afisareInversaListaCarti(coada);

	printf("\nPretul mediu pentru o carte este %.2f lei!\n", pretMediuCarte(coada));



	//LDI Circulara
	coada->next = cap;
	cap->prev = coada;
	
	afisareListaCircularaCarti(cap);
	printf("\nPretul maxim pentru o carte este %.2f lei!\n", pretMaximCircular(cap));

	//TO DO DE FACUT DEZALOCARE LDI CIRCULARA
	///dezalocare(&cap,&coada);

	return 0;
}
//to do de inserat dupa anumite criterii!! 
//to do de facut LSI CIRCULARA
//citire din fisier, cat si ce am lucrat azi
//de stiu conversie intre LSI SI LDI (intre structuri) o coada in vectori, LSI in vector, orice structura in orice structura
