#include <iostream>
#include <string>
#include <fstream>
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

    // Evaluamos si están los parámetros mínimos
    if (argc >= 2) {
        // Abrimos el archivo
        std::ifstream csv(argv[1]);
        if (csv.is_open()) {

#pragma omp parallel // Crea una region paralela
#pragma omp single // Sólo un hilo ejecutará la siguiente instrucción
            {
                for (std::string line; std::getline(csv, line);) {
#pragma omp task firstprivate(line)
                    {
                        // Procesamos línea a línea
                        DBService service;
                        service.process(line);
                    }
                }

#pragma omp taskwait
            }
            csv.close();
        }
    } else {
        std::cout << "El programa " << argv[0] << " requiere la ruta al CSV" << std::endl;
        std::cout << argv[0] << " /Compartido/bins.csv" << std::endl;
    }

    return 0;
}

