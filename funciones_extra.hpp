#ifndef FUNCIONES_EXTRA_HPP
#define FUNCIONES_EXTRA_HPP

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*****
* string* leerArchivo
******
* Resumen Función:
* Función que recorre 2 veces el archivo, una primera vez para calcular la cantidad de líneas que tiene el archivo
* y así determinar el largo del arreglo donde se guardará cada línea del .TXT, y una segunda vez para ir guardando
* cada línea dentro del arreglo.
******
* Input:
* string nombreArchivo : Nombre del archivo que se va a leer.
* int numLineas : Variable en la que se guardará la cantidad de líneas dentro del archivo, en otras palabras nos
* entrega el largo del arreglo.
******
* Returns:
* string* : Puntero a un arreglo con las líneas del .TXT
*****/
string* leerArchivo(const string& nombreArchivo, int& numLineas) {
    ifstream archivo(nombreArchivo);

    //Comprobar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        numLineas = 0;
        return nullptr;
    }

    // Contador de líneas
    int contador = 0;
    string linea;
    // Primer recorrido para contar las líneas
    while (getline(archivo, linea)) {
        contador++;
    }

    // Crear un arreglo para almacenar las líneas del archivo
    string* lineasArchivo = new string[contador];
    archivo.clear();
    archivo.seekg(0, ios::beg);

    // Segundo recorrido para almacenar las líneas en el arreglo
    for (int i = 0; i < contador; i++) {
        getline(archivo, linea);
        lineasArchivo[i] = linea;
    }

    archivo.close();
    numLineas = contador;
    return lineasArchivo;
}

/*****
* string* separar_string
******
* Resumen Función:
* Función que recibe un string, el cual se va a separar en partes que serán designadas de acuerdo
* al separador entregado.
******
* Input:
* string frase : String que se va a separar dependiendo del separador.
* char separador : Carácter encargado de separar el string.
******
* Returns:
* string* : Arreglo de los strings resultantes de dividir el string frase por medio del separador.
*****/
string* separar_string(const string frase, const char separador) {

    // Contar la cantidad de separadores en la frase
    int Cantidad_Separadores = 0;
    for (char caracter : frase) {
        if (caracter == separador) {
            Cantidad_Separadores++;
        }
    }

    // Calcular la cantidad de strings resultantes
    int Cantidad_Strings = Cantidad_Separadores + 1;
    string* ArregloReturn = new std::string[Cantidad_Strings];
    int pos_arr = 0;
    int parte = 0;

    // Separar la frase según el separador
    for (size_t i = 0; i < frase.size(); i++) {
        if (frase[i] == separador) {
            ArregloReturn[pos_arr] = frase.substr(parte, i - parte);
            pos_arr++;
            parte = i + 1;
        }
    }

    // Asignar la última parte de la frase al arreglo
    ArregloReturn[pos_arr] = frase.substr(parte, frase.size() - parte);

    return ArregloReturn;
}

#endif