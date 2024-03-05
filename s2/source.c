#include<stdio.h>
#include<malloc.h>

struct Farmacie {
	int id;
	char* nume;
	float suprafata;

};

//funct de initializare
struct Farmacie initializareFarmacie(int id, const char* nume, float suprafata)
{
	struct Farmacie f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char*) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;

	return f;

}

void afisareFarmacie(struct Farmacie farmacie) {
	printf("%d. %s are o suprafata de %5.2f mp\n", farmacie.id, farmacie.nume, farmacie.suprafata);
}

//functie de afisare vector
void afisareVector(struct Farmacie* farmacii, int nrFarmacii) {
	for (int i = 0; i < nrFarmacii; i++)
	{
		afisareFarmacie(farmacii[i]);
	}

}

//vector de copiere pt un nr de elemente
struct Farmacie* copiazaNElemente(struct Farmacie* vector, int nrFarmacii, int n) {
	//n=  nr orbiecte copiate
	if (n <= nrFarmacii && n > 0) {
		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * n);
		for (int i = 0; i < n; i++) {
			//copiat[i] = vector[i];shallow copy , nu merge ptc structura are elemente dinamice si se schimba doar adrese
			//trebuie sa facem copiere camp cu camp, ori fac facuntie de copiere ori refolosesc initializarea(asta fac)
			copiat[i] = initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
		return copiat;
	}
	else {
		return NULL;
	}
}

struct Farmacie* copiazaFarmaciiMici(struct Farmacie* farmacii, int nrFarmacii, float prag, int* nrFarmaciiMici) {

	*nrFarmaciiMici = 0;//il initializam cu 0 si il crestem cand cond e indeplinita
	for (int i = 0; i < nrFarmacii; i++) {
		if (farmacii[i].suprafata < prag){
			(*nrFarmaciiMici)++;
		}
	}
	//alocam spatiu noului vector
	struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*nrFarmaciiMici));//nrFarmaciiMici era pointer si trebuie dereferentiat
	int k = 0;//indexul noului vector
	for (int i = 0; i < nrFarmacii; i++) {
		if (farmacii[i].suprafata < prag){
			vector[k++] = initializareFarmacie(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata);
		}
	}
	////ca sa dezaloc pozitiile in care nu am pus trec din nou prin for si dezaloc negatia conditiei cu &
	return vector;
}

void dezalocareVectorFarmacii(struct Farmacie** vector, int* nrFarmacii) {//** se da adresa vectorului cu adrese, ptc a deveni null si a se dezaloca, nu pot sa pun doar * ptc e pointer gol idk

	for (int i = 0; i < *nrFarmacii; i++) {
		free((*vector)[i].nume);//dereferntiaz ca asa ajung la adresa finala si sa o sterg

	}
	free(*vector);
	*nrFarmacii = 0;
	*vector = NULL;
}

struct Farmacie getFarmacieById(struct Farmacie* vector, int nrFarmacii, int idCautat) {
	for (int i = 0; i < nrFarmacii; i++) {
		if (vector[i].id == idCautat) {
			return initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
	}
	return initializareFarmacie(0, "N/A", 0);

}


int main() {

	////un vector este o struct de date omogena, liniara, ocupa o zona de memorie contigua (ceea ce ne permite accesul)
	//int v1[40];declarat static (pe stiva)
	//alocare dinamica
	//int *v2=
	int nrFarmacii = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);
	for (int i = 0; i < nrFarmacii; i++)
	{
		farmacii[i] = initializareFarmacie(i + 1, "FARMACIE", 30 * i + 10);
	}
	afisareVector(farmacii, nrFarmacii);

	int nrObiecteCopiate = 2;

	struct Farmacie* farmaciiCopiate = copiazaNElemente(farmacii, nrFarmacii, nrObiecteCopiate);
	printf("\n\n");
	afisareVector(farmaciiCopiate, nrObiecteCopiate);

	farmacii[3].suprafata = 20;
	int nrFarmaciiMici = 0;

	struct Farmcaie* farmaciiMici = copiazaFarmaciiMici(farmacii, nrFarmacii, 50, &nrFarmaciiMici);
	printf("\n\n");
	afisareVector(farmaciiMici, nrFarmaciiMici);


	struct Farmacie farmacieCautata = getFarmacieById(farmacii, nrFarmacii, 9);
	printf("\nFarmacie cautata: ");
	afisareFarmacie(farmacieCautata);
	free(farmacieCautata.nume);

	dezalocareVectorFarmacii(&farmacii, &nrFarmacii);
	dezalocareVectorFarmacii(&farmaciiCopiate, &nrObiecteCopiate);
	dezalocareVectorFarmacii(&farmaciiMici, &nrFarmaciiMici);


}