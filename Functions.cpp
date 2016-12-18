#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <chrono> // pomiar czasu
#include "Functions.h"
using namespace std::chrono;
using namespace std;

void Kohonen::wypelnijWagi()
{
	srand(time(NULL));
	for (int i = 1; i < numberOfLayers; i++) // warstwa
	{
		for (int j = 0; j < n[i]; j++) // liczba neuronów w warstwie
		{
			for (int k = 0; k < n[i - 1]; k++) // ka¿dy neuron ma tyle wag, ile neuronów mia³a poprzednia warstwa
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

void Kohonen::wprowadzWejsciaUczace()
{
	int liczba = rand() % 3;

	for (int i = 0; i < numberOfNeurons; i++)
		O[0][i] = WZOR[0][i][liczba]; // pomnó¿my przez wagê od razu
}

void Kohonen::wprowadzWejsciaTestowe()
{
	int liczba = rand() % 3;
	int kategoria = rand() % 2;

	for (int i = 0; i < numberOfNeurons; i++)
		O[0][i] = TEST[kategoria][i][liczba]; // pomnó¿my przez wagê od razu
}

void Kohonen::Epoki()
{
	ofstream WYJSCIAtxt;
	WYJSCIAtxt.open("WYJSCIA.txt", std::ios::app);
	WYJSCIAtxt.precision(4); // wyniki ERMS

	milliseconds start = duration_cast< milliseconds >( // pocz¹tek pomiaru czasu
		system_clock::now().time_since_epoch());

	cout << "Liczba epok to " << uczaceIteracje << ". Ponizej sa wyswietlone ostatnie wyjscia dla wprowadzonych sygnalow." << endl;

	for (int it = 0; it < uczaceIteracje; it++)
	{
		WYJSCIAtxt << it << "                ";
		eta = 0.1 - it*0.00002; // wspó³czynnik eta dla Kohonena
		//eta = 0.5;

		if (!it % 4 == 0)
			wprowadzWejsciaUczace();
		else
			wprowadzWejsciaTestowe();
		
		for (int i = 1; i < numberOfLayers; i++) // zak³ada, ¿e outputy z pierwszej warstwy s¹ zawsze wprowadzane
			for (int j = 0; j < n[i]; j++)
			{
				I[i][j] = 0.0;
				for (int k = 0; k < n[i - 1]; k++) // il. synaps w neuronie równa liczbie neuronów poprzedniej warstwy
					I[i][j] += O[i - 1][k] * W[i][j][k]; // iloczyn sygna³ów wejœciowych przez wagi dla danych neuronów
				// O[i][j] = 1.0 / (1.0 + exp(alfa*(-I[i][j]))); // funkcja aktywacji
				O[i][j] = I[i][j];
				
				if (i == 2)
					WYJSCIAtxt << O[i][j] << "               ";
			}
		WYJSCIAtxt << endl;

		// wybierzmy neurony z najwiêkszymi wyjœciami (warstwa druga i trzecia)

		int jNaj2 = 0;
		int jNaj3 = 0; // zapamiêtajmy numery najwiêkszych wyjœæ z warstwy 2 i 3

		for (int i = 1; i < numberOfLayers; i++) // warstwa 2 i 3
		{
			for (int j = 0; j < n[i]-1; j++) // neurony 2 i 3 warstwy
			{
				if (i == 1)
					if (!(O[i][jNaj2] > O[i][j + 1]))
						jNaj2 = j + 1;

				if (i == 2)
					if (!(O[i][jNaj3] > O[i][j + 1]))
						jNaj3 = j+1;
			}
		}

		// znormalizujmy wektory wejœciowe

		double O2 = 0;
		double O3 = 0;

		for (int i = 1; i < numberOfLayers; i++) // warstwa 2 i 3
		{
			for (int j = 0; j < n[i]; j++) // wejœcia neuronów 2 i 3 warstwy
			{
				if (i == 1)
				{
					O2 += O[i-1][j]* O[i - 1][j];
					O2 = sqrt(O2);
				}

				if (i == 2)
				{
					O3 += O[i-1][j] * O[i - 1][j];
					O3 = sqrt(O3);
				}
			}
		}

		for (int i = 1; i < numberOfLayers; i++) // warstwa 2 i 3
		{
			for (int j = 0; j < n[i]; j++) // neurony 2 i 3 warstwy
			{
				if (i == 1)
					Iprim[0][j] = O[i - 1][j] / O2;
				if (i == 2)
					Iprim[1][j] = O[i - 1][j] / O3;
			}
		}

		// dostosowywanie wag
		for (int i = 1; i < numberOfLayers; i++)
			//for (int j = 0; j < n[i]; j++)
				for (int k = 0; k < n[i - 1]; k++)
				{
					if (i == 1)
					{
						tmp = W[i][jNaj2][k]; // zmieniamy tylko wagi dla najlepszego neuronu, warstwa ukryta
						W[i][jNaj2][k] += eta*(Iprim[0][k] - W1[i][jNaj2][k]);
						W1[i][jNaj2][k] = tmp;
					}

					if (i == 2)
					{
						tmp = W[i][jNaj3][k]; // zmieniamy tylko wagi dla najlepszego neuronu, warstwa wyjœciowa
						W[i][jNaj3][k] += eta*(Iprim[1][k] - W1[i][jNaj3][k]);
						W1[i][jNaj3][k] = tmp;
					}
				}

		if (it > uczaceIteracje - 11) // nasze ostatnie kilka epok, jest to zestaw testowy
		{
			cout << endl << endl; // narysuje nam liczbê
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0 + (i * 5); j < 5 + (i * 5); j++)
				{
					if (O[0][j] == 1)
						cout << "O";
					else
						cout << " ";
				}
				cout << endl;
			}
			cout << "Wyjscie 0: " << O[numberOfLayers - 1][0] << endl;
			cout << "Wyjscie 1: " << O[numberOfLayers - 1][1] << endl;
			cout << "Wyjscie 2: " << O[numberOfLayers - 1][2] << endl;
			/*cout << "Wyjscie 3: " << O[numberOfLayers - 1][3] << endl;
			cout << "Wyjscie 4: " << O[numberOfLayers - 1][4] << endl;
			cout << "Wyjscie 5: " << O[numberOfLayers - 1][5] << endl;
			cout << "Wyjscie 6: " << O[numberOfLayers - 1][6] << endl;
			cout << "Wyjscie 7: " << O[numberOfLayers - 1][7] << endl;
			cout << "Wyjscie 8: " << O[numberOfLayers - 1][8] << endl;
			cout << "Wyjscie 9: " << O[numberOfLayers - 1][9] << endl;*/
		}
	}
	milliseconds stop = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch());

	cout << endl << "Czas nauczania dla naszych epok: " << stop.count() - start.count() << " ms" << endl;

	//....................................... TESTY

	for (int it = 0; it < testoweIteracje; it++)
	{
		eta = 0.1 - it*0.000026; // wspó³czynnik eta dla Kohonena
		wprowadzWejsciaTestowe();

		for (int i = 1; i < numberOfLayers; i++) // zak³ada, ¿e outputy z pierwszej warstwy s¹ zawsze wprowadzane
			for (int j = 0; j < n[i]; j++)
			{
				I[i][j] = 0.0;
				for (int k = 0; k < n[i - 1]; k++) // il. synaps w neuronie równa liczbie neuronów poprzedniej warstwy
					I[i][j] += O[i - 1][k] * W[i][j][k]; // iloczyn sygna³ów wejœciowych przez wagi dla danych neuronów
				O[i][j] = 1.0 / (1.0 + exp(alfa*(-I[i][j]))); // funkcja aktywacji
			}

		// wybierzmy neurony z najwiêkszymi wyjœciami (warstwa druga i trzecia)

		int jNaj2 = 0;
		int jNaj3 = 0; // zapamiêtajmy numery najwiêkszych wyjœæ z warstwy 2 i 3

		for (int i = 1; i < numberOfLayers; i++) // warstwa 2 i 3
		{
			for (int j = 0; j < n[i] - 1; j++) // neurony 2 i 3 warstwy
			{
				if (i == 1)
					if (O[i][j] > O[i][j + 1])
						jNaj2 = j;

				if (i == 2)
					if (O[i][j] > O[i][j + 1])
						jNaj3 = j;
			}
		}

		// znormalizujmy wektory wejœciowe

		double O2 = 0;
		double O3 = 0;

		for (int i = 1; i < numberOfLayers; i++) // warstwa 2 i 3
		{
			for (int j = 0; j < n[i]; j++) // wejœcia neuronów 2 i 3 warstwy
			{
				if (i == 1)
					O2 += O[i - 1][j];

				if (i == 2)
					O3 += O[i - 1][j];
			}
		}

		for (int i = 1; i < numberOfLayers; i++) // warstwa 2 i 3
		{
			for (int j = 0; j < n[i]; j++) // neurony 2 i 3 warstwy
			{
				if (i == 1)
					Iprim[0][j] = O[i - 1][j] / O2;
				if (i == 2)
					Iprim[1][j] = O[i - 1][j] / O3;
			}
		}

		// dostosowywanie wag
		for (int i = 1; i < numberOfLayers; i++)
			//for (int j = 0; j < n[i]; j++)
			for (int k = 0; k < n[i - 1]; k++)
			{
				if (i == 1)
				{
					tmp = W[i][jNaj2][k]; // zmieniamy tylko wagi dla najlepszego neuronu, warstwa ukryta
					W[i][jNaj2][k] += eta*(Iprim[0][k] - W1[i][jNaj2][k]);
					W1[i][jNaj2][k] = tmp;
				}

				if (i == 2)
				{
					tmp = W[i][jNaj3][k]; // zmieniamy tylko wagi dla najlepszego neuronu, warstwa wyjœciowa
					W[i][jNaj3][k] += eta*(Iprim[1][k] - W1[i][jNaj3][k]);
					W1[i][jNaj3][k] = tmp;
				}
			}

			cout << endl << endl; // narysuje nam liczbê
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0 + (i * 5); j < 5 + (i * 5); j++)
				{
					if (O[0][j] == 1)
						cout << "O";
					else
						cout << " ";
				}
				cout << endl;
			}
			cout << "Wyjscie testowe 0: " << O[numberOfLayers - 1][0] << endl;
			cout << "Wyjscie testowe 1: " << O[numberOfLayers - 1][1] << endl;
			cout << "Wyjscie testowe 2: " << O[numberOfLayers - 1][2] << endl;
	/*		cout << "Wyjscie testowe 3: " << O[numberOfLayers - 1][3] << endl;
			cout << "Wyjscie testowe 4: " << O[numberOfLayers - 1][4] << endl;
			cout << "Wyjscie testowe 5: " << O[numberOfLayers - 1][5] << endl;
			cout << "Wyjscie testowe 6: " << O[numberOfLayers - 1][6] << endl;
			cout << "Wyjscie testowe 7: " << O[numberOfLayers - 1][7] << endl;
			cout << "Wyjscie testowe 8: " << O[numberOfLayers - 1][8] << endl;
			cout << "Wyjscie testowe 9: " << O[numberOfLayers - 1][9] << endl;*/
	}
}

