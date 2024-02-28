#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
struct KashmirHome { //Lant de magazine de saltele
    char* locatie;
    int nrSalteleInStoc;
    float* pret;
};

struct KashmirHome scrieMagazin(struct KashmirHome* ptrMagazin) {
    if (ptrMagazin != NULL)
    {
        char buffer[100];
        int nrSalteleInStoc;
        float pret;
        printf("Locatie magazin: ");
        scanf("%s", buffer);
        (*ptrMagazin).locatie = (char*)malloc(strlen(buffer) + 1);
        strcpy((*ptrMagazin).locatie, buffer);
        printf("Nr saltele in stoc: ");
        scanf("%d", &nrSalteleInStoc);

        if (nrSalteleInStoc > 0) {
            (*ptrMagazin).nrSalteleInStoc = nrSalteleInStoc;
            (*ptrMagazin).pret = (float*)malloc(nrSalteleInStoc * sizeof(float));
            for (int i = 0; i < nrSalteleInStoc; i++) {
                printf("Pretul saltelei %d", i + 1);
                printf(": ");
                scanf("%f", &pret);
                (*ptrMagazin).pret[i] = pret;
            }
        }
        else {
            (*ptrMagazin).nrSalteleInStoc = 0;
            (*ptrMagazin).pret = NULL;
        }
        return *ptrMagazin;
    }
}

struct KashmirHome init(const char* locatie, int n, float* pret) {
    if (locatie != NULL) {
        struct KashmirHome obiect;
        obiect.locatie = (char*)malloc(strlen(locatie) + 1);
        strcpy(obiect.locatie, locatie);
        if (n > 0 && pret != NULL) {
            obiect.nrSalteleInStoc = n;
            obiect.pret = (float*)malloc(sizeof(float) * n);
            for (int i = 0; i < n; i++) {
                obiect.pret[i] = pret[i];
            }
        }
        else {
            obiect.pret = NULL;
            obiect.nrSalteleInStoc = 0;
        }
        return obiect;
    }
}

void afisare(struct KashmirHome* ptrMagazin) {
    if (ptrMagazin != NULL) {
        printf("Locatie magazin: ");
        printf("%s", (*ptrMagazin).locatie);
        printf("\n");
        printf("Nr saltele in stoc: ");
        printf("%d", (*ptrMagazin).nrSalteleInStoc);
        printf("\n");
        if ((*ptrMagazin).nrSalteleInStoc > 0) {
            printf("Preturi: ");
            printf("\n");
            for (int i = 0; i < (*ptrMagazin).nrSalteleInStoc; i++) {
                printf("%f  ", (*ptrMagazin).pret[i]);
            }
        }
    }
}

float ceaMaiScumpaSaltea(struct KashmirHome* ptrMagazin) {
    if (ptrMagazin != NULL) {
        float max = 0;
        for (int i = 0; i < (*ptrMagazin).nrSalteleInStoc; i++) {
            if ((*ptrMagazin).pret[i] > max) {
                max = (*ptrMagazin).pret[i];
            }
        }
        return max;
    }
}

char* schimbaLocatie(struct KashmirHome* ptrMagazin, char* locatie) {
    if (ptrMagazin != NULL && locatie != NULL) {
        free(ptrMagazin->locatie);
        ptrMagazin->locatie = (char*)malloc(strlen(locatie) + 1);
        strcpy(ptrMagazin->locatie, locatie);
    }
    return locatie;
}
//Creaza un vector nou, care stocheaza toate magazinele cu mai mult de o saltea in stoc
struct KashmirHome* stocMaiMareDecatUnu(struct KashmirHome* vector, int n, int *nrRez) {
    int nrMagazine = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (vector[i].nrSalteleInStoc > 1) {
            nrMagazine++;
        }
    }
    *nrRez = nrMagazine;
    if (nrMagazine > 0) {
        struct KashmirHome* magazine = (struct KashmirHome*)malloc(nrMagazine * sizeof(struct KashmirHome));
        for (int i = 0; i < n; i++) {
            if (vector[i].nrSalteleInStoc > 1) {
                magazine[k++] = init(vector[i].locatie, vector[i].nrSalteleInStoc, vector[i].pret);
            }
        }
        return magazine;
    }
}

struct KashmirHome* stocZero(struct KashmirHome* vector, int n, int *nrRez) {
    int nrMagazine = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (vector[i].nrSalteleInStoc == 0) {
            nrMagazine++;
        }
    }
    *nrRez = nrMagazine;
    if (nrMagazine > 0) {
        struct KashmirHome* magazine = (struct KashmirHome*)malloc(nrMagazine * sizeof(struct KashmirHome));
        for (int i = 0; i < n; i++) {
            if (vector[i].nrSalteleInStoc == 0) {
                magazine[k++] = init(vector[i].locatie, vector[i].nrSalteleInStoc, vector[i].pret);
            }
        }
        return magazine;
    }
}

struct KashmirHome* concatenare(struct KashmirHome* v1, int n1, struct KashmirHome* v2, int n2) {
    int marime = n1 + n2;
    struct KashmirHome* concat = (struct KashmirHome*)malloc(marime * sizeof(struct KashmirHome));
    for (int i = 0; i < n1; i++) {
        concat[i] = init(v1[i].locatie, v1[i].nrSalteleInStoc, v1[i].pret);
    }
    int k = 0;
    for (int i = n1; i < marime; i++) {
        concat[i] = init(v2[k].locatie, v2[k].nrSalteleInStoc, v2[k].pret);
        k++;
    }
    return concat;
}

void afisareVector(struct KashmirHome* vector, int n) {
    printf("\n\nMagazine: \n\n");
    for (int i = 0; i < n; i++) {
        afisare(&vector[i]);
        printf("\n\n");
    }
}
void dezalocare(struct KashmirHome* obiect) {
    if (obiect != NULL) {
        if (obiect->pret != NULL) {
            free(obiect->pret);
        }
        if (obiect->locatie != NULL) {
            free(obiect->locatie);
        }
       // free(obiect);
    }
}
//Apelurile din main presupun ca se da un magazin cu 0 saltele, 3 cu mai mult de o salte, si unul cu 1 saltea.
void main() {
    int nrMagazine = 5;
    int nrMaiMari;
    int nrZero;
    struct KashmirHome* magazine = (struct KashmirHome*)malloc(nrMagazine * sizeof(struct KashmirHome)); //vector dinamic cu 5 magazine
    for (int i = 0; i < 5; i++) {
        scrieMagazin(&magazine[i]);
    }
    afisareVector(magazine, 5);
    struct KashmirHome* magazineMaiMari = stocMaiMareDecatUnu(magazine, 5, &nrMaiMari);
    afisareVector(magazineMaiMari, nrMaiMari);
    struct KashmirHome* magazineStocZero = stocZero(magazine, 5, &nrZero);
    afisareVector(magazineStocZero, nrZero);
    struct KashmirHome* concat = concatenare(magazineStocZero, nrZero, magazineMaiMari, nrMaiMari);
    afisareVector(concat, (nrZero + nrMaiMari));
    for (int i = 0; i < nrMagazine; i++) {
        dezalocare(&(magazine[i]));
    }
    for (int i = 0; i < nrMaiMari; i++) {
        dezalocare(&(magazineMaiMari[i]));
    }
    for (int i = 0; i < nrZero; i++) {
        dezalocare(&(magazineStocZero[i]));
    }
    for (int i = 0; i < (nrMaiMari + nrZero); i++) {
        dezalocare(&(concat[i]));
    }
    free(magazine);
    free(magazineMaiMari);
    free(magazineStocZero);
    free(concat);
}