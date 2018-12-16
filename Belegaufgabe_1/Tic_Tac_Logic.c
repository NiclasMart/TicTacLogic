/*Belegaufgabe Tic-Tac-Logic
Start 02.12.2018*/

#include <stdio.h>
#include <stdlib.h>
#include "Headerdatei/DauEingaben.h"
#include "Headerdatei/vektor.h"



int menu(char* prompt, int min, int max, int count);
void new_game();
void set_array(char arr[10][10], int choice, int* anz);
void print_field(char arr[10][10]);
void load_game();
void load_arr(char arr[10][10], char* name, int* anz);
void check_savegames(char* check);
void display_rules();
void save_arr(char arr[10][10], char *name, const int* anz);
void display_savegames(char* check);
void save_game(char arr[10][10], int *anz);
void set_check(char* check, int choice, char mode);
void options();
void delete_game();


int main() {

	printf("\n\t\t***Herzlich Willkommen zu \"Tic-Tac-Logic\"!***\n");

	while (1) {

		switch (menu("\n\nMen\201:\n\n1 - Spiel Laden\n2 - Neues Spiel\n3 - Optionen\n4 - About\n5 - Exit\n\n", 1, 5, 5)) {

		case 1: //Spiel Laden
			load_game();
			break;
		case 2: //Neues Spiel
			new_game();
			break;
		case 3: //optionen
			options();
			
			break;
		case 4: //About

			break;
		case 5: //Exit
			printf("\nDanke fürs Spielen. Bis zum nächsten Mal :D");
			return 0;
			break;
		}
	}
	return 0;
}


//ruft das Menü auf und ließt gewünschten Menü - Punkt von User DAU Sicher ein
int menu(char* prompt, int min, int max, int count) {
	printf("%s", prompt);
	return eingabe_int(">>>", min, max, count);
}


//Läd einen Spielstand aus einem vorherigen Spiel
void load_game() {
	char check[3], arr[10][10];
	int anz;

	while (1) {
		set_array(arr, 4, &anz);

		//Ausgabe der Auswahl über die display_savegames Funktion
		printf("\nWelchen Spielstand m\224chtest du laden ?\n");
		display_savegames(check);
		printf("0 - Zum Hauptmen\201 zur\201ck kehren!\n\n");

		//Auswahl des Spielers und return falls Rückkehr zum Hauptmenü (0) ausgewählt worde
		int choice = eingabe_int(">>>", 0, 3, 5);
		if (choice == 0) return;

		//verhindert, dass ein leerer Spielstand geladen wird
		if (check[choice - 1] == '0') {
			printf("\nDieser Spielstand kann nicht geladen werden, da keine Speicherdaten vorliegen (Spielstand ist leer)!\nBitte einen vollen Spielstand w\204hlen!\n\n");
			continue;
		}

		//Spielstand aus entsprechender Datei wird über load_arr Funktion geladen
		switch (choice) {
		case 1: load_arr(arr, "Saves/save_game1.txt", &anz);
			break;
		case 2: load_arr(arr, "Saves/save_game2.txt", &anz);
			break;
		case 3: load_arr(arr, "Saves/save_game3.txt", &anz);
			break;
		}

		//Anzeigen des Spielfeldes und fragen, ob mit diesem Spielstand gespielt werden soll
		print_field(arr);
		printf("\nMöchtest du mit diesem Spielstand fortfahren ?\n\nJ - Ja\nN - Nein\n\n");
		if (eingabe_char(">>>", "JN", 5) == 'N')
			continue;
		else break;
	}
	//Frage ob Spielregeln angezeigt werden sollen
	printf("\nMöchten sie die Spielregeln sehen ?\nJ - Ja\nN - Nein\n\n");
	if (eingabe_char(">>>", "JN", 5) == 'J')
		display_rules();

	//game()

	save_game(arr, &anz);


}


