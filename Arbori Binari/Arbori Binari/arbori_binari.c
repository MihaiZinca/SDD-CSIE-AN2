#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Nod Nod;


typedef struct Carte {
	int id;
	char* titlu;
	int nrPagini;
	float pret;
} Carte;

struct Nod {
	Carte info;
	Nod* stanga;
	Nod* dreapta;
};


Carte initCarte(int id, const char* titlu, int nrPagini, float pret) {
	Carte c;
	c.id = id;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);

	return c;
}

void afisareCarte(Carte carte) {
	printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
}

void inserareInABC(Nod** radacina, Carte c) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = c;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
	else if (c.id < (*radacina)->info.id) {
		inserareInABC(&(*radacina)->stanga, c);

	}
	else {
		inserareInABC(&(*radacina)->dreapta, c);

	}
}
void inordine(Nod* rad) {
	if (rad) {
		//srd
		inordine(rad->stanga);
		afisareCarte(rad->info);
		inordine(rad->dreapta);
	}
}
void preordine(Nod* rad) {
	if (rad) {
		//rsd
		afisareCarte(rad->info);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}
void postordine(Nod* rad) {
	// sdr
	if (rad) {

		postordine(rad->stanga);
		postordine(rad->dreapta);
		afisareCarte(rad->info);
	}
}

Carte cautareDupaId(Nod* rad, int id) {
	if (rad == NULL)
	{
		return initCarte(-1, "necunoscut", 0, 0);
	}
	else if (id == rad->info.id) {
		return initCarte(rad->info.id, rad->info.titlu, rad->info.nrPagini, rad->info.pret);

	}
	else if (id < rad->info.id) {
		return cautareDupaId(rad->stanga, id);
	}
	else {
		return cautareDupaId(rad->dreapta, id);

	}
}



void dezalocare(Nod** rad) {
	if (*rad != NULL)
	{

		dezalocare(&(*rad)->stanga);
		dezalocare(&(*rad)->dreapta);
		free((*rad)->info.titlu);
		free(*rad);
	}
}

int maxim(int a, int b) {
	return (a > b ? a : b);
}

int calculInaltimeArbore(Nod* rad) {
	if (rad) {
		return maxim(calculInaltimeArbore(rad->stanga), calculInaltimeArbore(rad->dreapta)) + 1;
	}
	else {
		return 0;
	}
}

void main()
{
	//7,4,10,2,6,8,11
	Nod* radacina = NULL;
	inserareInABC(&radacina, initCarte(7, "Carte1", 100, 55));
	inserareInABC(&radacina, initCarte(4, "Carte2", 200, 56));
	inserareInABC(&radacina, initCarte(10, "Carte3", 120, 57));
	inserareInABC(&radacina, initCarte(2, "Carte4", 250, 58));
	inserareInABC(&radacina, initCarte(6, "Carte5", 270, 59));
	inserareInABC(&radacina, initCarte(11, "Carte6", 219, 60));


	printf("parcurgere inordine : ");
	inordine(radacina);

	Carte carteCautata = cautareDupaId(radacina, 8);
	printf("carte cautata :");
	afisareCarte(carteCautata);
	free(carteCautata.titlu);

	printf("inaltime arbore: %d", calculInaltimeArbore(radacina));

	dezalocare(&radacina);
}