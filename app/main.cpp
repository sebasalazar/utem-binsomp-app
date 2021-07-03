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

    if (argc >= 2) {
        std::ifstream csv(argv[1]);
        if (csv.is_open()) {

            std::string line;
            int row = 0;

            DBService service;
            while (std::getline(csv, line)) {
                if (row > 0) {
                    service.process(line);
                }

                row += 1;
            }

            csv.close();
        }
    } else {
        std::cout << "El programa " << argv[0] << " requiere la ruta al CSV" << std::endl;
        std::cout << argv[0] << " /Compartido/bins.csv" << std::endl;
    }

    return 0;
}

