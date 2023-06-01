#pragma once
#ifndef CZLOWIEKGRACZ_H
#define CZLOWIEKGRACZ_H
#include "Gracz.h"

class CzlowiekGracz : public Gracz {
public:
	CzlowiekGracz(Pole kolor) : Gracz(kolor) { };
	void zrob_ruch(Plansza& plansza) override;
};

#endif // !CZLOWIEKGRACZ_H
