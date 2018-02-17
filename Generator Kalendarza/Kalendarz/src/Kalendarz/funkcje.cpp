#include "funkcje.h"
#include <iostream>
#include <fstream>
using namespace std;


int zeller(int d, int m, int y)                                                            // Funkcja wyliczaj¹ca dzien tygodnia dla zadanej daty.
{                                                                                          // Przypisuje cyfry od "0" dla niedzieli do "6" dla soboty.
	return ((d += m<3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7); // Funkcja bêdzie wykorzystana do wyliczenia dnia tygodnia,
}                                                                                          // przypadaj¹cego na 1. stycznia danego (parametrem w konsoli) roku.


Parametry parsowanie_parametrow(int argc, char**argv)
{
	Parametry p;
	string komunikat = " Program wygeneruje kalendarz na zadany rok po podaniu danych wg nastepujacego wzoru :\n\n \"program.exe -o nazwa_pliku.txt -r pozadany_rok -d pierwszy_wyswietlany_dzien_tygodnia\"\n\n";

	if (argc == 7 || argc == 2)                                                       // Program tworzy kalendarz w oparciu o 3 parametry przekazane przez 3 prze³¹czniki,
	{                                                                                 // dlatego te¿ sprawdza, czy podanych zosta³o w sumie 7 parametrów (uwzglêdniaj¹c argument 
		for (int i = 1; i < argc; i++)                                                // zerowy : nazwê programu). Drug¹ opcj¹ jest podanie tylko jednego argumentu w postaci "-h",
		{                                                                             // st¹d program akceptuje równie¿ liczbê dwóch argumentów.
			if (argv[i][0] == '-')                                                     // Jesli funkcja natrafi na znak "-", sprawdza jaki znak znajduje siê tu¿ za nim.
			{                                                                          // Program przewiduje cztery prze³¹cziki "-r", "-o", "-d" i "-h". Takich te¿ znaków wyszukuje
				if (argv[i][1] == 'o') p.nazwa_pliku = argv[++i];                      // i odczytuje nastêpny argument po danym prze³¹czniku, przypisuj¹c jego numer odpowiedniej
				else if (argv[i][1] == 'd') p.dzien = argv[++i][0];                 // zmiennej. W przypadku podania b³êdnych danych (inne niz przewidziane przez program)
				else if (argv[i][1] == 'r') p.rok = atoi(argv[++i]);                     // wyœwietla stosowny komunikat.
				else if (argv[i][1] == 'h') {                                          //  Wywo³anie prze³¹cznika "-h" powoduje wyswietlenie krotkiej pomocy obs³ugi programu.
					cout << " Pomoc: \n\n " << komunikat; exit(0);
				}
				else {
					cout << " Niepoprawny znak przelacznika.\n\n" << komunikat; exit(0);
				}  // Przypadek podania prze³¹cznika innego ni¿ przewiduje program.
			}
			else {
				cout << "Niepoprawny format danych \n\n" << komunikat; exit(0);
			}	        // Przypadek podania danych bez u¿ycia prze³¹cznika lub bez znaku "-".
		}
	}
	else { cout << " Niepoprawne dane. \n\n" << komunikat; exit(0); }             // Przypadek wprowadzenia liczby argumentów inne ni¿ przewidziane przez program.


	return p;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

int Tworzenie_pliku(ofstream & zapis, string & nazwa)
{
	zapis.open(nazwa, ios::out);                                         // Tworzenie pliku tekstowego
	if (!zapis.good()) zapis << "Proba otwarcia pliku zakonczona niepowodzeniem!";
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------

int Przypisanie(char & dzien, int &dzien1)
{                           // Przypisanie dniom tygodnia odpowiednich wartosci numerycznych                                       
							// Dzien tygodnia zawarty jest w podanym parametrze po prze³¹czniku -d.
	switch (dzien) {
	case 'n': dzien1 = 0; break;      // niedziela
	case 'o': dzien1 = 1; break;      // poniedzia³ek
	case 'w': dzien1 = 2; break;      // wtorek
	case 's': dzien1 = 3; break;      // œroda
	case 'c': dzien1 = 4; break;      // czwartek
	case 't': dzien1 = 5; break;      // pi¹tek
	case 'b': dzien1 = 6; break;      // sobota
	default: cout << "Podano niewlasciwy symbol dnia" << endl; exit(0);
	}
	return dzien1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------

int Pomocnicza_wciecie(int & wciecie, int & dzien1, int & rok)
{
	                                                  // Definiowanie pojecia "wciecia", wykorzystywanego
	int Zeller = zeller(1, 1, rok);                   // do okreslenia miejsca rozpoczecia numerowania
	if (Zeller >= dzien1) wciecie = Zeller - dzien1;  // dni w pierwszym tygodniu stycznia, w zale¿noœci 
	switch (dzien1 - Zeller)                          // od kolejnoœci wyœwietlania dni tygodnia.
	{
	case 1: wciecie = 6; break;
	case 2: wciecie = 5; break;
	case 3: wciecie = 4; break;
	case 4: wciecie = 3; break;
	case 5: wciecie = 2; break;
	case 6: wciecie = 1; break;
	}
	return wciecie;
}

//---------------------------------------------------------------------------------------------------------------------

int rok_przestepny(int & rok, int & i, int & liczbadni)
{
	if (i == 1)                                          // Uwzglednienie roku przestêpnego - luty ma 29 dni.
		if ((rok % 4 == 0) && !(rok % 100 == 0) || (rok % 400 == 0)) liczbadni = 29;
	return liczbadni;
}

//-----------------------------------------------------------------------------------------------------------------------

void wypisz_dni_tygodnia(ofstream &zapis, int &dzien1)
{
	string week[7] = { "ND","PON","WT","SR","CZW","PT","SOB" };
	for (int a = 0; a < 7; a++)
	{                                                            // Wypisanie nazw dni tygodnia w odpowiedniej kolejnoœci zdefiniowanej parametrem po prze³¹czniku -d.
		if (dzien1 + a < 7) zapis << week[dzien1 + a] << "	";   // Dni tygodnia jest 7, wiêc zostanie wypisanych 7 nazw, jedna obok drugiej.
		else zapis << week[dzien1 + a - 7] << "	";
	}
	zapis << endl;
}

//------------------------------------------------------------------------------------------------------------------------

void Wypisz_numery_dni_tygodnia(int &wciecie, int &ile_dni, ofstream &zapis)
{
	int licznik_dni = 1;
	for (int a = 0; a < 6; a++)                      // Funkcja wypisuj¹ca numery dni w danym miesi¹cu.
	{                                                // Funkcja ta uwzglêdnia wyliczon¹ wczeœniej wartoœæ "wciecie".
													 // Wykorzystuj¹c zmienn¹ "licznik_dni" zaczyna numeracjê od 1.
		if (licznik_dni > ile_dni) break;            // Wykona siê maksymalnie 6 razy, poniewa¿ 6 to maksymalna liczba
													 // wierszy tygodni w miesi¹cu.
		if (a == 0)                                  // Pierwszy wiersz tygodnia wykorzystuje zmienn¹ "wciecie"
		{                                            // wyliczon¹ w oparciu o wzór Zellera.
			for (int b = 0; b < wciecie; b++) zapis << "	";
			for (int b = 0; b < 7 - wciecie; b++) zapis << licznik_dni++ << "	";
			zapis << endl;
			wciecie = 0;                             // Po wypisaniu pierwszego tygodnia miesi¹ca wartoœæ "wciecie" jest zerowana, by kolejne
			continue;                                // wiersze kalendarza by³y wypisywane od pocz¹tku do koñca wiersza, czyli 7 razy
		}                                            // na wiersz.
		for (int b = 0; b < 7; b++)
		{
			if (licznik_dni > ile_dni)               // Jeœli liczba wypisanych dni zrówna³a siê z liczb¹ dni danego miesi¹ca,
			{                                        // zapamiêtywana jest wartoœæ zmiennej "wciecie" równa b, czyli liczbie dni
				wciecie = b;                         // ju¿ wypisanych w ostatnim wierszu danego miesi¹ca. Umo¿liwi to rozpoczêcie 
				break;                               // numeracji dni kolejnego miesi¹ca od miejsca w wierszu, w którym zakoñczy³a 
			}                                        // siê numeracja poprzedniego miesi¹ca.
			zapis << licznik_dni++ << "	";
		}
		zapis << endl;
	}
}