#include <iostream>

using namespace std;


//Clase nodo
template <class T>
class Nodo{
	public:
	T value;
	Nodo *next; //Nodos simples que solamente apuntan a sucesor 
	
    //Constructor con valor 
	Nodo(T val){
		value=val;
		next=NULL;
	}
};

// Clase Linked List (simple)
template <class T>
class LinkedList{
	public:
        //Primer elemento
		Nodo<T> *root;
		
        //Constructor
		LinkedList(){
			root=NULL;
		}
		

		void append(Nodo<T> *nuevo){
			if(root==NULL){
				root=nuevo;
			}else{
				Nodo<T> *it=root;
				while(it->next!=NULL){
					it=it->next;
				}
				it->next=nuevo;
			}
		}
		
		void append(T val){
			Nodo<T> *nuevo=new Nodo<T>(val);
			this->append(nuevo);
		}
		
		void imprimir(){
			Nodo<T> *it=root;
			while(it!=NULL){
				cout<<it->value<<",";
				it=it->next;
			}
			cout<<endl;
		}
		
		void accederElemento(int i){
			int actual=0;
			Nodo<T> *it=root;
			while(it!=NULL && actual<i){
				actual++;
				it=it->next;
			}
			if(actual==i){
				cout<<it->value<<endl;
			}else{
				cout<<"no existe esa posicion"<<endl;
			}
		}
		
		void modificarElemento(int i, T val){
			int actual=0;
			Nodo<T> *it=root;
			while(it!=NULL && actual<i){
				actual++;
				it=it->next;
			}
			if(actual==i){
				it->value=val;
			}else{
				cout<<"no existe esa posicion"<<endl;
			}
		}
		
		void insert(int pos, Nodo<T> *nuevo){
			if(root==NULL){
				return;
			}
			int actual=0;
			Nodo<T> *it=root;
			if(pos==0){
				nuevo->next=root;
				root=nuevo;
				return;
			}
			while(it!=NULL && actual<pos-1){
				it=it->next;
				actual++;
			}
			if(actual==pos-1){
				nuevo->next=it->next;
				it->next=nuevo;
			}
		}
		
		void insert(int pos, T val){
			Nodo<T> *nuevo=new Nodo<T>(val);
			this->insert(pos, nuevo);
		}
		
		void eliminar(T val){
			if(root==NULL){
				return;
			}
			if(root->value==val){
				Nodo<T> *temp=root;
				root=root->next;
				delete temp;
				return;
			}
			Nodo<T> *it=root;
			while(it->next!=NULL &&it->next->value!=val){
				it=it->next;
			}
			if(it->next!=NULL){
				Nodo<T> *temp=it->next;
				it->next=temp->next;
				delete temp;
			}
		}

        /////// Métodos tarea ////////

        // Método count() 
        int count(T buscarValor)
        {
            int counter = 0; //Contador del valor
            Nodo<T> *it=root; //Iterador desde "Root"
            while(it != NULL) //Iterar en toda la lista
            {
                //Condición para ver si encontramos valor buscado
                if (it->value == buscarValor)
                {
                    //Aumentar counter
                    counter++; 
                    // Ir al siguiente elemento
                    it = it->next; 
                }
                //De no encontrar el valor buscado...
                else
                {
                    // Ir al siguiente elemento
                    it = it->next; 
                }
            }
            //Devolver contador al terminar el ciclo
            return counter;  
        }

        // Método DeleteList
        void DeleteList()
        {
            if(root==NULL){
				return;
			}
            Nodo<T> *it=root; // Iterador desde root
            Nodo<T> *aux; // Iterador auxiliar (guarda dirección del siguiente nodo)
            while (it != NULL)  //Recorrer la lista
            {
                aux = it; //Auxiliar apunta a donde it
                it = it->next; // It se va al siguiente elemento
                delete aux; //Elemento anterior a it (en donde está aux) se elimina
            }
            root = NULL; //Se establece lista vacía
            //return; 
        }

