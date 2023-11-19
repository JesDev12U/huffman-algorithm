from collections import Counter
import heapq

#definimos el arbol
class Tree:
    def __init__(self, ch, freq, left=None, right=None):
        self.ch = ch
        self.freq = freq
        self.left = left
        self.right = right
    
    #El orden de los nodos esta definido por su frecuencia
    #Un nodo menos frecuente se considera mas pequeño que un nodo mas frecuente
    #Eso lo mencionamos con __lt__
    def __lt__(self, other):#lt = less than = menor que
        return self.freq < other.freq

def build_tree(text):
    #Contamos las frecuencias de las letras
    counter = Counter(text)
    #Usaemos las colas de prioridad para construir el arbol
    #Primero creamos los nodos que tendra el arbol por cada caracter con sus frecuencias
    priority_queue = [Tree(ch, counter[ch]) for ch in counter]
    #Al ordenar por prioridad, se acomodaran los nodos dependiendo de su frecuencia para asi construir el arbol
    heapq.heapify(priority_queue)
    #Repetiremos el proceso hasta que nos quede un nodo
    while len(priority_queue) > 1:
        #Extraemos los nodos pequeños que seran los hijos
        left = heapq.heappop(priority_queue)
        right = heapq.heappop(priority_queue)
        #Creamos el nodo padre que tendra la suma de sus hijos
        #No tendra un caracter, pero tendra la suma de frecuencias
        parent = Tree(None, left.freq + right.freq, left, right)
        #Insertamos al padre a nuestra cola de prioridad o arbol
        heapq.heappush(priority_queue, parent)
    #Cuando solo quede un elemento o nodo, quiere decir que es nuestra raiz, asi que lo devolvemos
    return heapq.heappop(priority_queue)
    #Como salida obtenemos un nodo que es la raiz, pero que esta conectado a todos los nodos

#Construimos un mapa con los codigos
def build_map(root):
    #Recorremos el arbol
    def dfs(root, code, encoding_map):
        #Si encontramos un nodo de caracteres
        if root.ch:
            #Armamos el codigo
            encoding_map[root.ch] = ''.join(code)
        #En caso contrario, asignamos un 0 y recorremos el arbol a la izquierda
        else:
            code.append('0')
            dfs(root.left, code, encoding_map)
            code.pop() #Quitamos el 0
            #Ahora recorremos a la derecha
            code.append('1')
            dfs(root.right, code, encoding_map)
            code.pop();
    #Creamos nuestro mapa o diccionario de codigos
    encoding_map = {}
    dfs(root, [], encoding_map)
    #devolvemos el mapa
    return encoding_map

#Codificamos nuestra palabra ya con el diccionario de codigos hecho
def encode(text):
    root = build_tree(text)
    encoding_map = build_map(root)
    #Recorremos el diccionario poniendo el caracter para que asi nos regrese el codigo
    return ''.join(encoding_map[ch] for ch in text)

#Decodificamos un codigo para convertirlo en palabra
def decode(encoded, root):
    #Practicamente recorremos el arbol para ir encontrando las letras
    #Si la raiz tiene un caracter quiere decir que la cadena esta formada por un caracter
    #Por lo que regresamos el caracter por las veces que se repite
    if root.ch:
        return root.ch * len(encoded)
    #Si no hay problema con la raiz, creamos una lista decodificada
    #Ahi pondremos el texto decodificado
    decoded = []
    node = root
    for bit in encoded:
        if bit == "0":
            node = node.left
        else:
            node = node.right
        if node.ch:
            decoded.append(node.ch)
            node = root
    return ''.join(decoded)

if __name__ == '__main__':
    text = input("Ingrese un texto: ")
    print(f"Cantidad de bits: {len(text) * 8}")
    code = encode(text)
    print(f"\nCodigo de Huffman:\n{code}")
    print(f"Compresion Huffman, cantidad de bits: {len(code)}")
    print(f"\nDecodificacion del codigo")
    print(decode(code, build_tree(text)))