#include <iostream>
#include <fstream>
#include <string>
#include "registro_cuentas.hpp"
#include "funciones_extra.hpp"

using namespace std;

int main () {

    //Cantidad de lineas que contiene el archivo "prueba.txt"
    int lineasTXT;
    //Arreglo de strings con cada linea del archivo
    string* arrLineasTXT = leerArchivo("prueba.txt",lineasTXT);
    //Creacion de un objeto de la clase "registro_cuentas"
    registro_cuentas registro;

    /*
    Ciclo for en el que se recorre cada linea del txt dentro del arreglo "arrLineasTXT"
    Este ciclo determina cual es el comando en la linea del txt y la manda a su respectiva funcion
    */
    for (int i = 0; i < lineasTXT; i++){

        string lineaActual = arrLineasTXT[i];
        //Arreglo con cada una de las partes del comando
        string* arrComando = separar_string(lineaActual,' ');

        if (arrComando[0]=="AGREGAR"){
            agregar(arrComando[1],arrComando[2],arrComando[3], registro);
        }

        if (arrComando[0]=="QUITAR"){
            quitar(arrComando[1],registro);
        }

        if (arrComando[0]=="MODIFICAR"){
            modificar(arrComando[1],arrComando[2],registro);
        }

        if (arrComando[0]=="OBTENER"){
            obtener(arrComando[1],registro);
        }        

        if (arrComando[0]=="ESTADISTICAS"){
            estadisticas(registro);
        }

        delete[] arrComando;
    }
    
    delete[] arrLineasTXT;
    return 0;
}