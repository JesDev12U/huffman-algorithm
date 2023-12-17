#include <queue>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

class Nodo
{
public:
    char caracter;
    int frecuencia;
    Nodo *izquierdo;
    Nodo *derecho;

    Nodo(char caracter, int frecuencia)
    {
        this->caracter = caracter;
        this->frecuencia = frecuencia;
        this->izquierdo = NULL;
        this->derecho = NULL;
    }
};

struct comparar {
    bool operator()(Nodo* l, Nodo* r) {
        if (l->frecuencia == r->frecuencia) {
            // Si las frecuencias son iguales, ordenar alfabéticamente
            return l->caracter > r->caracter;
        }
        // Si las frecuencias son diferentes, ordenar por frecuencia
        return l->frecuencia > r->frecuencia;
    }
};

class Huffman
{
private:
    Nodo *raiz;
    map<char, string> huffmanCode;

    void codificar(Nodo *raiz, string str)
    {
        if (raiz == NULL)
            return;
        if (!raiz->izquierdo && !raiz->derecho)
        {
            huffmanCode[raiz->caracter] = str;
        }
        codificar(raiz->izquierdo, str + "0");
        codificar(raiz->derecho, str + "1");
    }

public:

    void imprimirColaPrioridad(priority_queue<Nodo *, vector<Nodo *>, comparar> pq)
    {
        priority_queue<Nodo *, vector<Nodo *>, comparar> temp = pq; // Copia de la cola para no alterar la original
        cout << "Cola de Prioridad:\n";
        while (!temp.empty())
        {
            Nodo *nodo = temp.top();
            cout << nodo->caracter << " (" << nodo->frecuencia << ") ";
            temp.pop();
        }
        cout << "\n";
    }

    Huffman(string texto)
    {
        map<char, int> frecuencia;
        for (char ch : texto)
        {
            frecuencia[ch]++;
        }

        priority_queue<Nodo *, vector<Nodo *>, comparar> pq;
        for (auto pair : frecuencia)
        {
            pq.push(new Nodo(pair.first, pair.second));
        }

        imprimirColaPrioridad(pq); // Llamada al método para imprimir la cola de prioridad

        while (pq.size() > 1)
        {
            Nodo *izquierdo = pq.top();
            pq.pop();
            Nodo *derecho = pq.top();
            pq.pop();
            int sum = izquierdo->frecuencia + derecho->frecuencia;
            Nodo *nuevo = new Nodo('\0', sum);
            nuevo->izquierdo = izquierdo;
            nuevo->derecho = derecho;
            pq.push(nuevo);
        }

        raiz = pq.top();
        codificar(raiz, "");
    }

    map<char, string> getHuffmanCode()
    {
        return huffmanCode;
    }
    Nodo *getRaiz()
    {
        return raiz;
    }

    void imprimirArbol(Nodo *raiz, int cont = 0)
    {
        if (raiz == NULL)
            return;

        imprimirArbol(raiz->derecho, cont + 1);
        for (int i = 0; i < cont; i++)
            cout << "\t";
        cout << raiz->caracter << " (" << raiz->frecuencia << ")\n";

        imprimirArbol(raiz->izquierdo, cont + 1);
    }
};

void codDecodText(string texto)
{
    Huffman huffman(texto);
    map<char, string> huffmanCode = huffman.getHuffmanCode();

    cout << "Codificacion de Huffman:\n";
    string strEncoded;
    for (char ch : texto)
    {
        strEncoded += huffmanCode[ch];
        cout << ch << ": " << huffmanCode[ch] << "\n";
    }

    cout << "Texto codificado: " << strEncoded << "\n";

    string strDecoded;
    Nodo *nodo = huffman.getRaiz();
    for (char bit : strEncoded)
    {
        if (bit == '0')
        {
            nodo = nodo->izquierdo;
        }
        else
        {
            nodo = nodo->derecho;
        }

        if (nodo->izquierdo == NULL && nodo->derecho == NULL)
        {
            strDecoded += nodo->caracter;
            nodo = huffman.getRaiz(); // Reiniciar desde la raíz para el próximo bit
        }
    }

    // // Comprobar si el último nodo es una hoja
    // if (nodo != NULL && nodo->izquierdo == NULL && nodo->derecho == NULL)
    // {
    //     strDecoded += nodo->caracter;
    // }

    cout << "Texto decodificado: " << strDecoded << "\n";
    long long bitsEnconded = strEncoded.size();
    long long bitsDecoded = strDecoded.size() * 8;
    cout << "Bits codificados: " << bitsEnconded << "\n";
    cout << "Bits decodificados: " << bitsDecoded << "\n";
    cout << "\n\nArbol de Huffman:\n";
    huffman.imprimirArbol(huffman.getRaiz());
    cout << endl
         << endl;
    cout << "Press any key to continue...";
    getch();
}

void codDecodTxt()
{
    string nombreArchivo = "";
    cout << "Introduce el nombre del archivo: ";
    fflush(stdin);
    getline(cin, nombreArchivo);
    ifstream archivo;
    archivo.open(nombreArchivo, ios::in);
    if (!archivo)
    {
        cerr << "No se pudo abrir el archivo";
        return;
    }
    string texto;
    string linea;
    while (getline(archivo, linea))
    {
        texto += linea;
    }
    codDecodText(texto);
}

int main()
{
    bool seguir = true;
    do
    {
        int opcion = 0;
        // cls
        cout << "\033[2J\033[1;1H";
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
            codDecodText(texto);
            break;
        }
        case 2:
        {
            codDecodTxt();
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
    getch();
    return 0;
}