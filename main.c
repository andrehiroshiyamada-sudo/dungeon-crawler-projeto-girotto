

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINHAS  25
#define MAX_COLUNAS 25

char mapa[MAX_LINHAS][MAX_COLUNAS];
char mapa_salvo[MAX_LINHAS][MAX_COLUNAS];
int  num_linhas, num_colunas;

int  jogador_linha, jogador_coluna;
char jogador_direcao;
int  vidas;
int  arma;
int  tem_chave;
int  fase_atual;

int  monstro_linha[20];
int  monstro_coluna[20];
char monstro_tipo[20];
int  monstro_vivo[20];
int  total_monstros;

int  boss_vida;
int  boss_contador_turno;

char celula_sob_jogador;

int  jogador_linha_inicio;
int  jogador_coluna_inicio;
char jogador_direcao_inicio;

void pausar() {
    char c;
    printf("\n[pressione enter]\n");
    scanf(" %c", &c);
}

void desenhar() {
    int linha, coluna;
    system("cls");
    printf("fase:%d  vidas:%d  arma:%d  chave:%d\n\n",
        fase_atual, vidas, arma, tem_chave);
    for (linha = 0; linha < num_linhas; linha++) {
        for (coluna = 0; coluna < num_colunas; coluna++)
            printf("%c", mapa[linha][coluna]);
        printf("\n");
    }
    printf("\nw/a/s/d=mover  i=interagir  o=atacar  q=sair\n");
}

void salvar_mapa() {
    memcpy(mapa_salvo, mapa, sizeof(mapa));
    jogador_linha_inicio   = jogador_linha;
    jogador_coluna_inicio  = jogador_coluna;
    jogador_direcao_inicio = jogador_direcao;
}

void carregar_vila() {
    int linha, coluna;
    char temp[10][11] = {
        "**********",
        "*        *",
        "* N      *",
        "*        *",
        "*   >    *",
        "*        *",
        "*        *",
        "*      L *",
        "*        *",
        "**********"
    };
    fase_atual  = 0;
    num_linhas  = 10;
    num_colunas = 10;
    for (linha = 0; linha < num_linhas; linha++)
        for (coluna = 0; coluna < num_colunas; coluna++)
            mapa[linha][coluna] = temp[linha][coluna];
    jogador_linha      = 4;
    jogador_coluna     = 4;
    jogador_direcao    = '>';
    celula_sob_jogador = ' ';
    mapa[jogador_linha][jogador_coluna] = jogador_direcao;
    total_monstros = 0;
    salvar_mapa();
}

void carregar_andar1() {
    int linha, coluna;
    char temp[10][11] = {
        "**********",
        "*>       *",
        "*  *****D*",
        "*  *     *",
        "*  * k   *",
        "*  *     *",
        "*  ****  *",
        "*  @ *   *",
        "*    * L *",
        "**********"
    };
    fase_atual  = 1;
    num_linhas  = 10;
    num_colunas = 10;
    for (linha = 0; linha < num_linhas; linha++)
        for (coluna = 0; coluna < num_colunas; coluna++)
            mapa[linha][coluna] = temp[linha][coluna];
    jogador_linha      = 1;
    jogador_coluna     = 1;
    jogador_direcao    = '>';
    celula_sob_jogador = ' ';
    mapa[jogador_linha][jogador_coluna] = jogador_direcao;
    total_monstros = 0;
    tem_chave      = 0;
    salvar_mapa();
}

void carregar_andar2() {
    int linha, coluna;
    char temp[15][16] = {
        "***************",
        "*>            *",
        "*      @      *",
        "*  *********  *",
        "*  *       *  *",
        "*  *     X *  *",
        "*  *       *  *",
        "*  *       *  *",
        "*  **D******  *",
        "*             *",
        "*  O    @     *",
        "*             *",
        "*      D      *",
        "*          L  *",
        "***************"
    };
    fase_atual  = 2;
    num_linhas  = 15;
    num_colunas = 15;
    for (linha = 0; linha < num_linhas; linha++)
        for (coluna = 0; coluna < num_colunas; coluna++)
            mapa[linha][coluna] = temp[linha][coluna];
    jogador_linha      = 1;
    jogador_coluna     = 1;
    jogador_direcao    = '>';
    celula_sob_jogador = ' ';
    mapa[jogador_linha][jogador_coluna] = jogador_direcao;
    total_monstros    = 1;
    monstro_linha[0]  = 5;
    monstro_coluna[0] = 9;
    monstro_tipo[0]   = 'X';
    monstro_vivo[0]   = 1;
    mapa[monstro_linha[0]][monstro_coluna[0]] = 'X';
    tem_chave = 0;
    salvar_mapa();
}

