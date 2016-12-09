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
	for (int i = 1; i < numberOfLayers; i++) // warstwa
	{
		/*if (i - 1 == 0) // powpisujmy warto�ci dla neuron�w z warstwy pierwszej
		{
			for (int j = 0; j < n[i-1]; j++) {
				for (int k = 0; k < n[i - 1]; k++) // ka�dy neuron warstwy pierwszej ma tyle synaps ile neuron�w
				{
					W[i - 1][j][k] = (((rand() % 1000000L) / 1700.0) - 9.8)*0.0015;
					if (W[i - 1][j][k] == 0.0)
						W[i - 1][j][k] = 0.01492;
				}
			}
		}*/

		for (int j = 0; j < n[i]; j++) // liczba neuron�w w warstwie
		{
			for (int k = 0; k < n[i-1]; k++) // ka�dy neuron ma tyle wag, ile neuron�w mia�a poprzednia warstwa
			{
				W[i][j][k] = (((rand() % 1000000L) / 1700.0) - 9.8)*0.0015;
				W1[i][j][k] = W[i][j][k];
				if (W[i][j][k] == 0.0)
				{
					W[i][j][k] = 0.01492;
					W1[i][j][k] = 0.01492;
				}
			}
		}
	}
}

void MLP::utworzWzorce()
{
	for (int i = 0; i < liczby; i++)
	{
		for (int j = 0; j < wiersze; j++) // wype�niamy wiersz i jedziemy w d�
		{
			if (i == 0) // stw�rzmy zero
			{
				if (j == 0 || j == 6)
				{
					WZORZEC[j][0][i] = 0;
					WZORZEC[j][1][i] = 1;
					WZORZEC[j][2][i] = 1;
					WZORZEC[j][3][i] = 1;
					WZORZEC[j][4][i] = 0;
				}

				else
				{
					WZORZEC[j][0][i] = 1;
					WZORZEC[j][1][i] = 0;
					WZORZEC[j][2][i] = 0;
					WZORZEC[j][3][i] = 0;
					WZORZEC[j][4][i] = 1;
				}
			}

			if (i == 1) // tworzymy jedynk�
			{
				if (j==0 || j == 3 || j == 4 || j == 5 || j == 6)
				{
					WZORZEC[j][0][i] = 0;
					WZORZEC[j][1][i] = 0;
					WZORZEC[j][2][i] = 1;
					WZORZEC[j][3][i] = 0;
					WZORZEC[j][4][i] = 0;
				}
				
				else if (j == 1)
				{
					WZORZEC[j][0][i] = 0;
					WZORZEC[j][1][i] = 1;
					WZORZEC[j][2][i] = 1;
					WZORZEC[j][3][i] = 0;
					WZORZEC[j][4][i] = 0;
				}

				else if (j == 2)
				{
					WZORZEC[j][0][i] = 1;
					WZORZEC[j][1][i] = 0;
					WZORZEC[j][2][i] = 1;
					WZORZEC[j][3][i] = 0;
					WZORZEC[j][4][i] = 0;
				}
			}

			//" OOO ",
			//"O   O",
			//"    O",
			//"   O ",
			//"  O  ",
			//" O   ",
			//"OOOOO" } }
			if (i == 2)
			{
				if (j == 0)
				{
					WZORZEC[j][0][i] = 0;
					WZORZEC[j][1][i] = 1;
					WZORZEC[j][2][i] = 1;
					WZORZEC[j][3][i] = 1;
					WZORZEC[j][4][i] = 0;
				}

				else if (j == 1)
				{
					WZORZEC[j][0][i] = 1;
					WZORZEC[j][1][i] = 0;
					WZORZEC[j][2][i] = 0;
					WZORZEC[j][3][i] = 0;
					WZORZEC[j][4][i] = 1;
				}

				else if (j == 2)
				{
					WZORZEC[j][0][i] = 0;
					WZORZEC[j][1][i] = 0;
					WZORZEC[j][2][i] = 0;
					WZORZEC[j][3][i] = 0;
					WZORZEC[j][4][i] = 1;
				}

				else if (j == 3)
				{
					WZORZEC[j][0][i] = 0;
					WZORZEC[j][1][i] = 0;
					WZORZEC[j][2][i] = 0;
					WZORZEC[j][3][i] = 1;
					WZORZEC[j][4][i] = 0;
				}

				else if (j == 4)
				{
					WZORZEC[j][0][i] = 0;
					WZORZEC[j][1][i] = 0;
					WZORZEC[j][2][i] = 1;
					WZORZEC[j][3][i] = 0;
					WZORZEC[j][4][i] = 0;
				}

				else if (j == 5)
				{
					WZORZEC[j][0][i] = 0;
					WZORZEC[j][1][i] = 1;
					WZORZEC[j][2][i] = 0;
					WZORZEC[j][3][i] = 0;
					WZORZEC[j][4][i] = 0;
				}

				else if (j == 6)
				{
					WZORZEC[j][0][i] = 1;
					WZORZEC[j][1][i] = 1;
					WZORZEC[j][2][i] = 1;
					WZORZEC[j][3][i] = 1;
					WZORZEC[j][4][i] = 1;
				}
			}
		}
	}
}

