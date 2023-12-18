/**
 * @file huffman.cpp
 * @brief Implementación del algoritmo de compresión de Huffman
 * @version 1.0
 * @date 2023-12-17
 * @author Jesus Antonio Lopez Bandala
 * @title Compresión de Huffman
*/

#include <queue> //Libreria para usar la cola de prioridad
#include <vector> //Libreria para usar vectores que nos ayudarán para la cola de prioridad
#include <map> //Mapas para recopilar los códigos de Huffman
#include <iostream> //Libreria para usar cout y cin
#include <fstream> //Libreria para usar archivos
#include <conio.h> //Libreria para usar getch()

using namespace std; //Para no usar std::cout o std::cin

// Clase Nodo para el árbol de Huffman
class Nodo
{
public:
    char caracter; // Caracter del nodo
    int frecuencia; // Frecuencia del caracter
    Nodo *izquierdo; // Nodo izquierdo
    Nodo *derecho; // Nodo derecho

    // Constructor para inicializar el nodo
    Nodo(char caracter, int frecuencia)
    {
        this->caracter = caracter;
        this->frecuencia = frecuencia;
        this->izquierdo = NULL;
        this->derecho = NULL;
    }
};

// Estructura comparar para la cola de prioridad, esto es para ordenar los nodos
struct comparar {
    bool operator()(Nodo* l, Nodo* r) { // Se sobrecarga el operador () para comparar los nodos, un nodo es el primer par (l) y el otro es el segundo par (r)
        if (l->frecuencia == r->frecuencia) {
            // Si las frecuencias son iguales, ordenar alfabéticamente
            return l->caracter > r->caracter; // Se ordena conforme al código ASCII
        }
        // Si las frecuencias son diferentes, ordenar por frecuencia
        return l->frecuencia > r->frecuencia;
    }
};

// Clase Huffman
class Huffman
{
private:
    Nodo *raiz; // Raíz del árbol de Huffman
    map<char, string> huffmanCode; // Mapa para almacenar los códigos de Huffman

    // Método para codificar el árbol de Huffman
    void codificar(Nodo *raiz, string str)
    {
        // Si la raiz es nula, regresar
        if (raiz == NULL)
            return;
        if (!raiz->izquierdo && !raiz->derecho)
        {
            // Si la raiz no tiene hijos, es una hoja, por lo tanto, se guardará el código correspondiente
            huffmanCode[raiz->caracter] = str;
        }
        // Recorrer el árbol de Huffman si es que aún no se ha llegado a una hoja
        // Recorremos primero el lado izquierdo (0) y después el derecho (1) hasta encontrar una hoja
        codificar(raiz->izquierdo, str + "0");
        codificar(raiz->derecho, str + "1");
    }

public:

    // Método para imprimir la cola de prioridad, esto sirve para visualizar si la cola de prioridad se está ordenando correctamente
    void imprimirColaPrioridad(priority_queue<Nodo *, vector<Nodo *>, comparar> pq)
    {
        priority_queue<Nodo *, vector<Nodo *>, comparar> temp = pq; // Copia de la cola para no alterar la original
        cout << "Cola de Prioridad:\n";
        // Imprimir la cola de prioridad
        while (!temp.empty()) // Mientras la cola no esté vacía
        {
            // Obtener el nodo de la cima de la cola
            Nodo *nodo = temp.top();
            cout << nodo->caracter << " (" << nodo->frecuencia << ") "; // Imprimir el caracter y la frecuencia
            temp.pop(); // Eliminar el nodo de la cima de la cola, esto para irla recorriendo
        }
        cout << "\n";
    }

