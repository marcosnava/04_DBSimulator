#include <stdio.h>
#include <string.h>
#include "arrayList.h"
#include "listaDuplamenteLigada.h"

// Variaveis
struct ALregistro registro;
struct LLno no;

// Constantes
enum
{
    OP_NAO_SELECIONADA = 0,
    OP_ADICIONAR,
    OP_EXCLUIR,
    OP_LISTAR_FISICO,
    OP_LISTAR_LOGICO_CRESCENTE,
    OP_LISTAR_LOGICO_DECRESCENTE,
    OP_SAIR,
};

// Protótipos
void inicializar();
void finalizar();
void adicionar(struct ALregistro reg);
void excluir(struct ALregistro reg);
void listarFisico();
void listarLogicoCrescente();
void listarLogicoDecrescente();
int menu();

int main() {
    int opcao = OP_NAO_SELECIONADA;
    char nome[101];
    char endereco[101];
    char telefone[21];

    inicializar();

    while(opcao != OP_SAIR)
    {
        opcao = menu();
        switch(opcao)
        {
            case OP_ADICIONAR:
                printf("Digite o nome: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Digite o endereco: ");
                fgets(endereco, 100, stdin);
                endereco[strcspn(endereco, "\n")] = 0;

                printf("Digite o telefone: ");
                fgets(telefone, 20, stdin);
                telefone[strcspn(telefone, "\n")] = 0;

                strcpy(registro.nome, nome);
                strcpy(registro.endereco, endereco);
                strcpy(registro.telefone, telefone);

                adicionar(registro);
                break;
            case OP_EXCLUIR:
                printf("Digite o nome: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;

                strcpy(registro.nome, nome);

                excluir(registro);
                break;
            case OP_LISTAR_FISICO:
                listarFisico();
                break;
            case OP_LISTAR_LOGICO_CRESCENTE:
                listarLogicoCrescente();
                break;
            case OP_LISTAR_LOGICO_DECRESCENTE:
                listarLogicoDecrescente();
                break;
            case OP_SAIR:
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    finalizar();

    return 0;
}

void inicializar()
{
    ALinicializar();
    LLinicializar();
}

void finalizar()
{
    ALfinalizar();
    LLfinalizar();
}

int menu()
{
    int op;

    printf("%d - Adicionar\n", OP_ADICIONAR);
    printf("%d - Excluir\n", OP_EXCLUIR);
    printf("%d - Listar ordem Fisica\n", OP_LISTAR_FISICO);
    printf("%d - Listar ordem Logica Crescente\n", OP_LISTAR_LOGICO_CRESCENTE);
    printf("%d - Listar ordem Logica Decrescente\n", OP_LISTAR_LOGICO_DECRESCENTE);
    printf("%d - Sair\n", OP_SAIR);
    printf("Selecione sua opcao: ");
    scanf("%d", &op);
    scanf("%*c");

    return op;
}

void adicionar(struct ALregistro reg)
{
    BOOLEAN deuCerto = FALSE;
    int nRegistro = 0;

    // adicionar no array list
    deuCerto = ALadicionar(&registro, &nRegistro);
    if(!deuCerto)
    {
        ALexpandir();
        ALadicionar(&registro, &nRegistro);
    }

    // adicionar na lista duplamente ligada
    LLadicionar(reg.nome, nRegistro);
}

void excluir(struct ALregistro reg)
{
    // excluir no array list
    ALexcluirLogico(&reg);

    // excluir na lista duplamente ligada
    LLexcluir(reg.nome);
}

void listarFisico()
{
    printf("Listagem por ordem de cadastro:\n");
    int i;
    for(i = 0; i < ALquantidadeElementos(); i++)
    {
        if(ALbuscarPorIndice(i, &registro)) {
            printf("Registro.: %d\n", i);
            printf("Nome.....: %s\n", registro.nome);
            printf("Endereco.: %s\n", registro.endereco);
            printf("Telefone.: %s\n\n", registro.telefone);
        }
    }
    printf("FIM DO ARQUIVO\n");
}

void listarLogicoCrescente()
{
    printf("Listar Ordem Crescente\n");
    LLprimeiro();
    do {
        if(LLregAtual != NULL)
        {
            ALbuscarPorIndice(LLregAtual->reg, &registro);
            printf("Registro.: %d\n", LLregAtual->reg);
            printf("Nome.....: %s\n", LLregAtual->nome);
            printf("Endereco.: %s\n", registro.endereco);
            printf("Telefone.: %s\n\n", registro.telefone);
        }
    } while(LLproximo());
}

void listarLogicoDecrescente()
{
    printf("Listar Ordem Decrescente\n");
    LLultimo();
    do {
        if(LLregAtual != NULL)
        {
            ALbuscarPorIndice(LLregAtual->reg, &registro);
            printf("Registro.: %d\n", LLregAtual->reg);
            printf("Nome.....: %s\n", LLregAtual->nome);
            printf("Endereco.: %s\n", registro.endereco);
            printf("Telefone.: %s\n\n", registro.telefone);
        }
    } while(LLanterior());
}
