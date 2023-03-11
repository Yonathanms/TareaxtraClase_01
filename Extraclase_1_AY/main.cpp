#include <iostream>
#include <cstddef>
#include <list>
using namespace std;

class Collector; 

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

void *Node::operator new(std::size_t size){
    std::list<Node*>& lista_libre = collector.lista_libre;
    if (!lista_libre.empty()){
        Node *nodo = lista_libre.front();
        lista_libre.pop_front();
        return nodo;
    }
    return ::operator new(size);
}

void Node::operator delete(void *puntero, std::size_t){

    std::list<Node*> &lista_libre = collector.lista_libre;
    lista_libre.push_front(static_cast<Node*>(puntero));
}

Collector &Collector::obtenerInstancia(){
    static Collector instancia;
    return instancia;
}

void Collector::agregar(Node *nodo){
    lista_libre.push_front(nodo);
}

class List{
public:
    Node *principal;

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
 

    list.insertar(1);
    list.insertar(2);
    list.insertar(3);

    Node *actual = list.principal;
    while (actual != nullptr)
    {
        cout<<"\n"<< actual->valor << "";
        actual = actual -> siguiente; 
    }
    cout<<std::endl;

    Node* nodoparaborrar = list.principal;
    list.principal = nodoparaborrar->siguiente;
    delete nodoparaborrar; 

    list.insertar(4);

    actual = list.principal;
    while (actual != nullptr)
    {
        cout<<"\n"<< actual->valor << "";
        actual = actual -> siguiente; 
    }
    
    std :: cout << std::endl;
    return 0;
}
