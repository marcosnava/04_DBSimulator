//
// Created by nava on 02/05/23.
//

#ifndef INC_04_DBSIMULATOR_LISTADUPLAMENTELIGADA_H
#define INC_04_DBSIMULATOR_LISTADUPLAMENTELIGADA_H

#include <stdlib.h>
#include "utils.h"

// Estruturas
struct LLno {
    char nome[101];
    int reg;
    struct LLno *proximo;
    struct LLno *anterior;
};

// Variáveis
extern struct LLno *LLregInicio;
extern struct LLno *LLregFim;
extern struct LLno *LLaux;
extern struct LLno *LLregAnterior;
extern struct LLno *LLnovo;
extern struct LLno *LLregAtual;

// Protótipos
void LLinicializar();
void LLfinalizar();
void LLfinalizarElemento(struct LLno *elemento);
struct LLno *LLnovoNo(char *nome, int reg);

void LLadicionar(char *nome, int reg);
void LLadicionarNoInicio();
void LLadicionarNoMeio();
void LLadicionarNoFim();

void LLexcluir(char *nome);
void LLexcluirNoInicio();
void LLexcluirNoMeio();
void LLexcluirNoFim();

void LLprimeiro();
void LLultimo();
struct LLno *LLregistroAtual();
BOOLEAN LLproximo();
BOOLEAN LLanterior();

#endif //INC_04_DBSIMULATOR_LISTADUPLAMENTELIGADA_H
