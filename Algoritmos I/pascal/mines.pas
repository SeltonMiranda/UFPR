(* Programa que joga o campo minado, feito por Marcos Castilho *)
(* em 11/07/2019 para a disciplina CI055 do DInf/UFPR.         *)
program mines;
uses crt, tad_pilha; // a pilha eh de coordenadas (x,y)

const
    MAX = 9;
    BORDA = -2;
    MINA = -1;
    NADA = 0;
    VITORIA = 1;
    DERROTA = 2;
    EM_ANDAMENTO = 3;
    SIMBOLO_MINA = '@ ';
    SIMBOLO_SEM_MINA_VIZ = '  ';
    SIMBOLO_ESCONDIDO = '* ';

type
    quadrado = record
        info: longint;       // BORDA, MINA ou numero de minas vizinhas
        revelado: boolean;   // quando true nao imprime o conteudo
    end;

    matriz = array [0..MAX+1,0..MAX+1] of quadrado; // util de 1 a MAX

    campo_minado = record
        x,y: longint;      // numero de linhas e colunas
        total_minas: longint; // numero total de minas no campo
        falta_abrir: longint;  // numero de quadrados que faltam abrir
        status: longint;       // indica se o jogador ganhou ou perdeu o jogo
        m: matriz;
    end;

procedure revelar_tudo (var c: campo_minado);
// usada quando o jogador perde, para mostrar o campo minado todo aberto
var i,j: longint;
begin
    for i:= 1 to c.x do
        for j:= 1 to c.y do
            c.m[i,j].revelado:= true;
end;

function eh_borda (i,j: longint; c: campo_minado): boolean;
// retorna true quando uma linha ou coluna eh uma borda
begin
    eh_borda:= (i = 0) or (i = c.x+1) or (j = 0) or (j = c.y+1);
end;

procedure zerar_campo (var c: campo_minado);
// prepara o campo: define as bordas, zera o tabuleiro e inicia info revelado
var i,j: longint;
begin
    for i:= 1 to c.x do       // zera a matriz e inicia revelado false
        for j:= 1 to c.y do
        begin
            if eh_borda (i,j,c) then
                c.m[i,j].info:= BORDA
            else
                c.m[i,j].info:= NADA;
            c.m[i,j].revelado:= false;
        end;
end;

procedure gerar_minas (var c: campo_minado);
// coloca o total de minas definido em posicoes aleatorias do campo
var i,x,y: longint;
begin
    randomize;
    for i:= 1 to c.total_minas do
    begin
        repeat
            x:= random (c.x) + 1;
            y:= random (c.y) + 1;
        until c.m[x,y].info = NADA; // garante mina em lugar vazio
        c.m[x,y].info:= MINA; 
    end;          
end;

function num_vizinhos_com_mina (x,y: longint; c: campo_minado): longint;
// para um quadrado valido conta as minas nos 8 vizinhos
// se entrou aqui eh porque o proprio quadrado nao tem mina
var i,j, cont: longint;
begin
    cont:= 0;
    for i:= x-1 to x+1 do
        for j:= y-1 to y+1 do
            if c.m[i,j].info = MINA then
                cont:= cont + 1;
    num_vizinhos_com_mina:= cont;
end;

procedure contar_vizinhos_com_mina (var c: campo_minado);
// para os quadrados que nao sao minas, conta os vizinhos que sao minas
var i, j: longint;
begin
    for i:= 1 to c.x do
        for j:= 1 to c.y do
            if c.m[i,j].info = NADA then // conta vizinhos com mina
                c.m[i,j].info:= num_vizinhos_com_mina (i,j,c);
end;

procedure inicializar_campo (var c: campo_minado);
// chamas as funcoes e procedimentos que iniciam a estrutura
begin
    write ('Defina numero de linhas (entre 1 e ',MAX,'): '); readln (c.x);
    write ('Defina numero de colunas (entre 1 e ',MAX,': '); readln (c.y);
    write ('Defina numero de minas (entre 1 e ',c.x*c.y,'): '); readln (c.total_minas);
    c.falta_abrir:= c.x*c.y - c.total_minas; // para teste se ganhou jogo
    c.status:= EM_ANDAMENTO;                 // para inicializar variavel
    zerar_campo (c);                         
    gerar_minas (c);
    contar_vizinhos_com_mina (c);
