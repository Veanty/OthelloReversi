#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <cstdlib>



int ilosc_czarnych = 0;
int ilosc_bialych = 0;

enum class Pole {PUSTE, BIALE, CZARNE};

enum class RodzajGracza {CZLOWIEK, KOMPUTER};

class Plansza {
	struct IlePionków {
		int ile_bialych;
		int ile_czarnych;
	};

private:
	Pole **pola_planszy;
public:
	int rozmiar_planszy;

	Plansza(int rozmiar_planszy) {
		this->rozmiar_planszy = rozmiar_planszy;

		pola_planszy = new Pole * [rozmiar_planszy];
		for (int i = 0; i < rozmiar_planszy; i++)
		{
			pola_planszy[i] = new Pole[rozmiar_planszy];
		}

		for (int i = 0; i < rozmiar_planszy; i++)
		{
			for (int j = 0; j < rozmiar_planszy; j++)
			{
				pola_planszy[i][j] = Pole::PUSTE;
			}
		}
		int numer = rozmiar_planszy / 2;
		
		pola_planszy[numer-1][numer-1] = Pole::BIALE;
		pola_planszy[numer-1][numer] = Pole::CZARNE;
		pola_planszy[numer][numer-1] = Pole::CZARNE;
		pola_planszy[numer][numer] = Pole::BIALE;
	}

	~Plansza() {
		for (int i = 0; i < rozmiar_planszy; i++)
		{
			delete[] pola_planszy[i];
		}
		delete[] pola_planszy;
	}

