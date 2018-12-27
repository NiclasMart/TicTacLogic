#pragma once

//Gibt Vektor auf dem Bildschirm aus
void print_intvek(int* arr, int anz);

//links Rotation des übergebenen Vektors
//Verwendung eingabe_int für rot (int rot = eingabe_int(">>>>", 1, anz, 3);)
void lrot_intvek(int* arr, int anz, int rot);

//rechts Rotation des übergebenen Vektors
//Verwendung eingabe_int für rot (int rot = eingabe_int(">>>>", 1, anz, 3);)
void rrot_intvek(int* arr, int anz, int rot);

//löschen eines Vektor Elements
//anz ist die Anzahl gefüllter Elemente, Bsp.: arr[20] = {1, 2, 3}; anz = 3
//ACHTUNG: Position ist nicht Vektorbassiert -> arr[0] == position 1 (NICHT 0)
//gibt 1 für erfolgreich und 0 für Fehler
int loeschen_intvek(int* vek, int* anz, int position);

//Entfernt alle doppelten Integer Werte aus dem übergebenen Array
//übergebene Anzahl entspricht der Anzahl der gefüllten Elemente  (Bsp.: arr[20] = {1, 2, 3}; anz = 3
void delduplikate_intvek(int* vek, int* anz);

//textbassiertes Speichern eines Vektors in einer Datei
//zuerst die Anzahl der Elemente des Vektors und dann den Vektor selbst
int tspeichern_intvek(int* arr, int anz, char *name);

//binär speichern eines Vekors in eine Datei
int bspeichern_intvek(int* arr, int anz, char *name);

//textbassiertes Laden eines vektors aus einer datei
//es wird überprüft ob der übergebene Vektor die menge an Elementen aus der datei aufnehmen kann
int tladen_intvek(int* arr, int* anz, char* name);