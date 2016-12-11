#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <chrono> // pomiar czasu
#include "Header.h"
using namespace std::chrono;
using namespace std;

void MLP::wypelnijWagi()
{
	srand(time(NULL));
	for (int i = 1; i < numberOfLayers; i++) // warstwa
	{
		for (int j = 0; j < n[i]; j++) // liczba neuronów w warstwie
		{
			for (int k = 0; k < n[i-1]; k++) // ka¿dy neuron ma tyle wag, ile neuronów mia³a poprzednia warstwa
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

void MLP::wprowadzWejsciaUczace()  
{
	int liczba = rand() % 10;

	for (int i = 0; i < numberOfNeurons; i++)
		O[0][i] = WZOR[0][i][liczba]; // pomnó¿my przez wagê od razu

	if (liczba == 0) // ustawianie nauczyciela
	{
		Z[2][0] = 1;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 1)
	{
		Z[2][0] = 0;
		Z[2][1] = 1;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 2)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 1;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 3)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 1;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 4)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 1;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 5)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 1;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 6)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 1;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}


	if (liczba == 7)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 1;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 8)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 1;
		Z[2][9] = 0;
	}

	if (liczba == 9)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 1;
	}
}

void MLP::wprowadzWejsciaTestowe()
{
	int liczba = rand() % 10;
	int kategoria = rand() % 2;

	for (int i = 0; i < numberOfNeurons; i++)
	{
		O[0][i] = TEST[kategoria][i][liczba]; // pomnó¿my przez wagê od razu
	}

	if (liczba == 0) // ustawianie nauczyciela
	{
		Z[2][0] = 1;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 1)
	{
		Z[2][0] = 0;
		Z[2][1] = 1;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 2)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 1;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 3)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 1;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 4)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 1;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 5)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 1;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 6)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 1;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}


	if (liczba == 7)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 1;
		Z[2][8] = 0;
		Z[2][9] = 0;
	}

	if (liczba == 8)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 1;
		Z[2][9] = 0;
	}

	if (liczba == 9)
	{
		Z[2][0] = 0;
		Z[2][1] = 0;
		Z[2][2] = 0;
		Z[2][3] = 0;
		Z[2][4] = 0;
		Z[2][5] = 0;
		Z[2][6] = 0;
		Z[2][7] = 0;
		Z[2][8] = 0;
		Z[2][9] = 1;
	}
}

