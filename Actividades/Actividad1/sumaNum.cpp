#include <iostream>

using namespace std; 

//Creación de la función para sumar x cantidad de números 
void sumaNum(int cantidad)
{
    //Inicializar variables 
    int num = 0; //número a ingresar por usuario
    int suma; //súma de x números

    //iterar la cantidad de veces pedida por el usuario
    for (int i = 0; cantidad > i; i++)
    {
        //Pedir número para sumarlo
        cout << "Ingrese número: "; 
        cin >> num; 

        //Sumar número al total
        suma = suma + num; 
    }
    //Proporcionar resultado
    cout << "La suma de los números ingresados es: " << suma << endl;
}

//Implementación
int main()
{
    //Pedir a usuario cantidad de números por sumar
    int cantidad; 
    cout << "Bienvenid@, ingresa la cantidad de números que quieres sumar: " ; 
    cin >> cantidad; 

    //Llamar función
    sumaNum(cantidad); 
}