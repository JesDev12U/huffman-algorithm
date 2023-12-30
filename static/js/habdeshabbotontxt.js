/*
 * @file habdeshabbotonhuff.js
 * @brief Archivo que contiene el código para la funcionalidad del botón de subir archivos .txt
 * Esto para habilitar el botón cuando se sube un archivo y mostrar el nombre del archivo subido
 * Si no se sube ningún archivo, el botón se deshabilita
 * @version 1.0
 * @date 2023-12-27
 * @author Jesus Antonio Lopez Bandala
 * @note Este archivo es una modificación del archivo habdeshabbotonhuff.js, para que funcione con archivos de texto
*/

// Función que se ejecuta cuando se carga el documento HTML
document.addEventListener('DOMContentLoaded', function () {
    var fileInput = document.getElementById('fileToCompress'); // Input de archivos
    var button = document.querySelector('.boton'); // Botón de subir archivo
    var uploadMessage = document.getElementById('upload-message'); // Mensaje de archivo subido

    // Inicialmente, deshabilita el botón
    button.disabled = true;

    // Escucha el evento de cambio en el input del archivo
    fileInput.addEventListener('change', function () {
        // Si hay un archivo seleccionado, habilita el botón y muestra el mensaje
        if (this.files.length) {
            button.disabled = false;
            uploadMessage.textContent = 'Archivo subido: ' + this.files[0].name;
        } else { // Si no hay un archivo seleccionado, deshabilita el botón y desaparece el mensaje
            button.disabled = true;
        }
    });

    // Cancela los eventos de arrastrar y soltar en el documento
    document.addEventListener('dragover', function (event) {
        event.preventDefault(); // Evita que el navegador abra el archivo
    });

    document.addEventListener('drop', function (event) {
        event.preventDefault(); // Evita que el navegador abra el archivo
    });

    // Permite los eventos de arrastrar y soltar en el input de archivos
    fileInput.addEventListener('dragover', function (event) {
        event.preventDefault(); // Evita que el navegador abra el archivo
    });
});