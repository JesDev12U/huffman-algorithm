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
});