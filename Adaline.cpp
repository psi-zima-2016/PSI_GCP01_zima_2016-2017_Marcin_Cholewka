#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <vector>
#include "Adaline.h"
using namespace std;

void HebbOj::fillVector(vector <Neuron>& neurons)
{
	for (int i = 0; i < numberOfNeurons; i++)
	{
		Neuron neurony;
		neurony.output = 0;
		neurony.z = 0;
		neurony.y = -1;
		
		for (int j = 0; j < numberOfSignals; j++)
		{
			neurony.tabX.push_back(0);
			cout << "Enter signal [" << i << "," << j << "]: "; cin >> neurony.tabX[j];
			neurony.wX.push_back(0.2 + 0.1*(j + 1) - 0.08*(i + 1));
			neurony.dW.push_back(0);
		}
		cout << "Enter expected output: "; cin >> neurony.z;
		neurons.push_back(neurony); // wpisujemy pierwszy (kolejny) wektor do naszej g³ównej tablicy neuronów
	}

	system("pause");
	Hebb(neurons);
}

// funkcja licz¹ca regu³ê delta, ustalanie y

void HebbOj::Hebb(vector <Neuron>& neuron)
{
	cout << "Iloœæ epok: " << iterations << endl;
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

		// regu³y
		for (int i = 0; i < numberOfNeurons; i++)
		{
			for (int j = 0; j < numberOfSignals; j++)
			{
				neuron[i].dW[j] = eta*(neuron[i].z - neuron[i].output)*neuron[i].tabX[j]; // delta
				//neuron[i].dW[j] = eta*neuron[i].z*neuron[i].tabX[j]; // Hebb with teacher
				//neuron[i].dW[j] = eta*neuron[i].output*neuron[i].tabX[j]; //nHebb without teacher
				//neuron[i].dW[j] = eta*neuron[i].output*(neuron[i].tabX[j] - neuron[i].output*neuron[i].wX[j]); // Oj, wst. pr. wyjœcie
				//neuron[i].dW[j] = eta*neuron[i].output*(neuron[i].tabX[j] - j*neuron[i].wX[j]); // Hebb z zapominaniem
				neuron[i].wX[j] += neuron[i].dW[j]; // aktualizacja wagi zwyk³a
				//neuron[i].wX[j] = (neuron[i].wX[j] * (1 - forget)) + neuron[i].dW[j]; // aktualizacja wagi dla Hebba z zapominaniem
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

		showResult(neuron); // wypiszmy rezultat zmian
	}

	end = clock(); // bie¿¹cy czas systemowy w ms
	long delta = (long)(end - start);//czas dzia³añ w ms
	cout.precision(8);
	cout << endl << "Czas wykonywania " << iterations << " iteracji to w ms: " << delta << endl;
}

void HebbOj::showResult(vector <Neuron>& neuron)
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

HebbOj::HebbOj()
{
	iterations = 100;
	numberOfNeurons = 2; // important
	numberOfSignals = 3; // important
	eta = 0.1;
	forget = 0.5;

	fillVector(neurony);
	//fillArrays();
	//Delta();
}