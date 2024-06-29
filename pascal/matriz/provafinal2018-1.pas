program final;
CONST MAX = 200;
type tpMatriz = array[1..MAX,1..MAX] of integer;
var m, k, r: tpMatriz; n, elemento, i, j: integer;

procedure ler_matriz(var m: tpMatriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

procedure copia_linha(var m, r: tpMatriz; inicio, fim: integer);
var j: integer;
begin
  for j:= 1 to fim do
    r[inicio,j]:= m[inicio,j];

  for j:= 1 to fim do
    r[fim,j]:= m[fim,j];
end;


procedure copia_coluna(var m, r: tpMatriz; inicio, fim: integer);
var i: integer;
begin
  for i:= 1 to fim do
    r[i,inicio]:= m[i,inicio];

  for i:= 1 to fim do
    r[i,fim]:= m[i,fim];
end;

function aplicar_filtro_no_pixel(var m, k: tpMatriz; n, x, y: integer): integer;
var p, q, i, j, soma: integer;
begin
  soma:= 0; q:=1;,  p:=1; 
  for i:= x-1 to x+1 do
    begin
      for j:= y-1 to y+1 do
	begin
	  soma:= soma + m[i,j]*k[q,p]; p:= p + 1;
	end;
      q:= q + 1; p:= 1;
    end;
  aplicar_filtro_no_pixel:= soma;
end;
  
procedure insere_elemento(var r: tpMatriz; elemento, x, y: integer);
begin
  r[x,y]:= elemento;
end;

procedure imprimir_matriz(var m: tpMatriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to n do
	write(m[i,j],'   ');
      writeln();
    end;
end;

begin
  read(n);
  ler_matriz(m, n);
  ler_matriz(k, 3);

  copia_linha(m, r, 1, n);
  copia_coluna(m, r, 1, n);

  for i:= 2 to n-1 do
    begin
      for j:= 2 to n-1 do
	begin
	  elemento:= aplicar_filtro_no_pixel(m, k, 3, i, j);
	  insere_elemento(r, elemento, i, j);
	end;
    end;

  imprimir_matriz(m, n);
  writeln();
  imprimir_matriz(r, n);
end.
