# Huffman algorithm in C++

If you want to see this project, <a href="https://youtu.be/J29Ls9i50Ew?si=u4pEV50TwGS8ntMC">you can see my video in YouTube</a>

<img src="https://github.com/JesDev12U/huffman-algorithm/assets/119618881/71517a54-8bc6-43c7-af69-d681932cddde" width="250px"/>
<img src="https://github.com/JesDev12U/huffman-algorithm/assets/119618881/48929c35-c76a-4603-96af-bcb54318aa14" width="700px"/>
<img src="https://github.com/JesDev12U/huffman-algorithm/assets/119618881/3127412a-0961-4abf-9c9c-2cc59ac00e81" width="700px"/>
<img src="https://github.com/JesDev12U/huffman-algorithm/assets/119618881/bc1a2ce1-7d1f-4035-83c7-61ca38133c11" width="700px"/>

# Considerations
<ul>
  <li>You need to install the latest version of C++ Compiler, I recommend the MinGW 6.3.0 compiler because in this compiler I was develop the algorithms</li>
  <li>You need to install the latest version of Python, or minimum the 3.10 version. Also you need to install Flask. You can install it with this command:</li>
  
```bash
pip install flask
```
  <li>None folder can be modify or delete because the app will stop works</li>
  <li>Maybe I'll host the app, but in this moment NO :p, so you can host the app with Ngrok or others host apps</li>
</ul>

# Run the aplication
<ol>
  <li>Compile the C++ algorithms</li>
 
  ```
  g++ -o huffmancompress huffmancompress.cpp <FILE INPUT .txt> <FILE OUTPUT .huff>
  g++ -o huffmandecompress huffmandecompress.cpp <FILE INPUT .huff> <FILE OUTPUT .txt>
  ```
  <li>Run the Python algorithm to run the Flask server</li>
  
  ```
  python app.py
  ```
  <li>Go to the localhost (127.0.0.1) in the port 5000 to open the app web</li>
  <li>Enjoy it :)</li>
</ol>

In this repository you can find the documentation PDF of this project
