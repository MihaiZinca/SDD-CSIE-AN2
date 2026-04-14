#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


typedef struct Carte
{
	char* titlu;
	int nrPagini;
	float pret;
}Carte;

void citireCarte(FILE* file, Carte* carte)
{
	char buffer[30];
	fscanf(file, "%s %d %f", buffer, &carte->nrPagini, &carte->pret);
	carte->titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(carte->titlu, buffer);
}

void afisareCarte(Carte c)
{
	printf("Titlu %s", c.titlu);
}

Carte* citireCarti(const char* numeFisier, int* nrCarti) 
{
	FILE* file = fopen(numeFisier, "r");
	if (!file)
		printf("eroare");

	fscanf(file, "%d", nrCarti);
	Carte* vectorCarti = (Carte*)malloc(sizeof(Carte) * (*nrCarti));
	for (int i = 0; i < *nrCarti; i++)
		citireCarte(file, &vectorCarti[i]);
	fclose(file);
	return vectorCarti;
}

void afisareCarti(Carte* carti, int nrCarti)
{
	for (int i = 0; i < nrCarti; i++)
		afisareCarte(carti[i]);
}

void dezalocare(Carte** vectorCarti, int* nrCarti)
{
	for (int i = 0; i < *nrCarti; i++)
		free((*vectorCarti)[i].titlu);
	free(*vectorCarti);
	*nrCarti = 0;
	*vectorCarti = NULL;
}

void main()
{
	FILE* f = fopen("carte.txt", "r");
	if (!f)
		printf("eroare la deschiderea fis");
	Carte c;
	CitireCarte(f, &c);
	afisareCarte(c);
	
	free(c.titlu);
	fclose(f);

	int nrCarti;
	Carte* vectorCarti = citireCarti("carti.txt", &nrCarti);
	if (vectorCarti)
		afisareCarti(vectorCarti, nrCarti);

	dezalocare(&vectorCarti, &nrCarti);
}