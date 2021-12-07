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


// Funcion que regresa un diccionario con el numero de conexiones entrantes para cada dominio (que no sea "-" ni reto.com)
unordered_map<string, int> conexionesPorDia(string fecha) 
{
    // Crear diccionario de dominios y numero de conexiones entrantes
    unordered_map<string, int> cnxPorDiaDict;

    // Obtener el dia de la fecha ingresada
	int dia = getDay(fecha); // convertir día a entero 

    // Iterar sobre cada record
    for( Record r :data)
    {
        // Evaluar que el nombreDestino no sea "-", y que no contenga reto.com
        if((r.nombreDestino != "-") && (r.nombreDestino.find("reto.com") == string::npos))
        {
            // Crear objeto de conexionesComputadora para que en su contructor llena las conexiones entrantes
            ConexionesComputadora cnxObj(r.ipDestino);

            int count = 0; // contador del numero de conexiones entrantes de ese dia

            // Iterar sobre cada conexion entrante (stack)
            while(!cnxObj.ConexionesEntrantes.empty())
            {
                // Obtener el dia de la fecha del record de la conexion entrante actual
                int diaConexion = getDay(cnxObj.ConexionesEntrantes.top().fecha);

                //Evaluar si el dia ingresado es igual al de la conexion entrante de la iteracion actual
                if(dia == diaConexion)
                    count++; // registrar conexion

                cnxObj.ConexionesEntrantes.pop(); // eliminar/ pasar al siguiente elemento          
            }   

           // Agregar elemento (dominio, count) al diccionario
           cnxPorDiaDict[r.nombreDestino] = count;

        }

    }

    return cnxPorDiaDict;
}

// Funcion que imprime el top n de sitios visitados de cierta fecha
void top(int n, string fecha)
{
    // Obtener el numero de conexiones entrantes para cada sitios visitado (dict -> key = dominio, value = cnx num)
    unordered_map<string, int> cnx = conexionesPorDia(fecha);

    // Crear BST que se va a ir llenando (*NOTA: el BST de STD compara el key para el ordenamiento, pero compara a todo el objeto para determinar si este ya esta en el arbol (es unico))
    set<pair<int, string>> cnx_tree;

    for(pair<string, int> p : cnx)
    {
        pair<int, string> newPair = {p.second, p.first}; // crear el par de la iteracion actual, con el orden correcto (dict -> key = cnx num, value = dominio)
        cnx_tree.insert(newPair); // insertar el par en el BST
    }

    // Imprimir top n
    cout << "Top " << n << " del número de conexiones en la fecha " << fecha << ": " << endl; 

    // Se itera al reves (de mayor a menor)
    for(auto it=cnx_tree.rbegin(); it!=cnx_tree.rend(); it++)
    {
        // Evaluar si ya se imprimieron los n sitios
        if(n == 0)
            return;

		cout<< it->first << ": " << it->second <<"," << endl; // imprimir valores
        n--; // decrementar n 
	}
    cout << endl;


}

int main()
{

   // Cargar datos
	cargarDatos("datosEquipo10.csv");
 
    // Prueba Pregunta 1: 
    unordered_map<string, int> cnxPorDia = conexionesPorDia("17-8-2020");

    // Imprimir diccionario
    for(auto p:cnxPorDia)
    {
        cout << p.first << ": " << p.second << endl;
    }
    cout << endl;

    // Prueba Pregunta 2:
    top(5, "17-8-2020");
    cout << endl;


    // Resolucion a la Pregunta 3
    string fecha; // variable que guarda la fecha de cada dia

    // Iterar sobre cada dia del dataset (del 10-21)
    for (int dia = 10; dia < 22; dia++)
    {
        fecha = to_string(dia) + "-8-2020"; // obtener fecha completa del dia actual
        top(5, fecha); // imprimir top 5 del dia actual  
        cout << endl;
    }

   
}