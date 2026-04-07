# Algoritmo de Huffman en C++

Si quieres ver este proyecto, <a href="https://youtu.be/J29Ls9i50Ew?si=u4pEV50TwGS8ntMC">puedes ver mi video en YouTube</a>

<img src="https://github.com/JesDev12U/huffman-algorithm/assets/119618881/71517a54-8bc6-43c7-af69-d681932cddde" width="350px"/>
<img src="https://github.com/JesDev12U/huffman-algorithm/assets/119618881/48929c35-c76a-4603-96af-bcb54318aa14" width="700px"/>
<img src="https://github.com/JesDev12U/huffman-algorithm/assets/119618881/3127412a-0961-4abf-9c9c-2cc59ac00e81" width="700px"/>
<img src="https://github.com/JesDev12U/huffman-algorithm/assets/119618881/bc1a2ce1-7d1f-4035-83c7-61ca38133c11" width="700px"/>

---

Proyecto demostrativo para compresión y descompresión usando el algoritmo de Huffman. Incluye:

- Programa interactivo (menú) en `huffman.cpp`.
- Herramientas de línea de comandos para comprimir y descomprimir.
- Interfaz web mínima con Flask (`app.py`) para subir/descargar archivos.

## Requisitos

- GNU C++ con soporte C++17 (g++)
- make (opcional)
- CMake (opcional)
- Python 3 (para la interfaz web) y `Flask`

En Debian/Ubuntu:

```bash
sudo apt update
sudo apt install build-essential cmake python3-venv python3-pip
```

## Estructura del repositorio

- [huffman.cpp](huffman.cpp) — Programa interactivo (menú) para codificar/decodificar texto y archivos.
- [huffcodeco.cpp](huffcodeco.cpp) — Herramienta de referencia que comprime y descomprime un archivo `.txt`.
- [huffmancompress.cpp](huffmancompress.cpp) — Compresor por línea de comandos.
- [huffmandecompress.cpp](huffmandecompress.cpp) — Descompresor por línea de comandos.
- [priority_queue.cpp](priority_queue.cpp) — Ejemplo educativo.
- `static/`, `templates/`, `uploads/`, `compressed/`, `descompressed/` — archivos y recursos usados por la web.
- [Makefile](Makefile) — Genera ejecutables en `./bin/`.
- [CMakeLists.txt](CMakeLists.txt) — Genera ejecutables en `build/bin/`.

## Compilación

### Usando Make (rápido)

```bash
# Desde la raíz del proyecto
make
# Los ejecutables se generan en ./bin/
ls bin/
./bin/huffman   # ejecutar el programa interactivo
```

### Usando CMake (flexible)

```bash
mkdir -p build
cd build
cmake ..
cmake --build . -- -j
# Ejecutables en build/bin/
ls bin/
./bin/huffman
```

## Ejecutar la interfaz web (Python / Flask)

1. Compila primero los ejecutables (Make o CMake) para que `huffmancompress` y `huffmandecompress` estén disponibles.
2. Crea un entorno virtual e instala Flask:

```bash
python3 -m venv venv
source venv/bin/activate
pip install Flask
```

3. Asegúrate de que los ejecutables estén en el directorio de trabajo (el servidor llama `./huffmancompress` y `./huffmandecompress`).
   - Opción rápida: crear enlaces simbólicos desde `bin/` al raíz:

```bash
ln -s "$(pwd)/bin/huffmancompress" ./huffmancompress
ln -s "$(pwd)/bin/huffmandecompress" ./huffmandecompress
```

4. Ejecuta el servidor:

```bash
python app.py
```

5. Abre http://127.0.0.1:5000 en tu navegador y usa la interfaz.

> Nota: los directorios `uploads/`, `compressed/` y `descompressed/` deben existir y ser escribibles.

## Comandos que usé durante esta sesión (ejemplos)

Estos son los comandos exactos que usé para compilar, probar y depurar mientras trabajaba en el proyecto:

```bash
# Compilar individualmente
g++ -std=c++17 huffman.cpp -o huffman -Wall -Wextra
# Compilar con ruta absoluta (ejemplo usado durante pruebas)
g++ -std=c++17 /home/jesdev12u/Projects/huffman-algorithm/huffman.cpp -o /home/jesdev12u/Projects/huffman-algorithm/huffman -Wall -Wextra

# Prueba no interactiva (piped input) usada para reproducir el fallo
printf "1\nCola de Prioridad:\nx\n3\n" | ./huffman

# Usando Make (construye bin/)
make

# Usando CMake
mkdir -p build && cd build
cmake ..
cmake --build . -- -j

# Comandos para compilar y probar desde el build dir
cmake --build . -- -j
./bin/huffman

# Comandos para ejecutar la web (ejemplo)
python3 -m venv venv
source venv/bin/activate
pip install Flask
python app.py
```

## Cambios aplicados y notas técnicas

- Reemplazo de `conio.h` por una implementación portable de `getch()` en `huffman.cpp` (usa `termios` en Unix). Esto para compatibilidad con sistemas POSIX.
- Reemplazo de `fflush(stdin)` por `cin.ignore(...)` para evitar saltos inesperados en `getline`.
- `getch()` ahora detecta si `stdin` es un TTY y no bloquea en pipes.
- Se eliminaron variables no usadas para reducir warnings.
- Se eliminó el objetivo `install` de `CMakeLists.txt` (proyecto demostrativo).
