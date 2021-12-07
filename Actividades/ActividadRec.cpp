#include <iostream> 
#include <cctype>
#include <array>
using namespace std; 

//Función recursiva para multiplicar 
//Como parámetros de entrada necesitamos: el número que se va a multiplicar, la cantidad de veces que se va a multiplicar y el resultado de cada vez que se suma
int Multiplicacion(int numMultip, int numVeces, int res) 
{
    res += numMultip; //Queremos ir sumando de una en una vez el numMultip al resultado
    //Condición de paro
    if (numVeces == 1) //se termina de sumar el numMulip por numVeces 
    {
        //obtener resultado
        return res; 
    }
    else
    {
        //Seguir con las sumas
        return Multiplicacion(numMultip, numVeces - 1, res); //numVeces nos funciona como contador para sumar numVeces a numMultip
    }
    
}

//Función recursiva para hacer potencias 
//Como parámetros de entrada necesitamos: el número que se va a elevar, el exponente al que se va a elevar y el resultado de cada multiplicación
int Potencia(int num, int exponente, int res)
{ 
    //El resultado es la multiplicación del resultado anterior por el número que se eleva (multiplicación siempre empieza con resultado = 0)
    res = Multiplicacion(res, num, 0); 
    //Condición de paro
    if (exponente == 1) // Se termina cuando se hicieron "exponente" iteraciones --> multiplicar núm por exponente veces 
    {
        //obtener resultado
        return res; 
    }
    else
    {
        //Seguir multiplicando
        return Potencia(num, exponente - 1, res); 
    }
}

//Función recursiva para encontrar el número máximo de un arreglo 
//Necesitamos: arreglo, índice del arreglo, número máximo obtenido --> no supe cómo encontrar el tamaño del arreglo, por lo que incluí un parámetro para eso
int NumeroMax(int array[], int arrayLen, int index, int max) 
{ 
    //Condición para encontrar máximo
    if (array[index] > max) //Si el elemento del arreglo es mayor al máximo
    {
        max = array[index]; //máximo se vuelve el elemento 
    } 
    //Condición de paro
    if (index == arrayLen-1) //Llegar al final del arreglo
    {
        //obtener resultado
        return max; 
    }
    else
    {
        //Seguir buscando el máximo
        return NumeroMax(array, arrayLen, index + 1, max); 
    }
}

//Segunda opción recursión para encontrar número máximo
int NumeroMax1(int array[], int index, int max) 
{ 
    //Condición para encontrar máximo
    if (array[index] > max) //Si el elemento del arreglo es mayor al máximo
    {
        max = array[index]; //máximo se vuelve el elemento 
    } 
    //Condición de paro
    if (index == 0) //Llegar al inicio del arreglo
    {
        //obtener resultado
        return max; 
    }
    else
    {
        //Seguir buscando el máximo
        return NumeroMax1(array, index - 1, max); 
    }
}

//Función recursiva para encontrar la cantidad de vocales en una frase
//Necesitamos: string, el tamaño del string y la cantidad de vocales contada
int numVocales(string str, int strLen, int cantidadVocales)
{
    //Se obtiene la letra del string en la posición strLen
    char letra = str[strLen]; 
    //Se para dicha letra a minúsculas (por facilidad para comparar)
    letra = tolower(letra); 
    //Condición para determinar si la letra es vocal
    if (letra == 'a' or letra == 'e' or letra == 'i' or letra == 'o' or letra == 'u')
    {
        //Si es vocal, agregar 1 a la cantidadVocales
        cantidadVocales++; 
    }
    //Condición de paro
    if (strLen == 0)
    {
        //Obtener resultado
        return cantidadVocales; //Si strLen llega a 0, terminar
    }
    else
    {
        //Seguir contando vocales
        return numVocales(str, strLen-1, cantidadVocales); 
    }
}

//Función recursiva para obtener númer de Fibonacci en un índice determinado
//Necesitamos: dos números (resultado y num) que se van a ir recorriendo, índice deseado, un contador para la condición de paro
int Fibonacci(int res, int num, int index, int contador)
{
    //Obtener resultado auxiliar (para que num luego se convierta en este número)
    int resultadoAux = res; 
    //Realizar suma para obtener siguiente número de Fibonacci
    res = res + num; 
    //"Recorrer" num al valor anterior de res
    num = resultadoAux; 
    //Validación para los primeros dos números de la serie
    if (index == 1 or index == 2) 
    {
        //Los primeros dos números son 1
        res = 1;
        //Condición para posición 1
        if (index == 1)
        {
            //Asignar valor a contador para terminar la recursión posteriormente
            contador = 1; 
        }
        //Condición para posición 2
        if (index == 2)
        {
            //Asignar valor a contador para terminar la recursión posteriormente
            contador = 2; 
        }
    }
    //Condición de paro
    if (contador == index)
    {
        //Obtener resultado
        return res; 
    }
    else
    {
        //Seguir buscando el número con el índice deseado
        return Fibonacci(res, num, index, contador+1); 
    }
    
}

//Función recursiva para sumar dígitos de un número 
//Necesitamos: número a sumar y suma de los números 
int sumaDigitos(int num, int suma)
{
    //Agregar a la suma el residuo del número entre 10 (así logramos que sea un dígito)
    suma += num%10; 
    //Condición de paro
    if (num == 0) //Cuando ya no sea un número entero (int redondea a 0 cuando es decimal)
    {
        //obtener resultado
        return suma; 
    }
    else
    {
        //Seguir sumando dígitos
        return sumaDigitos(num/10, suma); //Dividimos num/10 para obtener coeficiente (número completo menos 1 dígito)
    }
}

//Función para invertir un string 
//Necesitamos: el string a invertir, su longitud, el string invertido que se va formando
string Invertir(string str, int strLen, string nuevoStr)
{
    //Al string invertido, sumarle el char en la posición strLen-1 
    nuevoStr = nuevoStr + str[strLen-1]; //La posición del char incluye el 0 del principio
    //Condición de paro 
    if (strLen == 0)
    {
        //obtener resultado
        return nuevoStr; 
    }
    else
    {
        //Seguir invirtiendo
        return Invertir(str, strLen-1, nuevoStr); //Vamos a la siguiente posición 
    }
}

int main()
{
    int a = 4; 
    int b = 6; 
    int c[5] = {1, -2, 43, 76, 14};
    string d = "el rey de roma"; 
    int lenD = d.size(); 
    int ind = 8; 
    int dig = 188226; 
    int size = sizeof(c)/sizeof(c[0]); 
    //cout << Multiplicacion(a, b, 0) << endl; //Res siempre empieza en 0 para que funcione
    //cout << Potencia(a, b, 1) << endl; 
    cout << NumeroMax1(c, size-1, c[size-1]) << endl; 
    //cout << numVocales(d, lenD, 0) << endl; 
    //cout << Fibonacci(1,1, ind, 3) << endl; 
    //cout << sumaDigitos(dig, 0) << endl; 
    cout << Invertir(d, lenD, "") << endl; 
}