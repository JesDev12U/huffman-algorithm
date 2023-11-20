#include <queue>
#include <vector>
#include <map>
#include <iostream>

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

struct comparar
{
    bool operator()(Nodo *l, Nodo *r)
    {
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
};

int main()
{
    string texto;
    cout << "Introduce un texto: ";
    getline(cin, texto);

    Huffman huffman(texto);
    map<char, string> huffmanCode = huffman.getHuffmanCode();

    cout << "Codificación de Huffman:\n";
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
    return 0;
}