//los metodos no se documentan en doxygen a nivel de implementacion, se debe documentar en la declaracion de la clase :)

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
*@brief esta clase representa un nodo en una lista
*/

class Node{
public:
    /**
     * @brief el valor almacenado en el nodo
    */
    int valor;

    /**
     * @brief un puntero al siguiente nodo en la lista
    */
    Node *siguiente;

    /**
    * @brief Constructor del nodo 
    * @param valor El valor a almacenar en el nodo
    */
    Node(int valor) : valor(valor), siguiente(nullptr){}

    /**
     * @brief operador sobrecargado "new" para almacenador nodos de la lista libre
     * @param size El tamaño del nodo a almacenar
     * @return Un puntero al nodo almacenado
    */
    void *operator new(std::size_t size);

    /**
     * @brief operador sobrecargado "delete" para liberar nodos de lista_libre.
    */
    void operator delete(void *ptr, std::size_t size); 

    /**
     * @brief Una clase amigo para poder acceder a collector para almacenar y liberar nodos
    */
    friend class Collector;

public:

    /**
     * @brief una referencia estatica al collector.
    */
    static Collector &collector;

};

/**
*@class Collector
*@brief esta clase es un recolector que maneja la asignacion y desasignacion de nodos
*/

class Collector{
public:

    /**
     * @brief devuelve la instancia singleton del collector.
    */
    static Collector &obtenerInstancia();

    /**
     * @brief Agrega un nodo a la lista libre para rehusar
     * @param nodo a un puntero al nodo para agregar
    */
    void agregar(Node *nodo);

    /**
     *@brief la lista de nodos que podrian ser reutilizados  
    */  
    std::list<Node*> lista_libre;

    /**
     * @brief el constructor predeterminado del collector
    */
    Collector(){}

    /**
     * @brief copiar el constructor eliminado para garantizar que solo hay una instancia de collector
    */
    Collector(const Collector&) = delete;
    Collector &operator=(const Collector&) = delete; 
    
};

Collector &Node :: collector = Collector::obtenerInstancia();


/**
*@brief metodo sobrecargado operator new para almacenar nodos de la lista libre
*@param size el tamaño del nodo a almacenar
*@return devuelve un puntero al noodo almacenado
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
*@brief metodo sobrecargado operator delete para liberar nodos de lista_libre
*@param puntero Un puntero al nodo por liberar.
*@return size El tamaño del nodo a liberar
*/
void Node::operator delete(void *puntero, std::size_t){

    std::list<Node*> &lista_libre = collector.lista_libre;
    lista_libre.push_front(static_cast<Node*>(puntero));
}

/**
*@brief obtiene la instancia unica del recolector de nodos 
*@return devuelve una referencia a la instancia de la clase Collector.
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
*@brief Clase que implementa una lista enlazada para almacenar objetos de tipo Node. 
*/
class List{
public:

    /**
     * @brief El primer nodo de la lista enlazada
    */
    Node *principal;

    /**
    * @brief Construye un objeto lista vacio.
    */
    List() : principal(nullptr){}

    /**
     * @brief Inserta un nuevo Node con el valor dado al inicio de la lista.
     * @param valor el valor a almacenar en el nuevo nodo
    */

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

/**
 * @brief entrada del programa
 * 
 * Esta funcion main crea una nueva "lsta" de tipo List, inserta nodos con valores enteros
 * imprime la lista en su estado actual haciendo uso de un bucle While, borra un nodo e inserta otro
 * hace uso de la clase Collector para administar la asignacion y desasignacion de memoria de los objetos tipo Node
 * ademas, imprime tambien el valor  de lista_libre, donde se ejemplifica que al borrar un nodo la lista
 * tendra un valor de 1, y al crear otro y almacenarlo en esa posicion, se reutiliza ese espacio
 * y ahora la lista libre contara con un valor de 0.
 * 
 * @return 0 cuando el programa se ejecuta de manera correcta :)
*/

int main() {

    List lista;
    Collector &collector = Collector::obtenerInstancia();
 
    lista.insertar(1);
    lista.insertar(2);
    lista.insertar(3);
    lista.insertar(4);

    Node *actual = lista.principal;
    while (actual != nullptr)
    {
        cout<<"\n"<< actual->valor << "";
        actual = actual -> siguiente; 
    }
    cout<<std::endl;

    cout<<"\nlista libre tamaño antes de borrar: "<< collector.lista_libre.size() << endl;

    Node* nodoparaborrar = lista.principal;
    lista.principal = nodoparaborrar->siguiente;
    delete nodoparaborrar; 

    lista.insertar(7);

    cout<<"\nlista libre tamaño despues de borrar: "<< collector.lista_libre.size() << endl;

    actual = lista.principal;
    while (actual != nullptr)
    {
        cout<<"\n"<< actual->valor << "";
        actual = actual -> siguiente; 
    }
    
    Node *nuevo_nodo = new Node(5);
    nuevo_nodo->siguiente = lista.principal;
    lista.principal  = nuevo_nodo;

    cout<<"\n\nlista libre tamaño despues de insertar: "<< collector.lista_libre.size() << endl;

    return 0;
}
