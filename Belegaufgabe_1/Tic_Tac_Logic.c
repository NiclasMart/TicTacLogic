/*Belegaufgabe Tic-Tac-Logic
Start 02.12.2018*/

#include <stdio.h>
#include <stdlib.h>
#include "Headerdatei/DauEingaben.h"
#include <windows.h>



int menu(char* prompt, int min, int max, int count);
void new_game();
void set_array(char arr[10][10], int choice, int* anz);
void print_field(char arr[10][10]);
void load_game();
void load_arr(char arr[10][10], char* name, int* anz, int* undo_position, int undo_stack[100][2]);
void check_savegames(char* check);
void display_rules();
void save_arr(char arr[10][10], char *name, const int* anz, int* undo_position, int undo_stack[100][2]);
void display_savegames(char* check);
void save_game(char arr[10][10], int *anz, int* undo_position, int undo_stack[100][2]);
void set_check(char* check, int choice, char mode);
void options();
void delete_game();
int game(char arr[10][10], int* anz, int* undo_position, int undo_stack[100][2]);
void gotoXY(int x, int y);
int getKey(char arr[10][10], int *anz, int* x_field, int* y_field, char* symbol, int undo_stack[100][2], int* undo_position);
int funktion1(int x);
int funktion2(int x);
int duplicatec_check(char arr[10][10], int* duplicate, int column);
int duplicater_check(char arr[10][10], int* duplicate, int row);
void complete_check(char arr[10][10], int* tempr, int* tempc, int x_matrix, int y_matrix);
void undo(int* anz, int undo_stack[100][2], int* position, char arr[10][10], int zeile, int spalte, char mode);
int solve_algorithm(char arr[10][10]);
int go_back(char arr[10][10], char temp_arr[10][10], int* zeile, int* spalte, int* complete_row, int* complete_column);
void solve();



int main() {

	printf("\n\t\t***Herzlich Willkommen zu \"Tic-Tac-Logic\"!***\n\n-------------------------------------------------------------------------------------------");

	while (1) {

		switch (menu("\n\n     Men\201:\n\n\t1 - Spiel Laden\n\n\t2 - Neues Spiel\n\n\t3 - Optionen\n\n\t4 - About\n\n\t5 - Exit\n\n", '1', '5', 5)) {

		case 1: //Spiel Laden
			load_game();
			system("cls");
			break;
		case 2: //Neues Spiel
			new_game();
			system("cls");
			break;
		case 3: //optionen
			options();
			system("cls");
			break;
		case 4: //About

			break;
		case 5: //Exit
			printf("\n\nDanke fürs Spielen. Bis zum nächsten Mal :D");
			system("PAUSE");
			return 0;
			break;
		}
	}
	return 0;
}


//ruft das Menü auf und ließt gewünschten Menü - Punkt von User DAU Sicher ein
int menu(char* prompt, char min, char max, int count) {
	printf("%s", prompt);
	return eingabe_int(">>>", min, max, count);
}


//Läd einen Spielstand aus einem vorherigen Spiel
void load_game() {

	char check[3], arr[10][10];
	int anz, undo_position = 0, undo_stack[100][2];

	while (1) {
		system("cls");

		set_array(arr, 4, &anz);

		//Ausgabe der Auswahl über die display_savegames Funktion
		printf("\n     Welchen Spielstand m\224chtest du laden ?\n\n");
		display_savegames(check);
		printf("\n     0 - Zum Hauptmen\201 zur\201ckkehren!\n\n");

		//Auswahl des Spielers und return falls Rückkehr zum Hauptmenü (0) ausgewählt wurde
		int choice = eingabe_int(">>>", '0', '3', 5);
		if (choice == 0) return;

		//verhindert, dass ein leerer Spielstand geladen wird
		if (check[choice - 1] == '0') {
			printf("\nDieser Spielstand kann nicht geladen werden, da keine Speicherdaten vorliegen (Spielstand ist leer)!\nBitte einen vollen Spielstand w\204hlen!\n\n");
			system("PAUSE");
			continue;
		}

		//Spielstand aus entsprechender Datei wird über load_arr Funktion geladen
		switch (choice) {
		case 1: load_arr(arr, "Saves/save_game1.txt", &anz, &undo_position, undo_stack);
			break;
		case 2: load_arr(arr, "Saves/save_game2.txt", &anz, &undo_position, undo_stack);
			break;
		case 3: load_arr(arr, "Saves/save_game3.txt", &anz, &undo_position, undo_stack);
			break;
		}

		//Anzeigen des Spielfeldes und fragen, ob mit diesem Spielstand gespielt werden soll
		print_field(arr);
		printf("\n     M\224chtest du mit diesem Spielstand fortfahren ?");
		if (eingabe_char("\n\n\n\t> J - Ja\n\n\t> N - Nein\n\n>>>", "JN", 5) != 'N')
			break;
	}

	//Frage ob Spielregeln angezeigt werden sollen
	printf("\n     M\224chtest die die Spielregeln sehen ?");
	if (eingabe_char("\n\n\n\t> J - Ja\n\n\t> N - Nein\n\n>>>", "JN", 5) == 'J')
		display_rules();
	

	//bei return Value 1 wäre Spiel gewonnen oder verloren (kein Speichern nötig)
	if (game(arr, &anz, &undo_position, undo_stack) != 1) return;

	gotoXY(1, 27);
	printf("                                                                                       \n                                                                       ");
	gotoXY(1, 27);
	save_game(arr, &anz, &undo_position, undo_stack);
	return;


}