        // Método SortedInsert --> sipone que la lista está ordenada en orden creciente 
        void SortedInsert(Nodo<T> *nuevo)
        {
            if(root==NULL){ //Para lista vacía
				return;
			}
            Nodo<T> *it=root; // Iterador desde root
            Nodo<T> *aux;  //Nodo auxiliar 
            //Condición para valores menores o iguales al primero
            if (nuevo->value <= root->value) 
            {
                nuevo->next = root; //Nuevo nodo se vuelve primer elemento
                root = nuevo; //Actualizar root
                return; 
            }
            // Iterar
            while (it->next != NULL)
            {   
                aux = it; //Poner aux en donde apunta it
                it = it->next; // It va a siguiente nodo
                if (it->value >= nuevo->value) // Si el valor del nuevo nodo llega a ser mayor o igual al de it
                {
                    nuevo->next = it; // It se convierte en el siguiente de nuevo
                    aux->next = nuevo; // Nodo anterior a it ahora apunta al nuevo nodo
                    return; 
                }
            }
            // Caso en el que el valor del nuevo nodo sea mayor que todos 
            it->next = nuevo; 
        }

        void SortedInsert(T valor)
        {
            Nodo<T> *nuevo=new Nodo<T>(valor);
			this->SortedInsert(nuevo);
        }

        //Método para remover duplicados --> supone lista ordenada en orden creciente
        void RemoveDuplicates()
        {
            Nodo<T> *it = root; //Iterador desde root
            Nodo<T> *aux;  // Nodo auxiliar
            while (it->next != NULL) // Iterar en la lista
            {
                // Se hace de esta manera por si existen varios duplicados
                // Cuando los valores sean diferentes
                if (aux->value != it->value) // Si siguen duplicados, necesitamos que no se muevan aux ni it
                {
                    aux = it;  //mover aux a donde está it
                    it = it -> next; // hacer que it avance al siguiente
                }
                // Cuando los valores sean iguales
                else
                {
                    Nodo<T> *temp = it; //Temporal a donde está it actualmente
                    it = it->next; // It se va al siguiente elemento
                    aux->next = it; // Aux apunta al nuevo it
                    delete temp; // Se elimina el temporal
                }
            }
            // Caso de que los duplicados estén al final de la lista
            if (aux->value == it->value)
            {
                delete it; 
                aux->next = NULL; 
            }
            
        }

        // Método para reorganizar en reversa los elementos de una lista
        void Reverse()
        {
            Nodo<T> *it = root; // Iterador 
            Nodo<T> *aux1 = it; // Nodos auxiliares que empiezan en mismo lugar que it
            Nodo<T> *aux2 = it; 
            if (root == NULL || root->next == NULL) // Para lista vacía o lista de un solo elemento
            {
                return; 
            }
            it = it->next; // It se va a la siguiente posición 
            while (it != NULL)
            {  
                aux1 = it; //Mover un auxiliar a la posición actual de it
                if (aux2 == root) // Si aux 2 se encuentra en el primer elemento, cambiar
                {
                    aux2->next = NULL; // ahora no tiene siguiente elemento
                } 
                if (it->next==NULL) // Si llegamos al último elemento
                { 
                    it->next = aux2; // apuntar al de atrás 
                    root = it; // se vuelve primer elemento 
                    return; 
                }
                else // mientras no llegue a último elemento
                {
                    it = it->next; // it se mueve otra vez al siguiente elemento 
                }
                aux1->next = aux2; // elemento entre it y aux 2 apunta a aux 2
                aux2 = aux1; // aux2 se mueve a donde está aux1
            }
            
        }
};

int main(){
	/*LinkedList<int> ll;
	ll.append(5);
	ll.append(5);
	ll.append(6);
    ll.append(8); 
    ll.append(5); 
    ll.append(6); 
    ll.append(5);
    ll.imprimir();
    //cout << ll.count(5) << endl; 
    //ll.eliminar(8); 
    ll.DeleteList(); 
    ll.imprimir();  
    ll.append(11);
	ll.append(4);
	ll.append(11);
	ll.append(15);
	ll.imprimir();*/
    
    LinkedList<int> li;
    li.append(1); 
    li.append(1); 
    li.append(5); 
    li.append(8); 
    li.append(8); 
    li.append(8); 
    li.append(10); 
    //li.append(10); 
    li.SortedInsert(9); 
    li.imprimir();
    li.RemoveDuplicates(); 
    li.imprimir(); 
    li.Reverse(); 
    li.imprimir(); 

    LinkedList<int> l; 
    l.Reverse(); 
    l.imprimir(); 
    l.append(3);
    l.Reverse(); 
    l.imprimir();
    l.append(5); 
    l.Reverse(); 
    l.imprimir(); 
	/*ll.eliminar(4);
	ll.imprimir();
	ll.eliminar(5);
	ll.imprimir();
	ll.eliminar(15);
	ll.imprimir();*/
	
	
	return 0;
}
