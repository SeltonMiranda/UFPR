program teste;
CONST MAXCOL = 200; MAXLIN = 200;

type  tpMatriz = array [ 1..MAXLIN, 1..MAXCOL] of integer;
      tpVetor = array [ 1..MAXCOL] of integer;

var n, m, novaCol: integer; mat: tpMatriz; v: tpVetor;

procedure ler_matriz(var mat: tpMatriz; n, m: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to m do
      read(mat[i,j]);
end;

procedure ler_vetor(var v:tpVetor);
var i: integer;
begin
  for i:= 1 to 3 do
    read(v[i]);
end;

procedure insereVetor(elem: integer; pos: integer; var v: tpVetor; tam: integer);
var i: integer;
begin
  for i:= tam downto pos do
    v[i+1]:= v[i];
  v[pos]:= elem;
end;

procedure insereCol(var mat:tpMatriz; n: integer; var m: integer; var v: tpVetor; novaCol: integer);
var i: integer;
begin
  for i:= 1 to n do
    insereVetor(v[i], novaCol, mat[i], m);
  m:= m + 1;
end;

procedure imprimir_matriz(var mat: tpMatriz; n, m: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to m do
	write(mat[i,j],' ');
      writeln();
    end;
end;

begin
  writeln('Tamanho da matriz:');
  read(n, m);
  ler_matriz(mat, n, m);

  writeln('vetor:');
  ler_vetor(v);
  writeln();
  imprimir_matriz(mat, n, m);
  writeln();

  writeln('qual lugar inserir a nova coluna?:');
  read(novaCol);
  insereCol(mat, n, m, v, novaCol);

  imprimir_matriz(mat, n, m);
end.
