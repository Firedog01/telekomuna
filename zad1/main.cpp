#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "colors.h"
using namespace std;

const int ROSE = 8;
const int JACK = 16;

uint8_t H[8][2] {
		{0b11111111, 1<<7},
		{0b11011111, 1<<6},
		{0b11011101, 1<<5},
		{}
};

bool H[ROSE][JACK]{ {1,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,0},
					{1,1,0,1,1,1,1,1, 0,1,0,0,0,0,0,0},
					{1,1,0,1,1,1,0,1, 0,0,1,0,0,0,0,0},
					{1,1,0,1,0,1,0,1, 0,0,0,1,0,0,0,0},
					{1,0,0,1,0,1,0,1, 0,0,0,0,1,0,0,0},
					{1,0,0,1,0,1,0,0, 0,0,0,0,0,1,0,0},
					{1,0,0,1,0,0,0,0, 0,0,0,0,0,0,1,0},
					{1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1}};

vector<bool> StringToBool( string tekst ) { /* wczytuje tylko w postaci zero-jedynkowej */
	vector<bool> wiadomosc;
	for( int i=0; i<tekst.size(); i++ ) {
		if(tekst[i]=='1') wiadomosc.push_back(1);
		else wiadomosc.push_back(0);
	}
	return wiadomosc;
}

vector<bool> CharToBool( string tekst ) { /* zamienia ASCII na kod binarny */
	vector<bool> bin;
	int znak;

	for( int i=0; i<tekst.size(); i++ ) {
		znak = tekst[i];
		for( int n=0; n<8; n++ ) {
			bin.push_back( znak%2 );
			znak = znak/2;
		}
	}
	return bin;
}

char getChar( vector<bool> bin ) { /* zamienia kod binarny na ASCII */
	char znak = 0;
	for( int i=0; i<8; i++ ) {
		znak += bin[i]*pow(2,i);
	}
	return znak;
}

int bitParzystosci( vector<bool> wiadomosc, int nr_wiersza ) {
	int c = 0;
	for( int i=0; i<wiadomosc.size(); i++ ) {
		c += H[nr_wiersza][i] * wiadomosc[i];
	}
	c = c%2;
	return c;
}

void dodajBityParzystosci( vector<bool> &wiadomosc ) {
	vector<bool> kopia = wiadomosc;
	for( int i=0; i<ROSE; i++ ) {
		wiadomosc.push_back( bitParzystosci(kopia, i) );
	}
}

vector<bool> kodowanie( vector<bool> wiadomosc ) {
	vector<bool> kod;
	vector<bool> bity;

	for( int i=0; i<wiadomosc.size(); i++ ) {
		kod.push_back(wiadomosc[i]);
		bity.push_back(wiadomosc[i]);

		if( (i+1)%8 == 0 && i != 0 ) {  /* Wstawianie po każdym znaku reprezentowanym binarnie ośmiu bitów parzystości. */
			dodajBityParzystosci(bity);
			for( int n=0; n<ROSE; n++ ) kod.push_back(bity[n+8]);
			bity.clear();
		}
	}
	return kod;
}

void korekcja( vector<bool> &bledna, vector<bool> E ) {
	bool koryguj = false;
	cout << f_yellow << "ZMIANA." << endl << s_reset;

	for( int i=0; i<JACK; i++ ) { /* Sprawdzamy, która z kolumn jest równa wektorowi E. */
		for( int n=0; n<ROSE; n++ ) {
			if( E[n] == H[n][i] ) koryguj = true;
			else {
				koryguj = false; break;
			}
		}
		if( koryguj == true ) {
			bledna[i] = (~bledna[i])%2; /* Negacja - poprawa przekłamanego bitu. */
		}
	}
}

void weryfikacja( vector<bool> &wiadomosc, int dlugosc ) {
	bool zweryfikuj = true;

	if( wiadomosc.size() != dlugosc ) {
		cout << f_red << "Niezgodna ilosc bitow (" << wiadomosc.size() <<")." << s_reset << endl;
		return;
	}
	vector<bool> E; /* wektor błędu */
	int nr;

	for( int i=0; i<ROSE; i++ ) { /* Jeśli w wektorze błędu wystąpi wartość 1 to oznacza, że musimy skorygować wiadomość. */
		nr = bitParzystosci(wiadomosc, i);
		E.push_back( nr );
		if( nr == 1 ) zweryfikuj = false;
		//cout << f_red << nr << s_reset;
	}

	if(zweryfikuj == true)
		cout << f_green << "OK." << s_reset << endl;
	else korekcja(wiadomosc, E);
}

