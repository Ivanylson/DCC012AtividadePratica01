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

#ifndef BALDE_H
#define BALDE_H

/**Bibliotecas**/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <chrono>
#include <sstream>

using namespace std;
/**
Implementar um tipo abstrato de dados Balde que permita armazenar pseudo-chaves. Utilize o tipo string para representá-las.

**/
class Balde
{
private:
    int profundidadeLocal;
    int tamanhoM;
    vector<string> pseudoChaves;
    //Tamanho Balde e sua profundidade
    int tamBalde;
    //Balde
    vector<string> balde;

public:
    Balde(int tamM);
    Balde(int profundidadeLocal,int tamBalde);
    ~Balde();
    /**Aleatorio**/
    int getProfundidadeLocal();
    int getTamanhoM();
    string getPseudoChave(int i);
    bool isCheio();
    void apagaPseudoChave(int i);
    void imprimeBaldeAleatorio();
    void insere(string pseudoChave);
    bool busca(string pseudoChave);
    void atualizaBalde(int profundidadeNova);

    /**Comum**/
    bool verificaBaldeCheio();
    bool verificaEspacoBalde();
    int insereChaveBalde(string psch);
    bool buscaPseudoch(string ch);
    int aumentaProfundidadeLocal();
    string valores(int ind);
    void apaga(string ch);
    int gettam();
    void imprimeBalde();
};
#endif // BALDE_H
