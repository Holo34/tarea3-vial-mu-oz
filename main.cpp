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
            cuenta nueva_cuenta; nueva_cuenta.rol = arrComando[1]; nueva_cuenta.nombre = arrComando[2]; nueva_cuenta.descripcion = arrComando[3];
            registro.agregar(nueva_cuenta);
        }

        if (arrComando[0]=="QUITAR"){
            registro.eliminar(arrComando[1]);
        }

        if (arrComando[0]=="MODIFICAR"){
            registro.modificar(arrComando[1],arrComando[2]);
        }

        if (arrComando[0]=="OBTENER"){
            registro.obtener(arrComando[1]);
        }        

        if (arrComando[0]=="ESTADISTICAS"){
            registro.estadisticas();
        }

        delete[] arrComando;
    }
    
    delete[] arrLineasTXT;
    return 0;
}