    // Constructor para construir el árbol de Huffman
    Huffman(string texto)
    {
        map<char, int> frecuencia; // Mapa para almacenar la frecuencia de cada caracter
        for (char ch : texto) // Recorrer el texto
        {
            frecuencia[ch]++; // Incrementar la frecuencia del caracter en 1, si encuentra el mismo caracter, se incrementará su frecuencia
        }

        priority_queue<Nodo *, vector<Nodo *>, comparar> pq; // Cola de prioridad para ordenar los nodos
        for (auto pair : frecuencia) // Recorrer el mapa de frecuencias
        {
            pq.push(new Nodo(pair.first, pair.second)); // Insertar el caracter y su frecuencia en la cola de prioridad, respetando el orden definido en la estructura comparar
        }

        imprimirColaPrioridad(pq); // Llamada al método para imprimir la cola de prioridad

        while (pq.size() > 1) // Mientras la cola de prioridad tenga más de un elemento, esto es para construir el árbol de Huffman
        {
            Nodo *izquierdo = pq.top(); // Obtener el nodo de la cima de la cola
            pq.pop(); // Eliminar el nodo de la cima de la cola, esto para irla recorriendo
            Nodo *derecho = pq.top(); // Obtener el nodo de la cima de la cola
            pq.pop(); // Eliminar el nodo de la cima de la cola, esto para irla recorriendo
            int sum = izquierdo->frecuencia + derecho->frecuencia; // Sumar las frecuencias de los nodos
            Nodo *nuevo = new Nodo('\0', sum); // Crear un nuevo nodo con el caracter nulo y la suma de las frecuencias
            nuevo->izquierdo = izquierdo; // Asignar la parte izquierda del nuevo nodo a el primer nodo que recuperamos de la cola de prioridad
            nuevo->derecho = derecho; // Asignar la parte derecha del nuevo nodo a el segundo nodo que recuperamos de la cola de prioridad
            pq.push(nuevo); // Insertar el nuevo nodo en la cola de prioridad
        }

        raiz = pq.top(); // Obtener el nodo de la cima de la cola, este será la raíz del árbol de Huffman
        codificar(raiz, ""); // Llamada al método para codificar el árbol de Huffman
    }

    map<char, string> getHuffmanCode() // Método para obtener el mapa de códigos de Huffman
    {
        return huffmanCode;
    }
    Nodo *getRaiz() // Método para obtener la raíz del árbol de Huffman
    {
        return raiz;
    }

    void imprimirArbol(Nodo *raiz, int cont = 0) // Método para imprimir el árbol de Huffman
    {
        /*
        * La variable cont en esta función se utiliza para rastrear y controlar la profundidad del nodo actual en el árbol Huffman mientras 
        se imprime. Esta variable mantiene un registro del nivel del nodo en el árbol para que la impresión refleje correctamente 
        la estructura jerárquica del árbol.

        * El propósito principal de cont es controlar la cantidad de tabulaciones o espacios que se imprimen antes de cada nodo para 
        representar visualmente su nivel o profundidad en el árbol.
        */
        if (raiz == NULL)
            return;

        imprimirArbol(raiz->derecho, cont + 1);
        for (int i = 0; i < cont; i++)
            cout << "\t";
        cout << raiz->caracter << " (" << raiz->frecuencia << ")\n";

        imprimirArbol(raiz->izquierdo, cont + 1); // Recorrer el árbol de Huffman si es que aún no se ha llegado a una hoja
    }
};

