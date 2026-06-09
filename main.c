#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINHAS   25
#define MAX_COLUNAS  25
#define MAX_MONSTROS 20

char mapa[MAX_LINHAS][MAX_COLUNAS];
char mapa_salvo[MAX_LINHAS][MAX_COLUNAS];
int  num_linhas, num_colunas;

int  jogador_linha, jogador_coluna;
char jogador_direcao;
int  vidas, arma, tem_chave, fase_atual;

int  monstro_linha[MAX_MONSTROS];
int  monstro_coluna[MAX_MONSTROS];
char monstro_tipo[MAX_MONSTROS];
int  monstro_vivo[MAX_MONSTROS];
int  total_monstros;

int  boss_vida;
int  boss_contador_turno;

char celula_sob_jogador;

int  jogador_linha_inicio, jogador_coluna_inicio;
char jogador_direcao_inicio;
char celula_sob_jogador_inicio;
int  monstro_linha_inicio[MAX_MONSTROS];
int  monstro_coluna_inicio[MAX_MONSTROS];
int  boss_vida_inicio;

char ler_char() {
    int c;
    char lido = '\0';
    while ((c = getchar()) != EOF) {
        if ((char)c != '\n') { lido = (char)c; break; }
    }
    while (c != '\n' && c != EOF)
        c = getchar();
    return lido;
}

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\n[pressione enter]\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int pos_valida(int l, int c) {
    return (l >= 0 && l < num_linhas && c >= 0 && c < num_colunas);
}

char mapa_get(int l, int c) {
    if (!pos_valida(l, c)) return '*';
    return mapa[l][c];
}

void mapa_set(int l, int c, char val) {
    if (pos_valida(l, c))
        mapa[l][c] = val;
}

void sincronizar_monstros_no_mapa() {
    int k;
    for (k = 0; k < total_monstros; k++) {
        if (monstro_vivo[k] &&
            monstro_linha[k]  >= 0 && monstro_linha[k]  < num_linhas &&
            monstro_coluna[k] >= 0 && monstro_coluna[k] < num_colunas) {
            mapa[monstro_linha[k]][monstro_coluna[k]] = monstro_tipo[k];
        }
    }
}

void desenhar() {
    int l, c;
    limpar_tela();
    printf("fase:%d  vidas:%d  arma:%d  chave:%d\n\n",
           fase_atual, vidas, arma, tem_chave);
    for (l = 0; l < num_linhas; l++) {
        for (c = 0; c < num_colunas; c++)
            putchar(mapa[l][c]);
        putchar('\n');
    }
    printf("\nw/a/s/d=mover  i=interagir  o=atacar  q=sair\n");
}

void salvar_estado() {
    int k;
    memcpy(mapa_salvo, mapa, sizeof(mapa));
    jogador_linha_inicio      = jogador_linha;
    jogador_coluna_inicio     = jogador_coluna;
    jogador_direcao_inicio    = jogador_direcao;
    celula_sob_jogador_inicio = celula_sob_jogador;
    boss_vida_inicio          = boss_vida;
    for (k = 0; k < total_monstros; k++) {
        monstro_linha_inicio[k]  = monstro_linha[k];
        monstro_coluna_inicio[k] = monstro_coluna[k];
    }
}