//Läd ein völlig neues Spiel ohne gespeicherte Spieldaten
void new_game() {
	char arr[10][10];
	int anz;

	do {
		//Array leeren und Áuswahl des Levels
		set_array(arr, 4, &anz);
		printf("\nWelches Level möchtest du spielen ?\n\n\t1 - Level 1\n\n\t2 - Level 2\n\n\t3 - Level 3\n\n  0 - Zum Hauptmen\201 zur\201ck kehren!\n\n");
		int choice = eingabe_int(">>>", 0, 3, 5);

		//zurück zum Hauptmenü
		if (choice == 0) return;

		//Level initialisieren und Level anzeigen mit Frage ob es wirklich gespielt werden soll
		set_array(arr, choice, &anz);
		print_field(arr);
		printf("\nM\224chtest du dieses level spielen?\n\nJ - Ja\nN - Nein\n\n");
	} while (eingabe_char(">>>", "JN", 5) == 'N');

	//Frage ob Spielregeln angezeigt werden sollen
	printf("\nM\224chten sie die Spielregeln sehen ?\n\nJ - Ja\nN - Nein\n\n");
	if (eingabe_char(">>>", "JN", 5) == 'J')
		display_rules();

	//game()

	//Speichern des Spielestandes mittels der Funktion save_game
	save_game(arr, &anz);
	return;
}


//Gibt das optionsmenü aus
void options() {
	
	//Optionsmenü anzeigen und Auswahl was getan werden soll
	while (1) {
		printf("\n\n-------------------------------------------------------------------------\n\n     Optionen\n\n");

		switch (menu("\t1 - Spielst\204nde l\224schen\n\n\t2 - Regeln anzeigen\n\n   0 - zur\201ck zum Hauptmen\201\n\n", 0, 2, 5)) {
		case 0: return;
			break;
		case 1: delete_game();
			break;
		case 2: display_rules();
			break;
		}
	}
}


//Löschen von Spielständen
void delete_game() {

	while (1) {

		//Anzeigen aller Speicherslots und auswahl welche gelöscht werden sollen
		printf("\n\nWelchen Spielstand m\224chtest du l\224schen ?\n\n\t");
		char check[3];
		display_savegames(check);
		printf("\t4 - Alle Spielst\204nde l\224schen\n\n   0 - Zur\201ck\n\n");
		int choice = eingabe_int(">>>", 0, 4, 5);

		//zurück zum Hauptmnü
		if (choice == 0) return;

		//Sicherheitsfrage ob Spielstand wirklich gelöscht werden soll
		if (choice != 4) printf("\n\nM\224chtest du Spielstand %d wirklich l\224schen?", choice);
		else printf("\n\nM\224chtest du wirklich alle Spielst\204nde l\224schen?");

		if (eingabe_char("\n>J - Ja\n>N - Nein\n\n>>>", "JN", 5) == 'N') continue;

		//Löschen der Speicherdaten
			switch (choice) {
				case 1: if (remove("Saves/save_game1.txt"))
							printf("\nSpielstand konnte nicht gel\224scht werden!");
					break;
				case 2: if (remove("Saves/save_game2.txt"))
							printf("\nSpielstand konnte nicht gel\224scht werden!");
					break;
				case 3: if (remove("Saves/save_game3.txt"))
							printf("\nSpielstand konnte nicht gel\224scht werden!");
					break;
				case 4: if (remove("Saves/save_game1.txt"))
							printf("\nSpielstand 1 konnte nicht gel\224scht werden!");
						if (remove("Saves/save_game2.txt"))
							printf("\nSpielstand 2 konnte nicht gel\224scht werden!");
						if (remove("Saves/save_game3.txt"))
							printf("\nSpielstand 3 konnte nicht gel\224scht werden!");
					break;
			}

			//aktualisieren der check Datei
			if (choice == 4) {
				for (int i = 1; i <= 3; i++)
					set_check(check, i, 'd');
			}
			else set_check(check, choice, 'd');
			

			return;
	}
}


