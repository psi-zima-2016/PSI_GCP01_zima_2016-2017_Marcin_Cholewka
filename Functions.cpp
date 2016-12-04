#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <vector>
#include "Header.h"
using namespace std;

void MLP::wypelnijWagi()
{
	srand(time(NULL));
	for (int i = 1; i < numberOfLayers; i++)
		for (int j = 0; j < n[i]; j++)
			for (int k = 0; k <= n[i-1]; k++)
			{
				W[i][j][k] = (((rand() % 1000000L) / 1700.0) - 9.8)*0.0015;
				if (W[i][j][k] == 0.0) W[i][j][k] = 0.01492;

				if (i = 2)
					break;
			}
}

void MLP::Epoka()
{
	for (int i = 1; i<numberOfLayers; i++)
		for (int j = 0; j<n[i]; j++)
		{
			I[i][j] = 0.0;
			for (int k = 0; k <= n[i-1]; k++)
				I[i][j] += O[i - 1][k] * W[i][j][k];
			O[i][j] = 1.0 / (1.0 + exp(alfa*(-I[i][j]))); // funkcja aktywacji
		}

	// przetwarzanie sygna³u wejœciowego w sieci
	for (int j = 0; j < n[numberOfLayers - 1]; j++) // n[numberOfLayers-1]
		B[numberOfLayers-1][j] = Z[numberOfLayers-1][j] - O[numberOfLayers-1][j]; // co ma mieæ Z w wierszu?

	
	// Obliczanie b³êdów na neuronach 

	// warstwa wyjœciowa
	int i = numberOfLayers-1;
	for(int j=0; j<n[i]; j++)
		E[i][j] = (Z[numberOfLayers-1][j]-O[i][j]) * O[i][j]*(1.0-O[i][j]); // z, wiersz

	// warstwy ukryte
	for (i = numberOfLayers - 2; i >= 1; i--)
	{
		for (int j = 0; j < n[i]; j++)
		{
			E[i][j] = 0.0;
			for (int k = 0; k <= n[i + 1]; k++)
				E[i][j] += O[i][j] * (1.0 - O[i][j]) * E[i + 1][k] * W[i + 1][k][j];
		}
	}

	// dostosowywanie wag
	for (int i = 1; i < numberOfLayers; i++)
		for (int j = 0; j < n[i]; j++)
			for (int k = 0; k < n[i-1]; k++) // k <= n[i-1] – za³o¿enie, ¿e k, czyli iloœæ synaps, bêdzie w ca³ej sieci równa iloœci neuronów na
			{                                // przedostatniej warstwie. dlaczego?
				tmp = W[i][j][k];
				W[i][j][k] += eta * E[i][j] * O[i - 1][k] + alfa*(W[i][j][k] - W1[i][j][k]);
				W1[i][j][k] = tmp;
			}

	// obliczanie ERMS

	for (int j = 0; j<n[numberOfLayers - 1]; j++)
		RMS += (Z[numberOfLayers - 1][j] - O[numberOfLayers - 1][j])*(Z[numberOfLayers - 1][j] - O[numberOfLayers - 1][j]);
	ERMS = sqrt(RMS / (double)(Lvec*n[numberOfLayers - 1]));
}

MLP::MLP()
{	
	// wstêpna charakterystyka sieci
	numberOfNeurons = 3;
	numberOfLayers = 3;
	numberOfSignals = 3;
	Lvec = 3; // liczba wszystkich wektorów ucz¹cych

// alokacja danych
	n = new int[numberOfLayers]; // iloœæ neuronów w danej warstwie sieci
	for (int i = 0; i < numberOfLayers; i++)
	{
		if (i == 0)
			n[i] = numberOfNeurons;

		else if (i == 1)
			n[i] = numberOfNeurons;

		else
			n[i] = numberOfNeurons-1;
	}

	// wagi
	W = new double **[numberOfLayers];
	for (int i = 0; i< numberOfLayers; i++)
	{
		W[i] = new double *[numberOfNeurons];
		for (int j = 0; j<numberOfSignals; j++)
		{
			W[i][j] = new double[numberOfSignals];
		}
	}

	// wagiPoprzednie
	W1 = new double **[numberOfLayers];
	for (int i = 0; i< numberOfLayers; i++)
	{
		W1[i] = new double *[numberOfNeurons];
		for (int j = 0; j<numberOfSignals; j++)
		{
			W1[i][j] = new double[numberOfSignals];
		}
	}

	// wejœcia
	I = new double *[numberOfLayers]; 
	for (int i = 0; i < numberOfLayers; ++i)
	{
		I[i] = new double[numberOfNeurons];  // !
		for (int j = 0; j < numberOfNeurons; ++j)
			I[i][j] = 0;
	}


	// wyjœcia
	O = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		O[i] = new double[numberOfNeurons]; // !
		for (int j = 0; j < numberOfNeurons; ++j)
			O[i][j] = 0;
	}

	// b³¹d
	B = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		B[i] = new double[numberOfNeurons];  
		for (int j = 0; j < numberOfNeurons; ++j)
			B[i][j] = 0;
	}

	// oczekiwana wartoœæ
	Z = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		Z[i] = new double[numberOfNeurons];
		for (int j = 0; j < numberOfNeurons; ++j)
			Z[i][j] = 0;
	}

	// oczekiwana wartoœæ
	E = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		E[i] = new double[numberOfNeurons];
		for (int j = 0; j < numberOfNeurons; ++j)
			E[i][j] = 0;
	}


	// wpisywanie podstawowych wartoœci
	iterations = 100;
	eta = 0.6;
	alfa = 0.9;

	wypelnijWagi();
	Epoka();
}

MLP::~MLP()
{
	delete [] n;
	n = nullptr;

	for (int i(0); i < numberOfLayers; ++i)
	{
		delete[] I[i];
		delete[] O[i];
		delete[] B[i];
		delete[] Z[i];
		delete[] E[i];
	}
	delete[] I, O, B, Z;
	I = nullptr;
	O = nullptr;
	B = nullptr;
	Z = nullptr;
	E = nullptr;

	for (int i = 0; i< numberOfLayers ; i++)
	{
		for (int j = 0; j<numberOfNeurons; j++)
		{
			delete[] W[i][j];
		}
		delete[] W[i];
	}
	delete[]W;
	W = nullptr;

	for (int i = 0; i< numberOfLayers; i++)
	{
		for (int j = 0; j<numberOfNeurons; j++)
		{
			delete[] W1[i][j];
		}
		delete[] W1[i];
	}
	delete[]W1;
	W1 = nullptr;
}