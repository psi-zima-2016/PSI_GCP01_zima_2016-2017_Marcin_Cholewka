#ifndef Adaline_h
#define Adaline_h
#include <iostream>
using namespace std;

class Neuron {
public:
	int* tabX; // kolumny z sygna³ami wejœciowymi
	float* wX; // wagi dla ka¿dego z sygna³u neuronu
	float* dW;
	float output; // wyjœcie bêd¹ce sum¹ iloczyów sygna³ów i wag
	float z; // oczekiwane wyjœcie
	int y; // wartoœc wyjœciowa, zero lub jeden
};

class Adaline {
public:
	int numberOfNeurons;
	int numberOfSignals;
	int iterations;
	float eta; // wspó³czynnik szybkoœci.
	Neuron * neuron; // tablica sieci

	// funkcje
	void Allocate();
	void Delta();
	void fillArrays();
	void showResult();
	Adaline();
};
#endif

