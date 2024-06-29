program questao;
CONST MAX = 200;
type tpMatriz = array[1..MAX,1..MAX] of integer;
var achou: boolean; m: tpMatriz; i, j, n, tam: integer;

procedure imprimir_matriz(var m: tpMatriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to n do
	write(m[i,j],' ');
      writeln();
    end;
end;

procedure inverte_cor(var m: tpMatriz; n: integer);
var i, j, maiorElemento: integer;
begin
  maiorElemento:= m[1,1];
  for i:= 1 to n do
    for j:= 1 to n do
      if m[i,j] > maiorElemento then
	maiorElemento:= m[i,j];

  for i:= 1 to n do
    for j:= 1 to n do
      m[i,j]:= maiorElemento - m[i,j];
end;

function achar_x(var m: tpMatriz; linhaIni, colIni, tam: integer): boolean;
var i, j, elemento, inicio: integer;
begin
  achar_x:= true;
  i:= linhaIni;
  j:= colIni;
  elemento:= m[linhaIni,colIni];
  while i < linhaIni+tam-1 do
    begin
      if m[i,j] <> elemento then
	achar_x:= false;

      i:= i + 1;
      j:= j + 1;
    end;

  inicio:=linhaIni+tam-1;
  j:= colIni;
  while inicio >= linhaIni do
    begin
      if m[inicio,j] <> elemento then
	achar_x:= false;

      inicio:= inicio - 1;
      j:= j + 1;
    end;
end;

procedure ler_matriz(var m:tpMatriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

begin
  read(n);
  ler_matriz(m, n);
  
  achou:= false;
  tam:= 2;
  while (tam <= n) and not achou do
    begin
      for i:= 1 to n-tam+1 do
	  for j:= 1 to n-tam+1 do
	      if achar_x(m, i, j, tam) then
		  inverte_cor(m, n); achou:= true;
      tam:= tam + 1;
    end;
  writeln();
  imprimir_matriz(m, n);
end.
