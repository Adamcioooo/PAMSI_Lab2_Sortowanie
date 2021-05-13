#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <new>
#include "scal.hh"
using namespace std;

//Funkcja zaraca liosc wierszy
int policz(string nazwa){

	string str;				//Zmienna pomocnicza
	int zakres = 0;			//Zmienna zliczajaca ilosc wierszy

	fstream filmy;
	filmy.open(nazwa);		//Otwarcie pliku

	while(!filmy.eof()){	//Petla dziala tak dlugo az nie natrafi na ostatni wiersz
		getline(filmy,str);	//Przypisanie wartosci wiersza do zmiennej pomocniczej
		zakres++;			//Zwiekszenie zakresu
	}
	filmy.close();			//Zamkniecie pliku
	return zakres;			//Zwraca ilosc wierszy
}


//Funkcja  rozdziela wartosci i wybiera mniejsza z nich
void scal(Filmy *filmiki, int l, int m, int r)
{
    int n1 = m - l + 1;							//Zmienna pomocnicza zawierajaca zakres
    int n2 = r - m;								//Zmienna pomocnicza zawierajaca zakres

    Filmy *L = new (nothrow) Filmy[n1];			//Dynamiczne allocowanie pamieci dla tablicy pomocniczej
    Filmy *R = new (nothrow) Filmy[n2];			//Dynamiczne allocowanie pamieci dla tablicy pomocniczej




    for (int i = 0; i < n1; i++){				//Petla umozliwia przekopiowanie elementow dla 1 czesci
        L[i].ocena = filmiki[l + i].ocena;		//Kopiowanie wartosci ocen do tymczasowej tablicy
    	L[i].tytul = filmiki[l + i].tytul;		//Kopiowanie nazw tytulow do tymczasowej tablicy
    }
    for (int j = 0; j < n2; j++){				//Petla umozliwia przekopiowanie elementow dla 2 czesci
        R[j].ocena = filmiki[m + 1 + j].ocena;	//Kopiowanie wartosci ocen do tymczasowej tablicy
    	R[j].tytul = filmiki[m + 1 + j].tytul;	//Kopiowanie nazw tytulow do tymczasowej tablicy
    }

    int i = 0;							//Zmienna pomocnicza
    int j = 0;							//Zmienna pomocnicza

    int k = l;							//Zmienna pomocnicza

    while (i < n1 && j < n2) {				//Petla dziala tak dlugo az dojdzie do zakresu n1 lub n2.
        if (L[i].ocena <= R[j].ocena) {		//Porowanienie i przypisanie mniejszej/równej oceny z 2 filmow
        	filmiki[k].ocena = L[i].ocena;	//Przypisuje wartosc ocena na k-tym miejscu tabeli
            filmiki[k].tytul = L[i].tytul;	//Przypisuje tytul na k-tym miejscu tabeli
            i++; 							//Zwiekszenie zakresu zmiennej i
        }
        else {								//Jezeli wartosc w 1 tabeli jest wieksza od wartosci z 2 tabeli to
        	filmiki[k].ocena = R[j].ocena;	//Przypisuje wartosc oceny z 2 tabeli
        	filmiki[k].tytul = R[j].tytul;	//Przypisuje tytul z 2 tabeli
            j++;							//Zwiekszenie zakresu zmiennej j
        }
        k++;								//Zwiekszenie zakresu zmiennej k
    }
    										//Kopiowanie pozostalych elemetow
    while (i < n1){							//Petla dziala tak dlugo az i nie bedzie o 1 mniejsze od n1
    	filmiki[k].ocena = L[i].ocena;		//Przypisuje wartosc ocena na k-tym miejscu tabeli
    	filmiki[k].tytul = L[i].tytul;		//Przypisuje tytul na k-tym miejscu tabeli
        i++;
        k++;
    }

    while (j < n2){							//Petla dziala tak dlugo az j nie bedzie o 1 mniejsze od n2
    	filmiki[k].ocena = R[j].ocena;		//Przypisuje wartosc ocena na k-tym miejscu tabeli
    	filmiki[k].tytul = R[j].tytul;		//Przypisuje tytul na k-tym miejscu tabeli
        j++;								//Zwiekszenie zakresu zmiennej j
        k++;								//Zwiekszenie zakresu zmiennej k
    }
    delete[] R;					//Zwalnianie pamieci dla 1 tablicy
    delete[] L;					//Zwalnianie pamieci dla 2 tablicy

}




// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */

//Funkcja uruchamia sorotwanie
void sortuj(Filmy *filmiki,int l,int r){
    if(l>=r){								//Jezlei wartosc indeksu 1 tabeli jest wiekszy lub rowny indeksowi prawej tabeli
        return;								//wylacza funkcje / wychodzi z niej
    }
    int m =l+ (r-l)/2;						//Obliczanie srodkowego elementu
    sortuj(filmiki,l,m);					//Wywolanie funkcji sortuj dla parametrow l, m  - umozliwia to posortowanie 1 tymczasowej tablicy
    sortuj(filmiki,m+1,r);					//Wywolanie funkcji sortuj dla parametrow m+1, r - umozliwia to posortowanie 2 tymczasowej tablicy
    scal(filmiki,l,m,r);					//Wywolanie funkcji scal umozliwia porownanie wartosci i zwrocenie ich posortowanych w tablicy glownej (filmiki)

}



//Funkcaj usuwa wiersze z pustymi kolumnami
int usun_zbedne(Filmy *filmiki,string nazwa_pliku){



	fstream filmy;
	filmy.open(nazwa_pliku);		//Otwarcie pliku
	string wiersz;					//Zmienna pomocnicza
	int i = 0;						//Zmienna pomocnicza
	char delim = ';';				//Zmienna pomocnicza



	while(!filmy.eof()){			//Petla dziala tak dlugo az nie natrafi na ostatni wiersz

			getline(filmy,wiersz, delim);		//Wczytywanie wiersza do znaku
			getline(filmy,wiersz, delim);		//Wczytywanie tego samego wiersza az do znaku
			filmiki[i].tytul = wiersz;			//Podstawia nazwe tytulu pod zmienna tytul

			getline(filmy,wiersz);				//Wczytywanie tego samego wiersza az do znaku
			filmiki[i].ocena = atof(wiersz.c_str());	//Wczytanie oceny i zmiana stringa na float
			if(filmiki[i].ocena == '\0'){				//Sprawdzenie czy nie ma pustego pola
				i--;									//Jezeli jest puste pole wczytuje kolejny wiersz nadpisujac stary
			}
			i++;										//Zwiekszenie zakresu

		}
	return i;											//Zwraca ilosc wierszy po usunieciu niektorych pozycji
}

//Sprawdza poprawnosc sortowania
void sprawdz(Filmy *filmiki, int i){

	int j = 1;											//Zmienna pomocnicza

	while(j < i){											//Petla dziala tak dlugo az dojdzie do ostatniego wiersza
	    if(filmiki[j-1].ocena > filmiki[j].ocena){			//Porowanienie poprzedniego i obecnego elementu
	    	cout << "NIE UDALO SIE POSORTOWAC!!!" << endl;	//Zwraca ostrzezenie
	    }
	    j++;												//Zwiekszenie zakresu

	 }

}

//Funkcja zapisuje posortowanie wiersze do pliku
void zapisz(Filmy *filmiki, int i){

	int j = 0;				//Zmienna pomocnicza
	string nowy_plik;		//Zmienna przechowujac anazwe nowego pliku
	ofstream wyjscie;

	cout << "Podaj nazwe pliku: ";
	cin >>  nowy_plik;				//Zapisanie nazwy nowego pliku
	wyjscie.open(nowy_plik);		//Ustawienie jako wyjscie

	while(j < i){					//Petla dziala tak dlugo az dojdzie do ostatniego wiersza
									//Wpisywanie do pliku odpowiednich wartosci
		wyjscie  << j << "," << filmiki[j].tytul << ", " << filmiki[j].ocena << ".0" << endl;
	    j++;						//Zwiekszenie zakresu
	}
	wyjscie.close();				//Zamyka plik
}












