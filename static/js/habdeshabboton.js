document.addEventListener('DOMContentLoaded', function() {
    // Obtén referencias al input del archivo y al botón
    var fileInput = document.getElementById('fileToCompress');
    var button = document.querySelector('.boton');

    // Inicialmente, deshabilita el botón
    button.disabled = true;

    // Escucha el evento de cambio en el input del archivo
    fileInput.addEventListener('change', function() {
        // Si hay un archivo seleccionado, habilita el botón, de lo contrario, deshabilítalo
        button.disabled = !this.files.length;
    });

    // Escucha los eventos de arrastrar y soltar en el body
    document.body.addEventListener('dragover', function(event) {
        event.preventDefault();
    });

    document.body.addEventListener('drop', function(event) {
        event.preventDefault();
        // Si hay un archivo arrastrado y soltado, habilita el botón
        if (event.dataTransfer.files.length) {
            button.disabled = false;
        }
    });
});