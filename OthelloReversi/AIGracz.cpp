#include "AIGracz.h"

void AIGracz::zrob_ruch(Plansza& plansza) {

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