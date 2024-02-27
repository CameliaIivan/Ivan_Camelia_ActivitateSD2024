#include<stdio.h>
#include<malloc.h>

struct Farmacie {
	int id;
	char* nume;
	float suprafata;

};

//funct de initializare
struct Farmacie initializareFarm(int id, const char* nume, float suprafata)
{
	struct Farmacie f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char*) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;

	return f;

}

void afisareFarm(struct Farmacie farmacie) {
	printf("%d. %s are o suprafata de %5.2f\n", farmacie.id, farmacie.nume, farmacie.suprafata);
}

//functie de afisare vector
void afisareVector(struct Farmacie* farmacii, int nrFarm) {
	for (int i = 0; i < nrFarm; i++)
	{
		afisareFarm(farmacii[i]);
	}

}

//vector de copiere pt un nr de elemente
struct Farmacie* copiazaNelem(struct Farmacie* vector, int nrFarm, int nrObiecteCop) {
	if (nrObiectecop <= nrFarm && nrObiecteCop > 0) {
		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrObiecteCop);
		for (int i = 0; i < nrObiecteCop; i++) {
			//copiat[i] = vector[i];shallow copy , nu merge ptc structura are elemente dinamice si se schimba doar adrese
			//trebuie sa facem copiere camp cu camp, ori fac facuntie de copiere ori refolosesc initializarea(asta fac)
			copiat[i] = initializareFarm(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
		return copiat;
	}
	else {
		return NULL;
	}
}

struct Farmacie* copiazaFarmaciiMici(struct Farmacii* farmacii, int nrFarm, float prag, int* nrFarmaciiMici) {

	*nrfarmaciiMici = 0;//il initializam cu 0 si il crestem cand cond e indeplinita
	for (int i = 0; i < nrFarm; i++) {
		if (farmacii[i]) < prag){
			(*nrFarmaciiMici)++;
		}
	}
	//alocam spatiu noului vector
	struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*nrFarmaciiMici));//nrFarmaciiMici era pointer si trebuie dereferentiat
	int k = 0;//indexul noului vector
	for (int i = 0; i < nrFarm; i++) {
		if (farmacii[i]) < prag){
			vector[k++] = initializareFarm(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata);
		}
	}
	return vector;
}

void dezalocareVectorfarmacii(struct Farmacie** vector, int* nrFarm) {//** se da adresa vectorului cu adrese, ptc a deveni null si a se dezaloca, nu pot sa pun doar * ptc e pointer gol idk

	for (int i = 0; i < *nrFarm; i++) {
		free((*vector)[i].nume);//dereferntiaz ca asa ajung la adresa finala si sa o sterg

	}
	free(*vector);
	*nrFarm = 0;
	*vector = NULL;
}

struct Farmacie getFarmaciebyid(struct Farmacie* vector, int nrFarmacii, int idCautat) {
	for (int i = 0; i < nrFarmacii; i++) {
		if (vector[i].id == idCautat) {
			return initializareFarm(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
	}
	return initializareFarm(0, "N/A", 0);

}


int main() {

	//int v1[40];declarat static (pe stiva)
	//alocare dinamica
	//int *v2=
	int nrFarm = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarm);
	for (int i = 0; i < nrFarm; i++)
	{
		farmacii[i] = initializareFarm(i + 1, "FARMACIE", 30 * i + 10);
	}
	afisareVector(farmacii, nrFarm);

	int nrFarmaciicop = 2;

	struct Farmacie* farmCopiate = copiazaNelem(farmacii, nrFarm, nrFarmaciicop);
	printf("\n\n");
	afisareVector(vectorCopiat, nrObiectecop);

	int nrFarmaciiMici = 0;

	farmacii[3].suprafata = 20;

	struct Farmcaie* farmaciiMici = copiazaFarmaciiMici(farmacii, nrFarm, 50, &nrFarmaciiMici);
	printf("\n\n");
	afisareVector(farmaciiMici, nrFarmaciiMici);


	struct Farmacie farmaciecautata = getFarmaciebyid(farmacii, nrFarm, , 3);
	printf("\nFarmacie cautata\n");
	afisareFarm(farmaciecautata);
	free(farmaciecautata.nume);

	dezalocareVectorfarmacii(&farmacii, &nrFarm);
	dezalocareVectorfarmacii(&farmCopiate, &nrFarmaciicop);
	dezalocareVectorfarmacii(&farmaciiMici, &nrFarmaciiMici);


}