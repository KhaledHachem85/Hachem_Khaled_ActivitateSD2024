#include <stdio.h>
#include <malloc.h>
struct Avion {
	int nrPasageri;
	char* companie;
	float pretBilet;

};

struct Avion init(int nrPasageri, const char* companie, float pretBilet) {
	struct Avion avion;
	avion.nrPasageri = nrPasageri;
	avion.pretBilet = pretBilet;
	avion.companie = (char*)malloc(strlen(companie) + 1);
	strcpy(avion.companie, companie);
	return avion;
}

void afisareAvion(struct Avion a) {
	printf("%s are un avion de %d locuri cu pretul de %5.2f RON pe loc.\n", a.companie, a.nrPasageri, a.pretBilet);
}
void afisareAvioane(struct Avion* v, int n) {
	if (v != NULL) {
		for (int i = 0; i < n; i++) {
			afisareAvion(v[i]);
		}
	}
}
struct Avion* copiazaPrimeleNAvioane(struct Avion* v, int nrAvioane, int n) {
	if (n < nrAvioane && n > 0) {
		struct Avion* copie = (struct Avion*)malloc(sizeof(struct Avion) * n);
		for (int i = 0; i < n; i++) {
			copie[i] = init(v[i].nrPasageri, v[i].companie, v[i].pretBilet);
		}
		return copie;
	}
}

void dezalocare(struct Avion** v, int* n) {
	if ((*v) != NULL)
	{
		for (int i = 0; i < *n; i++) {
			free((*v)[i].companie);
		}
		free(*v);
		*n = 0;
		*v = NULL;
	}
}

void copiazaAvioanePretRedus(struct Avion* v, int n, float pret, struct Avion** avioaneNou, int* dimensiune) {
	if (*avioaneNou != NULL) {
		dezalocare(avioaneNou, dimensiune);
	}
	else {
		*dimensiune = 0;
	}
	for (int i = 0; i < n; i++) {
		if (v[i].pretBilet < pret) {
			(*dimensiune)++;
		}
	}
	*avioaneNou = (struct Avion*)malloc(sizeof(struct Avion) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < n; i++) {
		if (v[i].pretBilet < pret) {
			(*avioaneNou)[k++] = init(v[i].nrPasageri, v[i].companie, v[i].pretBilet);
		}
	}
}

struct Avion getPrimulAvionDupaCompanie(struct Avion* v, int n, const char* companieCautata) {
	if (v != NULL) {
		for (int i = 0; i < n; i++) {
			if (v[i].companie != NULL) {
				if (strcmp(v[i].companie, companieCautata) == 0) {
					struct Avion av = init(v[i].nrPasageri, v[i].companie, v[i].pretBilet);
					return av;
				}
			}
		}
	}
	else {
		return init(0, "/N", 0);
	}
}

void main() {
	int nrAvioane = 5;
	struct Avion* avioane = (struct Avion*)malloc(sizeof(struct Avion) * nrAvioane);
	for (int i = 0; i < nrAvioane; i++) {
		avioane[i] = init(100 + i * 10, "Tarom", i * 35.5 + 200);
	}
	int nrCp = 2;
	afisareAvioane(avioane, nrAvioane);
	struct Avion* cp = copiazaPrimeleNAvioane(avioane, 5, nrCp);
	printf("\n\n");
	afisareAvioane(cp, nrCp);
	struct Avion* avioaneReduse = NULL;
	int nrAvioaneReduse = 0;
	copiazaAvioanePretRedus(avioane, 5, 300, &avioaneReduse, &nrAvioaneReduse);
	printf("\n\n");
	afisareAvioane(avioaneReduse, nrAvioaneReduse);
	printf("\n\n");
	struct Avion av = getPrimulAvionDupaCompanie(avioane, nrAvioane, "Tarom");
	afisareAvion(av);

	dezalocare(&avioane, &nrAvioane);
	dezalocare(&avioaneReduse, &nrAvioaneReduse);
	dezalocare(&cp, &nrCp);
	free(av.companie);
	av.companie = NULL;
}