#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Locuinta {
	int id;
	char* strada;
	int numar;
};

void inserare(struct Locuinta** vector, int* dim, struct Locuinta l) {
	struct Locuinta* copie;
	copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) * ((*dim)+1));
	for (int i = 0; i < (*dim); i++) {
		copie[i] = (*vector)[i];
	}
	(*dim)++;
	copie[*dim - 1] = l;
	if (*vector != NULL) {
		free(*vector);
	}
	*vector = copie;
}

void citesteDinFisier(const char* numeFisier, struct Locuinta** locuinte, int* dim) {
	*dim = 0;
	//if ((numeFisier == NULL) || !strlen(numeFisier > 0)) {
	//	return;
	//}
	FILE* f;
	f = fopen(numeFisier, "r");
	if (f == NULL) {
		return;
	}
	char buffer[100];
	char delimitator[] = ",\n";
	while (fgets(buffer, 100, f) != NULL) {
		char* token = strtok(buffer, delimitator);
		struct Locuinta locuinta;
		locuinta.id = atoi(token);
		token = strtok(NULL, delimitator);
		locuinta.strada = (char*)malloc(strlen(token) + 1);
		strcpy(locuinta.strada, token);
		token = strtok(NULL, delimitator);
		locuinta.numar = atoi(token);
		inserare(locuinte, dim, locuinta);
	}
	fclose(f);
}
void afisareLocuinte(struct Locuinta l) {
	printf("\nId-ul: %d \nStrada: %s\nNumarul:%d", l.id, l.strada, l.numar);
}

void afisareVector(struct Locuinta* vector, int dim) {

		for (int i = 0; i < dim; i++) {
			afisareLocuinte(vector[i]);
		}
}

void stergeDupaId(struct Locuinta** vector, int* dim, int id) {
	char flag = 0;
	for (int i = 0; i < i < (*dim); i++) {
		if ((*vector)[i].id == id) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		//avem de sters
		int k = 0;
		struct Locuinta* copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) *
			(--(*dim)));
		for (int i = 0; i < (*dim) + 1; i++) {
			if ((*vector)[i].id != id) {
				copie[k++] = (*vector)[i];
			}
		}
		if ((*vector) != NULL)
			free((*vector));
		(*vector) = copie;
	}
}

void main() {
	struct Locuinta* locuinte = NULL;
	int dim = 0;
	citesteDinFisier("Locuinte.txt", &locuinte, &dim);
	printf("\nInitial: \n");
	afisareVector(locuinte, dim);
	printf("\nStergere struct cu ID 13: \n");
	stergeDupaId(&locuinte, &dim, 13);
	afisareVector(locuinte, dim);

}