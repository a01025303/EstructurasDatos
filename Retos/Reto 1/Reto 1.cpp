// Integrantes del Equipo: 
// Andreína Sanánez / A01024927
// Ana Paula Katsuda / A01025303

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Record{

	public:

		// Atributos
		string fecha; 
		string hora; 
		string ipFuente; 
		int puertoFuente;
		string nombreFuente;
		string ipDestino; 
		int puertoDestino; 
		string nombreDestino; 
		
		// Construcor por parámetros
		Record(string laFecha, string laHora, string elIpFuente, string elPuertoFuente, string elNombreFuente, string elIpDestino, string elPuertoDestino, string elNombreDestino)
		{
			// Asignación de valores
			this->fecha=laFecha;  
			this->hora=laHora;  
			this->ipFuente=elIpFuente;  
			this->nombreFuente=elNombreFuente;  
			this->ipDestino=elIpDestino; 
			this->nombreDestino=elNombreDestino;     

			// Evaluar para casos sin valor
			if(elPuertoFuente=="-")
				this->puertoFuente=0;
			else
				this->puertoFuente=stoi(elPuertoFuente); // convertir el número de puerto, de string a int

			if(elPuertoDestino=="-")
				this->puertoDestino=0;
			else
				this->puertoDestino=stoi(elPuertoDestino); // convertir el número de puerto, de string a int
			
		}
		
		// Método que imprime un record (una línea)
		void imprimirRecord()
		{
			cout<<fecha << "," << hora << "," << ipFuente << "," << puertoFuente << "," << nombreFuente << "," << ipDestino << "," << puertoDestino << "," << nombreDestino << endl;
		}
};


vector<Record> data; // vector que guarda cada línea de información

// Función que carga los datos 
void cargarDatos(string path)
{
	ifstream in; 
	in.open(path);
	string line, parte;
	vector<string> partes; // vector que guarda cada una de las partes en la línea

	while(getline(in, line)) // getline() lee toda la linea hasta encontrar'\n'; devuelve valor booleano true si logró leer, sino false
	{
		// Evaluar si hay un "\r" en el string (si no lo hay find() devuelve npos)
		if(line.find("\r")!=line.npos) // .npos (hasta el final del string)
			line=line.substr(0, line.size()-1); // se elimina el último elemento del string
	
		istringstream inString(line); // istringstream obj

		while(getline(inString, parte, ',')) // getline lee hasta encontrar "," que es el caracter delimitador
		{
			partes.push_back(parte); // se agrega la parte al vector de partes
		}

		Record r(partes[0], partes[1], partes[2], partes[3], partes[4], partes[5], partes[6], partes[7]); // se crea el Record (instancia) de la línea
		data.push_back(r); // se agrega al vector de records
		partes.clear(); // se reinicia el vector de partes
	}
	in.close();
}


///////////////////////// Sort & Search ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Comparadores
int compararRecordNombreFuente(Record r, string nF)
{
	if(r.nombreFuente < nF) 
		return -1;
	else if(r.nombreFuente == nF) 
		return 0;
	else 
		return 1;
}

int compararDosRecordsNombreFuente(Record r1, Record r2)
{
	if (r1.nombreFuente <= r2.nombreFuente)
		return -1;
	else
		return 1;
}

int compararRecordDia(Record r, int date)
{
	string strDia;
	istringstream dateStr(r.fecha); // istringstream obj
	getline(dateStr, strDia, '-'); // obtener día
	int intDia = stoi(strDia); // convertir día a entero 

	if(intDia < date) 
		return -1;
	else if(intDia == date) 
		return 0;
	else 
		return 1;
}

int compararRecordNombreDestino(Record r, string nD)
{
	if(r.nombreDestino < nD) 
		return -1;
	else if(r.nombreDestino == nD) 
		return 0;
	else 
		return 1;
}

int compararDosRecordsNombreDestino(Record r1, Record r2)
{
	if (r1.nombreDestino <= r2.nombreDestino)
		return -1;
	else
		return 1;
}

int compararRecordPuertoDestino(Record r, int pD)
{
	if(r.puertoDestino < pD) 
		return -1;
	else if(r.puertoDestino == pD) 
		return 0;
	else 
		return 1;
}

int compararDosRecordsPuertoDestino(Record r1, Record r2)
{
	if (r1.puertoDestino <= r2.puertoDestino)
		return -1;
	else
		return 1;
}


// Class Template que implementa el algoritmo QuickSort
template <class T>
class QuickSort {
	
    public:
        void Sort(vector<T> &data, int (*comparador)(T, T))
        {
            SortAux(data, 0, data.size()-1, comparador);
        }
	
	private:

