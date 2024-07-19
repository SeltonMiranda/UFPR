program ques;
type matriz = array[1..100,1..100] of longint;
var n, x: longint; m: matriz;

function sSec(var m: matriz; linha, coluna, tam: longint): longint;
var i, s, inicio: longint;
begin
   s:= 0;
   inicio:= linha+tam-1;
   for i:= inicio downto 1 do
     begin
       s:= s + m[i,inicio-i+1]
     end;
  sSec:= s;
end;


function sprinc(var m:matriz; linha, coluna, tam: longint): longint;
var i, s: longint;
begin
   s:= 0;
   for i:= linha to linha+tam-1 do
     s:= s + m[i,i];
  sprinc:= s;
end;


function scoluna(var m:matriz; linha, coluna, tam: longint): longint;
var i, j, s: longint;
begin
   s:= 0;
   for i:= linha to linha+tam-1 do
     for j:= coluna to coluna+tam-1 do
       s:= s + m[j,i];
     scoluna:= s;
end;

function slinha(var m:matriz; linha, coluna, tam: longint): longint;
var i, j, s: longint;
begin
   s:= 0;
   for i:= linha to linha+tam-1 do
     for j:= coluna to coluna+tam-1 do
       s:= s + m[i,j];
     slinha:= s;
end;

function ehMagic(var m: matriz; linha, coluna, tam: longint): boolean;
var somalinha, somacoluna, somadiagonalprincipal, somadiagonalsecundaria: longint;
begin
  ehMagic:= false;
  somalinha:= slinha(m, linha, coluna, tam);
  somacoluna:= scoluna(m, linha, coluna, tam);
  somadiagonalprincipal:= sprinc(m, linha, coluna, tam);
  somadiagonalsecundaria:= sSec(m, linha, coluna, tam);

  if somalinha = somacoluna then
    if somadiagonalprincipal = somadiagonalsecundaria then
      ehMagic:= true;
end;

function quantMagicSquare(var m: matriz; n: longint): longint;
var i, j, iniciolinha, iniciocoluna, tam, cont: longint;
begin
  tam:= 2;
  cont:= 0;
  while tam <= n do
    begin
      for i:= 1 to n-tam+1 do
	begin
	  for j:= 1 to n-tam+1 do
	    begin
	      iniciolinha:= i;
	      iniciocoluna:= j;
	      if ehMagic(m, iniciolinha,iniciocoluna, tam) then
		cont:= cont + 1;
	    end;
	end;
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
  read(n);
  lerMatriz(m, n);
  x:= quantMagicSquare(m, n);
  writeln(x);
end.
