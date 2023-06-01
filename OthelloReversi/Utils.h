#pragma once

#ifndef UTILS_H
#define UTILS_H

#include "Plansza.h"
#include "Gracz.h"
#include "CzlowiekGracz.h"
#include "AIGracz.h"
#include <string>

extern int ilosc_czarnych;
extern int ilosc_bialych;

void dodaj_mecz(int liczba_czarnych, int liczba_bialych, double czas, int rozmiar_planszy, std::string kto_gra);

void odczytaj_mecze();

void wyczysc_bufor();

void rozpocznij_gre();

void intro();

#endif // !UTILS_H
