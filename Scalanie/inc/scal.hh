#ifndef SCAL_HH
#define SCAL_HH
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <new>
using namespace std;


				//Struktura Filmy
				//zawiera string tytul który przechowuje nazwe filmu
				// float ocena przechowuje ocene filmy

struct Filmy {
    string tytul;
    float ocena;

};

//Funkcja zwraca ilosc wierszy w pliku
int policz(string nazwa);

//Funkcja rozdziela wartosci i wybiera mniejsza z nich
void scal(Filmy *filmiki, int l, int m, int r);

//Funkcja uruchamia sorotwanie
void sortuj(Filmy *filmiki,int l,int r);

//Funkcja usuwa puste pola
int usun_zbedne(Filmy *filmiki,string nazwa_pliku);

//Funkcaj sprwdza czy sortowanie powiodlo sie
void sprawdz(Filmy *filmiki, int i);

//Funkcja zapisuje do pliku
void zapisz(Filmy *filmiki, int i);
























#endif
