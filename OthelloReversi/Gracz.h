#pragma once
#ifndef GRACZ_H
#define GRACZ_H

#include "Plansza.h"

class Gracz {
protected:
	Pole kolor;
public:
	Gracz(Pole kolor) : kolor(kolor) {};
	Pole getKolor();

	virtual void zrob_ruch(Plansza& plansza) = 0;		//Metoda wirtualnie czysta

	virtual ~Gracz() {};
};

#endif
