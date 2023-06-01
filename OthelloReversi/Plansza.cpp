#include "Plansza.h"

Plansza::Plansza(int rozmiar_planszy) {
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

	pola_planszy[numer - 1][numer - 1] = Pole::BIALE;
	pola_planszy[numer - 1][numer] = Pole::CZARNE;
	pola_planszy[numer][numer - 1] = Pole::CZARNE;
	pola_planszy[numer][numer] = Pole::BIALE;
}

Plansza::~Plansza() {
	for (int i = 0; i < rozmiar_planszy; i++)
	{
		delete[] pola_planszy[i];
	}
	delete[] pola_planszy;
}

void Plansza::wypisz_plansze() {
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

int Plansza::sprawdzanie_ruchu(int rzad, int kolumna, Pole aktualny_gracz) const{

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

void Plansza::ruch(int rzad, int kolumna, Pole aktualny_gracz) {
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

Plansza::IlePionków Plansza::policz() {
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

int Plansza::czyMozliwyRuch(Pole aktualny_gracz) {
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

Pole Plansza::czyToKoniec(Pole aktualny_gracz) {
	IlePionków wszystkie_pionki = policz();

	if (wszystkie_pionki.ile_bialych == 0)
	{
		return Pole::CZARNE;
	}
	else if (wszystkie_pionki.ile_czarnych == 0)
	{
		return Pole::BIALE;
	}
	else if (czyMozliwyRuch(Pole::BIALE) == 0 || czyMozliwyRuch(Pole::CZARNE) == 0)
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