program aplica;
type matriz = array[1..100,1..100] of integer;
var m, k, R: matriz; n, i, j: integer;

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

function aplicar_filtro_no_pixel(var m, k: matriz; n, x, y: integer): integer;
var soma, i, j: integer;
begin
  soma:= 0;
  for i:= x-1 to x+1 do
    for j:= y-1 to y+1 do
      soma:= soma + m[i,j]*k[i,j];
    aplicar_filtro_no_pixel:= soma;
end;

procedure Copia_matriz(var m, R: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      R[i,j]:= m[i,j];
end;

procedure ler_matriz(var m: matriz; n: integer);
var i,j : integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

begin
  read(n);
  ler_matriz(m, n);
  ler_matriz(k, 3);
  Copia_matriz(m, R, n);

  for i:= 2 to n-1 do
    for j:= 2 to n-1 do
      R[i,j]:= aplicar_filtro_no_pixel(m, k, n, i, j);

  writeln();
  imprimir_matriz(R, n);

end.
