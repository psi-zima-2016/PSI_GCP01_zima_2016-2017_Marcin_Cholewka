#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "Adaline.h"
using namespace std;

void Adaline::Allocate()
{
	neuron = new Neuron[numberOfNeurons];

	// deklaracja pami�ci dla tablic neuron�w
	for (int i = 0; i < numberOfSignals; i++)
	{
		neuron[i].tabX = new int[numberOfSignals]; // kolumna sygna��w
		neuron[i].wX = new float[numberOfSignals]; // kolumna wag
		neuron[i].dW = new float[numberOfSignals]; // r�nice wag
		neuron[i].output = 0;
		neuron[i].z = 0;
		neuron[i].y = -1;

		for (int j = 0; j < numberOfSignals; j++)
		{
			neuron[i].tabX[j] = 0;
			neuron[i].dW[j] = 0;
			neuron[i].wX[j] = 0;
		}
	}
}

void Adaline::fillArrays()
{
	// przypisanie warto�ci do sieci
	for (int i = 0; i < numberOfNeurons; i++)
	{
		for (int j = 0; j < numberOfSignals; j++)
		{
			cout << "Wprowadz sygnal [" << i << "," << j << "]: "; cin >> neuron[i].tabX[j];
			neuron[i].wX[j] = 0.2+ 0.1*(j+1) - 0.08*(i+1);
			neuron[i].dW[j] = 0;
		}
		cout << "Wprowadz oczekiwane wyjscie: "; cin >> neuron[i].z;
	}
}

// funkcja licz�ca regu�� delta, ustalanie y

void Adaline::Delta()
{
	clock_t start, end;

	for (int it = 0; it < iterations; it++)
	{
		start = clock();
		// liczenie wyj��
		for (int i = 0; i < numberOfNeurons; i++)
			for (int j = 0; j < numberOfSignals; j++)
				neuron[i].output += neuron[i].tabX[j] * neuron[i].wX[j]; // sumator

		for (int i = 0; i < numberOfNeurons; i++)
		{
			if (neuron[i].output >= 0)
				neuron[i].y = 1;
			else
				neuron[i].y = -1;
		}

		// realizacja regu�y delta
		for (int i = 0; i < numberOfNeurons; i++)
		{
			for (int j = 0; j < numberOfSignals; j++)
			{
				neuron[i].dW[j] = eta*(neuron[i].z - neuron[i].output)*neuron[i].tabX[j]; // delta
				neuron[i].wX[j] += neuron[i].dW[j]; // aktualizacja wagi
			}
		}

		if (it == 0)
		{
			//wy�wietlanie informacji o danych, wy�wietlamy raz na samej g�rze
			for (int i = 0; i < numberOfSignals; i++)
				cout << "x" << i << "\t";
			for (int i = 0; i < numberOfSignals; i++)
				cout << "w" << i << "\t";
			for (int i = 0; i < numberOfSignals; i++)
				cout << "dW" << i << "\t";
			cout << "z" << "\t";
			cout << "output" << "\t";
			cout << "y" << "\t" << endl;
		}

		showResult(); // wypiszmy rezultat zmian
	}

	end = clock(); // bie��cy czas systemowy w ms
	long delta = (long)(end - start);//czas dzia�a� w ms
	cout.precision(8);
	cout << endl << "Czas wykonywania " << iterations << " iteracji to w ms: " << delta << endl;
}

void Adaline::showResult()
{
			for (int i = 0; i < numberOfNeurons; i++)
			{
				for (int j = 0; j < numberOfSignals; j++) // sygna�y wej�ciowe
					cout << setprecision(3) << neuron[i].tabX[j] << "\t";

				for (int k = 0; k < numberOfSignals; k++) // wagi
				{
					cout.precision(3);
					cout << setprecision(3) << neuron[i].wX[k] << "\t";
				}

				for (int l = 0; l < numberOfSignals; l++) // wagi
				{
					cout.precision(3);
					cout << setprecision(3) << neuron[i].dW[l] << "\t";
				}

				cout.precision(3);
				cout << setprecision(3) << neuron[i].z << "\t" << neuron[i].output << "\t" << neuron[i].y;

				cout << endl;
			}
			cout << "_____________" << endl;
}

Adaline::Adaline()
{
	iterations = 100;
	numberOfNeurons = 2;
	numberOfSignals = 3;
	eta = 0.6;

	Allocate();
	fillArrays();
	Delta();
}