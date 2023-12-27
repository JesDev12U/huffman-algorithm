document.addEventListener('DOMContentLoaded', function() {
    var fileInput = document.getElementById('fileToCompress');
    var dropzone = document.getElementById('dropzone');
    var dragCounter = 0;

    document.addEventListener('dragenter', function(event) {
        event.preventDefault();
        dragCounter++;
        dropzone.style.display = 'block';
        dropzone.classList.add('dragover');
    });

    document.addEventListener('dragleave', function(event) {
        event.preventDefault();
        dragCounter--;
        if (dragCounter === 0) {
            dropzone.style.display = 'none';
            dropzone.classList.remove('dragover');
        }
    });

    document.addEventListener('drop', function(event) {
        event.preventDefault();
        dragCounter = 0;
        dropzone.style.display = 'none';
        dropzone.classList.remove('dragover');
        if (event.dataTransfer.files.length === 1) {
            var file = event.dataTransfer.files[0];
            var fileName = file.name;
            var fileExtension = fileName.split('.').pop().toLowerCase();
            if (fileExtension !== 'txt') {
                alert('Por favor, arrastra archivos de texto plano .txt');
                return;
            }
            var dataTransfer = new DataTransfer();
            dataTransfer.items.add(file);
            fileInput.files = dataTransfer.files;
            // Dispara manualmente el evento change en el input de archivos
            var changeEvent = new Event('change');
            fileInput.dispatchEvent(changeEvent);
        } else {
            alert('Por favor, arrastra solo un archivo.');
        }
    });
    
});