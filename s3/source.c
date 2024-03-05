#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = masini[i];//shallow copy
	}
	aux[*nrMasini] = m;
	(*nrMasini)++;//* e pusa pt dereferentiere si trebuie prioritizata asa ca pun paranteze

	//!!!!!trebuie sa sterg vectorul inutil verificand mai intai daca e ceva de sters
	if(masini !=NULL)
		free(masini);
	return aux;

}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];//asta e pt fgets, ca sa stie unde sa citeasca
	char delimitare[] = ",\n";

	struct Masina* masini=NULL;//initial avem 0 masini adica nu alocam spatiu
	(*nrMasini) = 0;

	while (fgets(buffer, 100, file) != NULL) {//citeste de la buffer, maxim 100 de caractere (pe linie gen) din fisierul file
		char* element = strtok(buffer, delimitare);//aici scoate din rand element cu element iduul, numele, nrusi si pretul

		struct Masina m;

		m.id = atoi(element);
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);

		masini = adaugareVector(masini, m, nrMasini);//atentie la adresa! ptc e pointer nu are nevoie de *
	}
	fclose(file);
	return masini;
}

int main() {

	struct Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireFisier("masini.txt", &nrMasini);//il transmitem prin adresa ptc se modifica
	for (int i = 0; i < nrMasini; i++) {
		printf("Masina nr. %d \n", i);
		printf("Id: %d \n", masini[i].id);
		printf("Producator: %s \n", masini[i].producator);
		printf("Nr. Usi %d \n", masini[i].nrUsi);
		printf("Pret %5.3f \n", masini[i].pret);
		printf("\n\n");
	}

	return 0;
}