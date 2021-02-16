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

/**Bibliotecas padrao**/
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <cstdlib>
#include <iomanip>

/**Classes**/
#include "Diretorio.h"

using namespace std;

void cabecalho()
{
    cout << "Atividade 01 - ED2 - Hash Extensivel" <<endl;
    cout << "Aluno: Ivanylson Honorio Goncalves - MAT:201776002" <<endl;
    cout << endl;
}
void primeiraForma(int tamMB, int nBits)
{
    int nInsercoes;
    int nCasasMesmoPadrao;
    int naoInseridos = 0;

    cout << "Insira o numero de inserções N:" << endl;
    cin >> nInsercoes;
    cout << "Insira o numero de casas N para mesmo padrão:" << endl;
    cin >> nCasasMesmoPadrao;

    Diretorio* dir = new Diretorio(nBits, tamMB);
    cout << "Diretório criado" << endl;


    string pseudoChave = "";
    for (int i = 0; i < nInsercoes; i++)
    {
        for (int k = 0; k < nCasasMesmoPadrao; k++)
        {
            pseudoChave.push_back('0');
        }
        for (int j = 0; j < (nBits - nCasasMesmoPadrao); j++)
        {
            pseudoChave.push_back(random() % 2 + '0');
        }
        bool existe = dir->buscaPseudoChave(pseudoChave);
        cout << "Busca: " << existe << endl;
        if(!existe)
        {
            dir->inserePseudoChave(pseudoChave);
        }
        else
        {
            cout << "nao inseriu: " << naoInseridos << endl;
            naoInseridos++;
        }

        pseudoChave.erase(pseudoChave.begin(),pseudoChave.end());
    }


    dir->imprimeDiretorioAleatorio();
    cout << "Não inseridos: " << naoInseridos << endl;
    int a = nInsercoes - naoInseridos;
    int b = dir->calculaNumBaldes() * tamMB;
    double fatorCarga = double(a)/double(b);
    cout << "Fator de Carga: " << fixed << setprecision(4) << fatorCarga << endl;
    cout << "Tamanho Diretório: " << dir->getTamanhoDiretorio() << endl;
    cout << "Número de Baldes: " << dir->calculaNumBaldes() << endl;
}


void segundaForma(int tamanhoDosBaldes, int nbits)
{
    Diretorio *diretorio = new Diretorio(tamanhoDosBaldes,tamanhoDosBaldes);
    int escolha;
    string psdChaves;

    cout<<"1 - Insercoes de N pseudo-chaves aleatorias =>"<<tamanhoDosBaldes <<" ."<<endl;
    cout<<"2 - Insercoes de N pseudo-chaves escolhendo o bit inicial"<<endl;
    cin>>escolha;

    srand (time(NULL));

    if(escolha == 1)
    {
        //Bits aletorio;
        for(int j=0; j<tamanhoDosBaldes; j++)
        {
            for(int i=0; i<nbits; i++)
            {
                int teste=(rand()%100)%2;
                char o= teste;
                psdChaves+=std::to_string(teste);
            }
            diretorio->inserirChave(psdChaves);
            psdChaves.clear();
        }
        diretorio->imprimeDiretorio();
    }
    if(escolha == 2)
    {
        int primeirobit;
        cout<<"Escolha o primeiro bit da sua chave com '0' e/ou '1'"<<endl;
        cin>>primeirobit;

        //De acordo com a escolha do usuario o primeiro bit é fixo e o resto da chave aletoria entre 1 e 0
        char pri= primeirobit;
        psdChaves=std::to_string(primeirobit);

        for(int j=0; j<10; j++)
        {

            psdChaves=std::to_string(primeirobit);


            for(int i=1; i<nbits; i++)
            {

                int teste=(rand()%100)%2;

                char o= teste;
                psdChaves+=std::to_string(teste);
            }

            diretorio->inserirChave(psdChaves);
            psdChaves.clear();

        }

    }


}
/**
A função principal deve solicitar ao usuário o tamanho M a ser usado para os baldes
e o número de bits B a ser usado para as pseudo-chaves.
Devem ser realizados dois testes:
Inserções de N pseudo-chaves aleatórias
Inserções de N pseudo-chaves iniciadas com um mesmo padrão de bits

**/
int main()
{
    system("clear");
    cabecalho();
    int tamMB=0, nBits=0;
    int opcao=0;
    cout << "Insira o tamanho M dos baldes:" << endl;
    cin >> tamMB;
    cout << "Insira o numero de bits B para as  pseudo-chaves:" << endl;
    cin >> nBits;
    cout << endl;
    do
    {
        cout << "Escolha uma opção abaixo para executar de forma diferente, mas como mesmo resultado" << endl;
        cout << "1 - Primeira Forma" << endl;
        cout << "2 - Segunda Forma" << endl;
        cout << "-1 - Sair" << endl;
        cin >> opcao;

        switch(opcao)
        {
        case 1 :
        {
            system("clear");
            primeiraForma(tamMB,nBits);
            break;
        }
        case 2:
        {
            system("clear");

            segundaForma(tamMB,nBits);
            break;
        }
        default:
        {
            cout <<"Opção invalida" << endl;
        }
        }
    }
    while(opcao!=-1);
    cout << "Obrigado. Até...Abraço" <<endl;
    return 0;
}
