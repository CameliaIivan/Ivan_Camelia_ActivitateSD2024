#define CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h> //pt malloc gen alocare memorie pointer

struct Cofetarie {

	char* nume;
	int nrang;
	float* salarii; //e float* ptc e vector de salrii
	//am creat o stuctura cofetarie care are drept campuri numele cofetariei, nr de angajati si saleriile lor

};

void afisarecof(struct Cofetarie c) {
	if (c.nume != NULL) {
		printf("Nume :%s:\n", c.nume);
	}
	printf("Nr. Angajati:%d:\n", c.nrang);
	if (c.salarii != NULL) {
		printf("Salarii:");
		for (int i = 0; i < c.nrang; i++)
		{
			printf("%5.2f, ", c.salarii[i]);
		}
		printf("\n");
	}
}

//functie initializare
struct Cofetarie initializarecof(const char* nume, int nrang, const float* salarii) {
	struct Cofetarie c;
	c.nume = malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrang = nrang;
	c.salarii = malloc(sizeof(float) * nrang);
	for (int i = 0; i < nrang; i++)
	{
		c.salarii[i] = salarii[i];
	}
	return c;
}

void stergecof(struct Cofetarie c) {
	if (c.nume != NULL) {
		free(c.nume);
	}
	free(c.salarii);
	c.nume = NULL;
	c.salarii = NULL;
}

int main()
{
	//delarare obiect de tip cofetarie
	struct Cofetarie cof1;
	//se intializeaza fiecare atribut in parte
	//atribut=(tip)malloc(dimensiunea numelui + 1)
	cof1.nume = (char*)malloc(strlen("Dulce") + 1);
	/* fiind pointer ii alocam memorie cu malloc gen alocare dinamica
	* primeste ca dimensiune un nr de octeti gen (sterlen de nr +1) octeti
	* malloc returneaza un pointer  pt adresa de memorie adica void*(pointer general) dar transformam in (char*)
	* procesul asta din void* in char* se cheama cast, poate fi implicit de la compilator sau nu
	*/
	strcpy(cof1.nume, "Dulce"); //copiez numele in memoria alocata
	cof1.nrang = 3;
	
	//pt vectorul de salarii mai intai alocam memorie apoi facem for
	cof1.salarii = (float*)malloc(sizeof(float) * cof1.nrang);//size of de float e 4 octeti si inmultim cu nr de alemente
	for (int i = 0; i < cof1.nrang; i++)
		{
			cof1.salarii[i] = (i + 1) * 1000;
		}

	//afisare , asa e fara functie: printf("%s", cof1.nume);
	afisarecof(cof1);

	afisarecof(cof1);

	float* vector = malloc(sizeof(float) * 2);
	vector[0] = 5555;
	vector[1] = 88636;

	struct Cofetarie cof2 = initializarecof("Mara", 2, vector);
	afisarecof(cof2);

	free(vector);
	free(cof2.nume);
	free(cof2.salarii);

	//se poate crea o functie care sa dezaloce simultan zonele de memorie gen nu ma8i scriu  free pt cof1 si cof2
	stergecof(&cof2);
	//aici daca pun & imi da o eroare dar daca pun fara imi da bine


	//stergere, daca am alocat cu malloc, stergem cu free, daca alocam cu new stergem cu delete/pt cof1
	free(cof1.nume);
	free(cof1.salarii);

	return 0;
}