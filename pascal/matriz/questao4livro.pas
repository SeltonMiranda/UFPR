program quest;
type matriz = array[1..100,1..100] of integer;
    vetor = array[1..100] of integer;
var v: vetor; m: matriz; n, k: integer;

Function Calcula_custo(var m: matriz; var v: vetor; k: integer):integer;
var i, soma: integer;
begin
  soma:= 0;
  for i:= 1 to k-1 do
    soma:= soma + m[v[i],v[i+1]];
  Calcula_custo:= soma;
end;

procedure ler_vetor(var v:vetor; n: integer);
var i: integer;
begin
  for i:= 1 to n do
    read(v[i]);
end;

procedure ler_matriz(var m:matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

begin
  read(n);
  ler_matriz(m, n);
  read(k);
  ler_vetor(v, k);

  writeln(Calcula_custo(m, v, k));
end.
