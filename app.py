"""
@file app.py
@brief Archivo principal del servidor web
@details Este archivo contiene el código principal del servidor web, el cual se encarga de recibir los archivos,
llamar a los programas de compresión y descompresión, y enviar los archivos comprimidos o descomprimidos al 
cliente.
@date 2023-12-27
@version 1.0.0
@author Jesus Antonio Lopez Bandala
@details # Es necesario compilar el programa de compresión y descompresión antes de ejecutar el servidor web
"""

# Importar librerías
# Flask es el framework que usaremos para crear el servidor web
# render_template nos permite renderizar plantillas HTML
# request nos permite acceder a los archivos que nos envía el cliente
# send_file nos permite enviar archivos al cliente
# jsonify nos permite enviar mensajes JSON al cliente, mensajes cortos para indicar errores
# session nos permite guardar información en la sesión del usuario, esto es útil para guardar el nombre de los archivos
from flask import Flask, render_template, request, send_file, jsonify, session
# subprocess nos permite llamar a programas externos, en este caso los programas de compresión y descompresión
import subprocess
# uuid nos permite generar nombres únicos para los archivos
import uuid
# os nos permite eliminar archivos
import os
# threading nos permite ejecutar tareas en segundo plano, en este caso la eliminación de los archivos después de 5 minutos
import threading
# time nos permite esperar 5 minutos antes de eliminar los archivos
import time

app = Flask(__name__)
app.secret_key = 'jinofvx' # La clave es aleatoria, solo es para que funcione la sesión

# Función para generar nombres únicos para los archivos
def generar_nombre_unico(nombre_original):
    nombre_unico = uuid.uuid4().hex # Genera un nombre aleatorio
    extension = os.path.splitext(nombre_original)[1] # Obtiene la extensión del archivo
    return f"{nombre_unico}{extension}" # Regresa el nombre aleatorio con la extensión

def eliminar_archivo_despues_de_cinco_minutos(filename_generated, filename_uploads):
    time.sleep(300000) # Espera 5 minutos, 300000 milisegundos
    # Elimina los archivos, tanto el comprimido o descomprimido como el original
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
    file = request.files['fileToCompress'] # Obtiene el archivo que envía el cliente
    
    if file.filename.endswith('.txt'): # Verifica que el archivo tenga la extensión .txt
        unique_filename = generar_nombre_unico(file.filename) # Genera un nombre único para el archivo
        file.save('uploads/' + unique_filename) # Guarda el archivo en la carpeta uploads
        
        # Llamar al programa de compresión C++
        subprocess.run(['./huffmancompress', 'uploads/' + unique_filename, 'compressed/' + unique_filename])
        
        # Eliminar el archivo original y el comprimido después de 5 minutos
        threading.Thread(target=eliminar_archivo_despues_de_cinco_minutos, args=('compressed/' + unique_filename + '.huff', 'uploads/' + unique_filename)).start()
        # Guardar el nombre del archivo en la sesión
        session['download_file'] = 'compressed/' + unique_filename + '.huff'
        
        # Redirigir a la página de descarga
        return render_template('filecompressed.html')
    else: # Si el archivo no tiene la extensión .txt, regresa un mensaje de error
        return jsonify({'error': 'Se debe cargar un archivo .txt'})

@app.route('/download')
def download_file():
    # Iniciar la descarga del archivo
    return send_file(session['download_file'], as_attachment=True)

@app.route('/decompress', methods=['POST'])
def decompress_file():
    file = request.files['fileToDecompress'] # Obtiene el archivo que envía el cliente
    
    if file.filename.endswith('.huff'): # Verifica que el archivo tenga la extensión .huff
        unique_filename = generar_nombre_unico(file.filename) # Genera un nombre único para el archivo
        file.save('uploads/' + unique_filename) # Guarda el archivo en la carpeta uploads
        
        # Llamar al programa de descompresión C++
        subprocess.run(['./huffmandecompress', 'uploads/' + unique_filename, 'descompressed/' + unique_filename])  # Reemplaza con el nombre de tu ejecutable
        
        # Eliminar el archivo original y el descomprimido después de 5 minutos
        threading.Thread(target=eliminar_archivo_despues_de_cinco_minutos, args=('descompressed/' + unique_filename + '.txt', 'uploads/' + unique_filename)).start()
        # Guardar el nombre del archivo en la sesión
        session['download_file'] = 'descompressed/' + unique_filename + '.txt'
        
        # Redirigir a la página de descarga
        return render_template('filedecompressed.html')
    else: # Si el archivo no tiene la extensión .huff, regresa un mensaje de error
        return jsonify({'error': 'Se debe cargar un archivo .huff'})
    
@app.errorhandler(404)
def page_not_found(e):
    # Si el usuario intenta acceder a una página que no existe, regresa un error 404
    return render_template('404.html'), 404

if __name__ == '__main__':
    app.run(debug=True) # Inicia el servidor web en modo debug
