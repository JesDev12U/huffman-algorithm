document.addEventListener('DOMContentLoaded', function() {
    // Obtén referencias al input del archivo, al botón y al elemento del mensaje
    var fileInput = document.getElementById('fileToCompress');
    var button = document.querySelector('.boton');
    var uploadMessage = document.getElementById('upload-message');

    // Inicialmente, deshabilita el botón
    button.disabled = true;

    // Escucha el evento de cambio en el input del archivo
    fileInput.addEventListener('change', function() {
        // Si hay un archivo seleccionado, habilita el botón y muestra el mensaje
        if (this.files.length) {
            button.disabled = false;
            uploadMessage.textContent = 'Archivo subido: ' + this.files[0].name;
        } else {
            button.disabled = true;
        }
    });

    // Cancela los eventos de arrastrar y soltar en el documento
    document.addEventListener('dragover', function(event) {
        event.preventDefault();
    });

    document.addEventListener('drop', function(event) {
        event.preventDefault();
    });

    // Permite los eventos de arrastrar y soltar en el input de archivos
    fileInput.addEventListener('dragover', function(event) {
        event.preventDefault();
    });
});