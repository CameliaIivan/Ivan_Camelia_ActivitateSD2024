#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

struct Camin {
	char* camera;
	int nrstud;
	float regie;

};


int main()
{
	//Creati in functia main un vector alocat dinamic cu cel putin 5 obiecte de tipul structurii voastre.
	
	/*Funcția rand() din limbajul C este folosită pentru a genera un număr 
	pseudo-aleatoriu între 0 și RAND_MAX. RAND_MAX este o constantă definită în biblioteca stdlib.h 
	și reprezintă valoarea maximă pe care rand() o poate returna.*/
	srand(time(NULL));//INITIALIZARE se face obiligatoriu, cu time ca sa utilizeze timplul curent pentru generarea aleatoare
	
	//declarare
	struct Camin* v = (struct Camin*)malloc(sizeof(struct Camin) * 6);
	//struct Camin* e pointer ptc malloc returneaza adresa gen e pointerul general

	//initializare cu testare daca vectorul e nul sau nu
	for (int i = 0; i < 6; i++)
	{
		v[i].nrstud = rand() % 3 + 2;// se pune % cate valori sunt in interval aici 2 3 4
		// asta e daca vreau ca regia sa fie cu valori intregi : v[i].regie = (float)(rand() % 70 + 230);
		v[i].regie = (float)(rand() % 71 + 230) + ((float)(rand() % 101) / 100.0);

	}

	//afisare
	for (int i = 0; i < 6; i++) {
		printf("Camera %d: , Numar studenti: %d, Regie: %.2f\n",
			i + 101, v[i].nrstud, v[i].regie);
	}

	//stergere
	free(v);
	return 0;
}