//Läd ein völlig neues Spiel ohne gespeicherte Spieldaten
void new_game() {
	system("cls");

	//initialisieren der matrix, der Anzahl der gefüllten Felder 
	char arr[10][10];
	int anz, undo_position = 0, undo_stack[100][2];
	

	do {
		system("cls");

		//Array leeren und Auswahl des Levels
		set_array(arr, 4, &anz);
		printf("\n     Welches Level m\224chtest du spielen ?\n\n\n\t1 - Level 1\n\n\t2 - Level 2\n\n\t3 - Level 3\n\n\n    0 - Zum Hauptmen\201 zur\201ck kehren!\n\n");
		int choice = eingabe_int(">>>", '0', '3', 5);

		//zurück zum Hauptmenü
		if (choice == 0) return;

		//Level initialisieren und Level anzeigen mit Frage ob es wirklich gespielt werden soll
		set_array(arr, choice, &anz);
		print_field(arr);
		printf("\n     M\224chtest du dieses Level spielen?");
	} while (eingabe_char("\n\n\n\t> J - Ja\n\n\t> N - Nein\n\n>>>", "JN", 5) == 'N');

	//Frage ob Spielregeln angezeigt werden sollen
	printf("\nM\224chtest du die Spielregeln sehen ?");
	if (eingabe_char("\n\n\n\t> J - Ja\n\n\t> N - Nein\n\n>>>", "JN", 5) == 'J') 
		display_rules();


	//bei return Value 1 wäre Spiel gewonnen oder verloren (kein Speichern nötig)
	if (game(arr, &anz, &undo_position, undo_stack) != 1) return;
	

	//Speichern des Spielestandes mittels der Funktion save_game
	gotoXY(1, 27);
	printf("                                                                                       \n                                                                       ");
	gotoXY(1, 27);
	save_game(arr, &anz, &undo_position, undo_stack);
	return;
}


//Gibt das optionsmenü aus
void options() {
	system("cls");

	//Optionsmenü anzeigen und Auswahl was getan werden soll
	while (1) {
		printf("\n\n     Optionen\n\n\n");

		switch (menu("\t1 - Spielst\204nde l\224schen\n\n\t2 - Regeln anzeigen\n\n\t3 - Spiel automatisch l\224sen lassen\n\n\n     0 - zur\201ck zum Hauptmen\201\n\n", 0, 3, 5)) {
		case 0: {
			system("cls");
			return;
		}
			break;
		case 1: {
			delete_game();
			system("cls");
		}
			break;
		case 2: {
			display_rules();
			system("cls");
		}
			break;
		case 3: {
			solve();
			system("cls");
		}
		}
	}
}


