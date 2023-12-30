/**
 * @file huffcodeco.cpp
 * @brief Programa de referencia para el algoritmo de compresión y descompresión de Huffman
 * @version 1.0
 * @date 2023-12-24
 * @author Jesus Antonio Lopez Bandala
 * @title Compresión y descompresión de Huffman
 * @process Este código solo sirvió para el desarrollo de los códigos huffmancompress y huffmandecompress
 * El programa recibe un archivo de texto y lo comprime, generando un archivo binario con la extensión .bin
 * También recibe un archivo binario con la extensión .bin y lo descomprime, generando un archivo de texto
 */

#include <iostream>      //Libreria de E/S
#include <queue>         //Libreria de colas, esto es para la cola de prioridad
#include <unordered_map> //Libreria de mapas sin orden, esto es para guardar los códigos de Huffman
#include <fstream>       //Libreria de archivos, esto es para leer y escribir archivos
using namespace std;     // Para no escribir std::cout, std::cin, std::endl, etc.

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

void imprimirCodigos(Nodo *raiz, string codigo, unordered_map<char, string> &codigosHuffman)
{
    if (raiz == NULL)
        return;
    if (!raiz->izquierdo && !raiz->derecho)
    {
        // Si la raiz no tiene hijos, es una hoja, por lo tanto, se guardará el código correspondiente
        codigosHuffman[raiz->caracter] = codigo;
    }
    // Recorrer el árbol de Huffman si es que aún no se ha llegado a una hoja
    // Recorremos primero el lado izquierdo (0) y después el derecho (1) hasta encontrar una hoja
    imprimirCodigos(raiz->izquierdo, codigo + "0", codigosHuffman);
    imprimirCodigos(raiz->derecho, codigo + "1", codigosHuffman);
}

// Función para construir el árbol de Huffman
Nodo *construirArbolHuffman(string texto)
{
    unordered_map<char, unsigned> mapaFrecuencias; // Mapa para guardar las frecuencias de los caracteres
    for (char c : texto)
    {
        mapaFrecuencias[c]++; // Se incrementa la frecuencia del caracter c, aqui vamos guardando las frecuencias
    }

    // Cola de prioridad para guardar los nodos del árbol de Huffman
    priority_queue<Nodo *, vector<Nodo *>, comparar> colaPrioridad;

    // Se insertan los nodos en la cola de prioridad
    for (auto par : mapaFrecuencias)
    {
        colaPrioridad.push(new Nodo(par.first, par.second));
    }

    // Se construye el árbol de Huffman
    while (colaPrioridad.size() != 1)
    {
        // Se ejecuta el algoritmo para construir el árbol de Huffman
        Nodo *izquierdo = colaPrioridad.top();
        colaPrioridad.pop();
        Nodo *derecho = colaPrioridad.top();
        colaPrioridad.pop();

        unsigned suma = izquierdo->frecuencia + derecho->frecuencia;
        colaPrioridad.push(new Nodo('\0', suma, izquierdo, derecho));
    }

    return colaPrioridad.top(); // Se regresa la raíz del árbol de Huffman
}

// Función para escribir el árbol de Huffman en el archivo comprimido
void escribirArbolHuffman(Nodo *raiz, ofstream &archivoComprimido)
{
    if (raiz == nullptr)
    {
        return;
    }

    // Si es una hoja, se escribe un 1 y el caracter
    if (raiz->izquierdo == nullptr && raiz->derecho == nullptr)
    {
        archivoComprimido << "1";            // Marca un nodo hoja
        archivoComprimido << raiz->caracter; // Escribe el caracter
    }
    // Si es un nodo interno, se escribe un 0 y se recorre el árbol hasta encontrar una hoja
    else
    {
        archivoComprimido << "0"; // Marca un nodo interno
        escribirArbolHuffman(raiz->izquierdo, archivoComprimido);
        escribirArbolHuffman(raiz->derecho, archivoComprimido);
    }
}

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

// Función para comprimir el archivo
void comprimirArchivo(string texto, unordered_map<char, string> &codigosHuffman, string nomArchivo)
{
    ofstream archivoComprimido(nomArchivo + "_compress.bin", ios::out | ios::binary);
    if (!archivoComprimido.is_open())
    {
        cout << "No se pudo abrir el archivo comprimido" << endl;
        return;
    }
    Nodo *raiz = construirArbolHuffman(texto);     // Se construye el árbol de Huffman
    escribirArbolHuffman(raiz, archivoComprimido); // Se escribe el árbol de Huffman en el archivo comprimido

    unsigned int buffer = 0;       // Buffer de bits
    unsigned int bitsEnBuffer = 0; // Cantidad de bits en el buffer

    for (char c : texto)
    {
        string codigo = codigosHuffman[c];
        for (char bit : codigo)
        {
            // Se añade el bit al buffer
            // Se desplaza el buffer un bit a la izquierda y se añade el bit
            // Esto es para que el bit más significativo sea el primero
            // Y también para que no se guarden caracteres en el archivo binario y reducir el tamaño del archivo
            buffer = (buffer << 1) | (bit - '0'); // Añade el bit al buffer
            bitsEnBuffer++;
            if (bitsEnBuffer == 8)
            {                                                                  // Si el buffer está lleno
                archivoComprimido.write(reinterpret_cast<char *>(&buffer), 1); // Escribe el buffer en el archivo
                buffer = 0;                                                    // Vacía el buffer
                bitsEnBuffer = 0;                                              // Resetea la cantidad de bits en el buffer
            }
        }
    }
    // Escribe los bits restantes en el buffer, si los hay
    if (bitsEnBuffer > 0)
    {
        buffer <<= (8 - bitsEnBuffer);                                 // Desplaza los bits al inicio del buffer
        archivoComprimido.write(reinterpret_cast<char *>(&buffer), 1); // Escribe el buffer en el archivo
    }

    archivoComprimido.close();
}

void descomprimirArchivo(string nomArchivo)
{
    ifstream archivoComprimido(nomArchivo + "_compress.bin", ios::in | ios::binary);
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
    ofstream archivoDescomprimido(nomArchivo + "_descompress.txt", ios::out | ios::binary);
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

// Función para agregar un salto de línea al final del archivo
// Esta función se realizó ya que se genera un error al leer el último caracter del archivo
// Esto es porque no hay un salto de línea al final del archivo
void agregarSaltoDeLinea(string nomArchivo)
{
    ofstream archivo(nomArchivo, ios::app); // Abre el archivo en modo de agregar
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }
    archivo << '\n'; // Agrega un salto de línea al final del archivo
    archivo.close();
}

int main()
{
    string nomArchivo;
    cout << "Ingrese el nombre del archivo a comprimir: ";
    cin >> nomArchivo;
    ifstream archivoEntrada(nomArchivo + ".txt");
    if (!archivoEntrada.is_open())
    {
        cerr << "No se pudo abrir el archivo" << endl;
        return 1;
    }
    agregarSaltoDeLinea(nomArchivo + ".txt");
    string texto;
    char ch;
    // Se lee el archivo y se guarda en la variable texto
    while (archivoEntrada.get(ch))
    {
        texto += ch;
    }
    archivoEntrada.close();
    unordered_map<char, string> codigosHuffman;
    Nodo *raiz = construirArbolHuffman(texto); // Se construye el árbol de Huffman y se le asigna su raíz
    imprimirCodigos(raiz, "", codigosHuffman); // Se imprimen los códigos de Huffman, esto para tener listos los códigos

    comprimirArchivo(texto, codigosHuffman, nomArchivo);
    descomprimirArchivo(nomArchivo);
    return 0;
}