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

	// deklaracja pamiêci dla tablic neuronów
	for (int i = 0; i < numberOfSignals; i++)
	{
		neuron[i].tabX = new int[numberOfSignals]; // kolumna sygna³ów
		neuron[i].wX = new float[numberOfSignals]; // kolumna wag
		neuron[i].dW = new float[numberOfSignals]; // ró¿nice wag
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
	// przypisanie wartoœci do sieci
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

// funkcja licz¹ca regu³ê delta, ustalanie y

void Adaline::Delta()
{
	clock_t start, end;

	for (int it = 0; it < iterations; it++)
	{
		start = clock();
		// liczenie wyjœæ
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

		// realizacja regu³y delta
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
			//wyœwietlanie informacji o danych, wyœwietlamy raz na samej górze
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

	end = clock(); // bie¿¹cy czas systemowy w ms
	long delta = (long)(end - start);//czas dzia³añ w ms
	cout.precision(8);
	cout << endl << "Czas wykonywania " << iterations << " iteracji to w ms: " << delta << endl;
}

void Adaline::showResult()
{
			for (int i = 0; i < numberOfNeurons; i++)
			{
				for (int j = 0; j < numberOfSignals; j++) // sygna³y wejœciowe
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