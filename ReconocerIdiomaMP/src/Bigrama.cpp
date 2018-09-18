/** 
 * @file Bigrama.cpp
 * @author DECSAI
 * @warning Sustituir por el realizado por el alumno en la práctica 4
*/
#include <iostream>
#include"Bigrama.h"

using namespace std;

Bigrama::Bigrama() {
    _bigrama[0] = '\0';
    _frecuencia = -1;
}

const char* Bigrama::getBigrama() const{
    return _bigrama;
}

int Bigrama::getFrecuencia() const{
    return _frecuencia;
}

void Bigrama::setBigrama(const char cadena[]){
     int longitud = 0;
    
    for (int i = 0; cadena[i] != '\0'; i++)
        longitud++;
    
    if (longitud >= 2){
        for (int i = 0; i < 2; i++){
            _bigrama[i] = cadena[i];
        }
        _bigrama[2] = '\0';
    }
}

void Bigrama::setFrecuencia(int frec){
    _frecuencia = frec;
}

void ordenaAscFrec(Bigrama *v, int n){
    Bigrama aux;
    for (int j = 0; j < n; j++)
        for (int i = 1; i < n; i++)
            if ((v[i].getFrecuencia()) < (v[i-1].getFrecuencia())){
                aux = v[i];
                v[i] = v[i-1];
                v[i-1] = aux;
            }   
}

void ordenaAscBigr(Bigrama *v, int n){
    Bigrama aux;
    for (int i = 1; i < n; i++)
        if (v[i].getBigrama()[0] < v[i-1].getBigrama()[0]){
            aux = v[i];
            v[i] = v[i-1];
            v[i-1] = aux;
        }
        else if (v[i].getBigrama()[0] == v[i-1].getBigrama()[0] && v[i].getBigrama()[1] < v[i-1].getBigrama()[1]){
            aux = v[i];
            v[i] = v[i-1];
            v[i-1] = aux;
        }
}


void imprimeBigramas(const Bigrama *v, int n)  {
    cout << "Lista de " << n << " bigramas:" <<endl;
    for (int i=0; i<n; i++)
        cout << v[i].getBigrama() << "-" << v[i].getFrecuencia()<< ", "; // << endl;
}
