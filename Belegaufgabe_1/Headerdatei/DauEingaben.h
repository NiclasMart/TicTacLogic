#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#pragma once



/*Eingabe von einem Wert im Bereich von min bis max (falls keine Grenze gegeben;
dem User wird über promt angegen was er eingeben soll;
zudem zählt count wie viele Versuche der User zur Eingabe hat; 
... bei nichteinhaltung der Grenzen oder des Datentyps (int), kann
er es so oft neu probieren, wie er Versuche (count) hat, danach wird das Programm beendet*/
int eingabe_int (char* promt, char min, char max, int count ){
	
	int i;

	//Counter zählen (wenn == 0 --> exit Programm)
	if (count == 0) {
		printf("Maximale Anzahl an Versuchen aufgebraucht. \nProgramm wird beendet!\n");
		exit(1);
	}
	//Prompt ausgeben
	printf("%s ",promt);

	//Datentyp prüfen + Wert einlesen


	if (scanf_s("%d", &i) != 1) {
		printf(">>> FEHLER: Bitte ganzzahligen Wert eingeben! (Noch %d Versuche \201brig)\n", count-1);
		while (fgetc(stdin) != '\n')								
			;
		return eingabe_int(promt, min, max, count - 1);
	}

	if (fgetc(stdin) != '\n') {
		printf(">>> FEHLER: Eingegebene Zeichenfolge kann nicht verarbeitet werden! (Noch %d Versuche \201brig)\n", count - 1);
		while (fgetc(stdin) != '\n')
			;
		return eingabe_int(promt, min, max, count - 1);
	}

	//Min,Max prüfen
	if ((min == 'n') && (max == 'n')) return i;

	if ((i < ((int)min - '0')) && (max == 'n')) {
		printf(">>>Fehler: Bitte untere Grenze [%c] beachten! (Noch %d Versuche \201brig)\n", min, count - 1);
		return eingabe_int(promt, min, max, count - 1);
	}
	else return i;

	if ((i > ((int)max - '0')) && (min == 'n')) {
		printf(">>>Fehler: Bitte obere Grenze [%c] beachten! (Noch %d Versuche \201brig)\n", max, count - 1);
		return eingabe_int(promt, min, max, count - 1);
	}
	else return i;
	
	if ((i < ((int)min - '0')) || (i > ((int)max - '0'))) {
		printf(">>>Fehler: Bitte Wertebereich [%c, %c] beachten! (Noch %d Versuche \201brig)\n", min, max, count - 1);
			return eingabe_int(promt, min, max, count - 1);
	}
	

	return i;
}

/*Eingabe von einem Character mit Überprüfung ;
dem User wird über promt angegen was er eingeben soll;
zudem zählt count wie viele Versuche der User zur Eingabe noch hat; 
... bei nichteinhaltung der erlaubten Zeichen, welche in Form eines
Strings übergeben werden(char *letter), kann er es so oft neu probieren, wie er 
Versuche (count) hat, danach wird das Programm beendet*/

char eingabe_char(char *promt, char *letter, int count){
	char i; int l = 0;

	//Counter zählen (wenn == 0 --> exit Programm)
	if (count == 0){
		printf("Maximale Anzahl an Versuchen aufgebraucht. \nProgramm wird beendet!\n");
		exit(1);
	}
	//Prompt ausgeben
	printf("%s ", promt);
	scanf_s("%c", &i);

	//erneutes einlesen, falls noch Zeichen von auserhalb in das Programm kommen (Reste im Eingabepuffer, von Eingaben vor dem Funktionsaufruf)
	while ((i == '\n')||(i==10)){
		scanf_s("%c", &i);
	}
	
	//Buchstaben mittels übergebenem string prüfen
	int erfolgreich = 0;
	
	for (int j = 0; letter[j]!='\0'; j++){
		if (i == letter[j]) ++erfolgreich;
	}
	
	//Falls noch Zeichen im Eingabepuffer sind diese löschen und l hochzählen (für Fehlerausgabe, dass nur ein char eingegeben werden soll
	while (fgetc(stdin) != '\n')
		l++;

	if (l) {
		printf(">>>Fehler: Bitte nur ein Zeichen eingeben. (Noch %d Versuche \201brig)\n", count-1);
		return eingabe_char(promt, letter, --count);
	}

	if (!erfolgreich) {
		printf(">>>Fehler: Buchstabe steht nicht zur Eingabe zur Verf\201gung (besser: %s)! (Noch %d Versuche \201brig)\n",letter, count-1);
		return eingabe_char(promt, letter, --count);
	}

	
	return i;

}
