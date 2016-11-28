#ifndef HebbOj_h
#define HebbOj_h
#include <iostream>
#include <vector>
using namespace std;

class Neuron {
public:
	vector <int> tabX; // kolumny z sygna³ami wejœciowymi
	vector <float>  wX; // wagi dla ka¿dego z sygna³u neuronu
	vector <float>  dW;
	float output; // wyjœcie bêd¹ce sum¹ iloczyów sygna³ów i wag
	float z; // oczekiwane wyjœcie
	int y; // wartoœc wyjœciowa, zero lub jeden
};

class HebbOj {
public:
	int numberOfNeurons;
	int numberOfSignals;
	int iterations;
	float eta; // wspó³czynnik szybkoœci.
	float forget; // wspó³czynnik zapominania
	vector <Neuron> neurony; // tablica sieci

	// funkcje
	void fillVector(vector <Neuron>&);
	void Hebb(vector <Neuron>&);
	void showResult(vector <Neuron>& neuron);
	HebbOj();
};
#endif

