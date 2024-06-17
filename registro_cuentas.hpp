#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct cuenta {
// El rol es el identificador de la persona.
// El nombre y la descripcion son valores asociados al rol
    string rol, nombre, descripcion;
};
class registro_cuentas {
    private:
        float factor_de_carga = 0.0;
        cuenta* tabla; // Aca se almacenaran los elementos de la tabla
        int ranuras = 15; // Cuantas ranuras tiene la tabla hash (inicialmente)
        int hash(string rol); // Se obtiene el hash dado el rol
        int p(string rol, int i); // Se otiene la ranura a revisar en caso de colisión dado el rol y el intento i
        int rOcupadas=0;
    public:
        registro_cuentas() {
            // Initialize the hash table with null pointers
            tabla = new cuenta[ranuras];
        }

        ~registro_cuentas() {
            delete[] tabla; // Free the allocated memory
        }
        cuenta obtener(string rol); // Dado el rol, devuelve la cuenta con ese rol
        void agregar(cuenta c); // Se agrega una cuenta a la tabla
        void eliminar(string rol); // Se elimina la cuenta
        void modificar(string rol, string descripcion); // Se modifica la descripcion del rol
        
        void redimensionar(int n); // Se redimensiona la tabla a n espacios
        void estadisticas(); // Debe mostrar las estadisticas
};
//Definicion de metodos:*******************************************************************************
int registro_cuentas::hash(string rol){
    string rolNum=rol;
    rolNum.erase(8,1);
    int hashOut = stoi(rolNum)%ranuras;
    
    return hashOut;
}
int registro_cuentas::p(string rol, int i){
    int pOut=(hash(rol)+i*hash(rol))%ranuras;
    return pOut;
}

cuenta registro_cuentas::obtener(string rol){
    cuenta vacia;
    vacia.nombre="Cuenta no encontrada";
    vacia.rol="Cuenta no encontrada";
    vacia.descripcion="Cuenta no encontrada";
    int i=0;
    while (tabla[p(rol,i)].rol != rol && i<16){
        
        cout<<"OBTAINING"<<endl;
        cout<<p(rol,i)<<endl;
        i++;
    }
    if (i<16){
        return  tabla[p(rol,i)];
    }
    else{
        return vacia;
    }
    
}

void registro_cuentas::agregar(cuenta c){
    string rolStr = c.rol;
    int rolNum= stoi(rolStr.erase(8,1));
    int k=hash(c.rol);
    int i=0;
    while (tabla[k].rol!=""){
        cout<<"ADDING, is this empty?"<<endl;
        cout<<tabla[k].rol<<endl;
        i++;
        k+=p(c.rol,i);
    }
    if (tabla[k].rol==c.rol){
        cout<<"Rol ya existente"<<endl;
    }
    else{
        tabla[k]=c;
    }
    
}

void registro_cuentas::eliminar(string rol){
    int i=0;
    while (tabla[p(rol,i)].rol != rol){
        //cout<<"OBTAINING"<<endl;
        //cout<<p(rol,i)<<endl;
        i++;
    }
    cout<<"liberating rol"<<endl;
    tabla[p(rol,i)].rol="liberado";
    cout<<"rol is now"<<tabla[p(rol,i)].rol<<endl;


    cout<<"liberating nombre"<<endl;
    tabla[p(rol,i)].nombre="liberado";
    cout<<"name is now"<<tabla[p(rol,i)].nombre<<endl;

    cout<<"liberating description"<<endl;
    tabla[p(rol,i)].descripcion="liberado";
    cout<<"description is now"<<tabla[p(rol,i)].descripcion<<endl;
}

void registro_cuentas::modificar(string rol, string descripcion){
    int i=0;
    while (tabla[p(rol,i)].rol != rol){
        
        //cout<<"OBTAINING"<<endl;
        //cout<<p(rol,i)<<endl;
        i++;
    }
    tabla[p(rol,i)].descripcion=descripcion;

}

//Main************************************************************************************************
int main(){

    registro_cuentas rc;
    cuenta c1 = {"16161616-6", "John Doe", "Description"};
    cuenta c2 = {"17171717-7", "Jane Doess", "Another Description"};
    cout<<"running agragar"<<endl;
    rc.agregar(c1);
    cout<<"running obtener rol, name, desc"<<endl;
    cout<<rc.obtener("16161616-6").rol;
    cout<<rc.obtener("16161616-6").nombre;
    cout<<rc.obtener("16161616-6").descripcion;
    cout<<endl<<"running modificar"<<endl;
    rc.modificar("16161616-6", "Ha sido modificado la descripción");
    cout<<"running obtener moded desc"<<endl;
    cout<<rc.obtener("16161616-6").descripcion;
    cout<<"running eliminar"<<endl;
    rc.eliminar("16161616-6");
    cout<<"running obtener deleted rol name desc"<<endl;
    cout<<rc.obtener("16161616-6").rol;
    cout<<rc.obtener("16161616-6").nombre;
    cout<<rc.obtener("16161616-6").descripcion;
    
    
    return 0;
}