end;

procedure imprimir_campo (c: campo_minado);
// imprime o campo minado com base na info revelado, se o quadrado ja foi aberto
var i,j: longint;
begin
    clrscr;
    write ('   ');
    for i:= 1 to c.x do
        write (i,' ');
    writeln; 
    write (' +');
    for i:= 1 to 2 * c.x do
        write ('-');
    writeln;
    for i:= 1 to c.x do
    begin
        write (i,'| ');
        for j:= 1 to c.y do
            if not c.m[i,j].revelado then
                write (SIMBOLO_ESCONDIDO) // nao exibe o quadrado
            else 
                case c.m[i,j].info of
                    MINA: write (SIMBOLO_MINA);
                    NADA: write (SIMBOLO_SEM_MINA_VIZ);
                    else
                        write (c.m[i,j].info,' ');
                end;
        writeln;
    end;
end;

procedure ler_jogada (var x,y: longint; c: campo_minado);
// le uma jogada, nao testa consistencia, mas testa se eh quadrado novo.
begin
    repeat
        write ('Escolha a linha para jogar: ');
        readln (x);
        write ('Escolha a coluna para jogar: ');
        readln (y);
    until not c.m[x,y].revelado; // nao pode jogar no mesmo lugar novamente
end;

function abrir_vizinhos_sem_mina (var c: campo_minado; var p: pilha): longint;
// usa a pilha de coordenadas para abrir todos os vizinhos que nao tem mina
// retorna o numero de quadrados abertos
var quadrado, vizinho: coordenada; i, j, cont: longint;
begin
    cont:= 1;
    while not pilha_vazia (p) do
    begin
        quadrado:= desempilhar (p);
        for i:= quadrado.x-1 to quadrado.x+1 do
            for j:= quadrado.y-1 to quadrado.y+1 do
                if not c.m[i,j].revelado and (c.m[i,j].info = NADA)
                                       and not eh_borda (i,j,c) then 
                begin
                    vizinho.x:= i;
                    vizinho.y:= j;
                    empilhar (vizinho, p);
                    c.m[i,j].revelado:= true;
                    cont:= cont + 1;
                end;
    end;
    abrir_vizinhos_sem_mina:= cont;
end;

procedure executar_jogada (x,y: longint; var c: campo_minado);
// dada a coordenada (x,y) concretiza a jogada
var coord: coordenada;
    cont: longint;
    p: pilha;
begin
    if c.m[x,y].info = MINA then // achou mina...
    begin
        c.status:= DERROTA;
        revelar_tudo (c); // para revelado todo o campo no final
    end
    else // nao eh mina
    begin
        cont:= 1;
        c.m[x,y].revelado:= true;
        if c.m[x,y].info = NADA then  // quadrado sem vizinhos com mina
        begin
            coord.x:= x;
            coord.y:= y;
            inicializar_pilha (p);
            empilhar (coord, p);
            cont:= abrir_vizinhos_sem_mina (c, p);
        end;
        c.falta_abrir:= c.falta_abrir - cont;
        if c.falta_abrir = 0 then // ganhou
            c.status:= VITORIA;
    end;
end;

function ganhou (c: campo_minado): boolean;
// ganha quando nao falta abrir nenhum quadrado sem mina
begin
    ganhou:= c.status = VITORIA;
end;

function perdeu (c: campo_minado): boolean;
// c.status = DERROTA quando clicou em uma mina
begin
    perdeu:= c.status = DERROTA;
end;

var c: campo_minado;
    x, y: longint;

begin (* programa principal *)
    inicializar_campo (c);
    imprimir_campo (c);
    repeat
        ler_jogada (x,y,c);
        executar_jogada (x,y,c);
        imprimir_campo (c);
    until ganhou (c) or perdeu (c);
    if perdeu (c) then
        writeln ('Voce perdeu, tente novamente...')
    else
        writeln ('Parabens, voce ganhou !!!');
end.