//Initialisiert den vom User gewünschen Array
void set_array(char arr[10][10], int choice, int* anz) {
	
	switch (choice) {
		case 1: {
			arr[0][2] = 'o';
			arr[0][3] = 'x';
			arr[0][9] = 'o';
			arr[1][0] = 'x';
			arr[1][3] = 'x';
			arr[2][2] = 'o';
			arr[2][5] = 'x';
			arr[2][9] = 'o';
			arr[3][4] = 'o';
			arr[3][8] = 'o';
			arr[4][0] = 'o';
			arr[4][3] = 'x';
			arr[4][7] = 'x';
			arr[5][0] = 'o';
			arr[5][8] = 'o';
			arr[6][3] = 'x';
			arr[6][5] = 'x';
			arr[7][1] = 'o';
			arr[8][1] = 'o';
			arr[8][3] = 'o';
			arr[8][5] = 'x';
			arr[8][6] = 'x';
			arr[9][2] = 'x';
			arr[9][6] = 'o';
			arr[9][8] = 'x';
			arr[9][9] = 'o';
			*anz = 26;
		}
			break;
		case 2: {
			arr[0][5] = 'o';
			arr[0][8] = 'o';
			arr[1][0] = 'o';
			arr[1][3] = 'x';
			arr[2][2] = 'x';
			arr[2][6] = 'o';
			arr[3][4] = 'x';
			arr[3][5] = 'x';
			arr[3][8] = 'x';
			arr[4][0] = 'o';
			arr[4][1] = 'x';
			arr[5][0] = 'o';
			arr[5][4] = 'o';
			arr[5][5] = 'o';
			arr[5][8] = 'o';
			arr[6][2] = 'o';
			arr[6][3] = 'x';
			arr[7][1] = 'x';
			arr[7][7] = 'o';
			arr[8][0] = 'x';
			arr[8][5] = 'x';
			arr[9][1] = 'x';
			arr[9][4] = 'o';
			arr[9][9] = 'x';
			*anz = 24;
			
		}
			break;
		case 3: {
			arr[0][0] = 'x';
			arr[0][3] = 'x';
			arr[0][5] = 'o';
			arr[0][7] = 'x';
			arr[0][8] = 'x';
			arr[1][5] = 'o';
			arr[1][9] = 'o';
			arr[2][2] = 'x';
			arr[3][7] = 'x';
			arr[4][3] = 'x';
			arr[4][4] = 'x';
			arr[4][7] = 'x';
			arr[4][8] = 'o';
			arr[5][1] = 'x';
			arr[5][4] = 'o';
			arr[6][0] = 'x';
			arr[6][5] = 'x';
			arr[7][0] = 'x';
			arr[7][5] = 'x';
			arr[8][3] = 'x';
			arr[8][8] = 'o';
			arr[9][1] = 'o';
			*anz = 22;
			
		}
			break;
		case 4: {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					arr[i][j] = ' ';
				}
			}
			*anz = 0;
			break;
			
		}
	}
}


//Gibt das Spielfeld auf dem Bildschirm aus
void print_field(char arr[10][10]) {
	printf("\n\n\t    0   1   2   3   4   5   6   7   8   9\n\n\t");
	for (int i = 0; i < 10; i++) {
		printf("%d", i);
		for (int j = 0; j < 10; j++) {
				printf("%4c", arr[i][j]);
		}
		printf("\n\n\t");
	}
	printf("\n\n");
}