void MLP::Epoki()
{
	ofstream ERMStxt;
	ERMStxt.open("ERMS.txt", std::ios::app);
	ERMStxt.precision(10); // wyniki ERMS

	milliseconds start = duration_cast< milliseconds >( // pocz¹tek pomiaru czasu
		system_clock::now().time_since_epoch());

	cout << "ERMSy dla dla danej epoki. Liczba epok to " << uczaceIteracje << "." << endl;

	for (int it = 0; it < uczaceIteracje; it++)
	{
		if (!uczaceIteracje % 4 == 0)
			wprowadzWejsciaUczace();
		else
			wprowadzWejsciaTestowe();

	for (int i = 1; i < numberOfLayers; i++) // zak³ada, ¿e outputy z pierwszej warstwy s¹ zawsze wprowadzane
		for (int j = 0; j < n[i]; j++)
		{
			I[i][j] = 0.0;
			for (int k = 0; k < n[i - 1]; k++) // il. synaps w neuronie równa liczbie neuronów poprzedniej warstwy
				I[i][j] += O[i - 1][k] * W[i][j][k]; // iloczyn sygna³ów wejœciowych przez wagi dla danych neuronów
			O[i][j] = 1.0 / (1.0 + exp(alfa*(-I[i][j]))); // funkcja aktywacji
		}

	// przetwarzanie sygna³u wejœciowego w sieci, liczymy b³¹d
	for (int j = 0; j < n[numberOfLayers - 1]; j++) // n[numberOfLayers-1]
		B[numberOfLayers-1][j] = Z[numberOfLayers-1][j] - O[numberOfLayers-1][j]; // co ma mieæ Z w wierszu?

	// Obliczanie b³êdów na neuronach 

	// warstwa wyjœciowa
	int i = numberOfLayers-1;
	for(int j=0; j<n[i]; j++)
		E[i][j] = B[numberOfLayers - 1][j] * O[i][j] * (1.0 - O[i][j]); // Qw * dfi/de (pochodna funkcji aktywacji po e)
		//E[i][j] = (Z[numberOfLayers-1][j]-O[i][j]) * O[i][j]*(1.0-O[i][j]);

	// warstwy ukryte
	for (i = numberOfLayers - 2; i >= 1; i--) // mamy jedn¹, pêtla przejdzie raz
	{
		for (int j = 0; j < n[i]; j++)
		{
			E[i][j] = 0.0;
			for (int k = 0; k <= n[i + 1]; k++) // dfi/de * aktywacja warstwy poprzedniej
				E[i][j] += O[i][j] * (1.0 - O[i][j]) * E[i + 1][k] * W[i + 1][k][j]; // E dla trzech z wyliczonych w "poprzedniej" warstwie neuronów
		}																			 // bêd¹cych synapsami aktualnej
	}

	// dostosowywanie wag
	for (int i = 1; i < numberOfLayers; i++)
		for (int j = 0; j < n[i]; j++)
			for (int k = 0; k < n[i-1]; k++) 
			{                                
				tmp = W[i][j][k]; // poni¿ej wzór, na podstawie którego ostatecznie dokonuje siê procesu uczenia nieliniowej sieci
				W[i][j][k] += eta * E[i][j] * O[i - 1][k] + alfa*(W[i][j][k] - W1[i][j][k]);
				W1[i][j][k] = tmp;
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
	
	ERMStxt << ERMS << endl; // ERMS DO TXT!

		if (it > uczaceIteracje-10) // nasze ostatnie kilka epok, jest to zestaw testowy
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
			cout << "Wyjscie 3: " << O[numberOfLayers - 1][3] << endl;
			cout << "Wyjscie 4: " << O[numberOfLayers - 1][4] << endl;
			cout << "Wyjscie 5: " << O[numberOfLayers - 1][5] << endl;
			cout << "Wyjscie 6: " << O[numberOfLayers - 1][6] << endl;
			cout << "Wyjscie 7: " << O[numberOfLayers - 1][7] << endl;
			cout << "Wyjscie 8: " << O[numberOfLayers - 1][8] << endl;
			cout << "Wyjscie 9: " << O[numberOfLayers - 1][9] << endl;
		}
	}
	milliseconds stop = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch());

	cout << endl <<  "Czas nauczania dla naszych epok: " << stop.count() - start.count() << " ms" << endl;
	ERMStxt << stop.count() - start.count() << endl; // wrzuæmy czas do notatnika


	// *********************************************** testy


	for (int it = 0; it < testoweIteracje; it++)
	{
		wprowadzWejsciaTestowe();
		for (int i = 1; i < numberOfLayers; i++) // zak³ada, ¿e outputy z pierwszej warstwy s¹ wyliczone
			for (int j = 0; j < n[i]; j++)
			{
				I[i][j] = 0.0;
				for (int k = 0; k < n[i - 1]; k++) // il. neuronów równa liczbie sygna³ów? by³o k <= n[i-1]
					I[i][j] += O[i - 1][k] * W[i][j][k]; // to zak³ada, ¿e my wszystko na raz wjebiemy (50 neuronów 1-synapsowych)
				O[i][j] = 1.0 / (1.0 + exp(alfa*(-I[i][j]))); // funkcja aktywacji
			}

		// przetwarzanie sygna³u wejœciowego w sieci, liczymy b³¹d
		for (int j = 0; j < n[numberOfLayers - 1]; j++) // n[numberOfLayers-1]
			B[numberOfLayers - 1][j] = Z[numberOfLayers - 1][j] - O[numberOfLayers - 1][j]; 

		// Obliczanie b³êdów na neuronach 

		// warstwa wyjœciowa
		int i = numberOfLayers - 1;
		for (int j = 0; j<n[i]; j++)
			E[i][j] = (Z[numberOfLayers - 1][j] - O[i][j]) * O[i][j] * (1.0 - O[i][j]); // z, wiersz																				

		// warstwy ukryte
		for (i = numberOfLayers - 2; i >= 1; i--) // indeks 2, bo mamy tylko jedn¹
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
				for (int k = 0; k < n[i - 1]; k++) // k <= n[i-1] – za³o¿enie, ¿e k, czyli iloœæ synaps, bêdzie w ca³ej sieci równa iloœci neuronów na
				{                                // przedostatniej warstwie. dlaczego?
					tmp = W[i][j][k];
					W[i][j][k] += eta * E[i][j] * O[i - 1][k] + alfa*(W[i][j][k] - W1[i][j][k]);
					W1[i][j][k] = tmp;
				}

		// obliczanie ERMS

		RMS = 0;
		for (int j = 0; j<n[numberOfLayers - 1]; j++)
		{
			RMS += (Z[numberOfLayers - 1][j] - O[numberOfLayers - 1][j])*(Z[numberOfLayers - 1][j] - O[numberOfLayers - 1][j]);
		}
		ERMS = 0;
		ERMS = sqrt(RMS / (double)(Lvec*n[numberOfLayers - 1]));
		cout << ERMS << endl;

		if (testoweIteracje - it < 20)
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
			cout << "Wyjscie testowe 0: " << O[numberOfLayers - 1][0] << endl;
			cout << "Wyjscie testowe 1: " << O[numberOfLayers - 1][1] << endl;
			cout << "Wyjscie testowe 2: " << O[numberOfLayers - 1][2] << endl;
			cout << "Wyjscie testowe 3: " << O[numberOfLayers - 1][3] << endl;
			cout << "Wyjscie testowe 4: " << O[numberOfLayers - 1][4] << endl;
			cout << "Wyjscie testowe 5: " << O[numberOfLayers - 1][5] << endl;
			cout << "Wyjscie testowe 6: " << O[numberOfLayers - 1][6] << endl;
			cout << "Wyjscie testowe 7: " << O[numberOfLayers - 1][7] << endl;
			cout << "Wyjscie testowe 8: " << O[numberOfLayers - 1][8] << endl;
			cout << "Wyjscie testowe 9: " << O[numberOfLayers - 1][9] << endl;
		}
	}
}

MLP::MLP()
{	
// wstêpna charakterystyka sieci

	numberOfLayers = 3;
	n = new int[numberOfLayers]; // iloœæ neuronów w danej warstwie sieci
	n[0] = 35;
	n[1] = 20;
	n[2] = 10;
	
	numberOfNeurons = 35;
	numberOfSignals = 35;
	Lvec = 5; // liczba wszystkich wektorów ucz¹cych

	// wpisywanie podstawowych wartoœci
	uczaceIteracje = 7000;
	testoweIteracje = 10;
	eta = 0.25;
	alfa = 0.65;

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