#include <iostream>

using namespace std; 


//Creación de clase animal
class Animal
{
    public: 
        //Atributos generales del animal
        string especie; 
        int patas; 
        bool alas; 
        string sonido; 

        //Método para hacer sonido 
        void hacerSonido(){
            cout << "El animal hace " << sonido << endl; 
        }
};

//Creación de clase Perro que hereda de animal
class Perro : public Animal {
    public: 
        //Atributo específico del perro
        string nombre; 

        //Constructor con parámetros del perro --> solo usamos nombre como parámetro
        Perro(string n)
        {
            nombre = n; 
            especie = "Canino"; 
            patas = 4; 
            alas = false; 
            sonido = "guau"; 
        }

        //Método para que perro haga sonido
        void hacerSonido(){
            cout << nombre << " hace " << sonido << endl; 
        }
};

//Creación de clase gato
class Gato : public Animal {
    public: 
        //Atributo específico del gato
        string nombre; 

        //Constructor con parámetros del gato --> solo usamos nombre como parámetro
        Gato(string n)
        {
            nombre = n; 
            especie = "felino"; 
            patas = 4; 
            alas = false; 
            sonido = "miau"; 
        }

        //Método para que gato haga sonido
        void hacerSonido(){
            cout << nombre << " hace " << sonido << endl; 
        }
};


//Creación de clase Veterinario usando generics
template <class T> 
class Veterinario{
    public: 
        //Atributo específico del 
        string nombre; 

        //Constructor de veterinari@
        Veterinario(string n){
            nombre = n; 
        }

        //Método para inyectar a paciente (paciente puede ser de distintas clases)
        void inyectar(T paciente)
        {
            cout << nombre << " inyecta a " << paciente.nombre << endl; 
            paciente.hacerSonido(); 
        }
};

//Implementación
int main(){
    //Creación de perro 
    Perro fido("Fido"); 
    //Sonido perro
    fido.hacerSonido(); 

    //Creación de gato
    Gato garfield("Garfield"); 
    //Sonido gato
    garfield.hacerSonido(); 

    //Creación de veterinaria para perro
    Veterinario <Perro> ale("Alejandra"); 
    //Inyección perro
    ale.inyectar(fido); 

    //Creación de veterinaria para gato
    Veterinario <Gato> ale1("Alejandra"); 
    //Inyección gato
    ale1.inyectar(garfield); 
}