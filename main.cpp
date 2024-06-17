#include "registro_cuentas.hpp"

using namespace std;

int main () {

    //Cantidad de lineas que contiene el archivo "prueba.txt"
    int lineasTXT;
    //Arreglo de strings con cada linea del archivo
    string* arrLineasTXT = leerArchivo("prueba.txt",lineasTXT);

    /*
    Ciclo for en el que se recorre cada linea del txt dentro del arreglo "arrLineasTXT"
    Este ciclo determina cual es el comando en la linea del txt y la manda a su respectiva funcion
    */
    for (int i = 0; i < lineasTXT; i++){

        string lineaActual = arrLineasTXT[i];
        //Arreglo con cada una de las partes del comando
        string* arrComando = separar_string(lineaActual,' ');

        if (arrComando[0]=="AGREGAR"){
        
        }
        if (arrComando[0]=="QUITAR"){
        
        }

        if (arrComando[0]=="MODIFICAR"){

        }
        if (arrComando[0]=="OBTENER"){

        }        

        if (arrComando[0]=="ESTADISTICAS"){
            
        }

        delete[] arrComando;
    }
    
    delete[] arrLineasTXT;
    return 0;
}