void carregar_vila() {
    int l, c;
    const char *temp[10] = {
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
    for (l = 0; l < num_linhas; l++)
        for (c = 0; c < num_colunas; c++)
            mapa[l][c] = temp[l][c];
    jogador_linha      = 4;
    jogador_coluna     = 4;
    jogador_direcao    = '>';
    celula_sob_jogador = ' ';
    mapa_set(jogador_linha, jogador_coluna, jogador_direcao);
    total_monstros = 0;
    boss_vida      = 0;
    salvar_estado();
}

void carregar_andar1() {
    int l, c;
    const char *temp[10] = {
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
    for (l = 0; l < num_linhas; l++)
        for (c = 0; c < num_colunas; c++)
            mapa[l][c] = temp[l][c];
    jogador_linha      = 1;
    jogador_coluna     = 1;
    jogador_direcao    = '>';
    celula_sob_jogador = ' ';
    mapa_set(jogador_linha, jogador_coluna, jogador_direcao);
    total_monstros = 0;
    tem_chave      = 0;
    boss_vida      = 0;
    salvar_estado();
}

void carregar_andar2() {
    int l, c;
    const char *temp[15] = {
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
    for (l = 0; l < num_linhas; l++)
        for (c = 0; c < num_colunas; c++)
            mapa[l][c] = temp[l][c];
    jogador_linha      = 1;
    jogador_coluna     = 1;
    jogador_direcao    = '>';
    celula_sob_jogador = ' ';
    mapa_set(jogador_linha, jogador_coluna, jogador_direcao);
    total_monstros   = 1;
    monstro_linha[0] = 5;  monstro_coluna[0] = 9;
    monstro_tipo[0]  = 'X'; monstro_vivo[0]  = 1;
    mapa_set(monstro_linha[0], monstro_coluna[0], 'X');
    tem_chave = 0;
    boss_vida = 0;
    salvar_estado();
}

void carregar_andar3() {
    int l, c, k;
    const char *temp[25] = {
        "*************************",
        "*>                      *",
        "*                       *",
        "*  ######   ########    *",
        "*                       *",
        "*           k           *",
        "*                  @    *",
        "*                       *",
        "****D********************",
        "*                       *",
        "*  ***       ***        *",
        "*  @                    *",
        "*  ***       ***        *",
        "*      Y         Y      *",
        "*                       *",
        "*                       *",
        "************D************",
        "*                       *",
        "*   * *   Z   * *       *",
        "*                       *",
        "*   * *       * *       *",
        "*                       *",
        "*                       *",
        "*                    L  *",
        "*************************"
    };
    fase_atual  = 3;
    num_linhas  = 25;
    num_colunas = 25;
    for (l = 0; l < num_linhas; l++)
        for (c = 0; c < num_colunas; c++)
            mapa[l][c] = temp[l][c];
    jogador_linha      = 1;
    jogador_coluna     = 1;
    jogador_direcao    = '>';
    celula_sob_jogador = ' ';
    mapa_set(jogador_linha, jogador_coluna, jogador_direcao);
    total_monstros    = 3;
    monstro_linha[0]  = 18; monstro_coluna[0] = 10; monstro_tipo[0] = 'Z'; monstro_vivo[0] = 1;
    monstro_linha[1]  = 13; monstro_coluna[1] =  7; monstro_tipo[1] = 'Y'; monstro_vivo[1] = 1;
    monstro_linha[2]  = 13; monstro_coluna[2] = 17; monstro_tipo[2] = 'Y'; monstro_vivo[2] = 1;
    for (k = 0; k < total_monstros; k++)
        mapa_set(monstro_linha[k], monstro_coluna[k], monstro_tipo[k]);
    boss_vida           = 4;
    boss_contador_turno = 0;
    tem_chave           = 0;
    srand((unsigned int)time(NULL) ^ (unsigned int)fase_atual);
    salvar_estado();
}

void reiniciar_fase() {
    int k;
    vidas--;
    printf("\nvoce morreu! vidas restantes: %d\n", vidas);
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
    celula_sob_jogador = celula_sob_jogador_inicio;
    mapa_set(jogador_linha, jogador_coluna, jogador_direcao);
    for (k = 0; k < total_monstros; k++) {
        monstro_vivo[k]   = 1;
        monstro_linha[k]  = monstro_linha_inicio[k];
        monstro_coluna[k] = monstro_coluna_inicio[k];
        mapa_set(monstro_linha[k], monstro_coluna[k], monstro_tipo[k]);
    }
    boss_vida = boss_vida_inicio;
    tem_chave = 0;
}

#define BFS_VAZIO -1

typedef struct { short l, c; } Celula;

static int   bfs_pai_l[MAX_LINHAS][MAX_COLUNAS];
static int   bfs_pai_c[MAX_LINHAS][MAX_COLUNAS];
static Celula bfs_fila[MAX_LINHAS * MAX_COLUNAS];

static int y_bloqueado(int l, int c) {
    char ch;
    if (!pos_valida(l, c)) return 1;
    ch = mapa_get(l, c);
    return ch == '*' || ch == 'D' || ch == 'k' || ch == 'N' || ch == '#';
}

static int bfs_proximo_passo(int orig_l, int orig_c,
                              int dest_l, int dest_c,
                              int *pl, int *pc) {
    const int dl[4] = { -1, 1,  0, 0 };
    const int dc[4] = {  0, 0, -1, 1 };
    int head, tail, d, nl, nc, cl, cc;

    for (cl = 0; cl < num_linhas; cl++)
        for (cc = 0; cc < num_colunas; cc++) {
            bfs_pai_l[cl][cc] = BFS_VAZIO;
            bfs_pai_c[cl][cc] = BFS_VAZIO;
        }

    head = tail = 0;
    bfs_pai_l[orig_l][orig_c] = orig_l;
    bfs_pai_c[orig_l][orig_c] = orig_c;
    bfs_fila[tail].l = (short)orig_l;
    bfs_fila[tail].c = (short)orig_c;
    tail++;

    while (head < tail) {
        cl = bfs_fila[head].l;
        cc = bfs_fila[head].c;
        head++;

        if (cl == dest_l && cc == dest_c) break;

        for (d = 0; d < 4; d++) {
            nl = cl + dl[d];
            nc = cc + dc[d];
            if (!pos_valida(nl, nc)) continue;
            if (bfs_pai_l[nl][nc] != BFS_VAZIO) continue;
            if (nl != dest_l || nc != dest_c)
                if (y_bloqueado(nl, nc)) continue;
            bfs_pai_l[nl][nc] = cl;
            bfs_pai_c[nl][nc] = cc;
            bfs_fila[tail].l = (short)nl;
            bfs_fila[tail].c = (short)nc;
            tail++;
        }
    }

    if (bfs_pai_l[dest_l][dest_c] == BFS_VAZIO) return 0;

    cl = dest_l; cc = dest_c;
    while (1) {
        int pl2 = bfs_pai_l[cl][cc];
        int pc2 = bfs_pai_c[cl][cc];
        if (pl2 == orig_l && pc2 == orig_c) break;
        cl = pl2; cc = pc2;
    }
    *pl = cl;
    *pc = cc;
    return 1;
}

void mover_monstros() {
    const int dl[4] = { -1,  1,  0,  0 };
    const int dc[4] = {  0,  0, -1,  1 };
    int k, dir, nl, nc, diff_l, diff_c;

    for (k = 0; k < total_monstros; k++) {
        if (!monstro_vivo[k]) continue;

        nl = monstro_linha[k];
        nc = monstro_coluna[k];

        if (monstro_tipo[k] == 'X') {
            dir = rand() % 4;
            nl  = monstro_linha[k] + dl[dir];
            nc  = monstro_coluna[k] + dc[dir];

        } else if (monstro_tipo[k] == 'Y') {
            int passo_l, passo_c;
            if (bfs_proximo_passo(monstro_linha[k], monstro_coluna[k],
                                  jogador_linha,    jogador_coluna,
                                  &passo_l, &passo_c)) {
                nl = passo_l;
                nc = passo_c;
            }

        } else if (monstro_tipo[k] == 'Z') {
            diff_l = jogador_linha  - monstro_linha[k];
            diff_c = jogador_coluna - monstro_coluna[k];
            if (jogador_linha >= 17 || (abs(diff_l) + abs(diff_c)) <= 7) {
                if (abs(diff_l) >= abs(diff_c))
                    nl = monstro_linha[k]  + (diff_l > 0 ? 1 : -1);
                else
                    nc = monstro_coluna[k] + (diff_c > 0 ? 1 : -1);
            }
        }

        if (nl == jogador_linha && nc == jogador_coluna) {
            reiniciar_fase();
            return;
        }

        if (pos_valida(nl, nc) && mapa_get(nl, nc) == ' ') {
            mapa_set(monstro_linha[k], monstro_coluna[k], ' ');
            monstro_linha[k]  = nl;
            monstro_coluna[k] = nc;
            mapa_set(monstro_linha[k], monstro_coluna[k], monstro_tipo[k]);
        }
    }
}

void atacar_celula(int l, int c) {
    int k;
    if (!pos_valida(l, c)) return;

    if (mapa_get(l, c) == 'k') {
        mapa_set(l, c, ' ');
        return;
    }

    for (k = 0; k < total_monstros; k++) {
        if (!monstro_vivo[k] || monstro_linha[k] != l || monstro_coluna[k] != c)
            continue;
        if (monstro_tipo[k] == 'Z') {
            boss_vida--;
            printf("boss vida: %d\n", boss_vida);
            if (boss_vida <= 0) {
                monstro_vivo[k] = 0;
                mapa_set(l, c, ' ');
            }
        } else {
            monstro_vivo[k] = 0;
            mapa_set(l, c, ' ');
        }
        break;
    }
}

void atacar() {
    int dir_l = 0, dir_c = 0;
    int lat_l, lat_c, prof, i;
    const int adj_l[8] = { -1, -1, -1,  0,  0,  1,  1,  1 };
    const int adj_c[8] = { -1,  0,  1, -1,  1, -1,  0,  1 };

    if      (jogador_direcao == '^') dir_l = -1;
    else if (jogador_direcao == 'v') dir_l =  1;
    else if (jogador_direcao == '<') dir_c = -1;
    else                             dir_c =  1;

    if (arma == 0) {
        lat_l = (dir_l == 0) ? 1 : 0;
        lat_c = (dir_c == 0) ? 1 : 0;
        for (prof = 1; prof <= 2; prof++) {
            atacar_celula(jogador_linha + dir_l*prof - lat_l,
                          jogador_coluna + dir_c*prof - lat_c);
            atacar_celula(jogador_linha + dir_l*prof,
                          jogador_coluna + dir_c*prof);
            atacar_celula(jogador_linha + dir_l*prof + lat_l,
                          jogador_coluna + dir_c*prof + lat_c);
        }
    } else if (arma == 1) {
        for (i = 1; i <= 4; i++)
            atacar_celula(jogador_linha + dir_l*i, jogador_coluna + dir_c*i);
    } else {
        for (i = 0; i < 8; i++)
            atacar_celula(jogador_linha + adj_l[i], jogador_coluna + adj_c[i]);
    }
}

void interagir() {
    int al, ac;
    char opcao, objeto;

    al = jogador_linha;
    ac = jogador_coluna;
    if      (jogador_direcao == '^') al--;
    else if (jogador_direcao == 'v') al++;
    else if (jogador_direcao == '<') ac--;
    else                             ac++;

    if (!pos_valida(al, ac)) {
        printf("nada aqui.\n");
        pausar();
        return;
    }

    objeto = mapa_get(al, ac);

    if (objeto == 'D') {
        if (tem_chave) {
            mapa_set(al, ac, '=');
            tem_chave = 0;
            printf("porta aberta!\n");
        } else {
            printf("precisa de chave!\n");
        }
        pausar();

    } else if (objeto == 'N') {
        do {
            limpar_tela();
            printf("NPC: escolha sua arma:\n");
            printf("1. espada (area 3x2 na frente)\n");
            printf("2. arco   (linha reta, alcance 4)\n");
            printf("3. cajado (todas as 8 celulas ao redor)\n");
            printf("> ");
            fflush(stdout);
            opcao = ler_char();
            if (opcao != '1' && opcao != '2' && opcao != '3')
                printf("\nescolha uma opcao valida! (1, 2 ou 3)\n");
        } while (opcao != '1' && opcao != '2' && opcao != '3');

        arma = (opcao == '1') ? 0 : (opcao == '2') ? 1 : 2;
        printf("\narma %d equipada!\n", arma + 1);
        pausar();

    } else {
        printf("nada aqui.\n");
        pausar();
    }
}

int loop_fase() {
    int nl, nc, k, acertou, boss_vivo, l, c, botao_ativado;
    char tecla, nova_dir, dest;

    while (1) {
        if (celula_sob_jogador == 'L') {
            printf("subindo...\n");
            pausar();
            return 2;
        }

        sincronizar_monstros_no_mapa();
        desenhar();

        if (fase_atual == 3) {
            boss_vivo = 0;
            for (k = 0; k < total_monstros; k++)
                if (monstro_tipo[k] == 'Z' && monstro_vivo[k]) { boss_vivo = 1; break; }
            if (!boss_vivo) return 3;
            printf("boss vida: %d/4\n", boss_vida);
        }

        fflush(stdout);
        tecla    = ler_char();
        nl       = jogador_linha;
        nc       = jogador_coluna;
        nova_dir = jogador_direcao;

        if      (tecla == 'q') return 0;
        else if (tecla == 'w') { nl--;  nova_dir = '^'; }
        else if (tecla == 's') { nl++;  nova_dir = 'v'; }
        else if (tecla == 'a') { nc--;  nova_dir = '<'; }
        else if (tecla == 'd') { nc++;  nova_dir = '>'; }
        else if (tecla == 'i') { interagir(); continue; }
        else if (tecla == 'o') { atacar(); mover_monstros(); if (fase_atual == -1) return 0; continue; }
        else continue;

        jogador_direcao = nova_dir;
        mapa_set(jogador_linha, jogador_coluna, jogador_direcao);

        if (!pos_valida(nl, nc)) {
            mover_monstros();
            if (fase_atual == -1) return 0;
            continue;
        }

        dest = mapa_get(nl, nc);

        if (dest == '*' || dest == 'D' || dest == 'k' || dest == 'N') {
            mover_monstros();
            if (fase_atual == -1) return 0;
            continue;
        }

        acertou = 0;
        for (k = 0; k < total_monstros; k++) {
            if (monstro_vivo[k] && monstro_linha[k] == nl && monstro_coluna[k] == nc) {
                acertou = 1;
                break;
            }
        }
        if (acertou) {
            reiniciar_fase();
            if (fase_atual == -1) return 0;
            continue;
        }

        if (dest == '@')
            tem_chave++;

        if (dest == '#') {
            reiniciar_fase();
            if (fase_atual == -1) return 0;
            continue;
        }

        if (dest == 'O') {
            botao_ativado = 0;
            for (l = 0; l < num_linhas && !botao_ativado; l++)
                for (c = 0; c < num_colunas && !botao_ativado; c++)
                    if (mapa_get(l, c) == 'D') {
                        mapa_set(l, c, '=');
                        botao_ativado = 1;
                    }
            printf("botao pressionado!\n");
        }

        mapa_set(jogador_linha, jogador_coluna, celula_sob_jogador);
        celula_sob_jogador = (dest == '@' || dest == 'O') ? ' ' : dest;
        jogador_linha  = nl;
        jogador_coluna = nc;
        mapa_set(jogador_linha, jogador_coluna, jogador_direcao);

        mover_monstros();
        if (fase_atual == -1) return 0;
    }
}

int main() {
    char opcao;
    srand((unsigned int)time(NULL));

    while (1) {
        do {
            limpar_tela();
            printf("\n=== DUNGEON CRAWLER ===\n\n");
            printf("1. jogar\n2. tutorial\n3. sair\n\n> ");
            fflush(stdout);
            opcao = ler_char();
            if (opcao != '1' && opcao != '2' && opcao != '3')
                printf("\nescolha uma opcao valida! (1, 2 ou 3)\n");
        } while (opcao != '1' && opcao != '2' && opcao != '3');

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
                limpar_tela();
                printf("\n=== VITORIA ===\n\n");
                printf("voce derrotou o boss e salvou a vila!\n\n");
                pausar();
            }

        } else if (opcao == '2') {
            limpar_tela();
            printf("=== TUTORIAL ===\n\n");
            printf("> ^ < v  jogador (mostra direcao)\n");
            printf("*        parede\n");
            printf("#        espinho (mata ao pisar)\n");
            printf("k        caixa (destruivel com ataque)\n");
            printf("O        botao (abre a primeira porta D do mapa)\n");
            printf("D / =    porta fechada / aberta\n");
            printf("@        chave\n");
            printf("L        escada (proximo andar)\n");
            printf("N        npc (escolher arma)\n");
            printf("X Y Z    monstros\n\n");
            printf("w a s d  mover\n");
            printf("i        interagir com objeto a frente\n");
            printf("o        atacar\n\n");
            printf("armas:\n");
            printf("  1 espada: area 3x2 na frente\n");
            printf("  2 arco:   linha reta (alcance 4)\n");
            printf("  3 cajado: todas as 8 celulas ao redor\n\n");
            printf("historia: monstros invadiram a masmorra.\n");
            printf("derrote o boss Z e salve a vila.\n\n");
            pausar();

        } else {
            limpar_tela();
            printf("\ncreditos: [seu nome]\nate mais!\n\n");
            return 0;
        }
    }
}