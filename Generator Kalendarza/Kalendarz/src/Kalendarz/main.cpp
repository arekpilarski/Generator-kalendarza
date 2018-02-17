#include <iostream>
#include <string>
#include <fstream>
#include "funkcje.h"

using namespace std;

//Definiowanie tablic do pracy programu :

string miesiac[12] = { "Styczen", "Luty","Marzec","Kwiecien","Maj","Czerwiec","Lipiec","Sieprien","Wrzesien","Pazdziernik","Listopad","Grudzien" };
int ilosc_dni[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

int main(int argc, char** argv)
{
	int dzien1, wciecie;
	ofstream zapis;

	Parametry p = parsowanie_parametrow(argc, argv);            // Pobranie parametrów z konsoli.

	//-------------------------------------------------------------------------------------------------------

	Tworzenie_pliku(zapis, p.nazwa_pliku);                      // Tworzenie pliku.

	//------------------------------------------------------------------------------------------------------

	Przypisanie(p.dzien, dzien1);                               // Tworzenie zmiennej do pracy programu.

	//--------------------------------------------------------------------------------------------------------

	Pomocnicza_wciecie(wciecie, dzien1, p.rok);                 // Tworzenie zmiennej do pracy programu.

	//-----------------------------------------------------------------------------------------------------------

	zapis << "			Rok " << p.rok << endl << endl;         // Wyœwietlenie danego roku.

	//------------------------------------------------------------------------------------------------------------


	for (int i = 0; i < 12; i++)                                // Pocz¹tek pêtli wyœwietlaj¹cej 12 miesiêcy kalendarza wraz z nazwami dni i ich numeracj¹.
	{
		int ile_dni = ilosc_dni[i];                             // ile_dni ogranicza numeracjê dni do liczby dni w danym miesi¹cu (odwo³anie do tablicy ilosc_dni).
		rok_przestepny(p.rok, i, ile_dni);                      // Sprawdzanie czy dany rok jest przestêpny.
		// --------------------------------------------------------------------------------------------------------

		zapis << "			" << miesiac[i] << endl;            //Wyœwietlenie odpowiedniej nazwy miesi¹ca (odwo³anie do tablicy miesiac).

		//-----------------------------------------------------------------------------------------------------------

		wypisz_dni_tygodnia(zapis, dzien1);                     // Wypisanie nazw dni tygodnia.

		//----------------------------------------------------------------------------------------------------------

		Wypisz_numery_dni_tygodnia(wciecie, ile_dni, zapis);    // Wypisanie numerów dni tygodnia.
		zapis << endl;
	}
	zapis.close();
	return 0;
}
