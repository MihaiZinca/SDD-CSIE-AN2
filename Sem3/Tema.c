//tema inserare dupa un crieteriu, in functie dupa un anumit id etc

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Carte
{
    int id;
    char* titlu;
    int nrPagini;
    float pret;

}Carte;

typedef struct Nod Nod;

struct Nod {
    Carte info;
    Nod* next;
};


void inserareDupaPret(Nod** cap, Carte c)
{
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c; 
    nou->next = NULL;
    if ((*cap) == NULL)
    {
        *cap = nou;
    }
    else
    {
        if (c.pret < (*cap)->info.pret) //inserez la inceput
        {
            nou->next = *cap;
            *cap = nou;
        }
        else
        {
            Nod* aux = *cap;
            while (aux->next != NULL && aux->next->info.pret < c.pret)
            {
                aux = aux->next;
            }
            nou->next = aux->next;
            aux->next = nou;
        }
    }
}

void inserareDupaId(Nod** cap, Carte c)
{
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next = NULL;
    if ((*cap) == NULL)
    {
        *cap = nou;
    }
    else
    {
        if (c.id < (*cap)->info.id)
        {
            nou->next = *cap;
            *cap = nou;
        }
        else
        {
            Nod* aux = *cap;
            while (aux->next != NULL && aux->next->info.id < c.id)
            {
                aux = aux->next;
            }
            nou->next = aux->next;
            aux->next = nou;
        }
    }
}

void inserareDupaPag(Nod** cap, Carte c)
{
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next = NULL;
    if ((*cap) == NULL)
    {
        *cap = nou;
    }
    else
    {
        if (c.nrPagini < (*cap)->info.nrPagini)
        {
            nou->next = *cap;
            *cap = nou;
        }
        else
        {
            Nod* aux = *cap;
            while (aux->next != NULL && aux->next->info.nrPagini < c.nrPagini)
            {
                aux = aux->next;
            }
            nou->next = aux->next;
            aux->next=nou->next
        }
    }
}

Carte citireCarte(FILE* file)
{
    char buffer[30];
    Carte c;
    fscanf(file, "%29s %d %f", buffer, &c.nrPagini, &c.pret);

    c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(c.titlu, buffer);
    return c;
}

void afisareCarte(Carte carte)
{
    printf("Titlu: %s, nrPagini: %d, pret: %.2f\n", carte.titlu, carte.nrPagini, carte.pret);
}

Nod* citireListaCarti(const char* numeFisier)
{
    FILE* file = fopen(numeFisier, "r");
    if (!file)
    {
        printf("eroare la deschiderea fisierului!\n");
        return NULL;
    }
    Nod* cap = NULL;

    inserareDupaPret(&cap, citireCarte(file));
    inserareDupaPret(&cap, citireCarte(file));
    inserareDupaPret(&cap, citireCarte(file));

   

    fclose(file);
    return cap;

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

float pretMediuCarti(Nod* cap) //am folosit prin valoare, ne folosim de ele nu le modificam doar parcurgem
{
    int nrCarti = 0;
    float sumaPreturi = 0;
    while (cap != NULL)
    {
        nrCarti++;
        sumaPreturi += cap->info.pret;
        cap = cap->next;
    }

    if (nrCarti != 0)return sumaPreturi / nrCarti;
    else
        return 0;
}

//returnare numele cartii care costa 46,9 lei

char* afisareTitlu(Nod* cap, float _pret)
{
    while (cap != NULL)
    {
        if (cap->info.pret == _pret)
        {
            char* copie = (char*)malloc(sizeof(char) * strlen(cap->info.titlu) + 1);
            strcpy(copie, cap->info.titlu);
            return copie;
        }
        cap = cap->next;
    }
    return("Not found");
}


int main()
{
    Nod* cap = citireListaCarti("carti.txt");

    afisareListaCarti(cap);

    printf("\nPretul mediu pentru p carte este %.2f lei", pretMediuCarti(cap));

    dezalocare(&cap);

    return 0;
}