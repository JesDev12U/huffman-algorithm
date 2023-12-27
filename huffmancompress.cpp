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

Nodo *construirArbolHuffman(string texto)
{
    unordered_map<char, unsigned> mapaFrecuencias;
    for (char c : texto)
    {
        mapaFrecuencias[c]++;
    }

    priority_queue<Nodo *, vector<Nodo *>, comparar> colaPrioridad;

    for (auto par : mapaFrecuencias)
    {
        colaPrioridad.push(new Nodo(par.first, par.second));
    }

    while (colaPrioridad.size() != 1)
    {
        Nodo *izquierdo = colaPrioridad.top();
        colaPrioridad.pop();
        Nodo *derecho = colaPrioridad.top();
        colaPrioridad.pop();

        unsigned suma = izquierdo->frecuencia + derecho->frecuencia;
        colaPrioridad.push(new Nodo('\0', suma, izquierdo, derecho));
    }

    return colaPrioridad.top();
}

void escribirArbolHuffman(Nodo *raiz, ofstream &archivoComprimido)
{
    if (raiz == nullptr)
    {
        return;
    }

    if (raiz->izquierdo == nullptr && raiz->derecho == nullptr)
    {
        archivoComprimido << "1";            // Marca un nodo hoja
        archivoComprimido << raiz->caracter; // Escribe el caracter
    }
    else
    {
        archivoComprimido << "0"; // Marca un nodo interno
        escribirArbolHuffman(raiz->izquierdo, archivoComprimido);
        escribirArbolHuffman(raiz->derecho, archivoComprimido);
    }
}

void comprimirArchivo(string texto, unordered_map<char, string> &codigosHuffman, string nomArchivoSalida)
{
    ofstream archivoComprimido(nomArchivoSalida + ".huff", ios::out | ios::binary);
    if (!archivoComprimido.is_open())
    {
        cout << "No se pudo abrir el archivo comprimido" << endl;
        return;
    }
    Nodo *raiz = construirArbolHuffman(texto);
    escribirArbolHuffman(raiz, archivoComprimido);

    unsigned int buffer = 0;       // Buffer de bits
    unsigned int bitsEnBuffer = 0; // Cantidad de bits en el buffer

    for (char c : texto)
    {
        string codigo = codigosHuffman[c];
        for (char bit : codigo)
        {
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

int main(int argc, char const *argv[])
{
    string nomArchivo;
    string nomArchivoSalida;
    if(argc < 3){
        cout<<"\nERROR! Debe ingresar el nombre del archivo a comprimir y el nombre del archivo de salida\n";
        return 1;
    }
    nomArchivo = argv[1];
    nomArchivoSalida = argv[2];
    ifstream archivoEntrada(nomArchivo);
    if (!archivoEntrada.is_open())
    {
        cerr << "No se pudo abrir el archivo" << endl;
        return 1;
    }
    agregarSaltoDeLinea(nomArchivo);
    string texto;
    char ch;
    while (archivoEntrada.get(ch))
    {
        texto += ch;
    }
    archivoEntrada.close();
    unordered_map<char, string> codigosHuffman;
    Nodo *raiz = construirArbolHuffman(texto);
    imprimirCodigos(raiz, "", codigosHuffman);
    comprimirArchivo(texto, codigosHuffman, nomArchivoSalida);
    return 0;
}