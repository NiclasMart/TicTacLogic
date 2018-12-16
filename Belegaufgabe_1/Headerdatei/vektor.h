#include<stdio.h>
#include<math.h>
#include "../Headerdatei/DauEingaben.h"

#pragma once



//Gibt Vektor auf dem Bildschirm aus
void print_intvek(int* arr, int anz){
	for (int i = 0; i < anz; i++){
		printf("%d ", arr[i]);
		if (i < anz - 1) printf(", ");
	}
}


//links Rotation des übergebenen Vektors
//Verwendung eingabe_int für rot (int rot = eingabe_int(">>>>", 1, anz, 3);)
void lrot_intvek(int* arr, int anz, int rot){
	
	for (int j = 0; j < rot; j++){
		int temp = arr[0];
		for (int i = 0; i < anz; i++){
			arr[i] = arr[i + 1];
		}
		arr[anz - 1] = temp;
	}
	
}


//rechts Rotation des übergebenen Vektors
//Verwendung eingabe_int für rot (int rot = eingabe_int(">>>>", 1, anz, 3);)
void rrot_intvek(int* arr, int anz, int rot) {
	

	for (int j = 0; j < rot; j++) {
		int temp = arr[anz - 1];
		for (int i = anz - 1; i >= 0; i--) {
			arr[i] = arr[i - 1];
		}
		arr[0] = temp;
	}
	
}


//löschen eines Vektor Elements
//anz ist die Anzahl gefüllter Elemente, Bsp.: arr[20] = {1, 2, 3}; anz = 3
//ACHTUNG: Position ist nicht Vektorbassiert -> arr[0] == position 1 (NICHT 0)
//gibt 1 für erfolgreich und 0 für Fehler
int loeschen_intvek(int* vek, int* anz, int position){
	if (*anz == 0) return 0;
	if ((position<=0) || (position>*anz)) return 0;
	
	
	while (position < *anz){
		vek[position-1] = vek[position];
		position++;
	}
	(*anz)--;
	vek[*anz] = 0;
	return 1;
}


//einfügen eines Vektorelements
//anz ist die Anzahl gefüllter Elemente, Bsp.: arr[20] = {1, 2, 3}; anz = 3
//gibt 1 für erfolgreich und 0 für Fehler
int einfügen_intvek(int* vek, int* anz, int value, int position) {
	if (*anz == 0) return 0;
	if ((position <= 0) || (position > (*anz)+1)) return 0;

	for (int i = *anz; i >= (position-1); i--) {
		vek[i + 1] = vek[i];
	}

	vek[position-1] = value;
	(*anz)++;
	return 1;
}



//Entfernt alle doppelten Integer Werte aus dem übergebenen Array
//übergebene Anzahl entspricht der Anzahl der gefüllten Elemente  (Bsp.: arr[20] = {1, 2, 3}; anz = 3
void delduplikate_intvek(int* vek, int* anz){
	for (int i = 0; i < (*anz - 1); i++){
		int temp1 = vek[i];
		

		for (int j = i + 1; j < *anz ; j++){
			while (temp1 == vek[j]){
				loeschen_intvek(vek, anz, j+1);
	
			}
		}
		
	}
}


//textbassiertes Speichern eines Vektors in einer Datei
//zuerst die Anzahl der Elemente des Vektors und dann den Vektor selbst
int tspeichern_intvek(int* arr, int anz, char *name) {
	int i;
	FILE *fp;
	if ((fp = fopen(name, "w+t")) == 0) {
		printf("\nFehler: konnte Datei %s nicht \224ffnen", name);
		return 0;
	}
	if (fprintf(fp, "%d\n", anz) == 0){
		printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
		exit(1);
	}
	for (i = 0; i < anz; i++){
		if (fprintf(fp, "%d ", arr[i]) == 0){
			printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
			exit(1);
		}
	}
	fclose(fp);
	return 1;
}


//binär speichern eines Vekors in eine Datei
int bspeichern_intvek(int* arr, int anz, char *name) {
	int i;
	FILE *fp;
	if ((fp = fopen(name, "w+b")) == 0) {
		printf("\nFehler: konnte Datei %s nicht \224ffnen", name);
		return 0;
	}
	if (fwrite(&anz, sizeof(int), 1, fp) == 0){
		printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
		exit(1);
	}
	if (fwrite(arr, sizeof(int), anz, fp) == 0){
		printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
		exit(1);
	}
	
	fclose(fp);
	return 1;
}





//textbassiertes Laden eines vektors aus einer datei
//es wird überprüft ob der übergebene Vektor die menge an Elementen aus der datei aufnehmen kann
int tladen_intvek(int* arr, int* anz, char* name){
	FILE *fp;
	if ((fp = fopen(name, "r+t")) == 0){
		printf("\nFehler: konnte Datei %s nicht \224ffnen", name);
		return 0;
	}
	//Laden der Anzahl
	int test = *anz;
	if (fscanf(fp, "%d", anz) != 1){
		printf("\nFehler datei Inhalt konnte nicht richtig geladen werden!\n");
		exit(1);
	}

	//prüfen ob größe des vektors geeignet
	if (test < *anz){
		printf("Fehler: Array kann Elemente aus der datei nicht laden!\n");
		exit(3);
	}

	//Laden des Vektors
	for (int i = 0; i < *anz; i++){
		if (fscanf(fp, "%d", &arr[i]) != 1){
			printf("\nFehler datei Inhalt konnte nicht richtig geladen werden!\n");
			exit(1);
		}
		
	}
	fclose(fp);
	return 1;
}




