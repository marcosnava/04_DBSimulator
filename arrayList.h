//
// Created by nava on 02/05/23.
//

#ifndef INC_04_DBSIMULATOR_ARRAYLIST_H
#define INC_04_DBSIMULATOR_ARRAYLIST_H

#include "utils.h"

// Estruturas
struct ALregistro
{
    char nome[101];
    char endereco[101];
    char telefone[21];
};

// Constantes
enum
{
    AL_NAO_ACHEI = -1
};

// Variáveis
extern int ALtamanho;
extern struct ALregistro *ALlista;
extern int ALposicao;

// Protótipos
BOOLEAN ALadicionar(struct ALregistro *reg, int *nReg);
int ALquantidadeElementos();
BOOLEAN ALbuscarPorIndice(int indice, struct ALregistro *reg);
int ALbuscarPorValor(struct ALregistro *reg);
void ALexcluir(struct ALregistro *reg);
void ALexpandir();

void ALinicializar();
void ALfinalizar();

#endif //INC_04_DBSIMULATOR_ARRAYLIST_H
