#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N 5 


typedef struct dadosMedicamento {
    int codigodebarra;
    char medicamento[100];
    char datacadastro[11];
    int quantidade; 
    float preco;
} dadosMedicamento;

typedef struct page {
    int qnt = 0; 
    bool folha = false; 
    int codigos[N - 1];  
    dadosMedicamento* medicamentos[N - 1]; 
    struct page* filhos[N];  
    struct page* pai = NULL;  
};
//criando pagina
page *criarpagina(bool folha) {
    page *novapagina = (page*) malloc(sizeof(page));
    if (novapagina != NULL) {  
        novapagina->qnt = 0;  
        novapagina->folha = folha;  
        for (int i = 0; i < N - 1; i++) {
            novapagina->codigos[i] = 0;  
            novapagina->medicamentos[i] = NULL;  
        }
        for (int i = 0; i < N; i++) {
            novapagina->filhos[i] = NULL;  
        }
        novapagina->pai = NULL;  
    }
    return novapagina;
}
// Função auxiliar para dividir uma página (split)
void dividirPagina(pagina* pai, int indice, pagina* paginaCheia) {
    int i, j;
    pagina* novaPagina = criarpagina(paginaCheia->folha);

    novaPagina->qnt = N / 2;
    paginaCheia->qnt = N / 2;

    // Movendo metade dos elementos para a nova página
    for (i = 0, j = (N + 1) / 2; j < N - 1; i++, j++) {
        novaPagina->codigos[i] = paginaCheia->codigos[j];
        novaPagina->medicamentos[i] = paginaCheia->medicamentos[j];
    }

    if (!paginaCheia->folha) {
        for (i = 0, j = (N + 1) / 2; j < N; i++, j++) {
            novaPagina->filhos[i] = paginaCheia->filhos[j];
        }
    }

    // Inserir nova página no pai
    for (i = pai->qnt; i >= indice + 1; i--) {
        pai->filhos[i + 1] = pai->filhos[i];
    }
    pai->filhos[indice + 1] = novaPagina;

    for (i = pai->qnt - 1; i >= indice; i--) {
        pai->codigos[i + 1] = pai->codigos[i];
    }
    pai->codigos[indice] = paginaCheia->codigos[(N + 1) / 2 - 1];
    pai->qnt++;
}

