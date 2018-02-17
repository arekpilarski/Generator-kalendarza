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

	Parametry p = parsowanie_parametrow(argc, argv);            // Pobranie parametr�w z konsoli.

	//-------------------------------------------------------------------------------------------------------

	Tworzenie_pliku(zapis, p.nazwa_pliku);                      // Tworzenie pliku.

	//------------------------------------------------------------------------------------------------------

	Przypisanie(p.dzien, dzien1);                               // Tworzenie zmiennej do pracy programu.

	//--------------------------------------------------------------------------------------------------------

	Pomocnicza_wciecie(wciecie, dzien1, p.rok);                 // Tworzenie zmiennej do pracy programu.

	//-----------------------------------------------------------------------------------------------------------

	zapis << "			Rok " << p.rok << endl << endl;         // Wy�wietlenie danego roku.

	//------------------------------------------------------------------------------------------------------------


	for (int i = 0; i < 12; i++)                                // Pocz�tek p�tli wy�wietlaj�cej 12 miesi�cy kalendarza wraz z nazwami dni i ich numeracj�.
	{
		int ile_dni = ilosc_dni[i];                             // ile_dni ogranicza numeracj� dni do liczby dni w danym miesi�cu (odwo�anie do tablicy ilosc_dni).
		rok_przestepny(p.rok, i, ile_dni);                      // Sprawdzanie czy dany rok jest przest�pny.
		// --------------------------------------------------------------------------------------------------------

		zapis << "			" << miesiac[i] << endl;            //Wy�wietlenie odpowiedniej nazwy miesi�ca (odwo�anie do tablicy miesiac).

		//-----------------------------------------------------------------------------------------------------------

		wypisz_dni_tygodnia(zapis, dzien1);                     // Wypisanie nazw dni tygodnia.

		//----------------------------------------------------------------------------------------------------------

		Wypisz_numery_dni_tygodnia(wciecie, ile_dni, zapis);    // Wypisanie numer�w dni tygodnia.
		zapis << endl;
	}
	zapis.close();
	return 0;
}
