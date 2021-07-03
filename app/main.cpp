#include <iostream>
#include <string>
#include "Bin.h"
#include "DBService.h"

/**
 * 
 * @param argc Cantidad de argumentos que reciben por la línea de comandos.
 * @param argv Matriz asociativa con los argumentos.
 * @return Estado de terminación de la aplicación (0 es éxito), 
 * cualquier otro valor es asumido como error de ejecución por el sistema operativo.
 */
int main(int argc, char** argv) {

    Bin vacio;
    std::cout << "[" << vacio.GetId() << "]" << std::endl;

    DBService service;
    std::cout << service.GetVersion() << std::endl;

    return 0;
}

