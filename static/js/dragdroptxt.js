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

    document.getElementById('fileToCompress').files = files;

    document.getElementById('upload-message').textContent = 'Archivo subido: ' + files[0].name;

    document.getElementById('upload-message').style.display = 'block';

    document.getElementById('error-message').style.display = 'none';
}

document.getElementById('fileToCompress').addEventListener('change', function() {
    var uploadMessage = document.getElementById('upload-message');
    if (this.files.length) {
        uploadMessage.style.display = 'block';
        uploadMessage.textContent = 'Archivo subido: ' + this.files[0].name;
    } else {
        uploadMessage.style.display = 'none';
    }
});

function dragLeave(e) {
    document.getElementById('file-label').classList.remove('dragging');
}