Kohonen::Kohonen()
{
	// wstêpna charakterystyka sieci

	numberOfLayers = 3;
	n = new int[numberOfLayers]; // iloœæ neuronów w danej warstwie sieci
	n[0] = 35;
	n[1] = 10;
	n[2] = 3;

	numberOfNeurons = 35;
	numberOfSignals = 35;
	alfa = 0.6;

	// wpisywanie podstawowych wartoœci
	uczaceIteracje = 5600;
	testoweIteracje = 5;

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

	// wejœcia
	I = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		I[i] = new double[numberOfNeurons];  // !
		for (int j = 0; j < numberOfNeurons; ++j)
			I[i][j] = 0;
	}

	// wejœcia
	Iprim = new double *[2];
	for (int i = 0; i < 2; ++i)
	{
		Iprim[i] = new double[numberOfNeurons];  // !
		for (int j = 0; j < numberOfNeurons; ++j)
			Iprim[i][j] = 0;
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

	// b³¹d delta
	E = new double *[numberOfLayers];
	for (int i = 0; i < numberOfLayers; ++i)
	{
		E[i] = new double[numberOfNeurons];
		for (int j = 0; j < numberOfNeurons; ++j)
			E[i][j] = 0;
	}

	stworzWzorce();
	stworzTesty();
	wypelnijWagi();
	Epoki();
}

Kohonen::~Kohonen()
{
	delete[] n;
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

	for (int i(0); i < 2; ++i)
		delete[] Iprim[i];
	delete[] Iprim;
	Iprim = nullptr;

	for (int i = 0; i< numberOfLayers; i++)
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