void MLP::wprowadzWejscia()  
{
	int liczba = rand() % 3;

	for (int i = 0; i < numberOfNeurons; i++)
	{
		O[0][i] = WZORZEC[0][i][liczba]; // pomn�my przez wag� od razu
	}

	if (liczba == 0)
	{
		Z[2][0] = 1;
		Z[2][1] = 0;
		Z[2][2] = 0;
	}

	if (liczba == 1)
	{
		Z[2][0] = 0;
		Z[2][1] = 1;
		Z[2][2] = 0;
	}

	if (liczba == 2)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 1;
	}
}

void MLP::Epoka()
{
	for (int it = 0; it < iterations; it++)
	{
	wprowadzWejscia();
	for (int i = 1; i < numberOfLayers; i++) // zak�ada, �e outputy z pierwszej warstwy s� wyliczone
		for (int j = 0; j < n[i]; j++)
		{
			I[i][j] = 0.0;
			for (int k = 0; k < n[i - 1]; k++) // il. neuron�w r�wna liczbie sygna��w? by�o k <= n[i-1]
				I[i][j] += O[i - 1][k] * W[i][j][k]; // to zak�ada, �e my wszystko na raz wjebiemy (50 neuron�w 1-synapsowych)
			O[i][j] = 1.0 / (1.0 + exp(alfa*(-I[i][j]))); // funkcja aktywacji

			//if (i==2)
			//cout << j+1 << ": " << O[i][j] << endl; // OK
		}

	// przetwarzanie sygna�u wej�ciowego w sieci, liczymy b��d
	for (int j = 0; j < n[numberOfLayers - 1]; j++) // n[numberOfLayers-1]
	{
		B[numberOfLayers-1][j] = Z[numberOfLayers-1][j] - O[numberOfLayers-1][j]; // co ma mie� Z w wierszu?
		// cout << "B " << j << ": " << B[numberOfLayers - 1][j] << endl; // OK
	}

	// Obliczanie b��d�w na neuronach 

	// warstwa wyj�ciowa
	int i = numberOfLayers-1;
	for(int j=0; j<n[i]; j++)
	{
		E[i][j] = (Z[numberOfLayers-1][j]-O[i][j]) * O[i][j]*(1.0-O[i][j]); // z, wiersz
		// cout << E[i][j] << endl; // OK
	}

	// warstwy ukryte
	for (i = numberOfLayers - 2; i >= 1; i--)
	{
		for (int j = 0; j < n[i]; j++)
		{
			E[i][j] = 0.0;
			for (int k = 0; k <= n[i + 1]; k++)
			{
				E[i][j] += O[i][j] * (1.0 - O[i][j]) * E[i + 1][k] * W[i + 1][k][j];
			}
			// cout << E[i][j] << endl; // OK, b. ma�e
		}
	}

	// dostosowywanie wag
	for (int i = 1; i < numberOfLayers; i++)
		for (int j = 0; j < n[i]; j++)
			for (int k = 0; k < n[i-1]; k++) // k <= n[i-1] � za�o�enie, �e k, czyli ilo�� synaps, b�dzie w ca�ej sieci r�wna ilo�ci neuron�w na
			{                                // przedostatniej warstwie. dlaczego?
				tmp = W[i][j][k];
				W[i][j][k] += eta * E[i][j] * O[i - 1][k] + alfa*(W[i][j][k] - W1[i][j][k]);
				W1[i][j][k] = tmp;
				//cout << W[i][j][k] << endl;
				//cout << "poprzednie: " << W1[i][j][k] << endl; // OK
				//system("pause");
			}

	// obliczanie ERMS

	RMS = 0;
	for (int j = 0; j<n[numberOfLayers - 1]; j++)
	{
		RMS += (Z[numberOfLayers - 1][j] - O[numberOfLayers - 1][j])*(Z[numberOfLayers - 1][j] - O[numberOfLayers - 1][j]);
	}
	//cout << RMS*0.5 << endl;
	ERMS = 0;
	ERMS = sqrt(RMS / (double)(Lvec*n[numberOfLayers - 1]));
	cout << ERMS << endl;

	// cout << ERMS << endl;
	}
}

