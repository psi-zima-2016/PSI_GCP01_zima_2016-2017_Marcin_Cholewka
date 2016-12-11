#ifndef Header_h
#define Header_h
#include <iostream>
using namespace std;

//const int wiersze = 7;
//const int kolumny = 5;
//const int liczby = 3;

class MLP {
public:
	int* n;
	int Lvec; // liczba wszystkich ucz�cych wektor�w (w ci�gu ucz�cym) !
	double ** I; // wej�cia
	double ** O; // wyj�cia
	double ** B; // b��d
	double ** E;
	double ** Z; // warto�� oczekiwana
	double *** W; // tablica wag
	double *** W1; // tablica poprzednich wag, potrzebna do obliczenia momentum
	//int WZORZEC[wiersze][kolumny][liczby];
	int WZOR[1][35][10]; // p�askie, najpierw kolumny, potem wiersze
	int TEST[2][35][10]; // j.w., ka�d� liczb� mo�emy zapisa� na dwa sposoby
	double tmp; // warto�� dla tablicy tymczasowej
	double RMS;
	double ERMS; // b��d przeliczany dla ca�ej sieci. d��ymy, �eby wynosi� < 0.01

	int numberOfNeurons;
	int numberOfSignals;
	int numberOfLayers;
	int uczaceIteracje;
	int testoweIteracje;
	double eta; // wsp�czynnik szybko�ci
	double alfa; // wsp�czynnik momentum

	// funkcje
	void wypelnijWagi();
	void stworzWzorce();
	void stworzTesty();
	void wprowadzWejsciaUczace();
	void wprowadzWejsciaTestowe();
	void Epoki();
	MLP();
	~MLP();
};
#endif

