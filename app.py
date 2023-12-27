from flask import Flask, redirect, render_template, request, send_file, jsonify, url_for
import subprocess
import os

app = Flask(__name__)

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
        file.save('uploads/' + file.filename)
        
        # Llamar al programa de compresión C++
        subprocess.run(['./huffmancompress', 'uploads/' + file.filename])  # Reemplaza con el nombre de tu ejecutable
        
        return render_template('filecompressed.html');
    else:
        return jsonify({'error': 'Se debe cargar un archivo .txt'})

@app.route('/decompress', methods=['POST'])
def decompress_file():
    file = request.files['fileToDecompress']
    
    if file.filename.endswith('.huff'):
        file.save('uploads/' + file.filename)
        
        # Llamar al programa de descompresión C++
        subprocess.run(['./huffmandecompress', 'uploads/' + file.filename])  # Reemplaza con el nombre de tu ejecutable
        
        return render_template('filedecompressed.html');
    else:
        return jsonify({'error': 'Se debe cargar un archivo .huff'})

@app.route('/download_compressed')
def download_compressed():
    compressed_file = './comprimido.huff'  # Ruta al archivo comprimido generado
    if os.path.exists(compressed_file):
        return send_file(compressed_file, as_attachment=True)
    else:
        return jsonify({'error': 'Archivo comprimido no encontrado'})

@app.route('/download_decompressed')
def download_decompressed():
    decompressed_file = './descomprimido.txt'  # Ruta al archivo descomprimido generado
    if os.path.exists(decompressed_file):
        return send_file(decompressed_file, as_attachment=True)
    else:
        return jsonify({'error': 'Archivo descomprimido no encontrado'})

@app.errorhandler(404)
def page_not_found(e):
    # nota que pasamos el error como argumento a la plantilla
    return render_template('404.html'), 404

if __name__ == '__main__':
    app.run(debug=True)