//Gibt die Regeln des Spiels aus
void display_rules() {
	printf("\n\n\n\nAnleitung und Regelwerk zu \"Tic-Tac-Logic\"\n-------------------------------------------\n\nIm Spiel geht es darum, die komplette Tabelle mit 'o' und 'x' zu f\201llen.");
	printf("\nDamit dies nicht zu einfach ist, gibt es nat\201rlich ein paar Regeln zu beachten.\n\n     1. Es d\201rfen nicht mehr als 2 aufeinander folgende 'x' oder 'o' in einer Zeile\n        oder Spalte vorkommen.\n\n");
	printf("     2. In jeder Zeile oder Spalte stehen gleich viele 'x' und 'o'.\n\n     3. Alle Zeilen und alle Spalten sind einzigartig.\n\nUm in ein freies Feld zu schreiben, musst du zuerst die koordinaten dieses Feldes angeben.\n");
	printf("Dies tust du, indem du zuerst die Zeilennummer und dann die Spaltennummer angibst.\nDanach kannst du ein 'x' oder ein 'o' eingeben. Es wird \201berpr\201ft ob die Eingabe allen\nRegeln entspricht und zum Schluss kannst du deine Eingabe nocheinmal best\204tigen.\nGewonnen hast du, wenn die Tabelle unter beachtung aller Regeln gef\201llt ist\nViel Spa\xE1 und Erfolg beim Spielen :)\n\n\n\n");
}


//überprüft das Vorhandensein von Spielständen
void check_savegames(char* check) {
	FILE *fp;
	
	
	if ((fp = fopen("Saves/save_games.txt", "r")) == NULL) {
		printf("\nFehler beim öffnen der Datei!");
		exit(1);
	}

	//geht die ersten 3 Zeichen in der Datei "save_games.txt" durch und speichert sie im check Vektor
	//1 steht für Spielstand vorhanden und 0 für Spielstand leer
	for (int i = 0; i < 3; i++) {
		char c;
		if (fscanf(fp, "%c", &c) == EOF){
			printf("Fehler beim Lesen der Datei!");
			exit(2);
		}
		check[i] = c;
	}
		
}


//Verändert save_games Datei entsprechend der vorhandenen und nicht vorhandenen Spielstände
//Mode: s(save) --> ändert 0 zu 1 (nicht vorhanden zu vorhanden), d(delete) --> ändert 1 zu 0 (vorhanden zu nicht vorhanden
void set_check(char* check, int choice, char mode) {

	FILE *fp;

	if ((fp = fopen("Saves/save_games.txt", "w+t")) == NULL){
		printf("\nFehler: konnte Datei save_games.txt nicht \224ffnen");
		exit(1);
	}

	//aktualisieren der save_games.txt Datei welche anzeigt ob Spielstände vorhanden sind oder nicht
	if (mode == 's') {
		check[choice - 1] = '1';
	}
	else check[choice - 1] = '0';

	if (fprintf(fp, "%c%c%c", check[0], check[1], check[2]) == NULL) {
		printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
		exit(1);
	}

	fclose(fp);
}


//Initialisiert einen Array aus einer Datei (Laden eines zuvor gespeicherten Spielestands)
void load_arr(char arr[10][10], char* name, int* anz) {

	FILE *fp;
	if ((fp = fopen(name, "r+t")) == 0) {
		printf("\nFehler: konnte Datei %s nicht \224ffnen", name);
		exit(1);
	}

	//Laden der Anzahl (Anzahl entspricht der Anzahl der nicht mit '0' initialisierten Felder)
	if (fscanf(fp, "%d ", anz) != 1) {
		printf("\nFehler Datei Inhalt konnte nicht richtig geladen werden!\n");
		exit(1);
	}

	//Laden des Vektors als 3er Block /erste Zahl == Zeile, zweite Zahl == Spalte, danach folg das entsprechende Zeichen (x oder o)
	char wert;
	int zeile, spalte;
	for (int i = 0; i < *anz; i++) {
		if (fscanf(fp, "%d %d %c", &zeile, &spalte, &wert) != 3) {
				printf("\nFehler datei Inhalt konnte nicht richtig geladen werden!\n");
				exit(1);	
		}
		arr[zeile][spalte] = wert;

	}
	fclose(fp);
}


