#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
typedef struct Cafenea Cafenea;
typedef struct Nod Nod;

struct Cafenea {
    char* nume;
    int nrLocuri;
    float suprafata;
};

struct Nod {
    Cafenea info;
    Nod* next;
};

Cafenea initCaf(const char* numeNou, int nrLocuriNou, float suprafataNoua) {
    Cafenea cafenea;
    if (numeNou != NULL) {
        cafenea.nume = (char*)malloc(sizeof(char) * (strlen(numeNou) + 1));
        strcpy(cafenea.nume, numeNou);
    }
    cafenea.nrLocuri = nrLocuriNou;
    cafenea.suprafata = suprafataNoua;
    return cafenea;
}

Nod* inserareInceput(Cafenea c, Nod* cap) {
    Nod* nou = malloc(sizeof(Nod));
    nou->next = cap;
    nou->info = initCaf(c.nume, c.nrLocuri, c.suprafata);
    return nou;
}

void afisareCafenea(Cafenea c) {
    printf("\nNume: %s", c.nume);
    printf("\nNr locuri: %d", c.nrLocuri);
    printf("\nsuprafata: %f", c.suprafata);
}

void afisareLista(Nod* cap) {
    while (cap != NULL) {
        afisareCafenea(cap->info);
        printf("\n\n");
        cap = cap->next;
    }
}

char* numeCafeneaDensitateMinima(Nod* cap) {
    char* rez = NULL;
    Nod* adresa = NULL;
    float minim;
    if (cap != NULL) {
        if (cap->info.suprafata != 0)
        {
            minim = (cap->info.nrLocuri) / (cap->info.suprafata);
            adresa = cap;
        }
    }
    while (cap != NULL) {

        if (((cap->info.nrLocuri) / (cap->info.suprafata)) < minim) {
            minim = ((cap->info.nrLocuri) / (cap->info.suprafata));
            adresa = cap;
        }
        cap = cap->next;
    }
    if (adresa != NULL)
    {
        rez = (char*)malloc(strlen(adresa->info.nume) + 1);
        strcpy(rez, adresa->info.nume);
        return rez;
    }
    return "-";
}

void stergereLista(Nod** cap) {
    while (*cap != NULL) {
        Nod* aux = *cap;
        *cap = (*cap)->next;
        free(aux->info.nume);
        free(aux);
        *cap = NULL;
    }
}

void inserareFinal(Nod** cap, Cafenea c) {
    if (*cap == NULL) {
        *cap = inserareInceput(c, *cap);
    }
    else {
        Nod* curent = *cap;
        while (curent->next != NULL) {
            curent = curent->next;
        }
        Nod* nodNou = (Nod*)malloc(sizeof(Nod));
        nodNou->info = initCaf(c.nume, c.nrLocuri, c.suprafata);
        nodNou->next = NULL;
        curent->next = nodNou;
    }
}

void main() {
    Nod* cap = NULL;
    Cafenea c = initCaf("Tucano", 12, 20);
    cap = inserareInceput(c, cap);
    cap = inserareInceput(initCaf("Teds", 20, 30), cap);
    cap = inserareInceput(initCaf("Urban", 10, 15), cap);
    inserareFinal(&cap, initCaf("StarBucks", 10, 16));
    afisareLista(cap);
    printf("%s", numeCafeneaDensitateMinima(cap));
    stergereLista(&cap);
    free(c.nume);
}