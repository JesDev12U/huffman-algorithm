//Codigo explicativo de la cola de prioridad en C++
//Complejidad del algoritmo: O(log n)
//Heap -> Arbol binario completo
//Encontrar al maximo o al minimo en O(1)
//Insertar en O(log n)
//Eliminar en O(log n)
//La altura es de log n

/*La cola de prioridad es basicamente un monticulo (heap) que nos permite tener un arbol binario
representado con un arreglo, lo que nos permite C++ es la eficiencia para hacer eso ya que si nosotros
lo hicieramos de forma manual todo, la complejidad podria ser de O(n^2)*/
#include <iostream>
#include <queue>

using namespace std;

struct comparador{
    //int& se refiere a unos alias
    bool operator()(const int& a, const int& b){
        return a > b;
    }
};

int main()
{
    //Asignamos un comparador para que la cola de prioridad sea minima
    //Podemos hacer el comparador que nosotros queramos
    priority_queue<int, vector<int>, comparador> pq;
    pq.push(-1);
    pq.push(2);
    pq.push(1);
    pq.push(5);
    pq.push(7);
    pq.push(8);
    pq.push(9);
    pq.pop();

    cout<<pq.empty()<<endl; //Regresa un binario si esta vacio o no
    cout<<pq.size()<<endl; //Regresa el tamaño de la cola de prioridad
    cout<<pq.top()<<endl;

    //Imprimir todos los elementos de la cola de prioridad
    // while(!pq.empty()){
    //     cout<<pq.top()<<endl;
    //     pq.pop();
    // }
    return 0;
}