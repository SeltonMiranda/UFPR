program cabeounao;
type matriz = array[1..100,1..100] of integer;
var m1, m2: matriz; l, c, l2, c2, i, j: integer;

procedure imprimir(var m: matriz; l, c: integer);
var i, j: integer;
begin
  for i:= 1 to l do
    begin
      for j:= 1 to c do
	write(m[i,j],' ');
      writeln();
    end;
end;

procedure insereMatriz(var m1, m2: matriz; i, j, l2, c2: integer);
var a, b, v, x: integer;
begin
  v:= 1;
  for a:= i to i+l2-1 do
    begin
      x:= 1;
      for b:= j to j+c2-1 do
	begin
	  m1[a,b]:= m2[v,x];
	  x:= x + 1;
	end;
      v:= v + 1;
    end;
end;

function cabeMatriz(var m1: matriz; i, j, l2, c2: integer): boolean;
var a, b: integer;
begin
  cabeMatriz:= true;
  if m1[i,j] <> 0 then
    cabeMatriz:= false
  else 
    begin
      for a:= i to i+l2-1 do
	for b:= j to j+c2-1 do
	  if m1[a,b] <> 0 then
	    cabeMatriz:= false;
    end;
end;

procedure ler_matriz(var m: matriz; l, c: integer);
var i, j: integer;
begin
  for i:= 1 to l do
    for j:= 1 to c do
      read(m[i,j]);
end;
  
begin
  read(l,c);
  ler_matriz(m1, l, c);
  read(l2, c2);
  ler_matriz(m2, l2, c2);

  if (l2 > l) or (c2 > c) then
    writeln('Nao eh possivel realizar a operacao')
  else 
    begin
      for i:= 1 to l-l2+1 do
	begin
	  for j:= 1 to c-c2+1 do
	   if cabeMatriz(m1, i, j, l2, c2) then
	     begin
	       insereMatriz(m1, m2, i, j, l2, c2);
	       imprimir(m1, l, c);
	     end;
	end;
    end;
end.
