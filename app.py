from flask import Flask, redirect, render_template, request, send_file, jsonify, session, url_for
import subprocess
import uuid
import os
import threading
import time

app = Flask(__name__)
app.secret_key = 'jinofvx'

def generar_nombre_unico(nombre_original):
    nombre_unico = uuid.uuid4().hex
    extension = os.path.splitext(nombre_original)[1]
    return f"{nombre_unico}{extension}"

def eliminar_archivo_despues_de_cinco_minutos(filename_generated, filename_uploads):
    time.sleep(300)
    os.remove(filename_generated)
    os.remove(filename_uploads)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/compress_page')
def compress_page():
    return render_template('compress.html')

@app.route('/decompress_page')
def decompress_page():
    return render_template('decompress.html')

@app.route('/compress', methods=['POST'])
def compress_file():
    file = request.files['fileToCompress']
    
    if file.filename.endswith('.txt'):
        unique_filename = generar_nombre_unico(file.filename)
        file.save('uploads/' + unique_filename)
        
        # Llamar al programa de compresión C++
        subprocess.run(['./huffmancompress', 'uploads/' + unique_filename, 'compressed/' + unique_filename])  # Reemplaza con el nombre de tu ejecutable
        
        threading.Thread(target=eliminar_archivo_despues_de_cinco_minutos, args=('compressed/' + unique_filename + '.huff', 'uploads/' + unique_filename)).start()
        # Guardar el nombre del archivo en la sesión
        session['download_file'] = 'compressed/' + unique_filename + '.huff'
        
        # Redirigir a la página de inicio
        return render_template('filecompressed.html')
    else:
        return jsonify({'error': 'Se debe cargar un archivo .txt'})

@app.route('/download')
def download_file():
    # Iniciar la descarga del archivo
    return send_file(session['download_file'], as_attachment=True)

@app.route('/decompress', methods=['POST'])
def decompress_file():
    file = request.files['fileToDecompress']
    
    if file.filename.endswith('.huff'):
        unique_filename = generar_nombre_unico(file.filename)
        file.save('uploads/' + unique_filename)
        
        # Llamar al programa de descompresión C++
        subprocess.run(['./huffmandecompress', 'uploads/' + unique_filename, 'descompressed/' + unique_filename])  # Reemplaza con el nombre de tu ejecutable
        
        threading.Thread(target=eliminar_archivo_despues_de_cinco_minutos, args=('descompressed/' + unique_filename + '.txt', 'uploads/' + unique_filename)).start()
        # Guardar el nombre del archivo en la sesión
        session['download_file'] = 'descompressed/' + unique_filename + '.txt'
        
        return render_template('filedecompressed.html')
    else:
        return jsonify({'error': 'Se debe cargar un archivo .huff'})
    
@app.errorhandler(404)
def page_not_found(e):
    # nota que pasamos el error como argumento a la plantilla
    return render_template('404.html'), 404

if __name__ == '__main__':
    app.run(debug=True)
