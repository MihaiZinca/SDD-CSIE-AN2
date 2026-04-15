#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


//HashTable(Chaining)

//coliziune -inserare mai multe elemente pe aceeasi pozitie
//chaining - toate elementele se pun intr o lista simpla,
//initial,vectorul este full null, apoi se retine in vector adresa capului listei
//elementele vectorului= adresele capetelor listelor -liste in liste gen

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
	Nod* prev; //pt conv in LDI
};

typedef struct HashTable HashTable;

struct HashTable
{
	Nod** vector; //vector de liste
	int size;
};

void inserareSfarsit(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	if ((*cap) == NULL)
		*cap = nou;
	else
	{
		Nod* aux = *cap;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nou;
	}
}

Carte initCarte(const char* titlu, int nrPagini, float pret)
{
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);
	return c;
}

void afisareCarte(Carte carte)
{
	printf("Titlu %s, nrPaigni: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
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

//initializare tabelahash cu null

HashTable initTable(int dim)
{
	HashTable tabela;
	tabela.size = dim;
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++)
		tabela.vector[i] = NULL;
	return tabela;
}

int hash(int nrPagini, int size)
{
	return nrPagini % size; //ret o val intre 0 si size-1
}

//mecanisul de tratare a coliziunii- chaining
void inserareinTabela(HashTable tabela, Carte c)
{
	if (tabela.size > 0)
	{
		int pozitie = hash(c.nrPagini, tabela.size);
		if (pozitie >= 0 && pozitie < tabela.size)
			inserareSfarsit(&(tabela.vector[pozitie]), c);
	}
}

void parcurgereTabela(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		afisareListaCarti(tabela.vector[i]);
}

void dezalocareTabela(HashTable tabela)
{
	for (int i = 0; i < tabela.size; i++)
		dezalocare(&(tabela.vector[i]));
	free(tabela.vector);
}

//pretul mediu pt o carte, pt toate cartile care au dat un nr de pagini dat ca parametru 
// --daca avem cheia facem functia hash!!
float calculPretMediu(HashTable tabela, int nrPagini)
{
	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz]; 

	float s = 0;
	int nr = 0;

	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
		{
			s += cap->info.pret;
			nr++;
		}
		cap = cap->next;
	}

	if (nr > 0)return s / nr;
	else return 0;
}


void stergere(HashTable tabela, int nrPagini)
{
	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz];
	Nod* prev = NULL;
	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
		{
			if (prev == NULL)
				tabela.vector[poz] = cap->next; //stergere prim element
			else 
				prev->next = cap->next; //sarim peste nodul curent -legam nodul anterior direct de urmatorul 

			free(cap->info.titlu);
			free(cap);
			return;
		}
		prev = cap;
		cap=cap->next;
	}
}

void stergereToate(HashTable tabela, int nrPagini)
{
	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz];
	Nod* prev = NULL;
	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
		{
			Nod* sters = cap;

			if (prev == NULL)
				tabela.vector[poz] = cap->next;
			else
				prev->next = cap->next;
			
			cap = cap->next;
			free(sters->info.titlu);
			free(sters);
		}
		else
		{
			prev = cap;
			cap = cap->next;
		}

	}
}

HashTable vectorToHash(Carte* v, int n, int size)
{
	HashTable tabela = initTable(size);
	for (int i = 0; i < n; i++)
	{
		inserareinTabela(tabela, v[i]);
	}
	return tabela;
}

Carte* hashToVector(HashTable tabela, int* nrElem)
{
	int nr = 0;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			nr++;
			cap = cap->next;
		}
	}

	Carte* vector = (Carte*)malloc(sizeof(Carte) * nr);
	int n = 0;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			vector[n++] = cap->info;
			cap = cap->next;
		}
	}

	*nrElem = nr;
	return vector;
}

HashTable lsiToHash(Nod* lsi, int size) //identic pt ldi
{
	HashTable tabela = initTable(size);
	while (lsi != NULL)
	{
		inserareinTabela(tabela, lsi->info);
		lsi = lsi->next;
	}
	return tabela;
}

Nod* hashToLsi(HashTable tabela)
{
	Nod* lsi = NULL;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			inserareSfarsit(&lsi, cap->info);
			cap = cap->next;
		}
	}
	return lsi;
}

Nod* hashToLdi(HashTable tabela)
{
	Nod* cap = NULL;
	Nod* coada = NULL;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* p = tabela.vector[i];
		while (p != NULL)
		{
			Nod* nou = (Nod*)malloc(sizeof(Nod));
			nou->info = p->info;
			nou->next = NULL;
			nou->prev = coada;

			if (cap == NULL)
				cap = nou;
			else
				coada->next = nou;
			
			coada = nou;
			p = p->next;
		}
	}
	return cap;
}

//pt STIVA -LSI
void inserareInceput(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	*cap = nou;
}

HashTable stivaToHash(Nod* stiva, int size) ///si pt COADA LA FEL;
{
	HashTable tabela = initTable(size);
	while (stiva != NULL)
	{
		int poz = hash(stiva->info.nrPagini, tabela.size);
		inserareSfarsit(&(tabela.vector[poz]), stiva->info);
		stiva = stiva->next;
	}
	return tabela;
}

Nod* hashToStiva(HashTable tabela)
{
	Nod* stiva = NULL;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			inserareInceput(&stiva, cap->info);
			cap = cap->next;
		}
	}
	return stiva;
}


Nod* hashToCoada(HashTable tabela)
{
	Nod* coada = NULL;
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			inserareSfarsit(&coada, cap->info);
			cap = cap->next;
		}
	}
	return coada;
}


HashTable resize(HashTable tabela, int newSize)
{
	HashTable nou = initTable(newSize);
	for (int i = 0; i < tabela.size; i++)
	{
		Nod* cap = tabela.vector[i];
		while (cap != NULL)
		{
			inserareinTabela(nou, cap->info);
			cap = cap->next;
		}
	}
	return nou;
}