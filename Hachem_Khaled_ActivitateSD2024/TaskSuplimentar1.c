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
        }
        return *ptrMagazin;
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

void main() {
    struct KashmirHome magazin1;
    struct KashmirHome* ptr = &magazin1;
    scrieMagazin(ptr);
    printf("Initial: \n");
    afisare(ptr);
    printf("\nCea mai scumpa saltea: ");
    printf("%f", ceaMaiScumpaSaltea(ptr));
    printf("\nDupa schimbare locatie: \n");
    char locatie[20] = "Bulgaria";
    schimbaLocatie(ptr, locatie);
    afisare(ptr);
    free(magazin1.locatie);
    free(magazin1.pret);
}