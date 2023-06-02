#include "CzlowiekGracz.h"

void CzlowiekGracz::zrob_ruch(Plansza& plansza) {
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