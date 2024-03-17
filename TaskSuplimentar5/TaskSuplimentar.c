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
    else {
        printf("NULL");
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
    if (v != NULL)
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

//Aici e codul pt task-ul 5:
struct elementLista {
    struct KashmirHome element;
    struct elementLista* elementUrmator;
};

void adaugareLista(struct elementLista** primulElement, struct KashmirHome magazin) {
    struct elementLista * elementNou = (struct elementLista*)malloc(sizeof(struct elementLista));
    elementNou->element = magazin;
    elementNou->elementUrmator = NULL;
    if (*primulElement != NULL) {
        //struct elementLista *ptr = *primulElement;
        //while (ptr->elementUrmator != NULL) {
        //    ptr = (ptr->elementUrmator);
        //}
        //ptr->elementUrmator = elementNou;
        if ((*primulElement)->element.nrSalteleInStoc > elementNou->element.nrSalteleInStoc) {
            elementNou->elementUrmator = *primulElement;
            *primulElement = elementNou;
            return;
        }
        struct elementLista* ptr = *primulElement;
        while (ptr->elementUrmator != NULL && ptr->elementUrmator->element.nrSalteleInStoc <= elementNou->element.nrSalteleInStoc) {
            ptr = (ptr->elementUrmator);
        }
        if (ptr->elementUrmator == NULL) {
            ptr->elementUrmator = elementNou;
        }
        else {
            struct elementLista* nextPtr = ptr->elementUrmator;
            elementNou->elementUrmator = nextPtr;
            ptr->elementUrmator = elementNou;
        }
    }
    else {
        *primulElement = elementNou;
    }
}
void citereDinFisierInLista(const char* nume, struct elementLista** primulElement) {
    FILE* f;
    f = fopen(nume, "r");
    if (f == NULL) {
        printf("Eroare la deschidere!");
        return NULL;
    }
    else {
        int nrMagazine = 0;
        fscanf(f, "%d", &nrMagazine);
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
            adaugareLista(primulElement, obiect);
        }
        fclose(f);

    }
}
void stergeElement(struct elementLista ** primulElement, int pozitie) {
    if(primulElement != NULL)
    {
        if (pozitie == 1) {
            struct elementLista* ptr;
            ptr = *primulElement;
            *primulElement = ptr->elementUrmator;
            free(ptr);
            return;
        }
        struct elementLista* ptr;
        ptr = *primulElement;
        int nrNoduri = 0;
        while (ptr->elementUrmator != NULL) {
            ptr = ptr->elementUrmator;
            nrNoduri++;
        }
        if (pozitie > nrNoduri+1) {
            return;
        }
        ptr = *primulElement;
        for (int i = 0; i < pozitie-2; i++) {
            ptr = ptr->elementUrmator;
        }
        if (ptr->elementUrmator->elementUrmator != NULL) {
            struct elementLista* deSters = ptr->elementUrmator;
            ptr->elementUrmator = ptr->elementUrmator->elementUrmator;
            free(deSters);
        }
        else {
            free(ptr->elementUrmator);
            ptr->elementUrmator = NULL;
        }
    }
}

void afisareLista(struct elementLista* primulElement) {
    while (primulElement != NULL) {
        afisare(primulElement);
        primulElement = primulElement->elementUrmator;
        printf("\n\n");
    }
}


struct kashmirHome* copiereInVector(struct elementLista * primulElement, int nrMinimSaltele, int * n) {
    struct elementLista * ptr = primulElement;
    int nrMagazine = 0;
    while (ptr != NULL) {
        if (ptr->element.nrSalteleInStoc >= nrMinimSaltele) {
            nrMagazine++;
        }
        ptr = ptr->elementUrmator;
    }
    *n = nrMagazine;
    if (nrMagazine == 0){
        return NULL;
    }
    else {
        int k = 0;
        struct KashmirHome* vector = (struct KashmirHome*)malloc(sizeof(struct KashmirHome) * nrMagazine);
        ptr = primulElement;
        while (ptr != NULL) {
            if (ptr->element.nrSalteleInStoc >= nrMinimSaltele) {
                vector[k++] = init(ptr->element.locatie, ptr->element.nrSalteleInStoc, ptr->element.pret);
            }
            ptr = ptr->elementUrmator;
        }
        return vector;
    }
}

void interschimbareElemente(struct elementLista** primulElement, int pozitie1, int pozitie2) {
    if (*primulElement == NULL) {
        return;
    }

    if (pozitie1 == pozitie2) {
        return;
    }

    struct elementLista* nod1 = *primulElement;
    struct elementLista* nod2 = *primulElement;
    struct elementLista* preNod1 = NULL;
    struct elementLista* preNod2 = NULL;

    int lungimeLista = 0;
    struct elementLista* ptr = *primulElement;

    // Calculăm lungimea listei
    while (ptr != NULL) {
        lungimeLista++;
        ptr = ptr->elementUrmator;
    }

    if (pozitie1 < 1 || pozitie2 < 1 || pozitie1 > lungimeLista || pozitie2 > lungimeLista) {
        return;
    }

    if (pozitie1 > pozitie2) {
        int temp = pozitie1;
        pozitie1 = pozitie2;
        pozitie2 = temp;
    }

    for (int i = 1; i < pozitie1; i++) {
        preNod1 = nod1;
        nod1 = nod1->elementUrmator;
    }

    for (int i = 1; i < pozitie2; i++) {
        preNod2 = nod2;
        nod2 = nod2->elementUrmator;
    }

    if (preNod1 != NULL) {
        preNod1->elementUrmator = nod2;
    }
    else {
        *primulElement = nod2;
    }

    if (preNod2 != NULL) {
        preNod2->elementUrmator = nod1;
    }
    else {
        *primulElement = nod1;
    }

    struct elementLista* temp = nod2->elementUrmator;
    nod2->elementUrmator = nod1->elementUrmator;
    nod1->elementUrmator = temp;
}

void main() {
    struct elementLista* primulElement = NULL;
    struct elementLista* ultimuLElement = NULL;
    int nrMagazine = 0;
    citereDinFisierInLista("data.txt", &primulElement);
    
    //afisareLista(primulElement);
    stergeElement(&primulElement, 10);
    afisareLista(primulElement);
    struct KashmirHome* lista = copiereInVector(primulElement, 3, &nrMagazine);
    for (int i = 0; i < nrMagazine; i++) {
        //afisare(&lista[i]);
    }
   // interschimbareElemente(&primulElement, 1, 10);
    //afisareLista(primulElement);
}