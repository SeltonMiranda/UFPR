program ques;
type matriz = array[1..100,1..100] of longint;
var n: longint; m: matriz;

function SomadSec(var m: matriz; linha, coluna, tam: longint): longint;
var i, s, inicio: longint;
begin
   s:= 0;
   inicio:= linha+tam-1;
   for i:= inicio downto linha do
       s:= s + m[i,inicio-i+1];
  SomadSec:= s;
end;


function SomadPrinc(var m:matriz; linha, coluna, tam: longint): longint;
var i, j, s: longint;
begin
   s:= 0;

  i:= linha;
  j:= coluna;
  while i <= linha+tam-1 do
    begin
      s:= s + m[i,j];
      i:= i + 1;
      j:= j + 1;
    end;

  SomadPrinc:= s;
end;

function verificalinhas(var m: matriz; linha, coluna, tam, sum: longint): boolean;
var soma, i, j: longint; 
begin
  verificalinhas:= true;
  for i:= linha to linha+tam-1 do
    begin
      soma:= 0;
      for j:= coluna to coluna+tam-1 do
	soma:= soma + m[i,j];

      if soma <> sum then
	verificalinhas:= false;
    end;
end;


function verificaColunas(var m: matriz; linha, coluna, tam, sum: longint): boolean;
var soma, i, j: longint; 
begin
  verificaColunas:= true;
  for j:= coluna to coluna+tam-1 do
    begin
      soma:= 0;
      for i:= linha to linha+tam-1 do
	soma:= soma + m[i,j];

      if soma <> sum then
	verificaColunas:= false;
    end;
end;

function ehMagic(var m: matriz; linha, coluna, tam: longint): boolean;
var i, somaEx, dPrinc, dSec: longint; 
begin
  somaEx:= 0;
  ehMagic:= true;
  
  //realizo a soma dos elementos de uma coluna para poder comparar
  for i:=linha to linha+tam-1 do
    somaEx:= somaEx + m[i,coluna];

  //somo os elementos das diagonais
  dPrinc:= SomadPrinc(m, linha, coluna, tam);
  dSec:= SomadSec(m, linha, coluna, tam);

  // compara linhas, colunas, diagonais
  if dPrinc <> somaEx then
    ehMagic:= false;

  if dSec <> somaEx then
    ehMagic:= false;

  if not verificalinhas(m, linha, coluna, tam, somaEx) then
    ehMagic:= false;

  if not verificaColunas(m, linha, coluna, tam, somaEx) then
    ehMagic:= false;
end;



function quantMagicSquare(var m: matriz; n: longint): longint;
var i, j, tam, cont: longint;
begin
  tam:= 2;
  cont:= 0;
  while tam <= n do
    begin
      for i:= 1 to n-tam+1 do
	  for j:= 1 to n-tam+1 do
	      if ehMagic(m, i, j, tam) then
		  cont:= cont + 1;
      tam:= tam + 1;
    end;
  quantMagicSquare:= cont;
end;

procedure lerMatriz(var m: matriz; n: longint);
var i, j: longint;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

begin
  readln(n);
  lerMatriz(m, n);
  writeln(quantMagicSquare(m, n));
end.