void carregar_andar3() {
    int linha, coluna, k;
    char temp[25][26] = {
        "*************************",
        "*>  @                   *",
        "*                       *",
        "*   ######### ######    *",
        "*                       *",
        "*             @         *",
        "*                       *",
        "* ****D**************** *",
        "*                       *",
        "*   k   k   k           *",
        "*                       *",
        "*        @              *",
        "*                       *",
        "* *************D******* *",
        "*                       *",
        "*                       *",
        "***********D*************",
        "*  Y             Y      *",
        "*                       *",
        "*         Z             *",
        "*                       *",
        "*  Y             Y      *",
        "*                       *",
        "*                    L  *",
        "*************************"
    };
    fase_atual  = 3;
    num_linhas  = 25;
    num_colunas = 25;
    for (linha = 0; linha < num_linhas; linha++)
        for (coluna = 0; coluna < num_colunas; coluna++)
            mapa[linha][coluna] = temp[linha][coluna];
    jogador_linha      = 1;
    jogador_coluna     = 1;
    jogador_direcao    = '>';
    celula_sob_jogador = ' ';
    mapa[jogador_linha][jogador_coluna] = jogador_direcao;

    total_monstros    = 5;
    monstro_linha[0]  = 19; monstro_coluna[0] = 10; monstro_tipo[0] = 'Z'; monstro_vivo[0] = 1;
    monstro_linha[1]  = 17; monstro_coluna[1] = 3;  monstro_tipo[1] = 'Y'; monstro_vivo[1] = 1;
    monstro_linha[2]  = 17; monstro_coluna[2] = 17; monstro_tipo[2] = 'Y'; monstro_vivo[2] = 1;
    monstro_linha[3]  = 21; monstro_coluna[3] = 3;  monstro_tipo[3] = 'Y'; monstro_vivo[3] = 1;
    monstro_linha[4]  = 21; monstro_coluna[4] = 17; monstro_tipo[4] = 'Y'; monstro_vivo[4] = 1;

    for (k = 0; k < total_monstros; k++)
        mapa[monstro_linha[k]][monstro_coluna[k]] = monstro_tipo[k];

    boss_vida           = 4;
    boss_contador_turno = 0;
    tem_chave           = 0;
    salvar_mapa();
}

void reiniciar_fase() {
    int k;
    vidas--;
    printf("\nvoce morreu! vidas: %d\n", vidas);
    if (vidas <= 0) {
        printf("\n=== GAME OVER ===\n");
        pausar();
        fase_atual = -1;
        return;
    }
    pausar();
    memcpy(mapa, mapa_salvo, sizeof(mapa));
    jogador_linha      = jogador_linha_inicio;
    jogador_coluna     = jogador_coluna_inicio;
    jogador_direcao    = jogador_direcao_inicio;
    celula_sob_jogador = ' ';
    mapa[jogador_linha][jogador_coluna] = jogador_direcao;
    for (k = 0; k < total_monstros; k++) {
        monstro_vivo[k] = 1;
        mapa[monstro_linha[k]][monstro_coluna[k]] = monstro_tipo[k];
    }
    tem_chave = 0;
}

void mover_monstros() {
    int deslocamento_linha[4];
    int deslocamento_coluna[4];
    int k, direcao_sorteada;
    int nova_linha, nova_coluna;
    int diff_linha, diff_coluna;

    deslocamento_linha[0]  = -1; deslocamento_linha[1]  =  1;
    deslocamento_linha[2]  =  0; deslocamento_linha[3]  =  0;
    deslocamento_coluna[0] =  0; deslocamento_coluna[1] =  0;
    deslocamento_coluna[2] = -1; deslocamento_coluna[3] =  1;

    for (k = 0; k < total_monstros; k++) {
        if (!monstro_vivo[k]) continue;

        nova_linha  = monstro_linha[k];
        nova_coluna = monstro_coluna[k];

        if (monstro_tipo[k] == 'X') {
            direcao_sorteada = rand() % 4;
            nova_linha  = monstro_linha[k]  + deslocamento_linha[direcao_sorteada];
            nova_coluna = monstro_coluna[k] + deslocamento_coluna[direcao_sorteada];

        } else if (monstro_tipo[k] == 'Y') {
            diff_linha  = jogador_linha  - monstro_linha[k];
            diff_coluna = jogador_coluna - monstro_coluna[k];
            if (abs(diff_linha) >= abs(diff_coluna))
                nova_linha  = monstro_linha[k]  + (diff_linha  > 0 ? 1 : -1);
            else
                nova_coluna = monstro_coluna[k] + (diff_coluna > 0 ? 1 : -1);

        } else if (monstro_tipo[k] == 'Z') {
            diff_linha  = jogador_linha  - monstro_linha[k];
            diff_coluna = jogador_coluna - monstro_coluna[k];
            if (abs(diff_linha) >= abs(diff_coluna))
                nova_linha  = monstro_linha[k]  + (diff_linha  > 0 ? 1 : -1);
            else
                nova_coluna = monstro_coluna[k] + (diff_coluna > 0 ? 1 : -1);
        }

        if (nova_linha == jogador_linha && nova_coluna == jogador_coluna) {
            reiniciar_fase();
            return;
        }

        if (nova_linha  >= 0 && nova_linha  < num_linhas  &&
            nova_coluna >= 0 && nova_coluna < num_colunas &&
            mapa[nova_linha][nova_coluna] == ' ') {
            mapa[monstro_linha[k]][monstro_coluna[k]] = ' ';
            monstro_linha[k]  = nova_linha;
            monstro_coluna[k] = nova_coluna;
            mapa[monstro_linha[k]][monstro_coluna[k]] = monstro_tipo[k];
        }
    }
}

