#ifndef HebbOj_h
#define HebbOj_h
#include <iostream>
#include <vector>
using namespace std;

class Neuron {
public:
	vector <int> tabX; // kolumny z sygna�ami wej�ciowymi
	vector <float>  wX; // wagi dla ka�dego z sygna�u neuronu
	vector <float>  dW;
	float output; // wyj�cie b�d�ce sum� iloczy�w sygna��w i wag
	float z; // oczekiwane wyj�cie
	int y; // warto�c wyj�ciowa, zero lub jeden
};

class HebbOj {
public:
	int numberOfNeurons;
	int numberOfSignals;
	int iterations;
	float eta; // wsp�czynnik szybko�ci.
	float forget; // wsp�czynnik zapominania
	vector <Neuron> neurony; // tablica sieci

	// funkcje
	void fillVector(vector <Neuron>&);
	void Hebb(vector <Neuron>&);
	void showResult(vector <Neuron>& neuron);
	HebbOj();
};
#endif