void codDecodText(string texto)
{
    Huffman huffman(texto); // Crear un objeto de la clase Huffman
    map<char, string> huffmanCode = huffman.getHuffmanCode(); // Obtener el mapa de códigos de Huffman

    cout << "Codificacion de Huffman:\n";
    string strEncoded;
    map<char, bool> caracteresImpresos; // Mapa para almacenar los caracteres ya impresos
    for (char ch : texto) // Recorrer el texto
    {
        // Concatenar el código de Huffman de cada caracter
        strEncoded += huffmanCode[ch];
        // Verificar si el carácter ya ha sido impreso
        if (caracteresImpresos.find(ch) == caracteresImpresos.end()) { // verifica si la busqueda del caracter ch en el mapa 
                                                                        // caracteresImpresos es igual al final del mapa, si es así, 
                                                                        //significa que no se encontró el caracter, por lo tanto debe 
                                                                        //imprimirse
            // Si no ha sido impreso, imprimir el carácter y su código de Huffman
            cout << ch << ": " << huffmanCode[ch] << "\n";
            // Marcar el carácter como impreso en el mapa
            caracteresImpresos[ch] = true; // Para que find() no devuelva el final del mapa
        }
    }

    cout << "Texto codificado: " << strEncoded << "\n";

    string strDecoded;
    Nodo *nodo = huffman.getRaiz(); // Obtener la raíz del árbol de Huffman
    for (char bit : strEncoded) // Recorrer el texto codificado
    {
        if (bit == '0') // Si el bit es 0, ir al nodo izquierdo
        {
            nodo = nodo->izquierdo;
        }
        else // Si el bit es 1, ir al nodo derecho
        {
            nodo = nodo->derecho;
        }
        // Comprobar si el nodo es una hoja
        if (nodo->izquierdo == NULL && nodo->derecho == NULL)
        {
            // Concatenar el caracter del nodo
            strDecoded += nodo->caracter;
            nodo = huffman.getRaiz(); // Reiniciar desde la raíz para el próximo bit
        }
    }

    cout << "Texto decodificado: " << strDecoded << "\n";
    long long bitsEnconded = strEncoded.size(); // Obtener el tamaño del texto codificado
    long long bitsDecoded = strDecoded.size() * 8; // Obtener el tamaño del texto decodificado, recordando que cada caracter son 8 bits
    cout << "Bits codificados: " << bitsEnconded << "\n";
    cout << "Bits decodificados: " << bitsDecoded << "\n";
    cout << "\n\nArbol de Huffman:\n";
    huffman.imprimirArbol(huffman.getRaiz());
    cout << endl
         << endl;
    cout << "Press any key to continue...";
    getch(); // Pausar el programa hasta que se presione una tecla
}

void codDecodTxt() //El proceso que hace esta función es casi igual al metodo codDecodText, la diferencia es que esta función lee un archivo de texto
{
    string nombreArchivo = "";
    cout << "Introduce el nombre del archivo: ";
    fflush(stdin);
    getline(cin, nombreArchivo);
    ifstream archivo; // Crear un objeto de la clase ifstream para leer el archivo
    archivo.open(nombreArchivo, ios::in); // Abrir el archivo
    if (!archivo) // Comprobar si el archivo se pudo abrir
    {
        cerr << "No se pudo abrir el archivo";
        return;
    }
    string texto;
    string linea;
    while (getline(archivo, linea)) // Leer el archivo línea por línea
    {
        texto += linea; // Concatenar las líneas del archivo
    }
    codDecodText(texto); // Llamada al método para codificar y decodificar el texto
}

int main()
{
    bool seguir = true;
    do
    {
        int opcion = 0;
        // cls
        cout << "\033[2J\033[1;1H"; // Limpiar la pantalla, útil para sistemas UNIX
        cout << "\nMENU\n";
        cout << "\n\n1. Codificar/Decodificar texto";
        cout << "\n2. Codificar/Decodificar archivo";
        cout << "\n3. Salir\n";
        cout << "\nTeclee una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
        {
            string texto;
            cout << "\nIntroduce el texto: ";
            fflush(stdin);
            getline(cin, texto);
            codDecodText(texto); // Llamada al método para codificar y decodificar el texto
            break;
        }
        case 2:
        {
            codDecodTxt(); // Llamada al método para codificar y decodificar el texto de un archivo
            break;
        }
        case 3:
        {
            seguir = false;
            break;
        }
        default:
        {
            cout << "\nOpcion no valida...";
        }
        }
    } while (seguir);
    cout << endl
         << endl;
    cout << "Press any key to continue...";
    getch(); // Pausar el programa hasta que se presione una tecla
    return 0;
}