void atacar_celula(int linha, int coluna) {
    int k;
    if (linha < 0 || linha >= num_linhas || coluna < 0 || coluna >= num_colunas) return;

    if (mapa[linha][coluna] == 'k') { mapa[linha][coluna] = ' '; return; }

    for (k = 0; k < total_monstros; k++) {
        if (!monstro_vivo[k] || monstro_linha[k] != linha || monstro_coluna[k] != coluna) continue;
        if (monstro_tipo[k] == 'Z') {
            boss_vida--;
            printf("boss vida: %d\n", boss_vida);
            if (boss_vida <= 0) { monstro_vivo[k] = 0; mapa[linha][coluna] = ' '; }
        } else {
            monstro_vivo[k]     = 0;
            mapa[linha][coluna] = ' ';
        }
    }
}

void atacar() {
    int dir_linha, dir_coluna;
    int lateral_linha, lateral_coluna;
    int profundidade, i;
    int adj_linha[8];
    int adj_coluna[8];

    adj_linha[0] = -1; adj_linha[1] = -1; adj_linha[2] = -1;
    adj_linha[3] =  0; adj_linha[4] =  0;
    adj_linha[5] =  1; adj_linha[6] =  1; adj_linha[7] =  1;
    adj_coluna[0] = -1; adj_coluna[1] = 0; adj_coluna[2] = 1;
    adj_coluna[3] = -1; adj_coluna[4] = 1;
    adj_coluna[5] = -1; adj_coluna[6] = 0; adj_coluna[7] = 1;

    dir_linha  = 0;
    dir_coluna = 0;
    if      (jogador_direcao == '^') dir_linha  = -1;
    else if (jogador_direcao == 'v') dir_linha  =  1;
    else if (jogador_direcao == '<') dir_coluna = -1;
    else                             dir_coluna =  1;

    if (arma == 0) {
        lateral_linha  = (dir_linha  == 0) ? 1 : 0;
        lateral_coluna = (dir_coluna == 0) ? 1 : 0;
        for (profundidade = 1; profundidade <= 2; profundidade++) {
            atacar_celula(jogador_linha + dir_linha*profundidade - lateral_linha,
                          jogador_coluna + dir_coluna*profundidade - lateral_coluna);
            atacar_celula(jogador_linha + dir_linha*profundidade,
                          jogador_coluna + dir_coluna*profundidade);
            atacar_celula(jogador_linha + dir_linha*profundidade + lateral_linha,
                          jogador_coluna + dir_coluna*profundidade + lateral_coluna);
        }
    } else if (arma == 1) {
        for (i = 1; i <= 4; i++)
            atacar_celula(jogador_linha + dir_linha*i, jogador_coluna + dir_coluna*i);
    } else {
        for (i = 0; i < 8; i++)
            atacar_celula(jogador_linha + adj_linha[i], jogador_coluna + adj_coluna[i]);
    }
}

void interagir() {
    int alvo_linha, alvo_coluna;
    char opcao, objeto;

    alvo_linha  = jogador_linha;
    alvo_coluna = jogador_coluna;
    if      (jogador_direcao == '^') alvo_linha--;
    else if (jogador_direcao == 'v') alvo_linha++;
    else if (jogador_direcao == '<') alvo_coluna--;
    else                             alvo_coluna++;

    objeto = mapa[alvo_linha][alvo_coluna];

    if (objeto == 'D') {
        if (tem_chave) {
            mapa[alvo_linha][alvo_coluna] = '=';
            tem_chave = 0;
            printf("porta aberta!\n");
        } else {
            printf("precisa de chave!\n");
        }
    } else if (objeto == 'N') {
        system("cls");
        printf("NPC: escolha sua arma:\n1. espada\n2. arco\n3. cajado\n> ");
        scanf(" %c", &opcao);
        arma = (opcao == '1') ? 0 : (opcao == '2') ? 1 : 2;
        printf("\narma %d equipada!\n", arma + 1);
        pausar();
    } else {
        printf("nada aqui.\n");
    }
}

