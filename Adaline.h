#ifndef Adaline_h
#define Adaline_h
#include <iostream>
using namespace std;

class Neuron {
public:
	int* tabX; // kolumny z sygna�ami wej�ciowymi
	float* wX; // wagi dla ka�dego z sygna�u neuronu
	float* dW;
	float output; // wyj�cie b�d�ce sum� iloczy�w sygna��w i wag
	float z; // oczekiwane wyj�cie
	int y; // warto�c wyj�ciowa, zero lub jeden
};

class Adaline {
public:
	int numberOfNeurons;
	int numberOfSignals;
	int iterations;
	float eta; // wsp�czynnik szybko�ci.
	Neuron * neuron; // tablica sieci

	// funkcje
	void Allocate();
	void Delta();
	void fillArrays();
	void showResult();
	Adaline();
};
#endif