//Löschen von Spielständen
void delete_game() {
	

	while (1) {
		system("cls");

		//Anzeigen aller Speicherslots und auswahl welche gelöscht werden sollen
		printf("\n\n     Welchen Spielstand m\224chtest du l\224schen ?\n\n\t");
		char check[3];
		display_savegames(check);
		printf("\t4 - Alle Spielst\204nde l\224schen\n\n\n     0 - Zur\201ck\n\n");
		int choice = eingabe_int(">>>", '0', '4', 5);

		//zurück zum Hauptmnü
		if (choice == 0) return;

		//Sicherheitsfrage ob Spielstand wirklich gelöscht werden soll
		if (choice != 4) printf("\n\nM\224chtest du Spielstand %d wirklich l\224schen?", choice);
		else printf("\n\n     M\224chtest du wirklich alle Spielst\204nde l\224schen?");

		if (eingabe_char("\n\n\n\t> J - Ja\n\n\t> N - Nein\n\n>>>", "JN", 5) == 'N') continue;

		//Löschen der Speicherdaten
			switch (choice) {
				case 1: if (remove("Saves/save_game1.txt"))
							printf("\n     Spielstand konnte nicht gel\224scht werden!\n");
						else printf("\n\n     Der Spielstand wurde erfolgreich gel\224scht!\n");
					break;
				case 2: if (remove("Saves/save_game2.txt"))
							printf("\n     Spielstand konnte nicht gel\224scht werden!\n");
						else printf("\n\n     Der Spielstand wurde erfolgreich gel\224scht!\n");
					break;
				case 3: if (remove("Saves/save_game3.txt"))
							printf("\n     Spielstand konnte nicht gel\224scht werden!\n");
						else printf("\n\n     Der Spielstand wurde erfolgreich gel\224scht!\n");
					break;
				case 4: if (remove("Saves/save_game1.txt"))
							printf("\n     Spielstand 1 konnte nicht gel\224scht werden!\n");
						else printf("\n\n     Spielstand  1 wurde erfolgreich gel\224scht!\n");
						if (remove("Saves/save_game2.txt"))
							printf("\n     Spielstand 2 konnte nicht gel\224scht werden!\n");
						else printf("\n\n     Spielstand  2 wurde erfolgreich gel\224scht!\n");
						if (remove("Saves/save_game3.txt"))
							printf("\n     Spielstand 3 konnte nicht gel\224scht werden!\n");
						else printf("\n\n     Spielstand  3 wurde erfolgreich gel\224scht!\n");
					break;
			}

			//aktualisieren der check Datei
			if (choice == 4) {
				for (int i = 1; i <= 3; i++)
					set_check(check, i, 'd');
			}
			else set_check(check, choice, 'd');
			
			system("PAUSE");
			return;
	}
}


