program quest;
type matriz = array[1..50,1..50] of integer;
var A, B: matriz; n, m: integer;

procedure imprimir(var mat: matriz; n, m: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to m do
	write(mat[i,j],' ');
      writeln();
    end;
end;

function elemento(var A: matriz; i, j: integer): integer;
var k, l, s: integer;
begin
  s:= 0;
  for k := i - 1 to i + 1 do
      for l := j - 1 to j + 1 do
        if (k >= 1) and (k <= n) and (l >= 1) and (l <= m) then
          s:= s + A[k, l];
  elemento:= s;
end;

procedure NovaMatriz(var A: matriz; n, m: integer; var B: matriz);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to m do
	begin
	  B[i,j]:= elemento(A, i, j) - A[i,j];
	end;
    end;
end;

procedure ler_matriz(var mat: matriz; n, m: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to m do
      read(mat[i,j]);
end;

begin
  read(n, m);
  ler_matriz(A, n, m);
  NovaMatriz(A, n, m, B);
  imprimir(B, n, m);
end.
