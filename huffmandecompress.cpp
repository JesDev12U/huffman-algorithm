/**
 * @file huffmandecompress.cpp
 * @brief Descompresión de un archivo binario .huff con el algoritmo de Huffman
 * @version 1.0
 * @date 2023-12-26
 * @author Jesus Antonio Lopez Bandala
 * @title Descompresión de un archivo binario .huff con el algoritmo de Huffman
 * @procedure El programa recibe como parámetro el nombre del archivo a descomprimir y el nombre del archivo
 * de salida, después lee el archivo binario .huff y construye el árbol de Huffman, posteriormente,
 * descomprime el archivo y lo guarda en un archivo de texto, para poderse descomprimir lee la estructura
 * del árbol de Huffman anteriormente guardado en el archivo comprimido y los bits del archivo comprimido
 * Este código tiene que ser compilado para poderse usar con la aplicación web
 */

#include <iostream>      // Librería para entrada y salida de datos
#include <queue>         // Librería para la cola de prioridad
#include <unordered_map> // Librería para el mapa de frecuencias
#include <fstream>       // Librería para leer y escribir archivos
using namespace std;     // Para no escribir std::cout, std::endl, etc.

// Clase Nodo para el árbol de Huffman
class Nodo
{
public:
    char caracter;       // Caracter del nodo
    unsigned frecuencia; // Frecuencia del caracter
    Nodo *izquierdo;     // Puntero al hijo izquierdo
    Nodo *derecho;       // Puntero al hijo derecho

    // Constructor de la clase Nodo
    // Este es un constructor con parámetros por defecto, esto es para que no sea necesario pasar los hijos
    // al crear un nodo, ya que al crear un nodo hoja, no tiene hijos
    // También es un constructor con lista de inicialización, esto es para inicializar los atributos de la clase
    // También para no utilizar this->atributo = atributo
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

// Función para leer el árbol de Huffman del archivo comprimido
// La estructura de un archivo comprimido es la siguiente:
// 1. El árbol de Huffman
// 2. El texto comprimido
// Ejemplo:
// 001o1s001a1l01
// Donde 0 es un nodo interno y 1 es un nodo hoja
// Y las letras son los caracteres de las hojas
Nodo *leerArbolHuffman(ifstream &archivoEntrada)
{
    char bit;                // Variable para leer los bits del archivo
    archivoEntrada.get(bit); // Lee un bit del archivo

    // Si el bit es 1, se crea un nodo hoja
    if (bit == '1')
    {
        char caracter;
        archivoEntrada.get(caracter);
        // Se regresa un nodo hoja, esto es para que se pueda construir el árbol de Huffman
        return new Nodo(caracter, 0);
    }

    // Si el bit es 0, se crea un nodo interno
    // Todo nodo interno tiene dos hijos, por lo tanto, se llama recursivamente a la función
    Nodo *izquierdo = leerArbolHuffman(archivoEntrada);
    Nodo *derecho = leerArbolHuffman(archivoEntrada);

    // Se regresa un nodo interno, esto es para que se pueda construir el árbol de Huffman
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
    Nodo *raiz = leerArbolHuffman(archivoComprimido); // Deciframos la esructura del árbol de Huffman que fue
                                                      // guardada en el archivo comprimido

    int buffer = 0;       // Buffer de bits
    int bitsEnBuffer = 0; // Cantidad de bits en el buffer
    // Lee la cantidad de bits válidos en el último byte
    int bitsValidos = 0;
    Nodo *nodoActual = raiz; // Nodo actual, esto es para decodificar el texto comprimido
    ofstream archivoDescomprimido(nomArchivoSalida + ".txt", ios::out | ios::binary);
    while (archivoComprimido.read(reinterpret_cast<char *>(&buffer), 1))
    { // Lee un byte del archivo
        for (int i = 7; i >= 0; i--)
        {                                 // Procesa cada bit del byte
            bool bit = (buffer >> i) & 1; // Obtiene el bit en la posición i
            if (bit)                      // Si el bit es 1, se recorre el lado derecho del árbol
            {
                nodoActual = nodoActual->derecho;
            }
            else // Si el bit es 0, se recorre el lado izquierdo del árbol
            {
                nodoActual = nodoActual->izquierdo;
            }
            if (nodoActual->izquierdo == nullptr && nodoActual->derecho == nullptr)
            { // Si hemos llegado a una hoja
                // cout << nodoActual->caracter; // Imprime el caracter correspondiente a la hoja
                archivoDescomprimido << nodoActual->caracter; // Escribe el caracter en el archivo descomprimido
                nodoActual = raiz;                            // Vuelve a la raíz del árbol, esto para decodificar el siguiente caracter
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
    if (argc < 3)
    {
        cout << "ERROR! Debe ingresar el nombre del archivo a descomprimir y el nombre del archivo de salida" << endl;
        return 1;
    }
    nomArchivo = argv[1];
    nomArchivoSalida = argv[2];
    descomprimirArchivo(nomArchivo, nomArchivoSalida);
    return 0;
}