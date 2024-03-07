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
struct KashmirHome* stocMaiMareDecatUnu(struct KashmirHome* vector, int n, int* nrRez) {
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

struct KashmirHome* stocZero(struct KashmirHome* vector, int n, int* nrRez) {
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
    if (vector != NULL) {
        printf("\n\nMagazine: \n\n");
        for (int i = 0; i < n; i++) {
            afisare(&vector[i]);
            printf("\n\n");
        }
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

struct KashmirHome* citereDinFisier(const char* nume, int* n) {
    FILE* f;
    f = fopen(nume, "r");
    if (f == NULL) {
        printf("Eroare la deschidere!");
        return NULL;
    }
    else {
        int nrMagazine = 0;
        fscanf(f, "%d", &nrMagazine);
        *n = nrMagazine;
        struct KashmirHome* v = (struct KashmirHome*)malloc(sizeof(struct KashmirHome) * nrMagazine);
        for (int i = 0; i < nrMagazine; i++)
        {
            struct KashmirHome obiect;
            obiect.locatie = NULL;
            obiect.pret = NULL;
            obiect.nrSalteleInStoc = 0;
            char buffer[100];
            fscanf(f, "%s", buffer);
            obiect.locatie = (char*)malloc(strlen(buffer) + 1);
            strcpy(obiect.locatie, buffer);
            fscanf(f, "%d", &obiect.nrSalteleInStoc);
            obiect.pret = (float*)malloc(sizeof(float) * obiect.nrSalteleInStoc);
            for (int j = 0; j < obiect.nrSalteleInStoc; j++) {
                fscanf(f, "%f, ", &obiect.pret[j]);
            }
            v[i] = obiect;
        }
        fclose(f);
        return v;
    }
}

void scriereInFisier(struct KashmirHome* v, int n, const char* nume) {
    if(v != NULL)
    {
        FILE* f;
        f = fopen(nume, "w");
        if (f == NULL) {
            printf("Eroare la deschidere!");
            return;
        }
        else {
            fprintf(f, "%d\n", n);
            for (int i = 0; i < n; i++) {
                fprintf(f, "%s\n", v[i].locatie);
                fprintf(f, "%d\n", v[i].nrSalteleInStoc);
                for (int j = 0; j < v[i].nrSalteleInStoc; j++) {
                    fprintf(f, "%5.2f ", v[i].pret[j]);
                }
                fprintf(f, "\n");
            }
            fclose(f);
        }
    }
}
struct KashmirHome** adaugaInMatrice(struct KashmirHome* vector, int dim, int**marimi, int * nrLinii) {
    if (vector != NULL) {
        int maxStoc = 0; //determina cate linii sunt in matrice (maxStoc + 1); Obiectele sunt asezate in linii in functie de cat au in stoc (stoc 0 = linia 0...)
        for (int i = 0; i < dim; i++) {
            if (vector[i].nrSalteleInStoc > maxStoc) {
                maxStoc = vector[i].nrSalteleInStoc;
            }
        }
        *nrLinii = maxStoc + 1;
        struct KashmirHome** matrice = (struct KashmirHome**)malloc(sizeof(struct KashmirHome*) * (1 + maxStoc)); //aloca numarul de adrese (numarul de linii)
        (*marimi) = (int*)malloc((1 + maxStoc) * sizeof(int));
        for (int i = 0; i < maxStoc + 1; i++) {
            int nrCompanii = 0;
            for (int j = 0; j < dim; j++) {
                if (vector[j].nrSalteleInStoc == i) {
                    nrCompanii++;
                }
            }
            (*marimi)[i] = nrCompanii;
            printf("Nr companii cu %d in stoc este %d \n", i, (*marimi)[i]);
            if(i > 0)
            {
                matrice[i] = (struct KashmirHome*)malloc((nrCompanii) * sizeof(struct KashmirHome));
                int k = 0;
                for (int j = 0; j < dim; j++) {
                    if (vector[j].nrSalteleInStoc == i) {
                        matrice[i][k++] = init(vector[j].locatie, vector[j].nrSalteleInStoc, vector[j].pret);
                    }
                }
            }
            else {
                matrice[i] = NULL;
            } 
        }
        return matrice;
    }
}

struct KashmirHome** sortareLiniiMatrice(struct KashmirHome**matrice, int nrLinii, int** marimi) {
    struct KashmirHome * auxKH;
    int marimeMaxima = 0;
    for (int i = 0; i < nrLinii; i++) {
        for(int j = 0; j < nrLinii; j++)
        {
            if ((*marimi)[j] > (*marimi)[i] && j > i) {
                int aux = (*marimi)[i];
                (*marimi)[i] = (*marimi)[j];
                (*marimi)[j] = aux;
                auxKH = matrice[i];
                matrice[i] = matrice[j];
                matrice[j] = auxKH;
            }
        }
    }
    for (int i = 0; i < nrLinii; i++) {
        printf("%d ", (*marimi)[i]);
    }
    return matrice;
}

void afisareMatrice(int nrLinii, struct KashmirHome** matrice, int *marimi) {
    for (int i = 0; i < nrLinii; i++) {
        afisareVector(matrice[i], marimi[i]);
    }
}

void main() {
    int nrMagazine = 0;
    int *marimi;
    int nrLinii;
    struct KashmireHome* k = citereDinFisier("data.txt", &nrMagazine);
    struct KashmirHome** matrice = adaugaInMatrice(k, nrMagazine, &marimi, &nrLinii);
    afisareMatrice(nrLinii, matrice, marimi);


    printf("\n\n\n\n\n");
    struct KashmirHome** matrice2 = sortareLiniiMatrice(matrice, nrLinii, &marimi);
    afisareMatrice(nrLinii, matrice2, marimi);

    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < marimi[i]; j++) {
            dezalocare(&matrice[i][j]);
        }
        free(matrice[i]);
        matrice[i] = NULL;
    }
    free(marimi);
    dezalocare(k);
    free(k);
}