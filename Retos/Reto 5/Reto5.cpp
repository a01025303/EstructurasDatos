
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<stack>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<set>

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


template <class T>
class Graph
{
    public:

        // Atributos
        unordered_map<T, int> ids; // diccionario con el nodo T, y el indx int
        vector<vector<int> > matriz; // matriz que en las columnas contiene los nodos entrantes, y en las filas los salientes
        int cantidad; // cantidad actual de nodos en el grafo
        
        // Constructor vacio
        Graph()
        {
            cantidad = 0; // la cantidad comienza en cero
        }
        
        void agregarNodo(T id)
        {
            ids[id] = cantidad; // se agrega el nodo al diccionario, con su indx correspondiente
            vector<int> nuevaFila; // se crea un nuevo vector, para agregarlo al vector de la matriz principal

            // Se itera "cantidad" numero de veces 
            for(int fila=0; fila<cantidad; fila++)
            {
                matriz[fila].push_back(0); // al final del vector de cada fila se le agrega un cero
                nuevaFila.push_back(0); // y la nuevaFila a la par se va llenando con ceros
            }

            nuevaFila.push_back(0); // dado que la "cantidad" es 1 menor al número de ceros que debe de tener la nueva fila, de le agraga otro cero a la nueva fila
            matriz.push_back(nuevaFila); // se agrega toda la nueva fila a la matriz (se agrega el vector nuevaFila, al vector externo de la matriz)
            cantidad++; // se incrementa la cantidad 
        }

        // Método que agrega a un nodo, un arco dirigido con peso
        void agregarArcoDirigidoConPeso(T fuente, T destino, int peso)
        {
            // Evaluar que tanto la fuente como el destino se encuentren en el grafo
            if((ids.find(fuente) != ids.end()) && (ids.find(destino) != ids.end()))
                matriz[ids[fuente]][ids[destino]] = peso; // se agrega el peso en los indx correspondientes, donde la fila (indx del vector interno) es de donde vengo, y la columna (indx dentro de dicho vector) es al nodo que voy
        }

        // Método que incrementa un peso ya establecido para ciertos nodos
        void incrementarPesoArcoDirigido(T fuente, T destino)
        {
            // Evaluar que tanto la fuente como el destino se encuentren en el grafo
            if((ids.find(fuente) != ids.end()) && (ids.find(destino) != ids.end()))
                matriz[ids[fuente]][ids[destino]]++; // incrementar peso en el indx correspondiente en la matriz        
        }
        
        // Metodo que agrega un arco con peso a un nodo  (es bidireccional, el peso es el mismo para ambas direcciones)
        void agregarArcoConPeso(T fuente, T destino, int peso)
        {
            agregarArcoDirigidoConPeso(fuente,destino,peso); // se agrega el arco dirigido de fuente a destino
            agregarArcoDirigidoConPeso(destino,fuente,peso); // se agrega el arco dirigido de destino a fuente
        }

        // Método que imprime el grafo
        void imprimir()
        {
            // Se itera sobre cada pair en el diccionario de nodos
            for(auto nodo : ids)
            {
                cout << nodo.first << ":" << nodo.second << endl; // Se imprime el nodo, y su indx
            }
            
            // Se itera sobre cada vector dentro del vector externo/principal
            for(int col=0; col<cantidad; col++)
            {
                // Se itera sobre cada elemento dentro del vector interno
                for(int filas=0; filas<cantidad; filas++)
                {
                    cout << matriz[col][filas] << ", "; // se imprime cada elemento del vector interno
                }
                cout << endl;
            }
        }	
};


// Funcion que obtiene el dia de una fecha string
int getDay(string fecha)
{
    // Obtener el dia de la fecha ingresada
    string strDia;
	istringstream dateStr(fecha); // istringstream obj
	getline(dateStr, strDia, '-'); // obtener día
	int intDia = stoi(strDia); // convertir día a entero 

    return intDia;
}

template <class T>
class Nodo
{
	public:

        // Atributos
        T id; // id del nodo
        unordered_map<Nodo<T>*, int> siguientes; // diccionario que guarda las direcciones de memoria de los nodos siguientes al mismo, con su peso
        
