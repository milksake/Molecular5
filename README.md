# Estructura Secundaria en ARN

Este proyecto incluye:

- `main.cpp`: Programa en C++ que imprime datos de estructuras de ARN.
- `plot.py`: Script en Python que lee desde stdin y dibuja la estructura como un grafo.

## Requisitos

### Python

Librerías necesarias:

```bash
pip install matplotlib networkx
````

### C++

Compilación con:

```bash
g++ -O2 -std=c++17 -o main main.cpp
```

## Uso

Ejecutar el programa C++ y pasar su salida al script de Python para visualizar la estructura:

```bash
./main | python plot.py
```