MLP::MLP()
{	
// wst�pna charakterystyka sieci

	numberOfLayers = 3;
	n = new int[numberOfLayers]; // ilo�� neuron�w w danej warstwie sieci
	n[0] = 35;
	n[1] = 5;
	n[2] = 3;
	
	numberOfNeurons = 35;
	numberOfSignals = 35;
	Lvec = 5; // liczba wszystkich wektor�w ucz�cych

	// wagi
	W = new double **[numberOfLayers];
	for (int i = 0; i< numberOfLayers; i++)
	{
		W[i] = new double *[numberOfNeurons];
		for (int j = 0; j<numberOfSignals; j++) // numberOfSignals
		{
			W[i][j] = new double[numberOfSignals]; // numberOfSignals
		}
	}

	// wagiPoprzednie
	W1 = new double **[numberOfLayers];
	for (int i = 0; i< numberOfLayers; i++)
	{
		W1[i] = new double *[numberOfNeurons];
		for (int j = 0; j<numberOfNeurons; j++)
		{
			W1[i][j] = new double[numberOfSignals];
		}
	}

	// wej�cia
	I = new double *[numberOfLayers]; 
	for (int i = 0; i < numberOfLayers; ++i)
	{
		I[i] = new double[numberOfNeurons];  // !
		for (int j = 0; j < numberOfNeurons; ++j)
			I[i][j] = 0;
	}


	// wyj�cia
	O = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		O[i] = new double[numberOfNeurons]; // !
		for (int j = 0; j < numberOfNeurons; ++j)
			O[i][j] = 0;
	}

	// b��d
	B = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		B[i] = new double[numberOfNeurons];  
		for (int j = 0; j < numberOfNeurons; ++j)
			B[i][j] = 0;
	}

	// oczekiwana warto��
	Z = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		Z[i] = new double[numberOfNeurons];
		for (int j = 0; j < numberOfNeurons; ++j)
			Z[i][j] = 0;
	}

	// b��d delta
	E = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		E[i] = new double[numberOfNeurons];
		for (int j = 0; j < numberOfNeurons; ++j)
			E[i][j] = 0;
	}

	// wpisywanie podstawowych warto�ci
	iterations = 5000;
	
	eta = 0.6;
	alfa = 0.9;

	utworzWzorce();
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