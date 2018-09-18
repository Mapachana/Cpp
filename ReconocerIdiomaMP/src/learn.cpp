/**
 * @file learn.cpp
 * @author DECSAI
*/

#include <iostream>
#include <cstring>
#include <string>
#include "Bigrama.h"
#include "Idioma.h"
#include "ContadorBigramas.h"

/// ... Resto de include

using namespace std;

/**
 * @brief Imprime mensaje de ayuda
*/
void pinta_mensaje() {
    cout << "Formato:" << endl;
    cout << "learn {-c|-a} [-t|-b] [-l nombreIdioma] [-f ficheroSalida] texto1.txt texto2.txt texto3.txt .... " << endl;
    cout << "           aprende el codigo para el lenguaje nombreIdioma a partir de los ficheros texto1.txt texto2.txt texto3.txt ..." << endl;
    cout << endl;
    cout << "Parámetros:" << endl;
    cout << "-c|-a: operación crear fichero de idioma (-c) o añadir a fichero de idioma (-a)" << endl;
    cout << "-l nombreIdioma: idioma (unknown por defecto)" << endl;
    cout << "-f ficheroSalida:  nombre del fichero de salida (salida.bgx por defecto)" << endl;
    cout << "texto1.txt texto2.txt texto3.txt ....: nombres de los ficheros de entrada (debe haber al menos 1)" << endl;
}

int main(int argc, char *argv[]) {
	/// Cadena de caracteres válidos de ISO8859-1 para múltiples idiomas
    string valid="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

	/// ... Resto de variables y código de main

    ContadorBigramas miidioma (valid);
    string opcion;
    string fsalida = "out.bgr";
    string idioma = "unknown";
    int pos = 2;

    if (argc == 1){
        cout << "Numero de argumentos insuficientes" << endl;
        pinta_mensaje();
    }

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-c") == 0)
            opcion = "c";
        else if (strcmp(argv[i],"-a") == 0)
            opcion = "a";

        else if (strcmp(argv[i], "-f") == 0){
            fsalida = argv[i+1];
            pos = i+2;
        }
        else if (strcmp(argv[i],"-l") == 0){
            idioma = argv[i+1];
            pos = i+2;
        }
    }

    if (opcion == "c"){
        for (int i = pos; i < argc; i++)
            miidioma.calcularFrecuenciasBigramas(argv[i]);

        Idioma nuevoidioma = miidioma.toIdioma();
        nuevoidioma.setIdioma(idioma);
        nuevoidioma.ordenar();
        nuevoidioma.salvarAFichero(fsalida.c_str());
    }
    else if (opcion == "a"){
        Idioma nuevoidioma;
        nuevoidioma.cargarDeFichero(fsalida.c_str());
        miidioma.fromIdioma(nuevoidioma);

        for (int i = pos; i < argc; i++)
            miidioma.calcularFrecuenciasBigramas(argv[i]);

        nuevoidioma = miidioma.toIdioma();
        nuevoidioma.setIdioma(idioma);
        nuevoidioma.ordenar();
        nuevoidioma.salvarAFichero(fsalida.c_str());
    }
    else
        pinta_mensaje();




   return 0;
}
