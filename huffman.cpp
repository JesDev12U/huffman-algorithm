#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<char, int>> ordenarPorFrecuencia(map<char, int> frecuencias) {
    vector<pair<char, int>> vec(frecuencias.begin(), frecuencias.end());
    sort(vec.begin(), vec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        return a.second < b.second;
    });
    return vec;
}

map<char, int> contar_frecuencias(string texto){
    map<char, int> frecuencias;
    for (int i = 0; i < texto.size(); i++){
        if (frecuencias.find(texto[i]) == frecuencias.end()){
            frecuencias[texto[i]] = 1;
        }else{
            frecuencias[texto[i]]++;
        }
    }
    return frecuencias;
}

class Nodo{
    public:
        char letra;
        int frecuencia;
        Nodo* izq;
        Nodo* der;
        Nodo(char letra, int frecuencia){
            this->letra = letra;
            this->frecuencia = frecuencia;
            this->izq = NULL;
            this->der = NULL;
        }
        Nodo(char letra){
            this->letra = letra;
            this->frecuencia = 1;
            this->izq = NULL;
            this->der = NULL;
        }
        Nodo(int frecuencia){
            this->letra = NULL;
            this->frecuencia = frecuencia;
            this->izq = NULL;
            this->der = NULL;
        }
};

class Lista{
    public:
        Nodo* inicio;
        Lista(){
            this->inicio = NULL;
        }
        void insertar(Nodo* nuevo){
            if (inicio == NULL){
                inicio = nuevo;
            }else{
                Nodo* aux = inicio;
                while (aux->der != NULL){
                    aux = aux->der;
                }
                aux->der = nuevo;
                nuevo->izq = aux;
            }
        }
        void imprimir(){
            Nodo* aux = inicio;
            while (aux != NULL){
                cout << aux->letra << " " << aux->frecuencia << endl;
                aux = aux->der;
            }
        }
};

class ArbolHuffman{
    public:
        Nodo* raiz;
        ArbolHuffman(){
            this->raiz = NULL;
        }
        void construirArbol(Lista lista){
            while (lista.inicio->der != NULL){
                Nodo* nuevo = new Nodo(lista.inicio->frecuencia + lista.inicio->der->frecuencia);
                nuevo->izq = lista.inicio;
                nuevo->der = lista.inicio->der;
                lista.inicio->der->der->izq = nuevo;
                lista.inicio = lista.inicio->der->der;
            }
            raiz = lista.inicio;
        }

        // void imprimirArbol(Nodo* raiz){
        //     if (raiz != NULL){
        //         cout << "NULL  "<< raiz->frecuencia << endl;
        //         imprimirArbol(raiz->izq);
        //         imprimirArbol(raiz->der);
        //     }
        // }
};

int main() {
    string texto = "laptop";
    //Haz el diccionario ordenado por frecuencias
    map<char, int> frecuencias = contar_frecuencias(texto);
    vector<pair<char, int>> ordenado = ordenarPorFrecuencia(frecuencias);
    // //Imprime el diccionario ordenado por frecuencias
    // for (auto i : ordenado){
    //     cout << i.first << " " << i.second << endl;
    // }
    //Crea la lista de nodos
    Lista lista;
    for (auto i : ordenado){
        Nodo* nuevo = new Nodo(i.first, i.second);
        lista.insertar(nuevo);
    }
    lista.imprimir();
    
    ArbolHuffman arbol;
    arbol.construirArbol(lista);
    //arbol.imprimirArbol(arbol.raiz);
    return 0;
}