import heapq
from collections import defaultdict
import json

class Nodo:
    def __init__(self, char, freq, izq=None, der=None):
        self.char = char
        self.freq = freq
        self.izq = izq
        self.der = der

    def __lt__(self, other):
        return self.freq < other.freq

def construir_cola(texto):
    frecuencias = defaultdict(int)
    for char in texto:
        frecuencias[char] += 1
    cola = [Nodo(char, freq) for char, freq in frecuencias.items()]
    heapq.heapify(cola)
    return cola

def construir_arbol(cola):
    while len(cola) > 1:
        izq = heapq.heappop(cola)
        der = heapq.heappop(cola)
        nodo = Nodo(None, izq.freq + der.freq, izq, der)
        heapq.heappush(cola, nodo)
    return cola[0]

def construir_diccionario(nodo, codigo_binario='', diccionario={}):
    if nodo is not None:
        if nodo.izq is None and nodo.der is None:
            diccionario[nodo.char] = codigo_binario
        construir_diccionario(nodo.izq, codigo_binario + '0', diccionario)
        construir_diccionario(nodo.der, codigo_binario + '1', diccionario)
    return diccionario

def comprimir(texto, diccionario):
    return ''.join(diccionario[char] for char in texto)

def descomprimir(comprimido, nodo):
    texto = ''
    actual = nodo
    for bit in comprimido:
        if bit == '0':
            actual = actual.izq
        else:
            actual = actual.der
        if actual.izq is None and actual.der is None:
            texto += actual.char
            actual = nodo
    return texto

def huffman(archivo_entrada, archivo_salida, archivo_diccionario):
    with open(archivo_entrada, 'r') as f:
        texto = f.read()
    cola = construir_cola(texto)
    arbol = construir_arbol(cola)
    diccionario = construir_diccionario(arbol)
    comprimido = comprimir(texto, diccionario)
    longitud = len(comprimido)
    comprimido_bytes = int(comprimido, 2).to_bytes((longitud + 7) // 8, byteorder='big')
    with open(archivo_salida, 'wb') as f:
        f.write(longitud.to_bytes(4, byteorder='big'))
        f.write(comprimido_bytes)
    with open(archivo_diccionario, 'w') as f:
        json.dump(diccionario, f)

def descomprimir_huffman(archivo_entrada, archivo_diccionario, archivo_salida):
    with open(archivo_entrada, 'rb') as f:
        longitud = int.from_bytes(f.read(4), byteorder='big')
        comprimido = f.read()
    comprimido = bin(int.from_bytes(comprimido, byteorder='big'))[2:].zfill(longitud)
    with open(archivo_diccionario, 'r') as f:
        diccionario = json.load(f)
    diccionario_decodificacion = {v: k for k, v in diccionario.items()}
    descomprimido = ''
    codigo = ''
    for bit in comprimido:
        codigo += bit
        if codigo in diccionario_decodificacion:
            descomprimido += diccionario_decodificacion[codigo]
            codigo = ''
    with open(archivo_salida, 'w') as f:
        f.write(descomprimido)

huffman('input.txt', 'comprimido.bin', 'diccionario.json')
descomprimir_huffman('comprimido.bin', 'diccionario.json', 'descomprimido.txt')