        // Constructor parametros
        Nodo(T id)
        {
            this->id = id;
        }
        
        // Metodo que agrega el arco con peso de un nodo siguiente 
        void agregarArcoConPeso(Nodo<T>* sig, int peso)
        {
            siguientes[sig] = peso; // se agrega al diccionario la direccion de memoria del nodo siguiente, con su peso
        }

        void incrementarPesoNodoSig(Nodo<T>* sig)
        {
            // Evaluar si el nodo aun no esta en el diccionario
            if(siguientes.find(sig) == siguientes.end())
                siguientes[sig] = 0; // si no esta se inicializa con 0, y asi en el incremento se asegura que no se este incrementando  basura 
                
            siguientes[sig]++; // se incrementa el peso
        }
        
        // Metodo que imprime a un nodo y sus nodos siguientes
        void imprimirNodo()
        {
            cout << this->id << ":" << endl; // se imprime el id del nodo principal
            int indx = 1;

            // Se itera sobre cada pair del diccionario de los nodos siguientes
            for(auto it=siguientes.begin(); it!=siguientes.end(); it++)
            {
                cout << "  " <<  indx << ")"<< it->first->id <<","<< it->second << endl; // se imprime el id y el peso de cada nodo siguiente
                indx++; // index que se imprime
            }
            //cout << endl;
        }
    };

    template <class T>
    class ListGraph
    {
        public:
            // Atributos
            unordered_map<T, Nodo<T>*> nodos; // diccionario que contiene el id y direccion de memoria de cada nodo que conforma al grafo
        
            // Metodo que crea/agrega un nodo en el grafo
            void agregarNodo(T id)
            {
                Nodo<T>* nuevo = new Nodo<T>(id); // se crea el nodo con el id deseado en el heap
                nodos[id] = nuevo; // se agrega el nodo en el diccionario
            }
            
            // Metodo que agrega un arco dirigido con peso entre dos nodos del grafo
            void agregarArcoDirigidoConPeso(T fuente, T destino, int peso)
            {
                // Evaluar si tanto el id del nodo fuente como el del destino existen en el grafo
                if((nodos.find(fuente) != nodos.end()) && (nodos.find(destino) != nodos.end()))
                    nodos[fuente]->agregarArcoConPeso(nodos[destino], peso); // se agrega el arco con peso al nodo fuente -> que agregara el nodo destino a su diccionario de siguientes
            }

            // Metodo que agrega un arco dirigido entre dos nodos del grafo, incrementando el peso 1 unidad
            void agregarArcoDirigidoConPesoIncremental(T fuente, T destino)
            {
                // Evaluar si tanto el id del nodo fuente como el del destino existen en el grafo
                if((nodos.find(fuente) != nodos.end()) && (nodos.find(destino) != nodos.end()))
                    nodos[fuente]->incrementarPesoNodoSig(nodos[destino]); // se agrega el arco con peso al nodo fuente -> que agregara el nodo destino a su diccionario de siguientes, mientras el peso incrementara 1 unidad
            }
            
            // Metodo que agrega un arco no dirigido con peso (arco bidireccional, el peso es el mismo para ambas direcciones)
            void agregarArcoNoDirigidoConPeso(T fuente, T destino, int peso)
            {
                agregarArcoDirigidoConPeso(fuente, destino, peso); // se agrega el arco dirigido de fuente a destino
                agregarArcoDirigidoConPeso(destino, fuente, peso); // se agrega el arco dirigido de destino a fuente
            }
            
            // Metodo que imprime el grafo
            void imprimir()
            {
                // Itera sobre el diccinario con los nodos del grafo
                for(auto it:nodos)
                {
                    it.second->imprimirNodo(); // se imprimen los nodos siguientes de cada nodo del grafo
                }
            }
        
};

// (karen.reto.com) Una ip interna, que llamaremos A, la cual se comunica con algunas otras computadoras internas.
// (p7necksgkbynlvmgenv5.org) Algún sitio con nombre raro, denominaremos B.
// (wiktionary.org) Un sitio web normal que tiene un volumen de trafico anómalo un día, el cual denominaremos C.

