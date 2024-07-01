#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct cuenta{
    // El rol es el identificador de la persona.
    // El nombre y la descripcion son valores asociados al rol
    string rol, nombre, descripcion;
};
class registro_cuentas{
    private:
        float factor_de_carga = 0.0;
        cuenta *tabla;            // Aca se almacenaran los elementos de la tabla
        int ranuras = 15;         // Cuantas ranuras tiene la tabla hash (inicialmente)
        int hash(string rol);     // Se obtiene el hash dado el rol
        int p(string rol, int i); // Se otiene la ranura a revisar en caso de colisión dado el rol y el intento i
        int rOcupadas = 0;
    public:
        registro_cuentas(){
            // Initialize the hash table with null pointers
            tabla = new cuenta[ranuras];
        }
        ~registro_cuentas(){
            delete[] tabla; // Free the allocated memory
        }
        cuenta obtener(string rol);                     // Dado el rol, devuelve la cuenta con ese rol
        void agregar(cuenta c);                         // Se agrega una cuenta a la tabla
        void eliminar(string rol);                      // Se elimina la cuenta
        void modificar(string rol, string descripcion); // Se modifica la descripcion del rol
        void redimensionar(int n); // Se redimensiona la tabla a n espacios
        void estadisticas();       // Debe mostrar las estadisticas
};
// Definicion de metodos:*******************************************************************************

/*****
* int registro_cuentas::hash(string rol)
******
* Resumen Función:
* Calcula el hash dado un rol.
******
* Input:
* string rol: El rol para el cual se calculará el hash.
******
* Returns:
* int: El valor del hash calculado.
*****/
int registro_cuentas::hash(string rol){
    string rolNum = rol;
    rolNum.erase(8, 1);
    int hashOut = stoi(rolNum) % ranuras;
    return hashOut;
}


/*****
* int registro_cuentas::p(string rol, int i)
******
* Resumen Función:
* Calcula la ranura a revisar en caso de colisión dado el rol y el intento i.
******
* Input:
* string rol: El rol para el cual se calculará la ranura.
* int i: El número de intento.
******
* Returns:
* int: La ranura a revisar.
*****/
int registro_cuentas::p(string rol, int i){
    int pOut = (hash(rol) + i) % ranuras;
    return pOut;
}


/*****
* cuenta registro_cuentas::obtener(string rol)
******
* Resumen Función:
* Dado el rol, devuelve la cuenta con ese rol.
******
* Input:
* string rol: El rol de la cuenta a obtener.
******
* Returns:
* cuenta: La cuenta con el rol especificado. Si no se encuentra, se devuelve una cuenta vacía.
*****/
cuenta registro_cuentas::obtener(string rol){
    cuenta vacia;
    vacia.nombre = "Cuenta no encontrada";
    vacia.rol = "Cuenta no encontrada";
    vacia.descripcion = "Cuenta no encontrada";
    int i = 0;
    while (tabla[p(rol, i)].rol != rol && i < 16)
    {
        i++;
    }
    if (i < 16)
    {
        cout << tabla[p(rol, i)].nombre << " " << tabla[p(rol, i)].descripcion << endl;
        return tabla[p(rol, i)];
    }
    else
    {
        return vacia;
    }
}


/*****
* void registro_cuentas::agregar(cuenta c)
******
* Resumen Función:
* Agrega una cuenta a la tabla.
******
* Input:
* cuenta c: La cuenta a agregar.
******
* Returns:
* void
*****/
void registro_cuentas::agregar(cuenta c){
    string rolStr = c.rol;
    int k = hash(c.rol);
    int i = 0;
    bool flag = false;
    while (tabla[k].rol != "" && i < ranuras + 1){
        if (tabla[k].rol == c.rol){
            cout << "Rol ya existente" << endl;
            flag = true;
        }
        i++;
        k = (hash(c.rol) + p(c.rol, i)) % ranuras;
    }
    if (flag == false){
        tabla[k] = c;
        rOcupadas++;
        if ((rOcupadas + 0.00) / (ranuras + 0.00) >= 0.75){
            redimensionar(ranuras * 2);
        }
    }
}


/*****
* void registro_cuentas::eliminar(string rol)
******
* Resumen Función:
* Elimina la cuenta con el rol especificado.
******
* Input:
* string rol: El rol de la cuenta a eliminar.
******
* Returns:
* void
*****/
void registro_cuentas::eliminar(string rol){
    int i = 0;
    while (tabla[p(rol, i)].rol != rol && i < ranuras + 1)
    {
        i++;
    }
    if (tabla[p(rol, i)].rol != "" && tabla[p(rol, i)].rol != "liberado")
    {
        tabla[p(rol, i)].rol = "liberado";
        tabla[p(rol, i)].nombre = "liberado";
        tabla[p(rol, i)].descripcion = "liberado";
        rOcupadas--;
    }
    else
    {
        cout << "Rol no encontrado" << endl;
    }
}


/*****
* void registro_cuentas::modificar(string rol, string descripcion)
******
* Resumen Función:
* Modifica la descripción del rol especificado.
******
* Input:
* string rol: El rol de la cuenta a modificar.
* string descripcion: La nueva descripción para el rol.
******
* Returns:
* void
*****/
void registro_cuentas::modificar(string rol, string descripcion){
    int i = 0;
    while (tabla[p(rol, i)].rol != rol)
    {
        i++;
    }
    tabla[p(rol, i)].descripcion = descripcion;
}


/*****
* void registro_cuentas::estadisticas()
******
* Resumen Función:
* Muestra las estadísticas de la tabla.
******
* Input:
* None
******
* Returns:
* void
*****/
void registro_cuentas::estadisticas(){
    std::cout.precision(4);
    cout << "RANURAS OCUPADAS: " << rOcupadas << endl;
    cout << "RANURAS TOTALES: " << ranuras << endl;
    factor_de_carga = ((rOcupadas + 0.0) / ranuras);
    cout << "FACTOR DE CARGA: " << factor_de_carga << endl;
}


/*****
* void registro_cuentas::redimensionar(int n)
******
* Resumen Función:
* Redimensiona la tabla a n espacios.
******
* Input:
* int n: El nuevo tamaño de la tabla.
******
* Returns:
* void
*****/
void registro_cuentas::redimensionar(int n){
    cuenta *nueva_tabla = new cuenta[n];
    int old_ranuras = ranuras;
    ranuras = n;

    for (int i = 0; i < old_ranuras; ++i)
    {
        if (!tabla[i].rol.empty() && tabla[i].rol != "liberado")
        {
            int j = 0;
            int new_slot;
            do
            {
                new_slot = (hash(tabla[i].rol) + j) % ranuras;
                j++;
            } while (!nueva_tabla[new_slot].rol.empty());
            nueva_tabla[new_slot] = tabla[i];
        }
    }

    delete[] tabla;
    tabla = nueva_tabla;
}