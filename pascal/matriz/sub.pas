program sub;
type matriz = array[1..100,1..100] of integer;
var m: matriz; MaiorSubMatriz, i, j, tam, n, x_ini, y_ini, x_fim, y_fim: integer;

function troca(var xi, yi, xf, yf: integer; i, j, tam: integer): integer;
begin
  xi:= i;
  yi:= j;
  xf:= i+tam-1;
  yf:= j+tam-1;
  troca:= tam;
end;


function verificaSubMatriz(var m: matriz; i, j, tam: integer): boolean;
var a, b: integer;
begin
  verificaSubMatriz:= true;
  for a:= i to i+tam-1 do
    for b:= j to j+tam-1 do
      if m[a,b] <> 1 then
	verificaSubMatriz:= false;
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
  MaiorSubMatriz:= 0;
  for tam:= 1 to n do
    for i:= 1 to n-tam+1 do
      for j:= 1 to n-tam+1 do
	if verificaSubMatriz(m, i, j, tam) then
	  begin
	    if tam > MaiorSubMatriz then
		MaiorSubMatriz:= troca(x_ini, y_ini, x_fim, y_fim, i, j, tam);
	  end;

  writeln(x_ini,',', y_ini);
  writeln(x_fim,',', y_fim);
end.