//Initialisiert den vom User gewünschen Array
void set_array(char arr[10][10], int choice, int* anz) {
	
	switch (choice) {
		case 1: {
			/*arr[0][0] = 'o';
			arr[0][1] = 'o';
			arr[0][4] = 'o';
			arr[0][5] = 'o';
			arr[0][8] = 'o';
			arr[0][9] = 'x';
			arr[0][2] = 'x';
			arr[0][3] = 'x';
			arr[0][6] = 'x';
			arr[0][7] = 'x';
			arr[1][0] = 'o';
			arr[1][1] = 'o';
			arr[1][4] = 'o';
			arr[1][5] = 'o';
			arr[1][8] = 'o';
			arr[1][9] = 'x';
			arr[1][2] = 'x';
			arr[1][3] = 'x';
			arr[1][6] = 'x';
			arr[1][7] = 'x';
			arr[2][0] = 'x';
			arr[3][0] = 'x';
			arr[4][0] = 'o';
			arr[5][0] = 'o';
			arr[6][0] = 'x';
			arr[7][0] = 'x';
			arr[8][0] = 'o';
			arr[2][1] = 'x';
			arr[3][1] = 'x';
			arr[4][1] = 'o';
			arr[5][1] = 'o';
			arr[6][1] = 'x';
			arr[7][1] = 'x';
			arr[8][1] = 'o';
			arr[9][1] = 'x';
			arr[9][0] = 'x';
			
			*anz = 26;*/
			
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
	system("cls");
	printf("\nAnleitung und Regelwerk zu \"Tic-Tac-Logic\"\n-------------------------------------------\n\nIm Spiel geht es darum, die komplette Tabelle mit 'o' und 'x' zu f\201llen.");
	printf("\nDamit dies nicht zu einfach ist, gibt es nat\201rlich ein paar Regeln zu beachten.\n\n\n     1. Es d\201rfen nicht mehr als 2 aufeinander folgende 'x' oder 'o' in einer Zeile\n        oder Spalte vorkommen.\n\n");
	printf("     2. In jeder Zeile oder Spalte stehen gleich viele 'x' und 'o'.\n\n     3. Alle Zeilen und alle Spalten sind einzigartig.\n\n\nUm in ein freies Feld zu schreiben, bewege den Cursor mit den Pfeiltasten an die gew\201nschte Position.\n");
	printf("Danach kannst du ein 'x' oder ein 'o' eingeben. Es wird \201berpr\201ft ob die Eingabe allen Regeln entspricht.\nGewonnen hast du, wenn die Tabelle unter Beachtung aller Regeln gef\201llt ist.\nViel Spa\xE1 und Erfolg beim Spielen :)\n\n\n\n");
	system("PAUSE");
}


//überprüft das Vorhandensein von Spielständen
void check_savegames(char* check) {
	FILE* fp;
	
	
	if ((fp = fopen("Saves/save_games.txt", "r")) == NULL) {
		printf("\nFehler beim öffnen der Datei!");
		exit(1);
	}

	//geht die ersten 3 Zeichen in der Datei "save_games.txt" durch und speichert sie im check Vektor
	//1 steht für Spielstand vorhanden und 0 für Spielstand leer
	for (int i = 0; i < 3; i++) {
		if (fscanf_s(fp, "%c", &check[i]) == EOF){
			printf("Fehler beim Lesen der Datei!");
			exit(2);
		}
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
void load_arr(char arr[10][10], char* name, int* anz, int* undo_position, int undo_stack[100][2]) {

	FILE *fp;
	if ((fp = fopen(name, "r+t")) == NULL) {
		printf("\nFehler: konnte Datei %s nicht \224ffnen", name);
		exit(1);
	}

	//Laden der Anzahl (Anzahl entspricht der Anzahl der nicht mit ' ' initialisierten Felder)
	if (fscanf_s(fp, "%d ", anz) != 1) {
		printf("\nFehler Datei Inhalt konnte nicht richtig geladen werden!\n");
		exit(1);
	}

	//Laden des Vektors als 3er Block /erste Zahl == Zeile, zweite Zahl == Spalte, danach folg das entsprechende Zeichen (x oder o)
	char wert;
	int zeile, spalte;
	for (int i = 0; i < *anz; i++) {
		if (fscanf_s(fp, "%d %d %c", &zeile, &spalte, &wert) != 3) {
				printf("\nFehler datei Inhalt konnte nicht richtig geladen werden!\n");
				exit(1);	
		}
		arr[zeile][spalte] = wert;

	}

	if (undo_position != NULL) {
		//Laden des Positions Zeigers auf den undo_stack
		if (fscanf_s(fp, "%d", undo_position) != 1) {
			printf("\nFehler Datei Inhalt konnte nicht richtig geladen werden!\n");
			exit(1);
		}

		//Laden des Undo Stacks
		for (int i = 0; i < *undo_position; i++) {
			if (fscanf_s(fp, "%d %d", &undo_stack[i][0], &undo_stack[i][1]) != 2) {
				printf("\nFehler datei Inhalt konnte nicht richtig geladen werden!\n");
				exit(1);
			}
		}
	}

	fclose(fp);
}


//speichern eines Arrays in einer Datei (Speichern eines Spielstandes)
void save_arr(char arr[10][10], char *name, const int* anz, int* undo_position, int undo_stack[100][2]) {
	FILE *fp;
	if ((fp = fopen(name, "w+t")) == NULL) {
		printf("\nFehler: konnte Datei %s nicht \224ffnen", name);
		exit (1);
	}

	//Speichern der Anzahl
	if (fprintf(fp, "%d ", *anz) == 0) {
		printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
		exit(1);
	}
	
	//Speichern des Vektorinhalts in die Datei
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

	//Speichern der Position des Zeigers auf den undo_stack
	if (fprintf(fp, " %d", *undo_position) == 0) {
		printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
		exit(1);
	}

	//Speichern des undo_stacks
	for (int zeile = 0; zeile < *undo_position; zeile++) {
		if (fprintf(fp, " %d %d", undo_stack[zeile][0], undo_stack[zeile][1]) == 0) {
			printf("\nFehler: Konnte Inhalt nicht in die Datei schreiben!\n");
			exit(1);
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
void save_game(char arr[10][10], int *anz, int* undo_position, int undo_stack[100][2]) {
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
		int choice = eingabe_int(">>>", '1', '3', 5);

		if (check[choice - 1] == '1') {
			printf("\nAuf diesem Speicherslot befindet sich bereits ein Spielstand!\nWenn du diesen Speicherslot trotzdem benutzt, wird der Spielstand darin \201berschrieben.\nTrotzdem überschreiben?\n\n");
			if (eingabe_char(">>>", "JN", 5) == 'N') continue;
		}

		//Spielstand wird auf entsprechendem Speicherslot gespeichert
		switch (choice) {
		case 1: save_arr(arr, "Saves/save_game1.txt", anz, undo_position, undo_stack);
			break;
		case 2: save_arr(arr, "Saves/save_game2.txt", anz, undo_position, undo_stack);
			break;
		case 3: save_arr(arr, "Saves/save_game3.txt", anz, undo_position, undo_stack);
			break;
		}
		
		//aktualisiert die Checkliste der Spielstände
		set_check(check, choice, 's');
		break;	
	} 

	printf("\nSpielstand erfolgreich gespeichert. Kehre zur\201ck zum Hauptmen\201!");

}


//Spiel Funktion
int game(char arr[10][10], int* anz, int* undo_position,int undo_stack[100][2]) {

	//Koordinaten für das Spielfeld und Speichervektoren für vollständige Zeilen/Spalten (20 dient als Leerfeld, also noch keine Initialisiereung)
	int x_field = 12, y_field = 6, complete_row[10] = { 20, 20, 20, 20 , 20, 20, 20, 20, 20, 20 }, complete_column[10] = { 20, 20, 20, 20 , 20, 20, 20, 20, 20, 20 };

	//Matrix muss auf vollständige Zeilen/Spalten vor Spielbeginn überprüft werden, damit 3. Regel auch für Spielstände aus Datein funktioniert
	for (int i = 0; i < 10; i++) {
		complete_check(arr, &complete_row[i], &complete_column[i], i, i);
	}

	//Bildschirm clear + Spielfeldausgabe
	system("cls");
	printf("\n  Bewege den Cursor mit den Pfeiltasten und geben sie im gew\201nschten Feld 'x' oder 'o' den Regeln entsprechend ein!\n");
	gotoXY(0, 2);
	print_field(arr);

	//Funktion um Cursor zu bewegen und Symbole einzugeben
	char symbol;
	int test;
	while (1) {
		do {
			gotoXY(x_field, y_field);
		} while (getKey(arr, anz, &x_field, &y_field, &symbol, undo_stack, undo_position, complete_row, complete_column));

		//Spiel verlassen
		if (symbol == 27) return 1;

		//umrechnen der angepassten x und y Werte des Spielfeldes auf die tatsächlichen Indexfelder der Matrix
		int x_matrix = (x_field - 12) / 4, y_matrix = (y_field - 6) / 2;

		//überprüfen des eingegebenen Zeichens auf Regelverstoß und Position Merken für Undo Funktion
		if (arr[y_matrix][x_matrix] == ' ') {
			if (rule_check(arr, x_field, y_field, x_matrix, y_matrix, symbol, complete_row, complete_column)) {
				undo(anz, undo_stack, undo_position, arr, y_matrix, x_matrix, 's');
				(*anz)++;
				printf("%c", symbol);

				//Testen ob Matrix komplett gefüllt und das Spiel damit gewonnen (nur Test von einem Vektor nötig, da wenn alle Zeilen gefüllt sind, automatisch auch alle Spalten gefüllt sein müssen
				int count = 0;
				for (int i = 0; i < 10; i++) {
					if (complete_row[i] == 20) break;
					if (complete_row[9] !=20){
						gotoXY(1, 27);
						printf("Herzlichen gl\201ckwunsch! Du hast Gewonnen und das Level erfolgreich geschafft.\n Drücke eine Taste um zurück zum Hauptmenü zu gelangen.                        ");
						system("PAUSE");
						return 0;
					}
				}
			}

		}
		
	}

}


//Cursor bewegen
void gotoXY(int x, int y) {
	HANDLE  hConsoleOutput; COORD koords;
	koords.X = x; koords.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, koords);
}


//erkennt welche Taste auf der Tastatur gedrückt wurde
int getKey(char arr[10][10], int *anz, int* x_field, int* y_field, char* symbol, int undo_stack[100][2], int* undo_position, int* complete_row, int* complete_column) {

	//liest einen charakter ohne Enter in result ein und überprüft ob es sich um eine Pfeiltaste oder die Eingabe eines 'x' oder 'o' handelt
	//wenn Pfeiltaste werden die x und y Koordinaten entsprechend aktualisiert
	//wenn 'x' oder 'o' werden Regeln überprüft und in Array geschrieben
	int result = getch();

	if ((result == 224) || (result == 0)) {
		switch (getch()) {
			
		//rechte Pfeiltaste mit Überprüfung ob Cursor bereits am rechtem Rand des Spielfeldes (48)
		case 77: {
			if (*x_field < 48)
				*x_field += 4;
			return 1;
		}
				 break;

		//linke Pfeiltaste mit Überprüfung ob Cursor bereits am linken Rand des Spielfeldes (12)
		case 75: {
			if (*x_field > 12)
				*x_field -= 4;
			return 1;
		}
				 break;

		//oben Pfeiltaste mit Überprüfung ob Cursor bereits am oberen Rand des Spielfeldes (6)
		case 72: {
			if (*y_field > 6)
				*y_field -= 2;
			return 1;
		}
				 break;

		//unten Pfeiltaste mit Überprüfung ob Cursor bereits am unteren Rand des Spielfeldes (24)
		case 80: {
			if (*y_field < 24)
				*y_field += 2;
			return 1;
		}
				 break;

		 //Undo Funktion auslösen mit Entfernen Taste 
		case 83: {
			for (int i = 0; i < 10; i++) {
				if (complete_row[i] == undo_stack[(*undo_position) - 1][0]) complete_row[i] = 20;
			}

			for (int i = 0; i < 10; i++) {
				if (complete_column[i] == undo_stack[(*undo_position) - 1][1]) complete_row[i] = 20;
			}

			undo(anz, undo_stack, undo_position, arr, *y_field, *x_field, 'd');
			gotoXY(0, 2);
			print_field(arr);
			gotoXY(*x_field, *y_field);
			return 1;
		}
				 break;
		return 1;

		}
	}
	//Eingabe von x oder o mit Regelprüfung
	else if ((result == 'x') || (result == 'o') || (result == 27) ) {

		*symbol = result;
		return 0;
	}
		
	return 1;
}


//überprüft ob die Eingabe allen Regeln entspricht
int rule_check(char arr[10][10], int x_field, int y_field, int x_matrix, int y_matrix, char symbol, int* complete_row, int* complete_column) {


	//Element in den Array einfügen
	arr[y_matrix][x_matrix] = symbol;

	//Regel 1: Umfeld kontrollieren
	//Zeile
	int counter = 0;


	for (int i = x_matrix - funktion1(x_matrix); i <= x_matrix + funktion2(x_matrix); i++) {
		if (arr[y_matrix][i] == symbol) counter++;
		else counter = 0;

		if (counter > 2) {
			arr[y_matrix][x_matrix] = ' ';
			gotoXY(1, 27);
			printf("'%c' an dieser Stelle den Regeln entsprechend nicht zul\204ssig!\n Maximal zweimal das selbe Zeichen nacheinander auf einer Zeile", symbol);
			gotoXY(x_field, y_field);
			return 0;
		}

	}

	//Spalte
	counter = 0;
	for (int i = y_matrix - funktion1(y_matrix); i <= y_matrix + funktion2(y_matrix); i++) {
		if (arr[i][x_matrix] == symbol) counter++;
		else counter = 0;

		if (counter > 2) {
			arr[y_matrix][x_matrix] = ' ';
			gotoXY(1, 27);
			printf("'%c' an dieser Stelle den Regeln entsprechend nicht zul\204ssig!\n Maximal zweimal das selbe Zeichen nacheinander in einer Spalte", symbol);
			gotoXY(x_field, y_field);
			return 0;
		}

	}

	//Regel 2: Zeilen/Spalten kontrollieren 
	//Zeile
	counter = 0;
	for (int i = 0; i < 10; i++) {
		if (arr[y_matrix][i] == symbol) counter++;

		if (counter > 5) {
			arr[y_matrix][x_matrix] = ' ';
			gotoXY(1, 27);
			printf("'%c' an dieser Stelle den Regeln entsprechend nicht zul\204ssig!\n In jeder Zeile m\201ssen gleich viele 'x' und 'o' stehen.", symbol);
			gotoXY(x_field, y_field);
			return 0;
		}
		
	}

	//Spalte
	counter = 0;
	for (int i = 0; i < 10; i++) {
		if (arr[i][x_matrix] == symbol) counter++;

		if (counter > 5) {
			arr[y_matrix][x_matrix] = ' ';
			gotoXY(1, 27);
			printf("'%c' an dieser Stelle den Regeln entsprechend nicht zul\204ssig!\n In jeder Spalte m\201ssen gleich viele 'x' und 'o' stehen.", symbol);
			gotoXY(x_field, y_field);
			return 0;
		}

	}


	//Regel 3: Matrix kontrollieren

	//initialisieren der Speichervektoren (20 dient als Leerfeld, also noch keine Initialisiereung) und der temporären Speicherplätze
	static 
	int tempr, tempc;
	tempr = 20;
	tempc = 20;

	//check ob Zeile/Spalte komplett, wenn ja wird die entsprechende Zeile/Spalte auf den temporären Variablen ausgegeben
	complete_check(arr, &tempr, &tempc, x_matrix, y_matrix);

	//wenn Zeile komplett ist (also tempr != 20) wird sie mit allen zuvor fertig gestellten Zeilen in der Funktion duplicate_check verglichen
	//wenn wenn kein Duplicat vorliegt wird die tempr in den Vektor geschrieben 
	static int placer = 0, placec = 0;
	if (tempr != 20) {
		if (duplicater_check(arr, complete_row, tempr) == 1) {
			arr[y_matrix][x_matrix] = ' ';
			gotoXY(1, 27);
			printf("'%c' an dieser Stelle den Regeln entsprechend nicht zul\204ssig!\n Zeilen m\201ssen einzigartig sein!", symbol);
			gotoXY(x_field, y_field);
			return 0;
		}
		else {
			complete_row[placer] = y_matrix;
			placer++;
		}
	}

	//Spalte auf Duplicate überprüfen ... gleiches Vorgehen wie bei Zeile
	if (tempc != 20) {
		if (duplicatec_check(arr, complete_column, tempc) == 1) {
			arr[y_matrix][x_matrix] = ' ';
			gotoXY(1, 27);
			printf("'%c' an dieser Stelle den Regeln entsprechend nicht zul\204ssig!\n Spalten m\201ssen einzigartig sein!", symbol);
			gotoXY(x_field, y_field);
			//wenn Zeile komplett und einzigartig aber Spalte Duplicate, wird Symbol nicht in Matrix übertragen und Zeile ist somit nicht komplett (muss wieder aus dem Merkvektor entfernt werden)
			if (tempr != 20) complete_column[placer] = 20;
			return 0;
		}
		else {
			complete_column[placec] = x_matrix;
			placec++;
		}
	}
	return 1;
}


//kontrolliert nach jedem eingegebenen Feld ob die Reihe/Spalte mit der Eingabe komplett ist
void complete_check(char arr[10][10], int* tempr, int* tempc, int x_matrix, int y_matrix) {

		int count = 0;
		// überprüfen ob Zeile komplett ist
			for (int i = 0; i < 10; i++) {
				if (arr[y_matrix][i] != ' ') count++;
			}
		//wenn Zeile Komplett, wird der index auf tempr gemerkt
		if (count == 10) {
			*tempr = y_matrix;
		}

		//überprüfen ob Spalte komplett ist
		count = 0;
		for (int i = 0; i < 10; i++) {
			if (arr[i][x_matrix] != ' ') count++;
		}
		//wenn wenn Spalte Komplett, wird der index auf tempc gemerkt
		if (count == 10) {
			*tempc = x_matrix;
		}
}


//Vergleicht eine soeben fertig gestellte Reihe mit allen bereits zuvor fertig gestellten Reihen und überprüft, ob sie einzigartig ist (kein Duplikat)
int duplicater_check(char arr[10][10], int* duplicate, int row) {

	//Duplicatprüfung für Zeilen
	int count;
		for (int i = 0; i < 10; i++) {
			if (duplicate[i] == 20) return 0;
			count = 0;
			for (int j = 0; j < 10; j++) {
				if (arr[duplicate[i]][j] == arr[row][j]) count++;

			}
			if (count == 10) return 1;
		}
	
}


//Vergleicht eine soeben fertig gestellte Spalte mit allen bereits zuvor fertig gestellten Spalten und überprüft, ob sie einzigartig ist (kein Duplikat)
int duplicatec_check(char arr[10][10], int* duplicate, int column) {

	//Duplicatprüfung für Spalte
	int count;
	for (int i = 0; i < 10; i++) {
		if (duplicate[i] == 20) return 0;
		count = 0;
		for (int j = 0; j < 10; j++) {
			if (arr[j][duplicate[i]] == arr[j][column]) count++;

		}
		if (count == 10) return 1;
	}

}


//dient der Festlegung der Grenzen Für Regel 2, zwei Felder vor eingegebenem Feld muss überprüft werden, jedoch nicht für 1. und 2. Feld
//wenn x == 0 -> return 0; x == 1 -> return 1, 1 < x <= 9 -> return 2
int funktion1(int x) {
	                                                      
	if (x >= 2) return 2;
	else return x;
}    


//dient der Festlegung der Grenzen Für Regel 2 zwei Felder nach eingegebenem Feld muss überprüft werden, jedoch nicht für 8. und 9. Feld
//wenn x == 8 -> return 1; x == 9 -> return 0, 0 <= x < 8 -> return 2
int funktion2(int x) {

	if (x <= 7) return 2;
	else return -x+9;
}


//Undo Funktion um Spielzüge wieder rückgängig zu machen
//Mode: 's' ist save ... jeder Spielzug muss im undo_stack vermerkt werden
//Mode: 'd' ist do ... ausführen der Undo funktion, letzter Zug wird rückgängig gemacht
void undo(int* anz, int undo_stack[100][2],int* position, char arr[10][10], int zeile, int spalte, char mode) {
	
	if (mode == 's') {
		if (*position > 100) {
			printf("\nFehler im Programm! Spiel bitte neu starten.");
			exit(1);
		} 

		int i = 0;
		undo_stack[*position][i] = zeile;
		undo_stack[*position][i + 1] = spalte;
		(*position)++;
	}

	if (mode == 'd') {
		if (*position > 0) {
			(*position)--;
			(*anz)--;
			arr[undo_stack[*position][0]][undo_stack[*position][1]] = ' ';
			undo_stack[*position][0] = 0;
			undo_stack[*position][1] = 0;
		}
		else {
			gotoXY(1, 27);
			printf("Anfang des Spiels erreicht, kein weiteres Zur\201ckspringen m\224glich                    \n                                                                   ");
			gotoXY(zeile, spalte);

		}
	}
}

void solve() {
	char check[3], arr[10][10];
	int anz;
	
	while (1) {

		//Ausgabe der Auswahl über die display_savegames Funktion
		printf("\nWelchen Spielstand m\224chtest du l\224sen lassen ?\n");
		display_savegames(check);
		printf("0 - Zur\201ck zum vorhergehenden Men\201 kehren!\n\n");

		//Auswahl des Spielers und return falls Rückkehr zum Menü (0) ausgewählt wurde
		int choice = eingabe_int(">>>", '0', '3', 5);
		if (choice == 0) return;

		//verhindert, dass ein leerer Spielstand geladen wird
		if (check[choice - 1] == '0') {
			printf("\nDieser Spielstand kann nicht ausgew\204lt werden, da keine Speicherdaten vorliegen (Spielstand ist leer)!\nBitte einen vollen Spielstand w\204hlen!\n\n");
			continue;
		}

		set_array(arr, 4, &anz);

		//Spielstand aus entsprechender Datei wird über load_arr Funktion geladen
		switch (choice) {
		case 1: load_arr(arr, "Saves/save_game1.txt", &anz, NULL, NULL);
			break;
		case 2: load_arr(arr, "Saves/save_game2.txt", &anz, NULL, NULL);
			break;
		case 3: load_arr(arr, "Saves/save_game3.txt", &anz, NULL, NULL);
			break;
		}
		break;
	}
	if (solve_algorithm(arr) == 0) {
		printf("Fehler. Rätsel kann nicht gel\224st werden");
	} 
	else {
		printf("L\224sung:\n\n");
		print_field(arr);
	}
}



int solve_algorithm(char arr[10][10]) {

	int complete_row[10] = { 20, 20, 20, 20 , 20, 20, 20, 20, 20, 20 }, complete_column[10] = { 20, 20, 20, 20 , 20, 20, 20, 20, 20, 20 };

	for (int i = 0; i < 10; i++) {
		complete_check(arr, &complete_row[i], &complete_column[i], i, i);
	}

	//umwandeln der char Matrix in eine Integer Matrix
	//alle nicht gefüllten Felder werden zu 0 und alle bereits initialisierten Felder zu 20
	char temp_arr[10][10];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			temp_arr[i][j] = arr[i][j];
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (arr[i][j] == ' ') {
				if (rule_check(arr, NULL, NULL, j, i, 'x', complete_row, complete_column) == 1) continue;
				/*else {
					system("cls");
					if (rule_check(arr, NULL, NULL, j, i, 'o', complete_row, complete_column) == 1) continue;
					else {*/
						system("cls");
						if (go_back(arr, temp_arr, &i, &j, complete_row, complete_column) == 0) return 0;
					/*}*/
				/*}*/
			}
			else continue;
			
				

		}

	}
	return 1;

}





int go_back(char arr[10][10], char temp_arr[10][10], int* zeile, int* spalte, int* complete_row, int* complete_column) {

	//if ((*zeile == 0) && (*spalte == 0) && (arr[0][0] == 'o')) return 0;

	if (*spalte == 0) {
		(*zeile)--;
		*spalte = 9;
		/*complete_row[*zeile] == 20;*/
	}
	else {
		(*spalte)--;
		/*if (*zeile == 9) complete_column[*spalte] == 20;*/
	}

	if ((arr[*zeile][*spalte] == 'x') && (temp_arr[*zeile][*spalte] == ' ')) {
		if (rule_check(arr, NULL, NULL, *spalte, *zeile, 'o', complete_row, complete_column) == 1) return 1;
		else {
			system("cls");
			go_back(arr, temp_arr, zeile, spalte, complete_row, complete_column);
		}
	}
	else {
		if (temp_arr[*zeile][*spalte] == ' ') {
			arr[*zeile][*spalte] = ' ';
			go_back(arr, temp_arr, zeile, spalte, complete_row, complete_column);
		}
		go_back(arr, temp_arr, zeile, spalte, complete_row, complete_column);
	}
}


