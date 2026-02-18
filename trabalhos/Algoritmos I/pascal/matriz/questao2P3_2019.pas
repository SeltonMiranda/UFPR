program mat;
type matriz = array[1..100,1..100] of longint;
var m: matriz; n: longint;

function SomaLinha(var m: matriz; linha, coluna, tam: longint): longint;
var j, soma: longint;
begin
    soma:= 0;
    for j:= coluna to coluna+tam-1 do
	soma:= soma + m[linha,j];
      SomaLinha:= soma;
end;

function SomaMatrizAtual(var m: matriz; linha, coluna, tam: longint): longint;
var somaLinhas, somaTotal: longint;
begin
  somaLinhas:= SomaLinha(m, linha, coluna, tam) + SomaLinha(m, linha+2, coluna, tam);
  somaTotal:= somaLinhas + m[linha+1,coluna+1];
  SomaMatrizAtual:= somaTotal;
end;

function MaiorSoma(var m: matriz; n: longint): longint;
var i, j, soma: longint;
begin
  soma:= 0;
  for i:= 1 to n-3+1 do
    for j:= 1 to n-3+1 do
      if SomaMatrizAtual(m, i, j, 3) > soma then
      	soma:= SomaMatrizAtual(m, i, j, 3);

  MaiorSoma:= soma;
end;

procedure lerMatriz(var m: matriz; n: longint);
var i, j: longint;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

begin
  read(n); 
  lerMatriz(m, n);
  writeln(MaiorSoma(m, n));
end.
