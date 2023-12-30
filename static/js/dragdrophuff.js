/*
 * @file dragdrophuff.js
 * @brief Archivo que contiene el código para la funcionalidad de arrastrar y soltar archivos comprimidos .huff
 * @version 1.0
 * @date 2023-12-27
 * @author Jesus Antonio Lopez Bandala
 */

// Función que se ejecuta cuando se carga el documento HTML
document.addEventListener("DOMContentLoaded", function () {
    var fileInput = document.getElementById("fileToDecompress"); // Input de archivos
    var dropzone = document.getElementById("dropzone"); // Zona de arrastrar y soltar archivos
    var dragCounter = 0; // Contador de archivos arrastrados, esto para saber cuando se sale de la zona de arrastrar y soltar

    /*
      dragenter: Este evento se dispara cuando un elemento arrastrable entra en un área de destino. 
      Cuando un archivo se arrastra hacia la zona de arrastrar y soltar, se incrementa un contador (dragCounter), 
      se muestra la zona de arrastrar y soltar (dropzone.style.display = 'block') y se agrega una clase CSS 
      (dragover) a la zona de arrastrar y soltar para cambiar su apariencia.
      */
    document.addEventListener("dragenter", function (event) {
        event.preventDefault(); // Evita que el navegador abra el archivo
        dragCounter++; // Incrementa el contador de archivos arrastrados
        dropzone.style.display = "block"; // Muestra la zona de arrastrar y soltar
        dropzone.classList.add("dragover"); // Agrega la clase CSS dragover a la zona de arrastrar y soltar
    });

    /*
      dragleave: Este evento se dispara cuando un elemento arrastrable sale de un área de destino. 
      Cuando un archivo se arrastra fuera de la zona de arrastrar y soltar, se decrementa el contador
      (dragCounter). Si el contador llega a cero, lo que significa que no hay archivos arrastrados sobre la zona, 
      se oculta la zona de arrastrar y soltar (dropzone.style.display = 'none') y 
      se elimina la clase CSS (dragover) de la zona de arrastrar y soltar.
      */
    document.addEventListener("dragleave", function (event) {
        event.preventDefault(); // Evita que el navegador abra el archivo
        dragCounter--; // Decrementa el contador de archivos arrastrados
        if (dragCounter === 0) {
            // Si el contador llega a cero, lo que significa que no hay archivos arrastrados sobre la zona
            dropzone.style.display = "none"; // Oculta la zona de arrastrar y soltar
            dropzone.classList.remove("dragover"); // Elimina la clase CSS dragover de la zona de arrastrar y soltar
        }
    });

    // Función que se ejecuta cuando se suelta el archivo en la zona de arrastrar y soltar
    document.addEventListener("drop", function (event) {
        event.preventDefault(); // Evita que el navegador abra el archivo
        dragCounter = 0; // Reinicia el contador de archivos arrastrados
        dropzone.style.display = "none"; // Oculta la zona de arrastrar y soltar
        dropzone.classList.remove("dragover"); // Elimina la clase CSS dragover de la zona de arrastrar y soltar
        if (event.dataTransfer.files.length === 1) {
            // Si solo se arrastra un archivo
            var file = event.dataTransfer.files[0]; // Obtiene el archivo
            var fileName = file.name; // Obtiene el nombre del archivo
            var fileExtension = fileName.split(".").pop().toLowerCase(); // Obtiene la extensión del archivo
            if (fileExtension !== "huff") {
                // Si la extensión del archivo no es .huff
                alert("Por favor, arrastra archivos comprimidos .huff");
                return; // Termina la ejecución de la función
            }
            var dataTransfer = new DataTransfer(); // Crea un objeto DataTransfer, esto para poder agregar el archivo al input de archivos
            dataTransfer.items.add(file); // Agrega el archivo al objeto DataTransfer
            fileInput.files = dataTransfer.files; // Agrega el archivo al input de archivos
            // Dispara manualmente el evento change en el input de archivos
            var changeEvent = new Event("change");
            fileInput.dispatchEvent(changeEvent); // Dispara el evento change en el input de archivos
        } else {
            alert("Por favor, arrastra solo un archivo.");
        }
    });
});
