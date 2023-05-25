//
// Created by nava on 18/05/23.
//

#ifndef INC_04_DBSIMULATOR_ARVOREBINARIA_H
#define INC_04_DBSIMULATOR_ARVOREBINARIA_H

#include <stdlib.h>

// Estruturas
struct ABno {
    char nome[101];
    int reg;
    struct ABno *direita;
    struct ABno *esquerda;
};

// Variáveis
extern struct ABno *ABinicio;
extern struct ABno *ABanterior;

// Protótipos
struct ABno *ABnovoNo(char *nome, int reg);
void ABinicializar();
void ABfinalizar(struct ABno *elemento);

void ABadicionar(struct ABno *aonde, struct ABno *novo);
struct ABno *ABlocalizar(struct ABno *aonde, char *nome);
void ABexcluir(char *nome);

#endif //INC_04_DBSIMULATOR_ARVOREBINARIA_H
