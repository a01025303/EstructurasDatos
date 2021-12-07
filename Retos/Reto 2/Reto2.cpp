#include<iostream>
#include<string>
#include <fstream>
#include <vector>
#include <sstream>
#include<stack>
#include<queue>

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

// Clase conexiones de computadora
class ConexionesComputadora
{
    public: 

        // Atributos
        string ip;
        string nombre;
        stack<Record> ConexionesEntrantes;
        queue<Record> ConexionesSalientes; 

        // Constructor por default
        ConexionesComputadora() = default;

        // Constructor por parametros (define todos los atributos, llena el stack y queue)
        ConexionesComputadora(string theIP) // data es variable global por lo que no se necesita como parámetro
        {
            // Se define el atributo IP 
            ip = theIP;

            // Leer cada Record
            for (int i = 0; i < data.size(); i++)
            {
                // Si se encuentra en el IP destino se agrega al stack (Conexión Entrante)
                if(theIP == data[i].ipDestino)
                {
                    // Condición para asignar valor al atributo nombre de la clase ConexionesComputadora
                    if ((ConexionesEntrantes.empty()) && (ConexionesSalientes.empty()))
                        nombre = data[i].nombreDestino;
                     
                     ConexionesEntrantes.push(data[i]);
                }
                
                // Si se encuentra en el IP fuente se agrega al queue (Conexión Saliente))
                if(theIP == data[i].ipFuente)
                {
                    // Evaluar si una vez que encuentras un match para el IP, aun no se llenan las conexiones
                    if( (ConexionesSalientes.empty()) && (ConexionesEntrantes.empty()) )
                        nombre = data[i].nombreFuente; // asi solo una vez se llena el atributo del nombre
                    
                    ConexionesSalientes.push(data[i]);
                }   
            }
            
        }
}; 

// Función que genera un IP Address
string ipGenerator(string lastNum)
{
    return  "172.24.238." + lastNum; // se concatena el IP address de la red interna con el del número con el cual se desea generar
}

int main()
{
    // Cargar datos al vector de Records
    cargarDatos("datosEquipo10.csv"); 
    
    // Generar IP
    string generatedIP = ipGenerator("38");
    
    // Crear obj de conexiones
    ConexionesComputadora conexiones(generatedIP); // llenar el stack y queue, definir atributos de instancia conexiones 
    
    

    
    
   
    

    //¿Qué dirección ip estas usando?
    cout << "Dirección de IP que se está utilizando: " << endl; 
    cout << generatedIP << endl; 
    cout << endl; 

     // **PREGUNTAR ¿Cuál fue la ip de la última conexión que recibió esta computadora? ¿Es interna o externa? (ENTRANTE)
    cout << "IP de la última conexión que recibió la computadora: " << endl; 
	cout << conexiones.ConexionesEntrantes.top().ipFuente << endl; 
    cout << endl; 

    // ¿Cuántas conexiones entrantes tiene esta computadora?
    cout << "Número de conexiones entrantes de la computadora: " << endl;
    cout << conexiones.ConexionesEntrantes.size() << endl;
    cout << endl;
	
	
    // ¿Cuántas conexiones salientes tiene esta computadora?
	cout << "Número de conexiones salientes de la computadora: " << endl;
	cout << conexiones.ConexionesSalientes.size() << endl;
	cout << endl;

	// Extra: ¿Tiene esta computadora 3 conexiones seguidas a un mismo sitio web? (SALIENTE)
    int count = 0; // contador
    string temp; // variable temporal que guarda el IP address

	// Iterar sobre cada conexion saliente
	while (!conexiones.ConexionesSalientes.empty())
	{
		temp = conexiones.ConexionesSalientes.front().ipDestino; // temp guarda el valor del primer ip destino
		conexiones.ConexionesSalientes.pop(); // se borra el primer ip destino

		// Se evalua si el ip destino es igual al siguiente y no se han registrado las tres conexiones seguidas ya encontradas
		if ((temp == conexiones.ConexionesSalientes.front().ipDestino))
			count++; // se incrementa count
		else
			count = 0; // se reinicia count

		// Se evalua si ya hay 3 conexiones iguales
		if (count == 3)
		{
			cout << "La computadora tiene 3 conexiones seguidas con el IP address:  " << conexiones.ConexionesSalientes.front().ipDestino << endl;
			break; // se termina el ciclo
		}
			
	}
}


    



    
/*
    while(!conexiones.ConexionesSalientes.empty())
    {
		conexiones.ConexionesSalientes.front().imprimirRecord();
		conexiones.ConexionesSalientes.pop();
	}
    cout << endl; 
    while(!conexiones.ConexionesEntrantes.empty())
    {
        conexiones.ConexionesEntrantes.top().imprimirRecord();
        conexiones.ConexionesEntrantes.pop();
    }   
     
*/


    

    
