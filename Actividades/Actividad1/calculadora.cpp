#include <iostream> 
#include <string>

using namespace std; 

//Creación de clase calculadora con generics
template <class T>
class Calculadora 
{
    //Atributos
    private: 
        string tipo; 
        string modelo; 
        string color; 
        string marca; 
    public: 
        //Constructores calculadora
        Calculadora(){}
        Calculadora(string tipo, string modelo, string marca, string color): tipo(tipo), modelo(modelo), marca(marca), color(color){}

        //Método para sumar dos números del mismo tipo
        T suma(T num1, T num2)
        {
            return num1 + num2; 
        }
        //Método para restar dos números del mismo tipo
        T resta(T num1, T num2)
        {
            return num1-num2; 
        }
        //Método para multiplicar dos números del mismo tipo
        T multiplica(T num1, T num2)
        {
            return num1*num2; 
        }
        //Método para dividir dos números del mismo tipo
        T divide(T num1, T num2)
        {
            return num1/num2; 
        }
};

int main()
{
    //Creación de calculadoras para dos tipos de datos
    Calculadora <int> calcu1("estandar", "TX111", "Casio", "Negra"); 
    Calculadora <float> calcu2("estandar", "TX111", "Casio", "Negra"); 
    Calculadora <double> calcu3("estandar", "TX111", "Casio", "Negra");

    //Variables con números de tipo int y float
    int numero1 = 6; 
    int numero2 = 10; 
    float numero3 = 3.14; 
    float numero4 = 2.7; 

    //Resultados de operaciones con cada calculadora
    //Suma
    cout << "Suma de ints: " << calcu1.suma(numero1, numero2) << endl; 
    cout << "Suma de floats: " << calcu2.suma(numero3, numero4) << endl; 
    cout << "Suma de doubles: " << calcu3.suma(27.3, 3.5) << endl; 
    //Resta
    cout << "Resta de ints: " << calcu1.resta(numero1, numero2) << endl;
    cout << "Resta de floats: " << calcu2.resta(numero3, numero4) << endl;  
    cout << "Resta de doubles: " << calcu3.resta(27.3, 3.5) << endl; 
    //Multiplicación
    cout << "Multiplicación de ints: " << calcu1.multiplica(numero1, numero2) << endl;
    cout << "Multiplicación de floats: " << calcu2.multiplica(numero3, numero4) << endl; 
    cout << "Multiplicación de doubles: " << calcu3.multiplica(27.3, 3.5) << endl; 
    //División
    cout << "División de ints: " << calcu1.divide(numero1, numero2) << endl;
    cout << "División de floats: " << calcu2.divide(numero3, numero4) << endl; 
    cout << "División de doubles: " << calcu3.divide(27.3, 3.5) << endl; 
}