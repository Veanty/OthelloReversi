#pragma once

#ifndef PLANSZA_H
#define PLANSZA_H

#include <iostream>
#include <iomanip>
#include <string>
#include "PoleRodzajGracza.h"


class Plansza {

private:
	Pole** pola_planszy;
public:
	
	int biale;
	int czarne;

	int rozmiar_planszy;

	Plansza(int rozmiar_planszy);

	~Plansza();

	void wypisz_plansze();

	int sprawdzanie_ruchu(int rzad, int kolumna, Pole aktualny_gracz) const;

	void ruch(int rzad, int kolumna, Pole aktualny_gracz);

	void policz();

	int czyMozliwyRuch(Pole aktualny_gracz);

};


#endif