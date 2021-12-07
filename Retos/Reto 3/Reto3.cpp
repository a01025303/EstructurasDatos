#include<iostream>
#include<string>
#include <fstream>
#include <vector>
#include <sstream>
#include<stack>
#include<queue>
#include<unordered_map>
#include<unordered_set>

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

int main()
{
	// Cargar datos
	cargarDatos("datosEquipo10.csv");

	// Crear conjunto (hash) de los dominios que no pertenecen a reto.com
	unordered_set<string> dominio;
	unordered_map<string, string> dominioDict; // crear diccionario llave nombreDestino/Fuente, contenido IP

	for (Record r:data)
	{
		// Evaluar si el nombre destino no tiene reto.com
		if(r.nombreDestino.find("reto.com") == string::npos) // VER REFERENCIAS 
		{
			dominio.insert(r.nombreDestino); // se inserta el nombre en el hash
			dominioDict[r.nombreDestino] = r.ipDestino; // se agrega al diccionario
		}
			
		// Evaluar si el nombre fuente no tiene reto.com
		if(r.nombreFuente.find("reto.com") == string::npos) 
		{
			dominio.insert(r.nombreFuente); // se inserta el nombre en el hash
			dominioDict[r.nombreFuente] = r.ipFuente; // se agrega al diccionario
		}
				
	}

	cout<<"Datos leídos"<<endl;
	unordered_map<string, ConexionesComputadora> cnx; // se crea un diccionario

	// Se itera sobre cada record, en la data 
	for(Record r:data)
	{
		// Se evalua si el ip fuente de la iteracion actual aun no se encuentra en el diccionario
		if(cnx.find(r.ipFuente)==cnx.end())
		{
			ConexionesComputadora a(r.ipFuente); // se crea un obj conexionesComputadora con el ip fuente correspondiente
			cnx[r.ipFuente]=a; // se agrega dicho obj al diccionario (key->r.ipFuente) (valor->a)
		}

		// Se evalua si el ip destino de la iteracion actual aun no se encuentra en en diccionario
		if (cnx.find(r.ipDestino)==cnx.end())
		{
			ConexionesComputadora a(r.ipDestino); // se crea un obj conexionesComputadora con el ip Destino correspondiente
			cnx[r.ipDestino]=a; // se agrega dicho obj al diccionario (key->r.ipDestino) (valor->a)
		}
		
		// cnx[r.ipFuente].agregarSaliente(r.ipDestino); -> en el constructor ya se agregar tanto las conexiones entrantes como la s salientes
	}

	// Preguntas

	// 1. Hay alguna nombre de dominio que sea anómalo (Esto puede ser con inspección visual.

	//Imprimir Hash de los dominios sin reto.com
	cout << "Imprimir Dominios sin reto.com: " << endl;
	for (string d:dominio)
	{
		cout << d << endl;
	}
	cout << endl;

	// Se encontraron los dominos anómalos (p7necksgkbynlvmgenv5.org, j73fzlugbhbhy3k8jgmv.com)

	// 2. Del los nombres de dominio encontrados en el paso anterior, ¿cuál es su ip? ¿Cómo determinarías esta información de la manera más optima en complejidad temporal?
	cout << "IP de p7necksgkbynlvmgenv5.org: " << dominioDict["p7necksgkbynlvmgenv5.org"] << endl;
	cout << "IP de j73fzlugbhbhy3k8jgmv.com: " << dominioDict["j73fzlugbhbhy3k8jgmv.com"] << endl;
	cout << endl;

	// 3. De las computadoras pertenecientes al dominio reto.com determina la cantidad de ips que tienen al menos una conexión entrante. (Recuerda que ya tienes la dirección de la red y el último octeto puede tener computadoras del .1 al .254. Imprime la cantidad de computadoras.

	int count = 0; // contador que cuenta cuantas ip del dominio reto.com tienen 1+ conexiones entrantes
	for(auto pair:cnx)
	{
		// Evaluar si el par pertenece a la dirección de red interna y si tiene conexiones entrantes contar la conexión
		if ((pair.first.find("172.24.238") != string::npos) && (!pair.second.ConexionesEntrantes.empty()))
			count++;
	}

	cout << "Número de computadoras pertenecientes al dominio reto con por lo menos una conexión entrante: " << count << endl;
	cout << endl;

	// 4. Toma algunas computadoras internas que no sean server.reto.com o el servidor dhcp. Obten las ip unicas de las conexiones entrantes
	
	// charles.reto.com -> 172.24.238.137
	unordered_set<string> charlesHash; // hash de conexiones entrantes de charles.reto.com

	// LLenar el hash
	while(!cnx["172.24.238.137"].ConexionesEntrantes.empty())
    {
        charlesHash.insert(cnx["172.24.238.137"].ConexionesEntrantes.top().ipFuente); // Insertar el ipFuente
        cnx["172.24.238.137"].ConexionesEntrantes.pop();  // Eliminar elemento de hasta arriba
    } 

	// Imprimir conexiones entrantes de Charles
	cout << "Conexiones entrantes de charles.reto.com" << endl;
	for (string h:charlesHash) // Iterar en el hash
	{
		cout << h << endl; // Imprimir
	}
	cout << endl;
	

	// jason.reto.com -> 172.24.238.144
	unordered_set<string> jasonHash; // hash de conexiones entrantes de charles.reto.com

	// LLenar el hash
	while(!cnx["172.24.238.144"].ConexionesEntrantes.empty())
    {
        jasonHash.insert(cnx["172.24.238.144"].ConexionesEntrantes.top().ipFuente); // Insertar el ipFuente
        cnx["172.24.238.144"].ConexionesEntrantes.pop(); // Eliminar elemento de hasta arriba
    }  

	// Imprimir conexiones entrantes de Jason
	cout << "Conexiones entrantes de jason.reto.com" << endl;
	for (string h:jasonHash) // Iterar en el hash
	{
		cout << h << endl; // Imprimir 
	} 
	cout << endl;


	// sharon.reto.com -> 172.24.238.135
	unordered_set<string> sharonHash; // hash de conexiones entrantes de charles.reto.com

	// LLenar el hash
	while(!cnx["172.24.238.135"].ConexionesEntrantes.empty())
    {
        sharonHash.insert(cnx["172.24.238.135"].ConexionesEntrantes.top().ipFuente); // Insertar el ipFuente
        cnx["172.24.238.135"].ConexionesEntrantes.pop(); // Eliminar elemento de hasta arriba
    } 

	// Imprimir conexiones entrantes de Sharon
	cout << "Conexiones entrantes de sharon.reto.com" << endl;
	for (string h:sharonHash) // Iterar en el hash
	{
		cout << h << endl; // Imprimr
	}  
	cout << endl;
	
	
	// 6. Para las ips encontradas en el paso anterior, determina si se han comunicado con los datos encontrados en la pregunta 1.
	// 7. (Extra):  En caso de que hayas encontrado que las computadoras del paso 1 y 4 se comunican, determina en qué fecha ocurre la primera comunicación entre estas 2 y qué protocolo se uso.

	// IP encontrado: 172.24.238.38
	cout << "Comunicaciones entre la IP 172.24.238.38 y los dominios anónimos:  (El primer Record es el que tiene la fecha más reciente)" << endl;

	// Buscar conexiones con p7necksgkbynlvmgenv5.org o j73fzlugbhbhy3k8jgmv.com
	while (!cnx["172.24.238.38"].ConexionesSalientes.empty()) // Iterar hasta que las conexiones estén vacías
	{
		// Evaluar si en las conexionesSalientes del ip 172.24.238.38 tienen un nombre destino p7necksgkbynlvmgenv5.org o j73fzlugbhbhy3k8jgmv.com
		if( (cnx["172.24.238.38"].ConexionesSalientes.front().nombreDestino == "p7necksgkbynlvmgenv5.org") || (cnx["172.24.238.38"].ConexionesSalientes.front().nombreDestino == "j73fzlugbhbhy3k8jgmv.com"))
			cnx["172.24.238.38"].ConexionesSalientes.front().imprimirRecord(); // imprimir record 
		
        cnx["172.24.238.38"].ConexionesSalientes.pop(); // eliminar el primer elemento (pasar al siguiente)
	}
	


	//Referencias:
	// https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c

	
	
    
}