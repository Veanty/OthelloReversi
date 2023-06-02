#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
#include <fstream>
#include <conio.h>

 void dodaj_mecz(int liczba_czarnych, int liczba_bialych, double czas, int rozmiar_planszy, std::string kto_gra){
	 std::ofstream plik("historia_meczy.txt", std::ios::app);

	 time_t log_meczu;
	 time(&log_meczu);
	 struct tm* czas_lokalny = localtime(&log_meczu);

	 if (plik.is_open())
	 {
		 plik << "|" << (czas_lokalny->tm_year + 1900) << "-"
			 << std::setw(2) << std::setfill('0') << (czas_lokalny->tm_mon + 1) << "-"
			 << std::setw(2) << std::setfill('0') << czas_lokalny->tm_mday << " "
			 << std::setw(2) << std::setfill('0') << czas_lokalny->tm_hour << ":"
			 << std::setw(2) << std::setfill('0') << czas_lokalny->tm_min << ":"
			 << std::setw(2) << std::setfill('0') << czas_lokalny->tm_sec << "| ";
		 plik << "|Liczba czarnych: " << liczba_czarnych << ", liczba bialych: " << liczba_bialych << "| |Dlugosc gry: " << czas << "s| |Tryb: " << kto_gra << "| |Rozmiar planszy: " << rozmiar_planszy << "x" << rozmiar_planszy << "|" << std::endl;
		 std::cout << "Mecz zostal wpisany do historii gier" << std::endl;
		 plik.close();
	 }
	 else
	 {
		 std::cout << "Pliku nie udalo sie otworzyc";
	 }
}

 void odczytaj_mecze() {
	 system("cls");
	 FILE* plik = fopen("historia_meczy.txt", "r");
	 if (plik != NULL)
	 {
		 char data[20];
		 int czarne, biale, dlugosc_gry;
		 char tryb[4];
		 int rozmiar_x, rozmiar_y;

		 while (!feof(plik))
		 {
			 int liczba_skanowanych = fscanf(plik, " |%19[^|]| |Liczba czarnych: %d, liczba bialych: %d| |Dlugosc gry: %ds| |Tryb: %3[^|]| |Rozmiar planszy: %dx%d| ",
				 data, &czarne, &biale, &dlugosc_gry, tryb, &rozmiar_x, &rozmiar_y);

			 if (liczba_skanowanych == 7)
			 {
				 printf("|%s| |Liczba czarnych: %d, liczba bialych: %d| |Dlugosc gry: %ds| |Tryb: %s| |Rozmiar planszy: %dx%d|\n",
					 data, czarne, biale, dlugosc_gry, tryb, rozmiar_x, rozmiar_y);
			 }
			 else
			 {
				 printf("[Niepoprawny format log'a]\n");
				 char ignoruj[300];
				 fgets(ignoruj, sizeof(ignoruj), plik);
			 }
		 }
		 fclose(plik);
	 }
	 else
	 {
		 printf("Nie udalo sie otworzyc pliku z historia meczy\n");
	 }
 }

 void wyczysc_bufor() {
	 int c;
	 while ((c = getchar()) != '\n' && c != EOF) {}
 }

 void rozpocznij_gre() {
	 Plansza* plansza = nullptr;
	 Gracz* gracz1;
	 Gracz* gracz2;
	 Pole zwyciezca = {};

	 time_t start;
	 time_t koniec;
	 double czas;

	 std::string kto_gra;

	 std::cout << "Wybierz tryb gry:" << std::endl;
	 std::cout << "[G] - GRACZ VS GRACZ\t [K] - GRACZ VS KOMPUTER" << std::endl;
	 char opcja;

	 std::cin >> opcja;
	 wyczysc_bufor();

	 while (true)
	 {
		 if (opcja == 'g' || opcja == 'G')
		 {
			 std::cout << "Wybrano tryb GRACZ VS GRACZ" << std::endl;
			 kto_gra = "PVP";
			 gracz1 = new CzlowiekGracz(Pole::CZARNE);
			 gracz2 = new CzlowiekGracz(Pole::BIALE);
			 break;

		 }
		 else if (opcja == 'k' || opcja == 'K')
		 {
			 std::cout << "Wybrano tryp GRACZ VS KOMPUTER" << std::endl;
			 kto_gra = "PvE";
			 gracz1 = new CzlowiekGracz(Pole::CZARNE);
			 gracz2 = new AIGracz(Pole::BIALE);
			 break;
		 }
		 else
		 {
			 std::cout << "Nieznany tryb, sprobuj jeszcze raz." << std::endl;
			 std::cin >> opcja;
			 wyczysc_bufor();
			 continue;
		 }
	 }

	 std::cout << "Podaj rozmiar planszy:" << std::endl;
	 std::cout << "1. Domyslna: 8x8" << std::endl;
	 std::cout << "2. Niestandardowa" << std::endl;


	 int opcja2;
	 std::cin >> opcja2;
	 wyczysc_bufor();

	 while (true)
	 {
		 if (opcja2 == 1)
		 {
			 plansza = new Plansza(8);
			 break;
		 }
		 else if (opcja2 == 2)
		 {
			 int rozmiar = 1;
			 std::cout << "Tworzenie niestandardowej planszy..." << std::endl;
			 std::cout << "Podaj rozmiar planszy (Liczba parzysta z przedzialu [4 - 98]): " << std::endl;
			 std::cin >> rozmiar;
			 while ((rozmiar % 2 == 1) || (rozmiar < 4 || rozmiar > 98))
			 {
				 std::cout << "Podano niepoprawny rozmiar, sprobuj jeszcze raz" << std::endl;
				 std::cin >> rozmiar;
			 }
			 plansza = new Plansza(rozmiar);
			 break;
		 }
		 else
		 {
			 std::cout << "Podana opcja nie istnieje, sprobuj jeszcze raz." << std::endl;
			 std::cin >> opcja2;
			 wyczysc_bufor();
			 continue;
		 }
	 }


	 time(&start);

	 Gracz* aktualny_gracz = gracz1;
	 Gracz* przeciwnik = gracz2;
	 while (true)
	 {

		 plansza->wypisz_plansze();


		 if (aktualny_gracz->getKolor() == Pole::CZARNE)
		 {
			 przeciwnik = gracz2;
		 }
		 else
		 {
			 przeciwnik = gracz1;
		 }
		 

		 if (!plansza->czyMozliwyRuch(aktualny_gracz->getKolor()))
		 {
			 plansza->policz();
			 break;
		 }
		 else
		 {
			 aktualny_gracz->zrob_ruch(*plansza);
			 aktualny_gracz = przeciwnik;
			 continue;
		 }
	 }

	 time(&koniec);
	 czas = difftime(koniec, start);
	 std::cout << "\nGra dobiegla konca!!!" << std::endl;
	 if (czas < 60)
	 {
		 std::cout << "Czas gry: " << czas << "s" << std::endl;
	 }
	 else
	 {
		 std::cout << "Czas gry: " << std::fixed << std::setprecision(0) << czas / 60 << "min " << (int)czas % 60 << "s" << std::endl;
	 }
	 std::cout << "Ilosc pionkow CZARNE: " << plansza->czarne << std::endl;
	 std::cout << "Ilosc pionkow BIALE: " << plansza->biale << std::endl;
	 if (plansza->czarne < plansza->biale)
	 {
		 std::cout << "Zwyciezca: BIALE !!!";
	 }
	 else if (plansza->czarne > plansza->biale)
	 {
		 std::cout << "Zwyciezca: CZARNE !!!";
	 }
	 else
	 {
		 std::cout << "!#! Remis !#!";
	 }
	 std::cout << std::endl;

	 delete gracz1;
	 delete gracz2;

	 dodaj_mecz(plansza->czarne, plansza->biale, czas, plansza->rozmiar_planszy, kto_gra);
 }

 void intro() {

	 std::cout << R"(
   ____  _   _          _ _          _______                         _ 
  / __ \| | | |        | | |        / /  __ \                       (_)
 | |  | | |_| |__   ___| | | ___   / /| |__) |_____   _____ _ __ ___ _ 
 | |  | | __| '_ \ / _ \ | |/ _ \ / / |  _  // _ \ \ / / _ \ '__/ __| |
 | |__| | |_| | | |  __/ | | (_) / /  | | \ \  __/\ V /  __/ |  \__ \ |
  \____/ \__|_| |_|\___|_|_|\___/_/   |_|  \_\___| \_/ \___|_|  |___/_|
                                                                       
                                                                       
)" << std::endl;

	 std::cout << "Autor: Jakub Drozd\n\n" << std::endl;

	 std::cout << "1. Nowa gra" << std::endl;
	 std::cout << "2. Historia meczy" << std::endl;
	 std::cout << "3. Wyjdz" << std::endl;
	 char opcja;
	 std::cin >> opcja;
	 wyczysc_bufor();

	 if (opcja == '1')
	 {
		 rozpocznij_gre();
		 std::cout << "Nacisnij dowolny klawsiz, aby powrocic do menu glownego." << std::endl;
		 _getch();
		 system("cls");
		 intro();
	 }
	 else if (opcja == '2')
	 {
		 odczytaj_mecze();
		 intro();
	 }
	 else if (opcja == '3')
	 {
		 return;
	 }
	 else
	 {
		 std::cout << "Nieznana opcja, sproboj ponownie." << std::endl;
		 intro();
	 }
 }