int main()
{
	system("CLS");
	cout << b_red << f_yellow << "  TELEKOMUNIKACJA - zad. 1  " << s_reset << endl << endl;

	vector<bool> wiadomosc;
	vector<bool> zakodowane;
	vector<bool> bledna;
	string tekst;

	ifstream plik_wej;
	ofstream plik_binarny;
	fstream plik_zakodowany;

	plik_wej.open("wiadomoscWyslana.txt");
	plik_binarny.open("wiadomoscBinarnie.txt");
	plik_zakodowany.open("wiadomoscZakodowana.txt", ios::out);

/* Wczytywanie wiadomości tekstowej, zamiana na system binarny. */
	while(!plik_wej.eof()) {
		getline(plik_wej, tekst);
	}
	int rozmiar = tekst.size();

	wiadomosc = CharToBool(tekst);
	cout << "Wiadomosc (\'" << tekst << "\') binarnie: " << endl;
	for( int i=0; i<wiadomosc.size(); i++ ) {
		cout << wiadomosc[i];
		plik_binarny << wiadomosc[i];
		if( (i+1)%8 == 0 ) cout << " ";
	}
	cout << f_cyan << "bity: " << wiadomosc.size() << s_reset << endl << endl;

/* Dodawanie bitów parzystości. */
	zakodowane = kodowanie(wiadomosc);
	int x = 0;

	cout << "Zakodowana wiadomosc (" << f_cyan << "niebieskie" << s_reset << " bity to bity parzystosci):" << endl;
	for( int i=0; i<zakodowane.size(); i++ ) {
		plik_zakodowany << zakodowane[i];

		if(x%2 != 0 ) cout << f_cyan << zakodowane[i] << s_reset;
		else cout << zakodowane[i];
		if( (i+1)%8 == 0 ) {
			cout << " ";
			x++;
		}
	}
	cout << f_cyan << "bity: " << zakodowane.size() << s_reset;

	plik_wej.close();
	plik_binarny.close();
	plik_zakodowany.close();

	cout << endl << endl << f_green << "Teraz mozesz wprowadzic zmiany w zakodowanym pliku (jeden blad na 16-bitowy ciag). [ENTER]" << endl << s_reset;
	getchar();

/* Wczytywanie zakodowanego pliku (z możliwymi zmianami). */
	plik_zakodowany.open("wiadomoscZakodowana.txt", ios::in);

	while(!plik_zakodowany.eof()) {
		getline(plik_zakodowany, tekst);
	}

	bledna = StringToBool(tekst);

	cout << "Po zmianie:" << endl;
	for( int i=0; i<bledna.size(); i++ ) {
		cout << bledna[i];
		if( (i+1)%8 == 0 ) cout << " ";
	}
	cout << f_cyan << "bity: " << bledna.size() << s_reset << endl;

/* Deklaracja wektora wektorów - każdy 16-bitowy ciąg (1 litera) zapisywany jest do osobnego wektora. */
	vector< vector<bool> > multiWektor;
	for(int i = 0; i < rozmiar; i++) {
		vector<bool> row;
		multiWektor.push_back(row);
	}

	vector<bool> poprawiona;
	int ilosc = 0; /* ilość znaków = ilość 16-bitowych wektorów */
	string odpowiedz;

/* Podział całej wczytanej (przekłamanej) wiadomości na mniejsze 16-bitowe wektory. */
	for( int i=0; i<bledna.size(); i++ ) {
		multiWektor[ilosc].push_back( bledna[i] );
		if( (i+1)%16 == 0 ) ilosc++;
	}
	bledna.clear();

	fstream plik_wyj;
	plik_wyj.open("wiadomoscOdebrana.txt", ios::out);

/* Weryfikacja i korekcja każdego wektora (reprezentującego jeden znak) + scalanie 16-bitowych wektorów w jeden + zapis do pliku. */
	for(int i = 0; i < rozmiar; i++) {
		weryfikacja(multiWektor[i], zakodowane.size()/rozmiar);
		bledna.insert(bledna.end(), multiWektor[i].begin(), multiWektor[i].end());
		odpowiedz += getChar(multiWektor[i]); /* Zamiana każdego ze zweryfikowanych 16-bitowych wektorów na pojedyncze znaki + wpisanie ich do stringa. */
		plik_wyj << getChar(multiWektor[i]);
	}

	plik_zakodowany.close();
	plik_wyj.close();

	cout << endl << "Poprawione:" << endl;
	for( int i=0; i<bledna.size(); i++ ) { /* Wypisanie scalonego, poprawionego wektora. */
		cout << bledna[i];
		if( (i+1)%8 == 0 ) cout << " ";
	}
	cout << f_cyan << "bity: " << bledna.size() << s_reset << endl << endl;

	cout << "Wiadomosc odebrana: " << odpowiedz << endl;

	cout << endl << f_green << "done :)";

	return 0;
}