        // Método recursivo que realiza el quick sort
        void SortAux(vector<T> &data, int lo, int hi, int (*comparador)(T, T))
        {
            // Cuando el sub-arreglo es de 1 elemento lo=hi, se devuelve y detiene la recursión 
            if(lo>=hi)
                return;
            
            int posOrdenado=Partition(data, lo, hi, comparador); // se hace partition del arreglo y se devuelve el indx final del pivote
            SortAux(data, lo, posOrdenado-1, comparador); // a traves de recursion de sigue con el partition del sub-arreglo izquierdo del index del pivote 
            SortAux(data, posOrdenado+1, hi, comparador); // a traves de recursion de sigue con el partition del sub-arreglo derecho del index del pivote
        }
	
        // Método que realiza la partición
        int Partition(vector<T> &data, int lo, int hi, int (*comparador)(T, T))
        {
            int p=lo; // pivote comienza teniendo el index del primer elemento
            int i=lo+1; // comienza teniendo el index del segundo elemento (se mueve hacia la der, nums menores o igual al pivote)
            int j=hi; // comienza teniendo el index del último elemento (se mueve hacia la izq, nums mayores al pivote)

            while (true)
            {
                // Mientras el elemento en i sea menor o igual al pivote y no haya llegado al final
				while( (comparador(data[i], data[p]) == -1) && i<hi)
                {
                    i++; // i avanza un lugar a la derecha
                }

                // Mientras el elemento en j sea mayor al pivote y no haya llegado al inicio 
				while( (comparador(data[j], data[p]) == 1) && j>lo)
                {
                    j--; // j avanza a la izquierda
                } 

                // Cuando la j sea menor o igual que el pivote; i sea mayor al pivote (o hayan llegado al extremo del arreglo)
                // Evaluar si el index de i es menor al de j
                if(i<j)
                    Intercambiar(data, i,j); // se intercambian los elementos en i y j

                // Si i=j se han evaluado todos los elementos
                else
                {
                    Intercambiar(data, p, j); // se pone al pivote en medio (del lado derecho el grupo i, del izq el grupo j)
                    break; // se sale del ciclo
                }
            }
            return j; // se devulve el index de j (que es el que tomó el pivote al final)
        }

		// Método que intercambia los contenidos de dos posiciones en un vector 
		void Intercambiar(vector<T> &data, int indx1, int indx2)
		{
			T temp=data[indx1]; // varible temporal que guarda el contenido de la posición 1
			data[indx1]=data[indx2]; // se remplaza el contenido del indx1 por el del indx 2 (en otras palabras se borra)
			data[indx2]=temp; // se asigna el contenido guardado del indx1 en el indx 2
		}
};

// Function Template que implementa la búsqueda binaria
template<class T, class B>
int BusquedaBinaria(vector<T> &data, B target, int comparador(T, B))
{
    int inicio = 0; // indice de inicio del vector
    int fin = data.size()-1; // indice en el cual termina el vector
    int medio = 0; // indice de la mitad de ya sea el vector o un sub arreglo del mismo

    // Iterar mientras inicio sea menor o igual a fin
    while (inicio <= fin)
    {
        // Calcular el indice que divide en 2 al vector/sub arreglo actual
        medio = (fin + inicio)/2;

        // Evaluar si el elemento en el indice medio es igual al buscado
        if (comparador(data[medio], target) == 0)
            return medio;
        // Evaluar si el número buscado es mayor que el elemento del medio     
        else if (comparador(data[medio], target) == -1)
            inicio = medio + 1; // el medio se vuelve el inicio del sub arreglo (se suma 1, ya que ya se evaluó el caso vector[medio] == target)
        else
            fin = medio - 1; // el medio se vuelve el final del sub arreglo (se resta 1, ya que ya se evaluó el caso vector[medio] == target)

    }
    return -1; // Si el elemento buscado no se encuentra en el vector
}  