	void wypisz_plansze() {
		int max_index_length = std::to_string(rozmiar_planszy).length();
		/*system("cls");*/
		std::cout << std::string(max_index_length + 2, ' ');
		for (int i = 0; i < rozmiar_planszy; i++)
		{
			std::cout << std::setw(max_index_length) << i + 1 << std::string(2, ' ');
		}
		std::cout << std::endl;

		for (int i = 0; i < rozmiar_planszy; i++)
		{
			if (i > 0)
			{
				std::cout << std::endl;
			}
			std::cout << std::setw(max_index_length) << i + 1 << "  ";
			for (int j = 0; j < rozmiar_planszy; j++)
			{
				char symbol = '.';
				if (pola_planszy[i][j] == Pole::CZARNE)
				{
					symbol = 'X';
				}
				else if (pola_planszy[i][j] == Pole::BIALE)
				{
					symbol = 'O';
				}
				std::cout << std::setw(max_index_length) << symbol << std::string(2, ' ');
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	int sprawdzanie_ruchu(int rzad, int kolumna, Pole aktualny_gracz) const {

		int deltaRzad[] = { -1,-1,-1, 0, 0, 1, 1 ,1 };		//Możliwe do wykonania ruchy relatywnie do pola, np. -1 i -1 to lewe górne pole w relacji													do aktualnego pola
		int deltaKolumna[] = { -1, 0, 1,-1, 1,-1, 0, 1 };

		Pole przeciwnik;

		if (aktualny_gracz == Pole::BIALE)
		{
			przeciwnik = Pole::CZARNE;
		}											//Definiowanie który gracz wykonuje ruch
		else
		{
			przeciwnik = Pole::BIALE;
		}

		if (rzad < 0 || rzad >= rozmiar_planszy || kolumna < 0 || kolumna >= rozmiar_planszy || pola_planszy[rzad][kolumna] != Pole::PUSTE)
		{
			return 0;				//Sprawdzanie czy ruch nie jest wykonany poza planszą
		}

		for (int i = 0; i < 8; i++)			//8 mozliwych pol wokol konkretnej pozycji (chyba ze na krancu planszy)
		{
			int poprawny = 0;
			int test_rzad = rzad + deltaRzad[i];
			int test_kolumna = kolumna + deltaKolumna[i];


			while (test_rzad >= 0 && test_rzad < rozmiar_planszy && test_kolumna >= 0 && test_kolumna < rozmiar_planszy && pola_planszy[test_rzad][test_kolumna] == przeciwnik)
			{
				test_rzad += deltaRzad[i];
				test_kolumna += deltaKolumna[i];	//Jeżeli ruch, ktory ma byc wykonany nie wychodzi poza granice planszy i nie jest to pole zajete										przez aktualnego gracza to jest to poprawny ruch
				poprawny = 1;
			}

			if (test_rzad >= 0 && test_rzad < rozmiar_planszy && test_kolumna >= 0 && test_kolumna < rozmiar_planszy && pola_planszy[test_rzad][test_kolumna] == aktualny_gracz && poprawny)
			{
				return 1;
			}
		}

		return 0;

	}

	void ruch(int rzad, int kolumna, Pole aktualny_gracz) {
		if (sprawdzanie_ruchu(rzad, kolumna, aktualny_gracz) == 1)
		{
			int deltaRzad[] = { -1,-1,-1, 0, 0, 1, 1 ,1 };		//Możliwe do wykonania ruchy relatywnie do pola, np. -1 i -1 to lewe górne pole w															relacji	do aktualnego pola, -1 i 0 to pole nad aktualnym polem itd.
			int deltaKolumna[] = { -1, 0, 1,-1, 1,-1, 0, 1 };

			Pole przeciwnik;
			if (aktualny_gracz == Pole::BIALE)
			{
				przeciwnik = Pole::CZARNE;
			}
			else
			{
				przeciwnik = Pole::BIALE;
			}

			pola_planszy[rzad][kolumna] = aktualny_gracz;

			for (int i = 0; i < 8; i++)
			{
				int test_rzad = rzad + deltaRzad[i];
				int test_kolumna = kolumna + deltaKolumna[i];

				while (test_rzad >= 0 && test_rzad < rozmiar_planszy && test_kolumna >= 0 && test_kolumna < rozmiar_planszy && pola_planszy[test_rzad][test_kolumna] == przeciwnik)
				{
					test_rzad += deltaRzad[i];
					test_kolumna += deltaKolumna[i];
				}

				if (test_rzad >= 0 && test_rzad < rozmiar_planszy && test_kolumna >= 0 && test_kolumna < rozmiar_planszy && pola_planszy[test_rzad][test_kolumna] == aktualny_gracz)
				{
					test_rzad -= deltaRzad[i];
					test_kolumna -= deltaKolumna[i];
					while (test_rzad != rzad || test_kolumna != kolumna)
					{
						pola_planszy[test_rzad][test_kolumna] = aktualny_gracz;			//Cofamy sie do tylu i przewracamy po drodze wszystkie pionki,																ktore nalezaly do przeciwnika na pionki aktualnego gracza
						test_rzad -= deltaRzad[i];
						test_kolumna -= deltaKolumna[i];
					}
				}
			}

		}
	}

	IlePionków policz() {
		IlePionków wszystkie_pionki = { 0, 0 };
		for (int i = 0; i < rozmiar_planszy; i++)
		{
			for (int j = 0; j < rozmiar_planszy; j++)
			{
				if (pola_planszy[i][j] == Pole::BIALE)
				{
					wszystkie_pionki.ile_bialych++;
				}
				else if (pola_planszy[i][j] == Pole::CZARNE)
				{
					wszystkie_pionki.ile_czarnych++;
				}
			}
		}
		ilosc_czarnych = wszystkie_pionki.ile_czarnych;
		ilosc_bialych = wszystkie_pionki.ile_bialych;
		return wszystkie_pionki;
	}

	int czyMozliwyRuch(Pole aktualny_gracz) {
		for (int i = 0; i < rozmiar_planszy; i++)
		{
			for (int j = 0; j < rozmiar_planszy; j++)
			{
				if (sprawdzanie_ruchu(i, j, aktualny_gracz) == 1)
				{
					return 1;
				}
			}
		}
		return 0;
	}

	Pole czyToKoniec(Pole aktualny_gracz) {
		IlePionków wszystkie_pionki = policz();

		if (wszystkie_pionki.ile_bialych == 0)
		{
			return Pole::CZARNE;
		}
		else if (wszystkie_pionki.ile_czarnych == 0)
		{
			return Pole::BIALE;
		}
		else if (czyMozliwyRuch(Pole::BIALE)==0 || czyMozliwyRuch(Pole::CZARNE) == 0)
		{
			if (wszystkie_pionki.ile_bialych > wszystkie_pionki.ile_czarnych)
			{
				return Pole::BIALE;
			}
			else if (wszystkie_pionki.ile_czarnych > wszystkie_pionki.ile_bialych)
			{
				return Pole::CZARNE;
			}
			else
			{
				return Pole::PUSTE;
			}
		}

		return{};
	}

};


class Gracz {
protected:
	Pole kolor;
public:
	Gracz(Pole kolor) : kolor(kolor) {};
	Pole getKolor();

	virtual void zrob_ruch(Plansza& plansza) = 0;		//Metoda wirtualnie czysta

	virtual ~Gracz() {};
};

Pole Gracz::getKolor() {
	return kolor;
}

class CzlowiekGracz : public Gracz {
public:
	CzlowiekGracz(Pole kolor) : Gracz(kolor) { };
	void zrob_ruch(Plansza& plansza) override {
		int rzad;
		int kolumna;
		while (true)
		{
			if (kolor == Pole::CZARNE)
			{
				std::cout << "\n\t\tRuch gracza CZARNE (X)\n";
			}
			else
			{
				std::cout << "\n\t\tRuch gracza BIALE (O)\n";
			}
			std::cout << "\n\t\tPodaj rzad i kolumne: ";
			std::cin >> rzad >> kolumna;
			rzad--;
			kolumna--;
			if (plansza.sprawdzanie_ruchu(rzad, kolumna, kolor) == 1)
			{
				plansza.ruch(rzad, kolumna, kolor);
				break;
			}
			else
			{
				plansza.wypisz_plansze();
				std::cout << "\n\t\tNiepoprawny ruch, sprobuj jeszcze raz!" << std::endl;
			}
		}
		
		
	}
};

class Ruch {
public:
	int rzad;
	int kolumna;
};


class AIGracz : public Gracz {
public:
	AIGracz(Pole kolor) : Gracz(kolor) {};
	void zrob_ruch(Plansza& plansza) override {

		Ruch zapamietane_ruchy[20];
		int k = 0;

		for (int rzad = 0; rzad < plansza.rozmiar_planszy; rzad++)
		{
			for (int kolumna = 0; kolumna < plansza.rozmiar_planszy; kolumna++)
			{
				if (plansza.sprawdzanie_ruchu(rzad, kolumna, kolor) == 1)
				{
					zapamietane_ruchy[k].rzad = rzad;
					zapamietane_ruchy[k].kolumna = kolumna;
					k++;
				}
			}
		}

		int random = rand() % k;
		while (true)
		{
			if (plansza.sprawdzanie_ruchu(zapamietane_ruchy[random].rzad, zapamietane_ruchy[random].kolumna, kolor) == 1)
			{
				plansza.ruch(zapamietane_ruchy[random].rzad, zapamietane_ruchy[random].kolumna, kolor);
				std::cout << "Komputer: " << zapamietane_ruchy[random].rzad + 1 << " " << zapamietane_ruchy[random].kolumna + 1 << std::endl;
				break;
			}
			else
			{
				random = rand() % k;
			}
		}
		
	}
};

void dodaj_mecz(int liczba_czarnych, int liczba_bialych, double czas, int rozmiar_planszy, std::string kto_gra){
	std::ofstream plik("historia_meczy.txt", std::ios::app);

	time_t log_meczu;
	time(&log_meczu);
	struct tm* czas_lokalny = localtime(&log_meczu);
	
	if (plik.is_open())
	{
		plik << "|" << (czas_lokalny->tm_year + 1900) << "-"
			<< (czas_lokalny->tm_mon + 1) << "-"
			<< czas_lokalny->tm_mday << " "
			<< czas_lokalny->tm_hour << ":"
			<< czas_lokalny->tm_min << ":"
			<< czas_lokalny->tm_sec << "| ";
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
	std::ifstream plik("historia_meczy.txt");
	std::string linia;
	if (plik.is_open())
	{
		while (std::getline(plik, linia))
		{
			std::cout << linia << '\n';
		}
		plik.close();
	}
	else
	{
		std::cout << "Nie udalo sie otworzyc pliku z historia meczy";
	}
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

	while (true)
	{
		if (opcja == 'g' || opcja == 'G')
		{
			std::cout << "Wybrano tryb GRACZ VS GRACZ" << std::endl;
			kto_gra = "PVP";
			gracz1 = new CzlowiekGracz(Pole::BIALE);
			gracz2 = new CzlowiekGracz(Pole::CZARNE);
			break;

		}
		else if (opcja == 'k' || opcja == 'K')
		{
			std::cout << "Wybrano tryp GRACZ VS KOMPUTER" << std::endl;
			kto_gra = "PvE";
			gracz1 = new CzlowiekGracz(Pole::BIALE);
			gracz2 = new AIGracz(Pole::CZARNE);
			break;
		}
		else
		{
			std::cout << "Nieznany tryb, sprobuj jeszcze raz." << std::endl;
			std::cin >> opcja;
			continue;
		}
	}

	std::cout << "Podaj rozmiar planszy:" << std::endl;
	std::cout << "1. Domyslna: 8x8" << std::endl;
	std::cout << "2. Niestandardowa" << std::endl;

	std::cin >> opcja;

	while (true)
	{
		if (opcja == '1')
		{
			plansza = new Plansza(8);
			break;
		}
		else if (opcja == '2')
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
			std::cin >> opcja;
			continue;
		}
	}
	

	time(&start);
	while (true)
	{



		plansza->wypisz_plansze();
		if (plansza->czyMozliwyRuch(gracz2->getKolor()))
		{
			gracz2->zrob_ruch(*plansza);
		}
		else if (!plansza->czyMozliwyRuch(gracz1->getKolor()))
		{
			zwyciezca = plansza->czyToKoniec(gracz1->getKolor());
			break;
		}

		plansza->wypisz_plansze();
		if (plansza->czyMozliwyRuch(gracz1->getKolor()))
		{
			gracz1->zrob_ruch(*plansza);
		}
		else if (!plansza->czyMozliwyRuch(gracz2->getKolor()))
		{
			zwyciezca = plansza->czyToKoniec(gracz2->getKolor());
			break;
		}
	}

	plansza->wypisz_plansze();
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
	std::cout << "Ilosc pionkow CZARNE: " << ilosc_czarnych << std::endl;
	std::cout << "Ilosc pionkow BIALE: " << ilosc_bialych << std::endl;
	if (zwyciezca == Pole::BIALE)
	{
		std::cout << "Zwyciezca: BIALE !!!";
	}
	else if (zwyciezca == Pole::CZARNE)
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

	dodaj_mecz(ilosc_czarnych, ilosc_bialych, czas, plansza->rozmiar_planszy, kto_gra);
}

void intro() {

	std::cout << "1. Nowa gra" << std::endl;
	std::cout << "2. Historia meczy" << std::endl;
	std::cout << "3. Wyjdz" << std::endl;
	char opcja;
	std::cin >> opcja;
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
	else if(opcja == '3')
	{
		return;
	}
	else
	{
		std::cout << "Nieznana opcja, sproboj ponownie." << std::endl;
		intro();
	}
}


int main() {

	std::srand(std::time(0));

	std::cout << "Witaj w grze Othello/Reversi by Jakub Drozd" << std::endl;
	intro();

	return 0;
}