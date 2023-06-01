#pragma once

#ifndef PLANSZA_H
#define PLANSZA_H

#include <iostream>
#include <iomanip>
#include <string>
#include "PoleRodzajGracza.h"

extern int ilosc_bialych;
extern int ilosc_czarnych;

class Plansza {

	struct IlePionków {
		int ile_bialych;
		int ile_czarnych;
	};

private:
	Pole** pola_planszy;
public:
	
	int rozmiar_planszy;

	Plansza(int rozmiar_planszy);

	~Plansza();

	void wypisz_plansze();

	int sprawdzanie_ruchu(int rzad, int kolumna, Pole aktualny_gracz) const;

	void ruch(int rzad, int kolumna, Pole aktualny_gracz);

	IlePionków policz();

	int czyMozliwyRuch(Pole aktualny_gracz);

	Pole czyToKoniec(Pole aktualny_gracz);

};


#endif