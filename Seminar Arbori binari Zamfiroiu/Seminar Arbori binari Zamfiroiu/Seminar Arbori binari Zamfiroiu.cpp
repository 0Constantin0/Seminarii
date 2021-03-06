// Seminar Arbori binari Zamfiroiu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Gradina {
	int nr_plante;
	char * denumire;
};
Gradina creareGradina(int x , const char * y) {
	Gradina aux;
	aux.denumire = (char*)malloc(sizeof(char)*(strlen(y) + 1));
	strcpy(aux.denumire, y);
	aux.nr_plante = x;
	return aux;
}
void afisareGradina(Gradina aux) {
	printf("Gradina = %s\n", aux.denumire);
	printf("Numar plante = %d\n", aux.nr_plante);
	printf("\n");
}
struct Nod {
	Gradina gradina;
	Nod * left;
	Nod * right;
};
Nod* creareNod(Gradina aux) {
	Nod * nou = (Nod*)malloc(sizeof(Nod));
	nou->left = 0;
	nou->right = 0;
	nou->gradina = aux;
	return nou;
}
Nod * inserareArbore(Nod* radacina , Gradina g) {
	if (radacina) {
		if (g.nr_plante < radacina->gradina.nr_plante) {
			radacina->left = inserareArbore(radacina->left, g);
		}
		else if (g.nr_plante > radacina->gradina.nr_plante){
			radacina->right = inserareArbore(radacina->right, g);
		}
		return radacina;
	}
	else {
		Nod * nou = creareNod(g);
		return nou;
	}
}
void afisareArborePost(Nod * radacina) { //RSD
	if (radacina) {
		afisareGradina(radacina->gradina);
		afisareArborePost(radacina->left);
		afisareArborePost(radacina->right);
	}
}

void afisareArborePre(Nod * radacina) { //SRD
	if (radacina) {
		afisareArborePre(radacina->left);
		afisareGradina(radacina->gradina);		
		afisareArborePre(radacina->right);
	}
}
void afisareArboreSDR(Nod * radacina) { //SDR
	if (radacina) {
		afisareArboreSDR(radacina->left);	
		afisareArboreSDR(radacina->right);
		afisareGradina(radacina->gradina);
	}
}
Gradina cautareGradina_nrPlante(Nod * radacina, int nr_plante) {
	if (radacina) {
		if (radacina->gradina.nr_plante == nr_plante)
			return radacina->gradina;
		else if (radacina->gradina.nr_plante < nr_plante) {
			return cautareGradina_nrPlante(radacina->right, nr_plante);
			}
		else return cautareGradina_nrPlante(radacina->left, nr_plante);

			
		
	}
	return creareGradina(-1,"");
}

void StergereSDR(Nod ** radacina) {
	if (*radacina) {
		StergereSDR(&(*radacina)->left);
		StergereSDR(&(*radacina)->right);
		free((*radacina)->gradina.denumire);
		free(*radacina);
		*radacina = 0;
		
	}
}
int inaltime(Nod * radacina) {
	if (radacina) {
		int stanga = inaltime(radacina->left);
		int dreapta = inaltime(radacina->right);
		int maxim = stanga < dreapta ? dreapta : stanga;
		maxim++;
		return maxim;
	}
	return 0;
}
int main()
{
	Nod * radacina = 0;
	radacina = inserareArbore(radacina, creareGradina(8, "Cismigiu"));
	radacina = inserareArbore(radacina, creareGradina(10, "Botanica"));
	radacina = inserareArbore(radacina, creareGradina(9, "Carol1"));
	radacina = inserareArbore(radacina, creareGradina(3, "Zoologica"));
	radacina = inserareArbore(radacina, creareGradina(1, "Herestrau"));
	radacina = inserareArbore(radacina, creareGradina(6, "Mihai1"));
	radacina = inserareArbore(radacina, creareGradina(5, "Moghiros"));
	//afisareArborePre(radacina);
	//afisareArborePost(radacina); //cauta sa fii sigur
	afisareArboreSDR(radacina);
	afisareGradina(cautareGradina_nrPlante(radacina, 9));
	printf("%d\n", inaltime(radacina));
	StergereSDR(&radacina);
	afisareArborePost(radacina);
	printf("%d\n", inaltime(radacina));
	return 0;
}

