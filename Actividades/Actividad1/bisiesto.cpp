#include <iostream>
using namespace std;

//Crear función que determina si un año es bisiesto
void isLeap(int year)
{
 	// Condición 1: año divisible entre 4 pero no divisible entre 100
	if (year % 4 == 0 && year % 100 != 0)
	{
		// Imprimir que es bisiesto
		cout << "Sí es bisiesto" << endl;
	}
	else 
	{
		// Condición 2: año divisible entre 4, entre 100 y entre 400
		if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0)
		{
			// Imprimir que es bisiesto
			cout << "Sí es bisiesto" << endl; 
		}
		// Si ninguna de las condiciones es cierta...
		else 
		{
			// imprimir que no es bisiesto
			cout << "No es bisiesto" << endl;
		}
	}   
}

	
int main()
{
	// Inicializar variable year
	int year;
	// Pedir al usuario introducir año
	cout << "Introduce un año: "; 
	// Entrada de año
	cin >> year; 
    // Utilizar función
    isLeap(year); 
}