/**
 * @file ContadorBigramas.cpp
 * @author DECSAI
 * @warning Código incompleto. Implementar la clase completa
*/

#include <iostream>
#include "ContadorBigramas.h"
#include "Idioma.h"
#include <fstream>
#include <cstring>

using namespace std;

ContadorBigramas::ContadorBigramas(const std::string& caracteresValidos){
    int tamanio = caracteresValidos.length();
    _bigramas = new int* [tamanio];
    _bigramas[0] = new int [tamanio*tamanio];
    for (int i = 1; i < tamanio; i++)
        _bigramas[i] = _bigramas[i-1]+tamanio;
    _caracteresValidos = caracteresValidos;
    for (int i = 0; i < tamanio; i++)
	for (int j = 0; j < tamanio; j++)
	    _bigramas[i][j] = 0;
}

ContadorBigramas::ContadorBigramas(const ContadorBigramas & orig){
    _bigramas = orig._bigramas;
    _caracteresValidos = orig._caracteresValidos;
}

ContadorBigramas::~ContadorBigramas(){
    liberarMemoria();
}

int ContadorBigramas::getSize() const{
    return _caracteresValidos.length();
}

int ContadorBigramas::getBigramasActivos() const{
    int bigact = 0;
    for (int i = 0; i < _caracteresValidos.length(); i++)
        for (int j = 0; j < _caracteresValidos.length(); j++){
            if (_bigramas[i][j] > 0)
                bigact++;
        }
    return bigact;
}

bool ContadorBigramas::addBigrama(const char cadena[], int frecuencia){
    int pos1 = -1;
    int pos2 = -1;
    bool comprobacion = true;
    for (int i = 0; i < _caracteresValidos.length()-1; i++){
         if (cadena[0] == _caracteresValidos[i])
             pos1 = i;
         if (cadena[1] == _caracteresValidos[i])
             pos2 = i;
    }

    if (pos1 < 0 || pos1 > _caracteresValidos.length() || pos2 < 0 || pos2 > _caracteresValidos.length())
        comprobacion = false;
    if (comprobacion)
        if (frecuencia == 0)
            _bigramas[pos1][pos2]++;
        else
            _bigramas[pos1][pos2] = _bigramas[pos1][pos2]+frecuencia;

    return comprobacion;
}

ContadorBigramas& ContadorBigramas::operator=(const ContadorBigramas& orig){
    copiar(orig);
}

bool ContadorBigramas::calcularFrecuenciasBigramas(const char* nfichero){
    ifstream entrada;
    bool comprobacion = true;
    char aux [3];
    aux[2] = '\0';
    string auxiliar;

    entrada.open(nfichero);

    if (entrada){
        while (entrada >> auxiliar){
            int longitud = auxiliar.length();
            if (longitud > 1){
                for (int i = 0; i < longitud-1; i++){
                    aux[0] = tolower(auxiliar[i]);
                    aux[1] = tolower(auxiliar[i+1]);
                    (*this).addBigrama(aux);
                }
            }
        }

    }
    else{
        cerr << "Error abriendo el fichero" << endl;
        comprobacion  = false;
    }

    entrada.close();

    return comprobacion;
}

Idioma ContadorBigramas::toIdioma() const{
    int numbig = (*this).getBigramasActivos();
    Idioma resultado (numbig);
    int cont = 0;
    Bigrama aux;
    char big [3];
    big[2] = '\0';
    while (cont < numbig){
        for (int i = 0; i < _caracteresValidos.length(); i++)
            for (int j = 0; j < _caracteresValidos.length(); j++)
                if (_bigramas[i][j] > 0){
                    big[0] = _caracteresValidos[i];
                    big[1] = _caracteresValidos[j];
                    aux.setBigrama(big);
                    aux.setFrecuencia(_bigramas[i][j]);
                    resultado.setPosicion(cont,aux);
                    cont++;
                }
    }
    return resultado;
}

void ContadorBigramas::fromIdioma(const Idioma &i){
    int cont = 0;
    char car1;
    int pos1 = 0;
    char car2;
    int pos2 = 0;
    int frec = 0;

    for (int j = 0; j < i.getSize(); j++){
        car1 = i.getPosicion(j).getBigrama()[0];
        car2 = i.getPosicion(j).getBigrama()[1];
        frec = i.getPosicion(j).getFrecuencia();

        for (int k = 0; k < _caracteresValidos.length(); k++){
            if (car1 == _caracteresValidos[k])
                pos1 = k;
            if (car2 == _caracteresValidos[k])
                pos2 = k;
        }
        _bigramas[pos1][pos2] = frec;
    }
}

void ContadorBigramas::reservarMemoria(int n){
     _bigramas = new int* [n];
     _bigramas[0] = new int [n*n];
    for (int i = 1; i < n; i++)
        _bigramas[i] = _bigramas[i-1]+n;

 }

  void ContadorBigramas::liberarMemoria(){
      delete[] _bigramas[0];
      delete[] _bigramas;
      _caracteresValidos = "";
  }

  void ContadorBigramas::copiar(const ContadorBigramas& otro){
      (*this).liberarMemoria();
      _caracteresValidos = otro._caracteresValidos;
       int tamanio = _caracteresValidos.length();
    _bigramas = new int* [tamanio];
    _bigramas[0] = new int [tamanio*tamanio];
    for (int i = 1; i < tamanio; i++)
        _bigramas[i] = _bigramas[i-1]+tamanio;
    for (int i = 0; i < tamanio; i++)
        for (int j = 0; i < tamanio; j++)
            _bigramas[i][j] = otro._bigramas[i][j];
  }
