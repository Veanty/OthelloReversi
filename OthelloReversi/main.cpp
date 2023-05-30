#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>


const int BOARD_SIZE = 4;

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
	Pole pola_planszy[BOARD_SIZE][BOARD_SIZE];
public:
	Plansza() {
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				pola_planszy[i][j] = Pole::PUSTE;
			}
		}
		int numer = BOARD_SIZE / 2;
		
		pola_planszy[numer-1][numer-1] = Pole::BIALE;
		pola_planszy[numer-1][numer] = Pole::CZARNE;
		pola_planszy[numer][numer-1] = Pole::CZARNE;
		pola_planszy[numer][numer] = Pole::BIALE;
	}
	void wypisz_plansze() {
		int max_index_length = std::to_string(BOARD_SIZE).length();
		system("cls");
		std::cout << std::string(max_index_length + 2, ' ');
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			std::cout << std::setw(max_index_length) << i + 1 << std::string(2, ' ');
		}
		std::cout << std::endl;

		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if (i > 0)
			{
				std::cout << std::endl;
			}
			std::cout << std::setw(max_index_length) << i + 1 << "  ";
			for (int j = 0; j < BOARD_SIZE; j++)
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

		if (rzad < 0 || rzad >= BOARD_SIZE || kolumna < 0 || kolumna >= BOARD_SIZE || pola_planszy[rzad][kolumna] != Pole::PUSTE)
		{
			return 0;				//Sprawdzanie czy ruch nie jest wykonany poza planszą
		}

		for (int i = 0; i < 8; i++)			//8 mozliwych pol wokol konkretnej pozycji (chyba ze na krancu planszy)
		{
			int poprawny = 0;
			int test_rzad = rzad + deltaRzad[i];
			int test_kolumna = kolumna + deltaKolumna[i];


			while (test_rzad >= 0 && test_rzad < BOARD_SIZE && test_kolumna >= 0 && test_kolumna < BOARD_SIZE && pola_planszy[test_rzad][test_kolumna] == przeciwnik)
			{
				test_rzad += deltaRzad[i];
				test_kolumna += deltaKolumna[i];	//Jeżeli ruch, ktory ma byc wykonany nie wychodzi poza granice planszy i nie jest to pole zajete										przez aktualnego gracza to jest to poprawny ruch
				poprawny = 1;
			}

			if (test_rzad >= 0 && test_rzad < BOARD_SIZE && test_kolumna >= 0 && test_kolumna < BOARD_SIZE && pola_planszy[test_rzad][test_kolumna] == aktualny_gracz && poprawny)
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

				while (test_rzad >= 0 && test_rzad < BOARD_SIZE && test_kolumna >= 0 && test_kolumna < BOARD_SIZE && pola_planszy[test_rzad][test_kolumna] == przeciwnik)
				{
					test_rzad += deltaRzad[i];
					test_kolumna += deltaKolumna[i];
				}

				if (test_rzad >= 0 && test_rzad < BOARD_SIZE && test_kolumna >= 0 && test_kolumna < BOARD_SIZE && pola_planszy[test_rzad][test_kolumna] == aktualny_gracz)
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
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
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
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
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
		else if (czyMozliwyRuch(aktualny_gracz) == 0)
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


class AIGracz : public Gracz {
public:
	AIGracz(Pole kolor) : Gracz(kolor) {};
	void zrob_ruch(Plansza& plansza) override {
		for (int rzad = 0; rzad < BOARD_SIZE; rzad++)
		{
			for (int kolumna = 0; kolumna < BOARD_SIZE; kolumna++)
			{
				if (plansza.sprawdzanie_ruchu(rzad, kolumna, kolor) == 1)
				{
					plansza.ruch(rzad, kolumna, kolor);
					return;
				}
			}
		}
	}
};


int main() {
	Plansza plansza;
	CzlowiekGracz gracz1(Pole::BIALE);
	CzlowiekGracz gracz2(Pole::CZARNE);
	Pole zwyciezca = {};

	time_t start;
	time_t koniec;
	double czas;

	time(&start);
	while (true)
	{



		plansza.wypisz_plansze();
		if (plansza.czyMozliwyRuch(gracz2.getKolor()))
		{
			gracz2.zrob_ruch(plansza);
		}
		else if (!plansza.czyMozliwyRuch(gracz1.getKolor()))
		{
			zwyciezca = plansza.czyToKoniec(gracz2.getKolor());
			break;
		}

		plansza.wypisz_plansze();
		if (plansza.czyMozliwyRuch(gracz1.getKolor()))
		{
			gracz1.zrob_ruch(plansza);
		}
		else if (!plansza.czyMozliwyRuch(gracz2.getKolor()))
		{
			zwyciezca = plansza.czyToKoniec(gracz1.getKolor());
			break;
		}
	}

	plansza.wypisz_plansze();
	time(&koniec);
	czas = difftime(koniec, start);
	std::cout << "\nGra dobiegla konca!!!" << std::endl;
	if (czas < 60)
	{
		std::cout << "Czas gry: " << czas  << "s" << std::endl;
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

	return 0;
}