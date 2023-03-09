//Librerias a utilizar
#include <iostream>
#include <cstddef>
#include <list>
using namespace std;

//Definir clase Node
class Node{
public:
    //objeto valor, que almacena el valor del nodo
    int valor;
    
    //puntero a otro objeto de tipo Node (almacena la direccion de memoria del siguiente nodo en la lista)
    Node *siguiente;

    //nuevo nodo con un "valor" y que establezca el puntero al siguiente nodo
    //se toma un valor entero y se asigna a "valor" e inicializa el puntero a null
    //el nodo que se està creando no tiene un nodo siguiente(en la lista simple)
    Node(int valor) : valor(valor), siguiente(nullptr){}
};

//Definir clase List(para implementar una lista enlazada simple)
class List{
public:
    //definir puntero principal para apuntar al primer nodo de la lista(Objeto de tipo Node)
    Node *principal;

    //constructor de la clase List
    //inicializa el puntero en un valor "null", que significa que la lista no cuenta con valores en un inicio.
    List() : principal(nullptr){}

    //Declarar el metodo de insercion para la clase List
    //Toma un "valor" definido anteriormente de tipo entero
    //tipo void porque no devuelve nada
    void insertar(int valor);
    void consultar();
};

//definicion del metodo insertar declarado en la clase llamada List{}
//el metodo toma un "valor" entero como parametro e inserta un nuevo objeto Node al inicio
void List::insertar(int valor){

    //Asignar memoria para un nuevo "Node" usando malloc, el "Node" especifica el tamaño de memoria a asignar
    Node *nodo = (Node*)malloc(sizeof(Node));

    nodo->valor = valor;
    nodo->siguiente = principal;
    principal = nodo;


}
//metodo para consultar el valor del nodo
void List::consultar(){
    if (principal!=nullptr){
        cout << "el valor del primer nodo de la lista es : " << principal->valor << endl;
    }
    else {
        cout << "La lista esta vacia" << endl;
    }
}

//Definir clase Collector
class Collector{

};

//funcion principal
int main() {

    return 0;
}