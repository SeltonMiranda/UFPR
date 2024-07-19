program imag;
type matriz = array[1..100,1..100] of integer;
var mat, mat2, matp: matriz; l, c, lp, cp, i, j: integer;

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

procedure Preenche_com_Zeros(var mat: matriz; i, j, lp, cp: integer);
var a, b: integer;
begin
  for a:= i to i+lp-1 do
      for b:= j to j+cp-1 do
	mat[a,b]:= 0;
end;

function foundPattern(var mat, matp: matriz; i, j, lp, cp: integer): boolean;
var a, b, k, p: integer;
begin
  foundPattern:= true;
  a:= i;
  b:= j;
  for k:= 1 to lp do
    begin
      b:= j;
      for p:= 1 to cp do
	begin
	  if (matp[k,p] >= 0) and (matp[k,p] <> mat[a,b]) then
	    foundPattern:= false;
	  b:= b + 1;
	end;
      a:= a + 1;
    end;
end;

procedure CopiaOriginal(var mat, mat2: matriz; l, c: integer);
var i, j: integer;
begin
  for i:= 1 to l do
    for j:= 1 to c do
      mat2[i,j]:= mat[i,j];
end;

procedure ler_matriz(var mat: matriz; n, m: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to m do
      read(mat[i,j]);
end;

begin
  read(c, l);
  ler_matriz(mat, l, c);
  read(cp, lp);
  ler_matriz(matp, lp, cp);

  CopiaOriginal(mat, mat2, l, c);

  for i:= 1 to l-lp+1 do
    for j:= 1 to c-cp+1 do
      if foundPattern(mat, matp, i, j, lp, cp) then
	  Preenche_com_Zeros(mat2, i, j, lp, cp);
	
  writeln();
  imprimir(mat2, l, c);
end.
