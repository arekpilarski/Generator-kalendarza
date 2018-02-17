#pragma once
#include <string>
#include <fstream>

struct Parametry
{
	int rok;
	char dzien;
	std::string nazwa_pliku;
};

int zeller(int d, int m, int y);


Parametry parsowanie_parametrow(int argc, char**argv);
int Tworzenie_pliku(std::ofstream & zapis, std::string & nazwa);
int Przypisanie(char & dzien, int &dzien1);
int Pomocnicza_wciecie(int & wciecie, int & dzien1, int & rok);
int rok_przestepny(int & rok, int & i, int & liczbadni);
void wypisz_dni_tygodnia(std::ofstream &zapis, int &dzien1);
void Wypisz_numery_dni_tygodnia(int &wciecie, int &ile_dni, std::ofstream &zapis);

