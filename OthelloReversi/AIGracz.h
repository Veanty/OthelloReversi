#pragma once
#ifndef AIGRACZ_H
#define AIGRACZ_H

#include "Gracz.h"

class AIGracz : public Gracz {
public:
	AIGracz(Pole kolor) : Gracz(kolor) {};
	void zrob_ruch(Plansza& plansza) override;
};


#endif // !AIGRACZ_H
