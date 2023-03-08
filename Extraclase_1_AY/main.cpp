//Librerias a utilizar
#include <iostream>
#include <cstddef>
#include <list>

//Definir clase Node
class Node{
public:
    //objeto valor, que almacena el valor del nodo
    int valor;
    
    //puntero a otro objeto de tipo Node (almacena la direccion de memoria del siguiente nodo en la lista)
    Node *siguiente;
}

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
    void insertar(int valor)
}

//definicion del metodo insertar declarado en la clase llamada List{}
//el metodo toma un "valor" entero como parametro e inserta un nuevo objeto Node al inicio
void List::insertar(int valor){

    //Asignar memoria para un nuevo "Node" usando malloc, el "Node" especifica el tamaño de memoria a asignar
    Node *nodo = (Node*)malloc(sizeof(Node));

    nodo->valor = valor;
    nodo->siguiente = principal;
    head = nodo;


}


//Definir clase Collector
class Collector{

}

//funcion principal
int main() {
    return 0;
}