/**
*@file main.cpp
*@brief Aplicacion que reutiliza la memoria 
*En este programa se implementa un sistema de reutilizacion de espacios en memoria para una lista enlazada
*/

#include <iostream>
#include <cstddef>
#include <list>
using namespace std;

class Collector; 

/**
*@class Node
*@brief almacenador de datos
*Almacena un valor de tipo int y un puntero al siguiente, así como los respectivos métodos
para consultar o modificar estos datos.
*/

class Node{
public:

    int valor;
    Node *siguiente;
    Node(int valor) : valor(valor), siguiente(nullptr){}
    void *operator new(std::size_t size);
    void operator delete(void *ptr, std::size_t size); 
    friend class Collector;
public:
    static Collector &collector;

};

/**
*@class Collector
*@brief Reutilizador de memoria
*Es responsable de reciclar la memoria liberada en List. Collector es implementado
mediante una lista que guarda las direcciones de memoria que han sido liberadas
*/

class Collector{
public:
    static Collector &obtenerInstancia();
    void agregar(Node *nodo);  
    std::list<Node*> lista_libre;
    Collector(){}
    Collector(const Collector&) = delete;
    Collector &operator=(const Collector&) = delete; 
    
};

Collector &Node :: collector = Collector::obtenerInstancia();


/**
*@brief asignar memoria dinaicamente
*el metodo operator new se sobrecarga para utilizar un patron
para que cada vez que se crea un nuevo objeto tipo "node" no se asigne memoria por cada creacion,
sino que se busque en una lista de nodos previamente eliminados y devolver uno si esta disponible
*@param std::size_t, indica el tamaño en bytes del objetos que se desea alojar en memoria dinamica
*@return devuelve un puntero a la memoria recien asignada
*/

void *Node::operator new(std::size_t size){
    std::list<Node*>& lista_libre = collector.lista_libre;
    if (!lista_libre.empty()){
        Node *nodo = lista_libre.front();
        lista_libre.pop_front();
        return nodo;
    }
    return ::operator new(size);
}

/**
*@brief desasignar memoria 
*Se encarga de desasignar la memoria previamente asignada por operator new
*@param un puntero que apunta al objeto que se desea liberar y su tamaño en bytes
*@return devuelve el nodo que se va a eliminara a lalista de nodos libres en el recolector de basura
no hay un return especifico para el metodo ya que lo que hace es desasignar memoria
*/


void Node::operator delete(void *puntero, std::size_t){

    std::list<Node*> &lista_libre = collector.lista_libre;
    lista_libre.push_front(static_cast<Node*>(puntero));
}

/**
*@brief obtiene la instancia unica del recolector de nodos 
*@return devuelve una referencia a la instancia del colector.
*/

Collector &Collector::obtenerInstancia(){
    static Collector instancia;
    return instancia;
}

/**
*@brief obtiene la instancia unica del recolector de nodos 
*@param nodo puntero al nodo a agregar.
*/

void Collector::agregar(Node *nodo){
    lista_libre.push_front(nodo);
}

/**
*@brief Clase que representa una lista enlazada 
*/

class List{
public:
    Node *principal;

    /**
    * 
    */
    List() : principal(nullptr){}


    void insertar(int valor);
    void consultar();
};

void List::insertar(int valor){

    Node *nodo = (Node*)malloc(sizeof(Node));

    nodo->valor = valor;
    nodo->siguiente = principal;
    principal = nodo;


}
void List::consultar(){
    if (principal!=nullptr){
        cout << "el valor del primer nodo de la lista es : " << principal->valor << endl;
    }
    else {
        cout << "La lista esta vacia" << endl;
    }
}

int main() {


    List list;
    Collector &collector = Collector::obtenerInstancia();
 

    list.insertar(1);
    list.insertar(2);
    list.insertar(3);
    list.insertar(4);

    Node *actual = list.principal;
    while (actual != nullptr)
    {
        cout<<"\n"<< actual->valor << "";
        actual = actual -> siguiente; 
    }
    cout<<std::endl;

    cout<<"\nlista libre tamaño antes de borrar: "<< collector.lista_libre.size() << endl;

    Node* nodoparaborrar = list.principal;
    list.principal = nodoparaborrar->siguiente;
    delete nodoparaborrar; 

    list.insertar(7);

    cout<<"\nlista libre tamaño despues de borrar: "<< collector.lista_libre.size() << endl;

    actual = list.principal;
    while (actual != nullptr)
    {
        cout<<"\n"<< actual->valor << "";
        actual = actual -> siguiente; 
    }
    
    Node *nuevo_nodo = new Node(5);

    nuevo_nodo->siguiente = list.principal;
    list.principal  = nuevo_nodo;

    cout<<"\n\nlista libre tamaño despues de insertar: "<< collector.lista_libre.size() << endl;

    return 0;
}
