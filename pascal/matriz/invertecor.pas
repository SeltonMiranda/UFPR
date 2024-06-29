program inverte;
CONST MIN_TAM = 2; 
type matriz = array[1..100,1..100] of integer;
var m: matriz; n, i, j, tam: integer; achou: boolean;

procedure imprimir_matriz(var m: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to n do
	write(m[i,j],' ');
      writeln();
    end;
end;

procedure inverte_cor(var m: matriz; n: integer);
var i, j, max: integer;
begin
  max:= m[1,1];
  for i:= 1 to n do
    for j:= 1 to n do
      if m[i,j] > max then
	max:= m[i,j];
    writeln(max);

  for i:= 1 to n do
    for j:= 1 to n do
      m[i,j]:= max - m[i,j];
end;

function achar_X(var m: matriz; n, linIni, colIni, tam: integer): boolean;
var i, j, a, b: integer;
begin
  achar_X:= true;
      j:= colIni;
      for i:= linIni to linIni+tam-1 do
	begin
	  if m[i,j] <> m[linIni, colIni] then
	    achar_X:= false;
	  j:= j + 1;
	end;
      a:= linIni+tam-1;
      for b:= colIni to colIni+tam-1 do
	begin
	  if m[a,b] <> m[linIni, colIni] then
	    achar_X:= false;
	  a:= a - 1;
	end;
end;

procedure ler_matriz(var m: matriz; n: integer);
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
  tam:= MIN_TAM;

  while (tam <= n) and not achou do
    begin
      for i:= 1 to n do
	  for j:= 1 to n do
	      if achar_X(m, n, i, j, tam) and not achou then
		begin
		  inverte_cor(m, n);
		  achou:= true;
		end;
      tam:= tam + 1;
    end;

  writeln();
  imprimir_matriz(m, n);
end.
