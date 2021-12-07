// Integrantes del Equipo:
// Andreina Sananez / A01024927
// Ana Paula Katsuda /  A01025303

#include <iostream>

using namespace std;

template <class T>
class Nodo
{
	public:
        // Atributos
        T value;
        Nodo *next; // Apuntador al elemento siguiente
        
        // Constructor por parámetros
        Nodo(T val)
        {
            value = val;
            next = NULL;
        }
};

template <class T>
class LinkedList
{
	public:
        // Atributo
		Nodo<T>* root; // Apuntador al primer elemento de la lista
		
		// Constructor vacío
        LinkedList()
        {
			root=NULL;
		}
		
        // Método que agrega un elemento al final de la lista
		void append(Nodo<T>* nuevo)
        {
            // Evaluar si no hay ningún elemento en la lista
			if(root == NULL)
				root = nuevo; // si esta vacía, la direccion del elemento nuevo es el primer elemento de la lista 

			else
            {
				Nodo<T>* it = root; // se crea un iterador o un elemento temporal, que comienza siendo el primer elemento

                // Se itera hasta que el iterador no tenga un elemento siguiente (null_ptr)
				while(it->next != NULL)
                {
					it = it->next; // se pasa al siguiente elemento
				}

				it->next = nuevo; // se asigna la dirección del nuevo elemento, al atributo next del que antes era el último
			}
		}
		
        // Wrapper del Método Append para crear automáticamente un nuevo elemento (dynamic memory)
		void append(T val)
        {
			Nodo<T>* nuevo = new Nodo<T>(val);
			this->append(nuevo);
		}
		
        // Método que imprime cada uno de los elementos de la lista
		void imprimir()
        {
			Nodo<T>* it = root; // se crea un apuntador de un elemento temporal que comienza en el primer elemento de la lista
			
            // Se itera mientras el elemento temporal (iterador) no sea null
            while(it != NULL)
            {
				cout << it->value << ","; // se imprime el valor del apuntador al elemento
				it = it->next; // se continua con el siguiente elemento
			}
			cout<<endl;
		}
		
        // Método que accede al valor de un elemento de una posición dada
		void accederElemento(int i)
        {
			int actual = 0; // la posición actual comienza en 0
			Nodo<T>* it = root; // se crea un apuntador de un elemento temporal que comienza en el primer elemento de la lista

            // Se itera mientras el iterador exista (no sea null ptr) y la posición actual sea menor a la buscada 
			while(it!=NULL && actual<i)
            {
				actual++; // se incrementa la posición actual
				it=it->next; // se pasa al siguiente elemento 
			}

            // Evaluar si la posición actual es igual a la buscada
			if(actual==i)
				cout<<it->value<<endl; // se imprime el valor en la posición

            // Sino, it==null_ptr por lo que la posición ingresada no existe
			else
				cout<<"no existe esa posición"<<endl;
			
		}
		
        
        // Método que cambia el valor de un elemento en cierta posición
		void modificarElemento(int i, T val)
        {
			int actual = 0; // posición actual
			Nodo<T>* it = root; // se crea un apuntador de un elemento temporal que comienza en el primer elemento de la lista

            // Se itera mientras el iterador exista (no sea null ptr) y la posición actual sea menor a la buscada 
			while(it!=NULL && actual<i)
            {
				actual++; // se incrementa la posición actual
				it = it->next; // se pasa al siguiente elemento 
			}

            // Evaluar si la posición actual es igual a la buscada
			if(actual==i)
				it->value = val; // se modifica el valor del elemento en dicha posición
            
            // Sino, it==null_ptr por lo que la posición ingresada no existe
			else
				cout<<"no existe esa posición"<<endl;
		}
		

        // Método que inserta un nuevo elemento en cierta posición de la lista 
		void insert(int pos, Nodo<T>* nuevo)
        {
            // Evaluar si no hay ningún elemento en la lista
			if(root == NULL) // if (root == NULL && pos != 0)
				return;
			
			int actual = 0; // posición actual
			Nodo<T>* it = root; // se crea un apuntador de un elemento temporal que comienza en el primer elemento de la lista

            // Evaluar si la posición solicitada es 0 (el primer elemento de la lista)
            if(pos == 0)
            {
				nuevo->next = root; // el primer elemento (root) se vuelve el siguiente del que se quiere insertar
				root = nuevo; // el elemento nuevo se vuelve el primero de la lista (root)
				return;
			}

            // Mientras el iterador exista y la posición actual sea menor a la posición anterior de la que se busca
			while(it != NULL && actual<pos-1)
            {
				it = it->next; // se pasa al siguiente elemento
				actual++; // se actualiza la posición actual
			}

            // Evaluar si la posición actual es igual a un índice anterior del que se quiere insertar el elemento
			if(actual == pos-1)
            {
				nuevo->next = it->next; // el elemento adelante de nuevo se vuelve el elmento que estaba en el indx buscado (el siguiente del elemento pos-1)
				it->next = nuevo; // el elemento adelande de (pos-1) es nuevo
			}
		}
		

