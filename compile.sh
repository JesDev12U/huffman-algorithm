#!/bin/bash

# Script interactivo de ayuda para compilar los algoritmos de C++ del proyecto Huffman
# Basado en las instrucciones del README.md

# Colores para la terminal
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
CYAN="\033[1;36m"
RED="\033[1;31m"
RESET="\033[0m"

echo -e "${CYAN}================================================${RESET}"
echo -e "${CYAN}   Herramienta de Compilación - Modo Interactivo${RESET}"
echo -e "${CYAN}================================================${RESET}"
echo ""
echo -e "¿Qué método deseas usar para compilar el proyecto?"
echo -e "  ${YELLOW}1)${RESET} Usar Make (Rápido, genera ejecutables en ./bin/)"
echo -e "  ${YELLOW}2)${RESET} Usar CMake (Avanzado, genera ejecutables en build/bin/)"
echo -e "  ${YELLOW}3)${RESET} Manual con g++ (Solo compila huffman.cpp interactivo en la raíz)"
echo -e "  ${YELLOW}4)${RESET} Limpiar el proyecto (Borra binículos, ./build y ejecutables)"
echo -e "  ${YELLOW}5)${RESET} Salir"
echo ""

read -p "Elige una opción [1-5]: " opcion

case $opcion in
    1)
        echo -e "\n${GREEN}[*] Ejecutando Make...${RESET}"
        make
        if [ $? -eq 0 ]; then
            echo -e "\n${GREEN}[+] ¡Compilación exitosa!${RESET} Puedes ver los ejecutables generados:"
            ls -l bin/
            echo -e "\n${YELLOW}Ejemplo de uso: ./bin/huffman${RESET}"
        else
            echo -e "\n${RED}[-] Hubo un error al compilar usando Make.${RESET}"
        fi
        ;;
    2)
        echo -e "\n${GREEN}[*] Configurando y compilando con CMake...${RESET}"
        mkdir -p build
        cd build
        cmake ..
        cmake --build . -- -j
        if [ $? -eq 0 ]; then
            echo -e "\n${GREEN}[+] ¡Compilación exitosa!${RESET} Puedes ver los ejecutables generados en build/bin/:"
            ls -l bin/
            echo -e "\n${YELLOW}Ejemplo de uso: ./build/bin/huffman${RESET}"
        else
            echo -e "\n${RED}[-] Hubo un error al compilar usando CMake.${RESET}"
        fi
        ;;
    3)
        echo -e "\n${GREEN}[*] Compilando huffman.cpp manualmente (g++)...${RESET}"
        g++ -std=c++17 huffman.cpp -o huffman -Wall -Wextra
        if [ $? -eq 0 ]; then
            echo -e "\n${GREEN}[+] ¡Ejecutable compilado correctamente en la raíz del proyecto!${RESET}"
            echo -e "\n${YELLOW}Ejemplo de uso: ./huffman${RESET}"
        else
            echo -e "\n${RED}[-] Hubo un error compilando manualmente.${RESET}"
        fi
        ;;
    4)
        echo -e "\n${GREEN}[*] Limpiando archivos autogenerados...${RESET}"
        make clean
        rm -rf build/
        rm -f huffman
        echo -e "${GREEN}[+] Directorios ./bin/, ./build/ y ./huffman eliminados.${RESET}"
        ;;
    5)
        echo -e "Saliendo del asistente de compilación..."
        exit 0
        ;;
    *)
        echo -e "\n${RED}[-] Opción no válida.${RESET} Por favor ejecuta el script de nuevo y elige un número del 1 al 5."
        exit 1
        ;;
esac
