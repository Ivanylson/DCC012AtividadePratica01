/**
    UNIVERSIDADE FEDERAL DE JUIZ DE FORA
    INSTITUTO DE CIÊNCIAS EXATAS
    DEPARTAMENTO DA CIẼNCIA DA COMPUTAÇÃO

    TRABALHO DE ESTRUTURA DE DADOS 2(||) - 2020.3 (ERE) - Hash Extensivel
    PROF.DR.MARCELO CANIATO RENHE

    GRUPO:
    IVANYLSON HONORIO GONÇALVES    MAT 201776002


    main.cpp
    *** comando pra rodar ***
    MAC/LINUX:  clear && g++ -std=c++11 main.cpp -o main && ./main
    WINDOWS:    cls & g++ -std=c++11 main.cpp -o main & main.exe

*/

#ifndef DIRETORIO_H
#define DIRETORIO_H
/**Bibliotecas**/
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <cmath>

/**Classe**/
#include "Balde.h"

using namespace std;
/**
Implementar um tipo abstrato de dados Diretório para armazenar o conjunto de baldes. Esse tipo de dados
deve possuir operações para inserir, buscar, dividir baldes e duplicar diretório.
**/

class Diretorio{
    private:
        /**Variavel**/
        int profundidadeGlobal; /**1 e 2**/
        int tamanhoBits; /**1**/
        int tamanhoDoBalde; /**2**/

        /**Vector**/
        vector<Balde*> conjuntoDeBaldesAleatorios; /**1**/
        vector<Balde*> baldes; /**2**/

        float funcaoHash(int chave); /**2**/

    public:
        Diretorio(int numeroDeBits, int tamanhoM); /**1 e 2**/
        ///Aleatorio
        int getTamanhoDiretorio();/**1**/
        int calculaNumBaldes();
        void inserePseudoChave(string pseudoChave);/**1**/
        bool buscaPseudoChave(string pseudoChave);/**1**/
        void divideBaldesPseudoChave(int indiceDoBalde);/**1**/
        void duplicaDiretorioPseudoChave();/**1**/
        void imprimeDiretorioAleatorio();/**1**/
        ///Diretorio
        void inserirChave(string chave);
        int getIndice(int indiceDoBalde, int profundidadetGlobal);
        void particionaDiretorio();
        void duplicaBalde(int indice,string chave);
        void imprimeDiretorio();

};

#endif // DIRETORIO_H
