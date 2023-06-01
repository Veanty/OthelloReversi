#include "Plansza.h"
#include "Gracz.h"
#include "CzlowiekGracz.h"
#include "AIGracz.h"
#include "Utils.h"

int ilosc_bialych = 0;
int ilosc_czarnych = 0;


int main() {

	std::srand(std::time(0));
	std::cout << "Witaj w grze Othello/Reversi by Jakub Drozd" << std::endl;
	intro();

	return 0;
}