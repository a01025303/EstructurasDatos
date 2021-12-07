#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

template <class T>
class Busqueda
{
        
    public:
        vector<T> elementos;  
        Busqueda()
        {
            for(int i = 0; i < 100000; i++) 
            {
		        elementos.push_back(i);
	        }
        }
        Busqueda(T numInicial, T max, T cantidadSumar)
        {
            for(T i = numInicial; i<max; i+=cantidadSumar) //Agregar max número de elementos al vector 
            {
		        elementos.push_back(i);
	        }
        }

        int BuquedaSecuencial(T buscado)
        {
            for(int i=0; i<elementos.size(); i++)
            {
		        if(elementos[i]==buscado)
                {
			        return i;
		        }
	        }
	        return -1;
        }

        int BusquedaMejorada1(T buscado)
        {
            for(int i=0; i<elementos.size(); i++)
            {
                if(elementos[i]==buscado)
                {
                    return i;
                }
                else if (elementos[i]>buscado)
                {
                    return -1; 
                }
	        }
            return -1;
        }

        int BusquedaMejorada2(T buscado)
        {
            int inicio = 0; 
            int salto = 1000; //Cuántos números me voy a saltar 
            int fin = 0; 
            while (inicio < elementos.size())
            {
                fin = inicio+salto; //en qué número acaba el salto
                if (fin > elementos.size())
                {
                    fin = elementos.size(); 
                }
                if (elementos[fin-1]>=buscado)
                {
                    for (int i = inicio; i < fin; i++)
                    {
                        if(elementos[i]==buscado)
                        {
                            return i; 
                        }
                    }
                    return -1;
                }
                inicio=fin;
            }
            return -1; 
        }

        int BusquedaBinaria(T buscado)
        {
            int inicio = 0; 
            int fin = elementos.size() - 1; 
            while (inicio<=fin)
            {
                int medio = (fin+inicio)/2; 
                if(elementos[medio]==buscado)
                {
                    return medio; 
                }
                else if (buscado>elementos[medio])
                {
                    inicio = medio + 1; 
                }
                else
                {
                    fin = medio-1; 
                }
            }
            return -1; 
        }
};


int main()
{
    Busqueda <int> nums;
    int buscado = 70000; 
    //Cacular tiempo para encontrar usando búsqueda secuencial
    auto antes1=high_resolution_clock::now();
    int pos1 = nums.BuquedaSecuencial(buscado); 
    auto despues1 = high_resolution_clock::now();
    auto tiempo1 = duration_cast<microseconds>(despues1-antes1).count(); //Para usar auto, cada vez q compilamos debemos escribir -std=c++11

    cout << "Se encontro el número " << buscado << " con búsqueda secuencial, en la posición " << pos1 << " y en un tiempo: " << tiempo1 << endl; 

    //Cacular tiempo para encontrar usando búsqueda mejorada 1
    auto antes2=high_resolution_clock::now();
    int pos2 = nums.BusquedaMejorada1(buscado); 
    auto despues2 = high_resolution_clock::now();
    auto tiempo2 = duration_cast<microseconds>(despues2-antes2).count();

    cout << "Se encontro el número " << buscado << " con búsqueda mejorada1, en la posición " << pos2 << " y en un tiempo: " << tiempo2 << endl; 

    //Cacular tiempo para encontrar usando búsqueda mejorada 2
    auto antes3=high_resolution_clock::now();
    int pos3 = nums.BusquedaMejorada2(buscado); 
    auto despues3 = high_resolution_clock::now();
    auto tiempo3 = duration_cast<microseconds>(despues3-antes3).count();

    cout << "Se encontro el número " << buscado << " con búsqueda mejorada2, en la posición " << pos3<< " y en un tiempo: " << tiempo3 << endl; 

    //Cacular tiempo para encontrar usando búsqueda binaria
    auto antes4=high_resolution_clock::now();
    int pos4 = nums.BusquedaBinaria(buscado); 
    auto despues4 = high_resolution_clock::now();
    auto tiempo4 = duration_cast<microseconds>(despues4-antes4).count();

    cout << "Se encontro el número " << buscado << " con búsqueda binaria, en la posición " << pos4 << " y en un tiempo: " << tiempo4 << endl; 

}