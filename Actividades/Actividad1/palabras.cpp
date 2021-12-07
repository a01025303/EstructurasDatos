#include <iostream>
#include <string>
#include <stdio.h>

using namespace std; 

//Crear función que busque cantidad de palabras en una frase 
void fraseYPalabra()
{
    //Declaración de variables
    string frase; 
    string palabra; 
    string auxiliar; 
    int counter; 

    //Obtención de frase y palabra
    cout << "Ingresa una frase: "; 
    getline(cin, frase); 
    cout << "Ingresa una palabra: "; 
    cin >> palabra; 

    //Tamaño frase
    cout << frase.length() << endl; 

    frase += " "; 
    
    //Iterar en cada caracter de la frase
    for(int i = 0; i <= frase.length(); i++)
    {
        //Condición para determinar palabra --> conversión a ascii (una palabra es todo lo que hay antes de un espacio)
        if(int(frase[i]) != 32)
        {
            //Ir construyendo palabra de caracter en caracter
            auxiliar = auxiliar + frase[i]; 
        }
        //si hay un espacio
        else if (int(frase[i]) == 32)
        {
            //Condición para revisar si la palabra encontrada es igual a la palabra proporcionada por el usuario
            if(auxiliar == palabra)
            {
                //Contador para palabras iguales a la deseada por el usuario
                counter ++; 
            }
            //Reiniciar variable auxiliar
            auxiliar = ""; 
        }
    }
    //Output
    cout << "La palabra " << palabra << " aparece " << counter << " veces en la frase" << endl; 
}

//Implementación de la función
int main()
{
    fraseYPalabra(); 
}