int loop_fase() {
    int nova_linha, nova_coluna, k, acertou_monstro, boss_vivo, linha, coluna;
    char tecla, nova_direcao, destino;

    while (1) {
        if (mapa[jogador_linha][jogador_coluna] == 'L' || celula_sob_jogador == 'L') {
            printf("subindo...\n");
            pausar();
            return 2;
        }

        desenhar();

        if (fase_atual == 3) {
            boss_vivo = 0;
            for (k = 0; k < total_monstros; k++)
                if (monstro_tipo[k] == 'Z' && monstro_vivo[k]) boss_vivo = 1;
            if (!boss_vivo) return 3;
            printf("boss vida: %d/4\n", boss_vida);
        }

        scanf(" %c", &tecla);
        nova_linha   = jogador_linha;
        nova_coluna  = jogador_coluna;
        nova_direcao = jogador_direcao;

        if      (tecla == 'q') return 0;
        else if (tecla == 'w') { nova_linha--;  nova_direcao = '^'; }
        else if (tecla == 's') { nova_linha++;  nova_direcao = 'v'; }
        else if (tecla == 'a') { nova_coluna--; nova_direcao = '<'; }
        else if (tecla == 'd') { nova_coluna++; nova_direcao = '>'; }
        else if (tecla == 'i') { interagir(); continue; }
        else if (tecla == 'o') { atacar(); mover_monstros(); continue; }
        else continue;

        jogador_direcao = nova_direcao;
        mapa[jogador_linha][jogador_coluna] = jogador_direcao;

        if (nova_linha < 0 || nova_linha >= num_linhas || nova_coluna < 0 || nova_coluna >= num_colunas) continue;

        destino = mapa[nova_linha][nova_coluna];
        if (destino == '*' || destino == 'D' || destino == 'k' || destino == 'N') continue;

        acertou_monstro = 0;
        for (k = 0; k < total_monstros; k++)
            if (monstro_vivo[k] && monstro_linha[k] == nova_linha && monstro_coluna[k] == nova_coluna)
                acertou_monstro = 1;
        if (acertou_monstro) { reiniciar_fase(); if (fase_atual == -1) return 0; continue; }

        if (destino == '@') { tem_chave++; printf("chave!\n"); }
        if (destino == '#') { reiniciar_fase(); if (fase_atual == -1) return 0; continue; }

        if (destino == 'O') {
            for (linha = 0; linha < num_linhas; linha++)
                for (coluna = 0; coluna < num_colunas; coluna++)
                    if (mapa[linha][coluna] == 'D') { mapa[linha][coluna] = '='; goto botao_ativado; }
            botao_ativado:
            printf("botao pressionado!\n");
        }

        mapa[jogador_linha][jogador_coluna] = celula_sob_jogador;
        celula_sob_jogador = (destino == '@' || destino == '#' || destino == 'O') ? ' ' : destino;
        jogador_linha  = nova_linha;
        jogador_coluna = nova_coluna;
        mapa[jogador_linha][jogador_coluna] = jogador_direcao;

        mover_monstros();
        if (fase_atual == -1) return 0;
    }
}

int main() {
    char opcao;
    srand(time(NULL));

    while (1) {
        system("cls");
        printf("\n=== DUNGEON CRAWLER ===\n\n");
        printf("1. jogar\n2. tutorial\n3. sair\n\n> ");
        scanf(" %c", &opcao);

        if (opcao == '1') {
            vidas     = 3;
            arma      = 0;
            tem_chave = 0;

            carregar_vila();
            if (loop_fase() != 2) continue;

            carregar_andar1();
            if (loop_fase() != 2) continue;

            carregar_andar2();
            if (loop_fase() != 2) continue;

            carregar_andar3();
            if (loop_fase() == 3) {
                system("cls");
                printf("\n=== VITORIA ===\n\n");
                printf("voce derrotou o boss e salvou a vila!\n\n");
                pausar();
            }

        } else if (opcao == '2') {
            system("cls");
            printf("=== TUTORIAL ===\n\n");
            printf("> ^ < v  jogador\n");
            printf("*        parede\n");
            printf("#        espinho (mata)\n");
            printf("k        caixa (destruivel)\n");
            printf("O        botao\n");
            printf("D / =    porta fechada / aberta\n");
            printf("@        chave\n");
            printf("L        escada\n");
            printf("N        npc\n");
            printf("X Y Z    monstros\n\n");
            printf("w a s d  mover | i interagir | o atacar\n\n");
            printf("historia: monstros invadiram a masmorra. derrote o boss e salve a vila.\n\n");
            pausar();

        } else if (opcao == '3') {
            system("cls");
            printf("\ncreditos: [seu nome]\nate mais!\n\n");
            return 0;
        }
    }
}
