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
	int Lvec; // liczba wszystkich ucz¹cych wektorów (w ci¹gu ucz¹cym) !
	double ** I; // wejœcia
	double ** O; // wyjœcia
	double ** B; // b³¹d
	double ** E;
	double ** Z; // wartoœæ oczekiwana
	double *** W; // tablica wag
	double *** W1; // tablica poprzednich wag, potrzebna do obliczenia momentum
	//int WZORZEC[wiersze][kolumny][liczby];
	int WZOR[1][35][10]; // p³askie, najpierw kolumny, potem wiersze
	int TEST[2][35][10]; // j.w., ka¿d¹ liczbê mo¿emy zapisaæ na dwa sposoby
	double tmp; // wartoœæ dla tablicy tymczasowej
	double RMS;
	double ERMS; // b³¹d przeliczany dla ca³ej sieci. d¹¿ymy, ¿eby wynosi³ < 0.01

	int numberOfNeurons;
	int numberOfSignals;
	int numberOfLayers;
	int uczaceIteracje;
	int testoweIteracje;
	double eta; // wspó³czynnik szybkoœci
	double alfa; // wspó³czynnik momentum

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

