#pragma once

//Gibt Vektor auf dem Bildschirm aus
void print_intvek(int* arr, int anz);

//links Rotation des �bergebenen Vektors
//Verwendung eingabe_int f�r rot (int rot = eingabe_int(">>>>", 1, anz, 3);)
void lrot_intvek(int* arr, int anz, int rot);

//rechts Rotation des �bergebenen Vektors
//Verwendung eingabe_int f�r rot (int rot = eingabe_int(">>>>", 1, anz, 3);)
void rrot_intvek(int* arr, int anz, int rot);

//l�schen eines Vektor Elements
//anz ist die Anzahl gef�llter Elemente, Bsp.: arr[20] = {1, 2, 3}; anz = 3
//ACHTUNG: Position ist nicht Vektorbassiert -> arr[0] == position 1 (NICHT 0)
//gibt 1 f�r erfolgreich und 0 f�r Fehler
int loeschen_intvek(int* vek, int* anz, int position);

//Entfernt alle doppelten Integer Werte aus dem �bergebenen Array
//�bergebene Anzahl entspricht der Anzahl der gef�llten Elemente  (Bsp.: arr[20] = {1, 2, 3}; anz = 3
void delduplikate_intvek(int* vek, int* anz);

//textbassiertes Speichern eines Vektors in einer Datei
//zuerst die Anzahl der Elemente des Vektors und dann den Vektor selbst
int tspeichern_intvek(int* arr, int anz, char *name);

//bin�r speichern eines Vekors in eine Datei
int bspeichern_intvek(int* arr, int anz, char *name);

//textbassiertes Laden eines vektors aus einer datei
//es wird �berpr�ft ob der �bergebene Vektor die menge an Elementen aus der datei aufnehmen kann
int tladen_intvek(int* arr, int* anz, char* name);