        // Wrapper del Método Insert para facilitar la creacion dinámica del Nodo/Elemento
		void insert(int pos, T val)
        {
			Nodo<T>* nuevo = new Nodo<T>(val);
			this->insert(pos, nuevo);
		}
		

        // Método eliminar que quita por completo a cierto elemento de la lista
		void eliminar(T val)
        {
            // Evaluar si no hay ningún elemento en la lista
			if(root == NULL)
				return; // termina el método y así no se ejecuta el resto del código
			
            // Evaluar si el valor del primer elemento es igual al valor que se desea eliminar
			if(root->value == val)
            {
				Nodo<T>* temp = root; // se crea un apuntador variable temporal que guarda la direccion del primer elemento de la lista
				root = root->next; // el segundo elemento se convierte en el primer elemento de la lista (root)
				delete temp; // se libera la memoria dinámica del que antes era el primer elemento 
				return;
			}

			Nodo<T>* it = root; // se crea un apuntador de un elemento temporal que comienza en el primer elemento de la lista

            // Se itera mientras el iterador tenga un elemento siguiente y mientras el elemento siguiente del iterador tenga un valor distinto al que se quiere eliminar
			while( (it->next != NULL) && (it->next->value != val))  
            {
				it = it->next; // se pasa al siguiente elemento
			}

            // Si el iterador es diferente de null_ptr, significa que el valor del elemento siguiente al iterador es igual al buscado
			if(it->next != NULL)
            {
				Nodo<T>* temp = it->next; // se crea un apuntador variable temporal que guarde la direccion de elemento adelante del iterador
				it->next = temp->next; // el elemento adelante del iterador es igual al que estaba dos lugares adelante del mismo (it->next = it->next->next)
				delete temp; // se libera la memoria dinámica del elemento eliminado
			}
		}


        // Método que cuenta cuantas veces se encuentra un elemento/valor en la lista (time complexity O(n))
        int Count(T searchFor)
        {
            Nodo<T>* it = root; // se crea un apuntador de un elemento temporal que comienza en el primer elemento de la lista
            int count = 0; // contador
			
            // Se itera mientras el elemento temporal (iterador) no sea nullptr
            while(it != NULL)
            {
                // Evaluar si el valor del iterador actual es igual al buscado
				if (it->value == searchFor)
                    count++;

				it = it->next; // se continua con el siguiente elemento
			}

            return count;
        }


        // Método que libera toda la memoria dinámica de la lista (time complexity O(n))
        void DeleteList()
        {
            Nodo<T>* temp = root->next; // se crea un apuntador de un elemento temporal que comienza en el segundo elemento de la lista
            
            // Se itera mientras el elemento root no sea nullptr (cuando root sea null significa que se borró el último elemento, porque el next de este es null)
            while(root != NULL)
            {
                delete root; // borrar el que está atrás de temp
                root = temp; // ahora el primer elemento de la lista es lo que está en temp 

                // Se evalúa si root es NULL, de ser así toda la lista ha sido borrada y temp->next resulta en un segmentation fault
                if (root != NULL)
                    temp = temp->next; // temp pasa al siguiente elemento 
			}
        }

        // Método que dada una lista ordenada (orden creciente) inserta un elemento en la posición ordenada de la lista (time complexity O(n))
        void SortedInsert (T value)
        {
            Nodo<T>* nuevo = new Nodo<T>(value); // se crea de forma dinámica el elemento con el valor correspondiente
            
            // Evaluar si no hay ningún elemento en la lista
			if(root == NULL) 
            {
                root = nuevo; // se inserta en el primer lugar
                return;
            }

            // Evaluar si el elemento nuevo se insertará en la primera posición
            if(root->value >= value)
            {
                nuevo->next = root; // el siguiente de nuevo es el que actualemente es root
                root = nuevo; // nuevo se convierte en el nuevo root
                return;
            }

            Nodo<T>* temp = root; // se crea una variable apuntador temporal que comienza en el primer elemento de la lista

            // Se itera temp tenga un elemento siguiente
            while(temp->next != NULL)
            {
                // Evaluar si el elemento siguiente de temp es >= que el valor, para de ser el caso insertar a nuevo en temp
                if(temp->next->value >= value)
                {
                    nuevo->next = temp->next; // adelante de nuevo esta el elemento que es mayor o igual a nuevo
                    temp->next = nuevo; // adelante de temp está nuevo (temp)->(nuevo)->(temp->next)
                    return; // se termina el método
                }

                temp = temp->next; // se pasa al siguiente elemento
            }

            // Si el while terminó, quiere decir que se llegó al último elemento 
            temp->next = nuevo; // (se inserta al final)
        }

