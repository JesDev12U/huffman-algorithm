#include <iostream>
#include <queue>
#include <unordered_map>
#include <fstream>
using namespace std;

class Nodo
{
public:
    char caracter;
    unsigned frecuencia;
    Nodo *izquierdo;
    Nodo *derecho;

    Nodo(char caracter, unsigned frecuencia, Nodo *izquierdo = nullptr, Nodo *derecho = nullptr)
        : caracter(caracter), frecuencia(frecuencia), izquierdo(izquierdo), derecho(derecho) {}
};

// Estructura comparar para la cola de prioridad, esto es para ordenar los nodos
struct comparar
{
    bool operator()(Nodo *l, Nodo *r)
    { // Se sobrecarga el operador () para comparar los nodos, un nodo es el primer par (l) y el otro es el segundo par (r)
        if (l->frecuencia == r->frecuencia)
        {
            // Si las frecuencias son iguales, ordenar alfabéticamente
            return l->caracter > r->caracter; // Se ordena conforme al código ASCII
        }
        // Si las frecuencias son diferentes, ordenar por frecuencia
        return l->frecuencia > r->frecuencia;
    }
};

Nodo *leerArbolHuffman(ifstream &archivoEntrada)
{
    char bit;
    archivoEntrada.get(bit);

    if (bit == '1')
    {
        char caracter;
        archivoEntrada.get(caracter);
        return new Nodo(caracter, 0);
    }

    Nodo *izquierdo = leerArbolHuffman(archivoEntrada);
    Nodo *derecho = leerArbolHuffman(archivoEntrada);

    return new Nodo('\0', 0, izquierdo, derecho);
}

void descomprimirArchivo(string nomArchivo, string nomArchivoSalida)
{
    ifstream archivoComprimido(nomArchivo, ios::in | ios::binary);
    if (!archivoComprimido.is_open())
    {
        cout << "No se pudo abrir el archivo comprimido" << endl;
        return;
    }
    Nodo *raiz = leerArbolHuffman(archivoComprimido);

    int buffer = 0;       // Buffer de bits
    int bitsEnBuffer = 0; // Cantidad de bits en el buffer
    // Lee la cantidad de bits válidos en el último byte
    int bitsValidos = 0;
    Nodo *nodoActual = raiz;
    ofstream archivoDescomprimido(nomArchivoSalida + ".txt", ios::out | ios::binary);
    while (archivoComprimido.read(reinterpret_cast<char *>(&buffer), 1))
    { // Lee un byte del archivo
        for (int i = 7; i >= 0; i--)
        {                                 // Procesa cada bit del byte
            bool bit = (buffer >> i) & 1; // Obtiene el bit en la posición i
            if (bit)
            {
                nodoActual = nodoActual->derecho;
            }
            else
            {
                nodoActual = nodoActual->izquierdo;
            }
            if (nodoActual->izquierdo == nullptr && nodoActual->derecho == nullptr)
            { // Si hemos llegado a una hoja
                // cout << nodoActual->caracter; // Imprime el caracter correspondiente a la hoja
                archivoDescomprimido << nodoActual->caracter;
                nodoActual = raiz; // Vuelve a la raíz del árbol
            }
        }
        buffer = 0; // Vacía el buffer
    }

    archivoDescomprimido.close();
    archivoComprimido.close();
}

int main(int argc, char const *argv[])
{
    string nomArchivo;
    string nomArchivoSalida;
    if(argc < 3){
        cout<<"ERROR! Debe ingresar el nombre del archivo a descomprimir y el nombre del archivo de salida"<<endl;
        return 1;
    }
    nomArchivo = argv[1];
    nomArchivoSalida = argv[2];
    descomprimirArchivo(nomArchivo, nomArchivoSalida);
    return 0;
}