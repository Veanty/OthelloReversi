#include "AIGracz.h"

void AIGracz::zrob_ruch(Plansza& plansza) {

	struct Ruch {
		int rzad;
		int kolumna;
	};

	const int max_ruchy = 20;
	Ruch zapamietane_ruchy[max_ruchy];
	int k = 0;

	for (int rzad = 0; rzad < plansza.rozmiar_planszy; rzad++)
	{
		for (int kolumna = 0; kolumna < plansza.rozmiar_planszy; kolumna++)
		{
			if (plansza.sprawdzanie_ruchu(rzad, kolumna, kolor) == 1 && k < max_ruchy)
			{
				zapamietane_ruchy[k].rzad = rzad;
				zapamietane_ruchy[k].kolumna = kolumna;
				k++;
			}
		}
	}

	if (k == 0)
	{
		std::cout << "Komputer: Brak dostępnych ruchow" << std::endl;
		return;
	}

	int random = rand() % k;

	plansza.ruch(zapamietane_ruchy[random].rzad, zapamietane_ruchy[random].kolumna, kolor);
	std::cout << "Komputer: " << zapamietane_ruchy[random].rzad + 1 << " " << zapamietane_ruchy[random].kolumna + 1 << std::endl;
}