        // Método que elimina los duplicados de una lista ordenada (time complexity O(n))
        void RemoveDuplicates()
        {
            Nodo<T>* temp = root; // se crea una variable ptr temporal que comienza en el primer elemento de la lista

            // Se itera sobre cada elemento de la lista
            while (temp->next != NULL)
            {
                // Evaluar si el valor del elemento actual es igual al del elemento siguiente
                if(temp->value == temp->next->value)
                {
                    Nodo<T>* deleteTemp = temp->next; // se guarda el elemento a eliminar en una variable temporal
                    temp->next = temp->next->next; // el elemento siguiente de temp, es el que esta adelante del que se va a eliminar
                    delete deleteTemp; // se libera la memoria del elemento guardado en la variable temporal (el que antes estaba adelante de temp)
                }

                // Primero se evalúa que temp->next sea diferente de nulo (para evitar segmentation fault en temp->next->value)
                // Se evalúa que los valores comparados anteriormente sean diferentes para pasar al siguiente elemento (esto por si un valor esta diplicado mas de una vez)
                if ((temp->next != NULL) && (temp->value != temp->next->value))
                    temp = temp->next; // se pasa al siguiente elemento
                

                
            }   
        }

        // Método que invierte el orden de la lista (time complexity O(n))
        void Reverse()
        {
            // Evaluar si la lista esta vacía o si solo tiene un elemento 
            if((root == NULL) || (root->next == NULL))
                return; //Se termina el método

            Nodo<T>* temp = root; // se crea una variable temporal para iterar, que comienza en el primer elemento de la lista 
            Nodo<T>* originalNode = temp->next; // guarda el nodo (valor de next) actual y original de temp, para pasar al siguiente elemento de la iteración
            Nodo<T>* originalNextNode = NULL; // guarda el nodo (valor de next) original de el elemento adelante de temp

            // Se itera sobre cada elemento de la lista
            while (originalNode != NULL)
            {
                originalNextNode = originalNode->next; // se guarda el nodo (valor del next) del elemento adelante del temp (antes de ser modificado para atrás)
                originalNode->next = temp; // el elemento adelante del actual va a apuntar (tener adelante) al actual. (se modifica hacia a donde apunta lo que se guardó en NextNode)

                temp = originalNode; // se pasa al siguiente elemento
                originalNode = originalNextNode; // el nodo para pasar de elemento en la siguiente iteración, es el que se guardó antes de que cambiara en esta iteración
            }

            root->next = NULL; // root ahora es el último elemento (entoces apunta a NULL)
            root = temp; // el que antes era el último ahora es root
            
        }

};

int main()
{
    // Objeto LikedList
	LinkedList<int> ll;
    LinkedList<int> emptyList;

    // Construcción de la lista
	ll.append(2);
    ll.append(2);
    ll.append(4);
    ll.append(7);
    ll.append(8);
    ll.append(8);
    ll.append(8);
    ll.append(8);
    ll.append(9);
    ll.append(10);

    //Pruebas:

    //Contar número de 8s en la lista
    cout << "Lista: ";
    ll.imprimir();
    cout << "Número de 8s en la lista: " << ll.Count(8) << endl;
    cout << endl;

    // SortedInsert al principio, medio, y final de la lista
    cout << "Se inserta un 1 (SortedInsert) :" << endl;
    ll.SortedInsert(1);
    ll.imprimir();

    cout << "Se inserta un 6 (SortedInsert) :" << endl;
    ll.SortedInsert(6);
    ll.imprimir();

    cout << "Se inserta un 10 (SortedInsert) :" << endl;
    ll.SortedInsert(10);
	ll.imprimir();
    cout << endl;

    // Remover Duplicados
    cout << "Se eliminan los duplicados :" << endl;
    ll.RemoveDuplicates();
    ll.imprimir();
    cout << endl;

    // Invertir Orden
    cout << "Se invierte el orden de la lista :" << endl;
    ll.Reverse();
    ll.imprimir();
    cout << endl;

    //Invertir Orden Lista Vacia
    cout << "Se invierte el orden de una lista vacía :" << endl;
    emptyList.Reverse();
    emptyList.imprimir();
    cout << endl;

    // Borrar Lista
    cout << "Se borra / libera la memoria dinámica de la lista:" << endl;
    ll.DeleteList();
    ll.imprimir();

	return 0;
}
