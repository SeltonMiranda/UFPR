program teste;
type matriz = array[1..100,1..100] of integer;
var mat, m2: matriz; k, p, n, passo, i, j, tam: integer;

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

function Maior_4_vizinhos(var m: matriz; i, j: integer): integer;
var maior, k, p: integer;
begin
  maior:= m[i,j];
  for k:= i to i + 1 do
    for p:= j to j + 1 do
      if m[k,p] > maior then
	  maior:= m[k,p];

  Maior_4_vizinhos:= maior;
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
  read(passo);
  ler_matriz(mat, n);
  tam:= n - passo;
  if passo = 2 then
    begin
      k:= 1;
      for i:= 1 to tam do
	begin
	  p:= 1;
	  for j:= 1 to tam do
	    begin
	      m2[i,j]:= Maior_4_vizinhos(mat, k, p);
	      p:= p + passo;
	    end;
	  k:= k + passo;
	end;
    end
  else if passo = 1 then
    begin
      for i:= 1 to tam do
	  for j:= 1 to tam do
	      m2[i,j]:= Maior_4_vizinhos(mat, i, j);
    end;
  writeln();
  imprimir(m2, tam);
end.
