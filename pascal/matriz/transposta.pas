program sss;
type matriz = array[1..100,1..100] of integer;
var m: matriz; i, n: integer;

procedure ler_matriz(var m: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

procedure imprimir(var m: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to n do
	write(m[i,j],' ');
      writeln();
    end;
end;
procedure imprimir_transposta(var m: matriz; n: integer);
var i, j: integer;
begin
  for j:= 1 to n do
    begin
      for i:= 1 to n do
	write(m[j,i],' ');
      writeln();
    end;
end;

begin
  read(n);
  ler_matriz(m, n);
  writeln();
  imprimir(m, n);
  writeln();
  imprimir_transposta(m, n);
  writeln();
  end.
