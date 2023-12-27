function dragOver(e) {
    e.preventDefault();
    document.getElementById('file-label').classList.add('dragging');
}

function drop(e) {
    e.preventDefault();
    e.currentTarget.classList.remove('dragging');

    // Obtén los archivos arrastrados
    var files = e.dataTransfer.files;

    // Comprueba si el archivo es de tipo .txt
    if (files[0].type !== 'text/plain') {
        document.getElementById('error-message').textContent = 'Por favor, solo arrastra archivos .txt';
        document.getElementById('error-message').style.display = 'block';
        return;
    }

    // Haz algo con los archivos (por ejemplo, cargarlos en el input)
    document.getElementById('fileToCompress').files = files;

    // Muestra un mensaje de que se ha subido el archivo
    document.getElementById('upload-message').textContent = 'Archivo subido correctamente: ' + files[0].name;
    document.getElementById('upload-message').style.display = 'block';

    // Oculta el mensaje de error
    document.getElementById('error-message').style.display = 'none';
}

function dragLeave(e) {
    document.getElementById('file-label').classList.remove('dragging');
}