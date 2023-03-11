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

    void *operator new(std::size_t tamano);
    void operator delete(void *puntero, std::size_t tamano); 

    friend class Collector;
private: 
    static Collector& collector;

};

Collector& Node::collector = Collector::obtenerInstancia();

void *Node::operator new(std::size_t tamano){
    std::list<Node*> lista_libre = collector.lista_libre;
    if (!lista_libre.empty()){
        Node *nodo = lista_libre.front();
        lista_libre.pop_front();
        return nodo;
    }
    return operator new(tamano)
}

void Node::operator delete(void *puntero, std::size_t tamano){

    std::list<Node*> *lista_libre = collector.lista_libre;
    lista_libre->push_front(static_cast<Node*>(puntero));
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
public:
//llamada a obtenerInstancia(), devuelve una referencia a la instancia unica
    static Collector &obtenerInstancia();

//llamada a la funcion para agregar un nodo a la lista_libre
    void agregar(Node *nodo);

//privado para que solo se pueda acceder desde la clase collector y no se vaya a hacer un desmadre
private:

//definicion de la lista_libre, para almacenar nodos que puedan ser reutilizados en un futuro
//lista_libre almacena los nodos eliminados de la lista, mas no de memoria, toma un puntero a un nodo como parametro
    std::list<Node*> lista_libre;

//Constructor de la clase collector(esta linea podria no estar aqui, nada mas se hace para que no se creen instancias desde fuera)


};

//metodos para la clase collector 

//Funcion obtenerInstancia: DEvuelve una referencia a la instancia unica de la clase llamada Collector
//La clase se crea como una variable estatica local dentro de la funcion y se devuelve a cada llamada
//Con la unica llamada se asegura que solo exista una instancia de la clase dentro del programa :3 

Collector &Collector::obtenerInstancia(){
    static Collector instancia;
    return instancia;
}

//Funcion agregar: agrega un nodo a la lista_libre. Nada mas agrega un nodo al inicio de la lista_libre
//definida en class collector. usando "push_front" que se utiliza para manipular elementos de la lista
void Collector::agregar(Node *nodo){
    lista_libre.push_front(nodo);
}



//funcion principal
int main() {


    List list;
    Collector& Collector = Collector::obtenerInstancia();

    //pruebas: se insertan nodos 
    list.insertar(1);
    list.insertar(2);
    list.insertar(3);

    //printea elementos de la lista
    Node *actual = list.principal;
    while (actual != nullptr)
    {
        cout<<"\n"<< actual->valor << "";
        actual = actual -> siguiente; 
    }
    cout<<std::endl;

    //Eliminar nodo del inicio
    Node* nodoparaborrar = list.principal;
    list.principal = nodoparaborrar->siguiente;
    Collector.agregar(nodoparaborrar);

    //se inserta otro nodo y se elimina el inicial
    list.insertar(4);

    //prints de los elementos de la lista :)
    actual = list.principal;
    while (actual != nullptr)
    {
        cout<<"\n"<< actual->valor << "";
        actual = actual -> siguiente; 
    }
    
    
    return 0;
}
