#include <iostream>
#include <string>
#include <fstream>
#include "Bin.h"
#include "DBService.h"

void process(std::string data);

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

            while (std::getline(csv, line)) {
                if (row > 0) {
                    process(line);
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

void process(std::string data) {
    Bin bin;

    data.erase(std::remove(data.begin(), data.end(), '\"'), data.end());
    std::stringstream ss(data);

    std::string text;
    int column = 0;
    while (std::getline(ss, text, ';')) {
        switch (column) {

            case 0:
                bin.SetBin(text);
                break;

            case 1:
                bin.SetBrand(text);
                break;

            case 2:
                bin.SetIssuer(text);
                break;

            case 3:
                if (text == "t") {
                    bin.SetCredit(true);
                } else {
                    bin.SetCredit(false);
                }
                break;
        }

        column += 1;
    }

    // Bin completo
    std::cout << bin.to_string() << std::endl;
}