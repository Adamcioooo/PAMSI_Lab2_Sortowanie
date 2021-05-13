#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <chrono>
#include "scal.hh"
using namespace std;






int main(){

	int i = 0;										//Zmienna pomocnicza
	int zakres = 0;									//Zmienna pomocnicza
	string nazwa_pliku = "dane.txt";				//Przechowuje nazwe pliku

	zakres = policz(nazwa_pliku);					//Oblicza ilosc wierszy


	Filmy *filmiki = new (nothrow) Filmy[zakres];	//Alokowanie pamiêci

	i = usun_zbedne(filmiki,nazwa_pliku);			//Usuwa wiersze z pustymi polami

													//Poczatek mierzenia czasu
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    sortuj(filmiki , 0, i - 1);						//Sortowanie przez scalanie

    												//Koniec mierzenia czasu
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << endl << endl;
    												//Wypisywanie czasu trwania algorytmu
    //cout << "Time = " << chrono::duration_cast<chrono::seconds>(end - begin).count() << " [s]  10^(1)s" << endl;
    cout << "Time = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]  10^(-3)s" << endl;
    //cout << "Time = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << " [us]  10^(-6)s" << endl;
    //cout << "Time = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << " [ns]  10^(-9)s" << endl;



    sprawdz(filmiki, i);							//Sprawdza czy wartosci zostaly dobrze posortowane
    //zapisz(filmiki, i);								//Zapisuje do pliku

	delete[] filmiki;								//Zwalnia pamiec

    return 0;

}