Graph<string> grafoCnxInternasPorFecha(string fecha)
{
    // Crear grafo 
    Graph<string> conexionesInternas;

    // Iterar sobre cada record en el data 
    for (Record r : data)
    {
        // Evaluar que el record sea de la fecha solicitada y el nombre destino este definido (nombre fuente siempre es reto.com) 
        if ((fecha == r.fecha) && (r.nombreDestino != "-"))
        {
            // Evaluar si el nombre fuente aun no esta en el grafo
            if(conexionesInternas.ids.find(r.nombreFuente) == conexionesInternas.ids.end())
                conexionesInternas.agregarNodo(r.nombreFuente); // se agrega el dominio
                
            // Evaluar si el nombre destino tambien es reto.com (entonces tanto fuento como destino son reto.com)
            if ((r.nombreDestino.find("reto.com") != string::npos)) 
            {
                // Evaluar si el nombre destino con el que se conecta aun no esta en el grafo
                if(conexionesInternas.ids.find(r.nombreDestino) == conexionesInternas.ids.end())
                    conexionesInternas.agregarNodo(r.nombreDestino); // se agrega el dominio

                // Agregar conexion entre nodos/arco
                conexionesInternas.incrementarPesoArcoDirigido(r.nombreFuente, r.nombreDestino);
            }
        }
    }

    return conexionesInternas;       
}

ListGraph<string> grafoCnxSitioWebPorFecha(string fecha)
{
    // Crear Grafo
    ListGraph<string> conexionesSitioWeb;

    // Iterar sobre cada record en el data 
    for (Record r : data)
    {
        // Evaluar que el record sea de la fecha solicitada y el nombre destino este definido (nombre fuente siempre es reto.com) 
        if ((fecha == r.fecha) && (r.nombreDestino != "-"))
        {
            // Evaluar si el nombre fuente aun no esta en el grafo
            if(conexionesSitioWeb.nodos.find(r.nombreFuente) == conexionesSitioWeb.nodos.end())
                conexionesSitioWeb.agregarNodo(r.nombreFuente); // se agrega el dominio
                
            // Evaluar si el nombre destino no es reto.com (entonces destino es un sitio web)
            if ((r.nombreDestino.find("reto.com") == string::npos)) 
            {
                // Evaluar si el nombre destino aun no esta en el grafo
                if(conexionesSitioWeb.nodos.find(r.nombreDestino) == conexionesSitioWeb.nodos.end())
                    conexionesSitioWeb.agregarNodo(r.nombreDestino); // se agrega el dominio

                // Agregar conexion entre nodos/arco
                conexionesSitioWeb.agregarArcoDirigidoConPesoIncremental(r.nombreDestino, r.nombreFuente); // se ponen al reves nombreDestino y nombreFuente para obtener las computadoras conectadas/ que interactuaron con cada sitioWeb, y no los sitios web que interactuaron con cada computadora
            }
            
        }
    }
    return conexionesSitioWeb;  
}

int main()
{
    // Cargar Datos
    cargarDatos("datosEquipo10.csv");

    // Pregunta 1 y 2:
    string fecha; // variable que guarda la fecha de cada dia
    

    // Iterar sobre cada dia del dataset (del 10-21)
    for (int dia = 10; dia < 22; dia++)
    {
        fecha = to_string(dia) + "-8-2020"; // obtener fecha completa del dia actual
        cout << "Grafo-Matriz de conexiones internas en la fecha " << fecha << endl;
        grafoCnxInternasPorFecha(fecha).imprimir(); // imprimir grafo del dia actual
        cout << endl;
    }

    // Pregunta 3:
    /*
    // Se imprime manualmente el grafo de cada dia, ya que sino no cabe en la terminal
    fecha = "20-8-2020"; // esta fecha se cambia manualmente al dia elegido
    cout << "Grafo-Lista de conexiones de los sitios web en la fecha " << fecha << endl;
    grafoCnxSitioWebPorFecha(fecha).imprimir(); // imprimir grafo del dia actual*/
    
   
    

}