//speichern eines Arrays in einer Datei (Speichern eines Spielstandes)
void save_arr(char arr[10][10], char *name, const int* anz) {
	FILE *fp;
	if ((fp = fopen(name, "w+t")) == 0) {
		printf("\nFehler: konnte Datei %s nicht \224ffnen", name);
		exit (1);
	}

	//Speichern der Anzahl
	if (fprintf(fp, "%d ", *anz) == 0) {
		printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
		exit(1);
	}
	
	//Speichern des Vektorinhalts ind die Datei
	for (int zeile = 0; zeile < 10; zeile++) {
		for (int spalte = 0; spalte < 10; spalte++) {
			if (arr[zeile][spalte] != ' ') {
				if (fprintf(fp, "%d %d %c", zeile, spalte, arr[zeile][spalte]) == 0) {
					printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
					exit(1);
				}
			}
		}
	}
	fclose(fp);
}


//Anzeigen der Speicherslots und deren Status (ob belegt mit anderem Spielstand oder frei)
void display_savegames(char* check) {
	

	//überprüft das vorhandensein von Spielständen, gibt gefüllten Check Vektor zurück
	check_savegames(check);


	//Ausgabe der Auswahl mit entsprechender Notation ob Spielstand vorhanden oder leer (anhand des check Vektors)
	printf("\n\t1 - Spielstand 1");
	if (check[0] == '0') printf("\t--LEER--\n\n\t");
	else printf("\t--SPIELSTAND VORHANDEN--\n\n\t");
	printf("2 - Spielstand 2");
	if (check[1] == '0') printf("\t--LEER--\n\n\t");
	else printf("\t--SPIELSTAND VORHANDEN--\n\n\t");
	printf("3 - Spielstand 3");
	if (check[2] == '0') printf("\t--LEER--\n\n");
	else printf("\t--SPIELSTAND VORHANDEN--\n\n");
	
}


//Dialogabfrage ob Spielstand gespeichert werden soll und wo
void save_game(char arr[10][10], int *anz) {
	char check[3];

	//Frage ob spielstand gelöscht oder gespeichert werden soll
	printf("\nM\224chtest du den Spielstand vor dem Beenden speichern?\n\n> J - Ja\n> N - Nein\n\n");
	if (eingabe_char(">>>", "JN", 5) == 'N') {
		printf("\nBist du dir sicher?\nAlle nicht gespeichrten Daten gehen verloren! Trotzdem beenden?\n\n");
		if (eingabe_char(">>>", "JN", 5) == 'J') return;
	}

	//Auswahl wo gespeichert werden soll, über check wird überprüft ob auf Slot bereits Spielstand und wenn ja ob dieser überschrieben werden soll
	while (1){
		
		printf("\n\nSPEICHERN: Auf welchem Speicherslot m\224chtest du den Spielstand speichern?\n");
		display_savegames(check);
		int choice = eingabe_int(">>>", 1, 3, 5);

		if (check[choice - 1] == '1') {
			printf("\nAuf diesem Speicherslot befindet sich bereits ein Spielstand!\nWenn du diesen Speicherslot trotzdem benutzt, wird der Spielstand darin \201berschrieben.\nTrotzdem überschreiben?\n\n");
			if (eingabe_char(">>>", "JN", 5) == 'N') continue;
		}

		//Spielstand wird auf entsprechendem Speicherslot gespeichert
		switch (choice) {
		case 1: save_arr(arr, "Saves/save_game1.txt", anz);
			break;
		case 2: save_arr(arr, "Saves/save_game2.txt", anz);
			break;
		case 3: save_arr(arr, "Saves/save_game3.txt", anz);
			break;
		}
		
		//aktualisiert die Checkliste der Spielstände
		set_check(check, choice, 's');
		break;	
	} 

	printf("\nSpielstand erfolgreich gespeichert. Kehre zur\201ck zum Hauptmen\201!");

}
		