int main()
{
	cargarDatos("datosEquipo10.csv"); // Cargar los datos al vector
	QuickSort<Record> sortObj; // objeto quicksort

	// 1) Cuántos registros tiene su archivo?
	cout << "Cuántos registros tiene su archivo?" << endl;
	cout << "Número de registros: "<< data.size() << endl;
	cout << endl;

	// 2) Cuántos records hay del segundo día registrado? Qué día es este?
	cout << "Cuántos records hay del segundo día registrado? Qué día es este?" << endl;

	// Encontrar el segundo día (data ya ordenada de menor a mayor día)
	string strDia;
	istringstream dateStr(data[0].fecha); // istringstream obj
	getline(dateStr, strDia, '-'); // obtener día
	int intDia = stoi(strDia) + 1; // convertir día a entero 

	// Aplicar búsqueda binaria para encontrar un index con fecha del segundo día
	int indx = BusquedaBinaria<Record, int>(data, intDia, compararRecordDia);

	int indxSuperior = indx;
	int indxInferior = indx;
	
	// Encontrar límite superior de los datos del segundo día
	while (compararRecordDia(data[indxSuperior], intDia) == 0)
	{
		indxSuperior++;
	}

	// Encontrar límite inferior de los datos del segundo día
	while (compararRecordDia(data[indxInferior], intDia) == 0)
	{
		indxInferior--;
	}

	// Calcular el número de records del segundo día
	int count = indxSuperior - indxInferior;
	cout << "Día: "<< intDia << endl;
	cout << "Número de records del segundo día: "<< count << endl;
	cout << endl;

	// 3) Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel, Raymond?
	cout << "Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel, Raymond? (-1 = NO)" << endl;

	// Ordenar data por orden lexico grafico del NombreFuente
	sortObj.Sort(data, &compararDosRecordsNombreFuente);

	// Buscar nombre Jeffrey
	indx = BusquedaBinaria<Record, string>(data, "jeffrey.reto.com", compararRecordNombreFuente);
	cout << "Resultado Búsqueda Jeffrey: " << indx << endl;

	// Buscar nombre Betty
	indx = BusquedaBinaria<Record, string>(data, "betty.reto.com", compararRecordNombreFuente);
	cout << "Resultado Búsqueda Betty: " << indx << endl;

	// Buscar nombre Katherine
	indx = BusquedaBinaria<Record, string>(data, "katherine.reto.com", compararRecordNombreFuente);
	cout << "Resultado Búsqueda Katherine: " << indx << endl;

	// Buscar nombre Scott
	indx = BusquedaBinaria<Record, string>(data, "scott.reto.com", compararRecordNombreFuente);
	cout << "Resultado Búsqueda Scott: " << indx << endl;

	// Buscar nombre Benjamin
	indx = BusquedaBinaria<Record, string>(data, "benjamin.reto.com", compararRecordNombreFuente);
	cout << "Resultado Búsqueda Benjamín: " << indx << endl;

	// Buscar nombre Samuel
	indx = BusquedaBinaria<Record, string>(data, "samuel.reto.com", compararRecordNombreFuente);
	cout << "Resultado Búsqueda Samuel: " << indx << endl;

	// Buscar nombre Raymond
	indx = BusquedaBinaria<Record, string>(data, "raymond.reto.com", compararRecordNombreFuente);
	cout << "Resultado Búsqueda Raymond: " << indx << endl;
	cout << endl;

	// 5) Alguna computadora se llama server.reto.com? 
	cout << "Alguna computadora se llama server.reto.com? (-1 = NO)" << endl;

	// Buscar nombre server (data ya está ordenada por nombre fuente)
	indx = BusquedaBinaria<Record, string>(data, "server.reto.com", compararRecordNombreFuente);
	cout << "Resultado Búsqueda Server: " << indx << endl;
	cout << endl;

	// 4) Cuál es la dirección de la red interna de la compañía? (Se incluye en el reporte)

	// 6) Qué servicio de email utilizan? (gmail.com, outlook.com, protomail.com, freemailserver.com)
	cout << "Qué servicio de email utilizan? (gmail.com, outlook.com, protonmail.com, freemailserver.com) (-1 = NO ENCONTRADO)" << endl;

	// Ordenar data por orden lexico grafico del NombreDestino
	sortObj.Sort(data, &compararDosRecordsNombreDestino);

	// Buscar nombre gmail
	indx = BusquedaBinaria<Record, string>(data, "gmail.com", compararRecordNombreDestino);
	cout << "Resultado Búsqueda gmail: " << indx << endl;

	// Buscar nombre outlook
	indx = BusquedaBinaria<Record, string>(data, "outlook.com", compararRecordNombreDestino);
	cout << "Resultado Búsqueda outlook: " << indx << endl;

	// Buscar nombre protomail
	indx = BusquedaBinaria<Record, string>(data, "protonmail.com", compararRecordNombreDestino);
	cout << "Resultado Búsqueda protomail: " << indx << endl;

	// Buscar nombre freemailserver
	indx = BusquedaBinaria<Record, string>(data, "freemailserver.com", compararRecordNombreDestino);
	cout << "Resultado Búsqueda freemailserver: " << indx << endl;
	cout << endl;


	// 7) Considerando solamente los puertos destino, qué puertos abajo del 1000 se están usando?
	cout << "Considerando solamente los puertos destino, qué puertos abajo del 1000 se están usando?" << endl;

	// Ordenar data respecto a los PuertosDestino
	sortObj.Sort(data, &compararDosRecordsPuertoDestino);

	int num = 1000;
	indx = -1;

	// Encontrar el index del puerto destino más grande abajo de 1000
	while (indx == -1)
	{
		num--;
		indx = BusquedaBinaria<Record, int>(data, num, compararRecordPuertoDestino);	
	}

	// Imprimir todos los puertos abajo de 1000
	for (int i = indx; i < data.size(); i--)
	{
		if (num != data[i].puertoDestino)
		{
			cout << num << endl;
			num = data[i].puertoDestino;
		}
	}	
   
}

// PREGUNTAS Y NOTAS EXTRA (BORRAR AL FINAL)
// Por qué se debe de crear istringstream inString(line); ?
// Diferencia entre pasar funcion como apuntador vs por valor/nombre
