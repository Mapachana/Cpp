/** 
 * @file Idioma.cpp
 * @author DECSAI
 * @warning Código incompleto. Implementar la clase completa
*/

#include <iostream>
#include "Idioma.h"
#include <fstream>
#include<cstring>

using namespace std;

Idioma::Idioma(){
    _idioma = "";
    _conjunto = NULL;
    _nBigramas = 0;
}

 Idioma::Idioma(int nbg){
     _idioma = "";
    _conjunto = new Bigrama [nbg];
    _nBigramas = nbg;
 }
 
 Idioma::Idioma(const Idioma& orig){
     _idioma = orig._idioma;
     _nBigramas = orig._nBigramas;
     _conjunto = new Bigrama [_nBigramas];
     for (int i = 0; i < _nBigramas; i++)
             _conjunto[i] = orig._conjunto[i];
 }
 
 Idioma::~Idioma(){
     liberarMemoria();
 }
 
 Idioma& Idioma::operator =(const Idioma& orig){
     copiar(orig);
 }
  
   std::string Idioma::getIdioma() const{
       return _idioma;
   }
   
   void Idioma::setIdioma(const std::string& id){
       _idioma = id;
   }
   
   Bigrama Idioma::getPosicion(int p) const{
       if (p >= _nBigramas)
           cerr << "La posición no es correcta" << endl;
       else{
           return _conjunto[p];
       }
   }
   
   void Idioma::setPosicion(int p, const Bigrama & bg){
       if (p >= _nBigramas)
           cerr << "La posición no es correcta" << endl;
       else{
           _conjunto[p].setBigrama(bg.getBigrama());
           _conjunto[p].setFrecuencia(bg.getFrecuencia());
       }
   }
   
   int Idioma::findBigrama(const std::string& bg) const{
       string aux;
       bool encontrado = false;
        int posicion = -1;
       int i = 0;
       while (i < _nBigramas && !encontrado){
           aux = _conjunto[i].getBigrama();
           if (aux == bg )
                posicion = i;
           i++;
       }
        return posicion;
   }
   
   void Idioma::ordenar(){
       Bigrama aux;
        for (int j = 0; j < _nBigramas; j++)
            for (int i = 1; i < _nBigramas; i++)
                if ((_conjunto[i].getFrecuencia()) > (_conjunto[i-1].getFrecuencia())){
                    aux = _conjunto[i];
                    _conjunto[i] = _conjunto[i-1];
                    _conjunto[i-1] = aux;
            }
        
   }
   
   bool Idioma::salvarAFichero(const char *fichero) const{
       bool sinfallos = false;
       ofstream salida;
       
       salida.open(fichero);
       
       if (salida){
           salida << (*this);
           sinfallos = true;
       }
       else{
           cerr  << "Error abriendo el fichero" << endl;
           sinfallos = false;
       }
       salida.close();
       
       return sinfallos;
   }
   
   bool Idioma::cargarDeFichero(const char *fichero){
       ifstream entrada;
       bool resultado = false;
       
       entrada.open(fichero);

       if (entrada){
           entrada >> (*this);
           if (entrada)
               resultado = true;
           else{
               cerr << "Error leyendo fichero" << endl;
               resultado = false;
           }
       }
       else
           cerr << "Error abriendo fichero" << endl;
       
       entrada.close();
       
       return resultado;
   }
   
   void Idioma::reservarMemoria(int n){
     if (_conjunto != NULL){
         delete[] _conjunto;
     }
     _conjunto = new Bigrama [n];
     _nBigramas = n;
 }
   
  void Idioma::liberarMemoria(){
      if (_conjunto != NULL)
        delete[] _conjunto;
      _nBigramas = 0;
      _idioma = "";
  }
  
  void Idioma::copiar(const Idioma& otro){
      _idioma = otro._idioma;
     _nBigramas = otro._nBigramas;
     if (_conjunto != NULL)
         delete[] _conjunto;
     _conjunto = new Bigrama [_nBigramas];
     for (int i = 0; i < _nBigramas; i++)
         _conjunto[i] = otro._conjunto[i];
  }
 
   std::ostream & operator<<(std::ostream & os, const Idioma & i){
       string linea = "MP-BIGRAMAS_IDIOMA-T-1.0";
       
           os << linea << endl;
           os << i._idioma << endl;
           os << i._nBigramas << endl;
           for (int j = 0; j < i._nBigramas; j++){
               os << i._conjunto[j].getBigrama() << " " << i._conjunto[j].getFrecuencia() << endl;
           }
       return os;    
   }
   
   std::istream & operator>>(std::istream & is, Idioma & i){
       string aux;
       int numbig;
       Bigrama auxiliar;
       char cadenac [3];
       
            is >> aux;
            is >> aux;
            i.setIdioma(aux);
            is >> numbig;
            i.reservarMemoria(numbig);

            for (int j = 0; j < i._nBigramas; j++){
                is >> aux;
                for (int k = 0; k < 2; k++)
                    cadenac[k] = aux[k];
                cadenac[2] = '\0';
                auxiliar.setBigrama(cadenac);
                is >> numbig;
                auxiliar.setFrecuencia(numbig);
                i.setPosicion(j, auxiliar);
            }
           return is;
   }
   
    
    
   
   
   
