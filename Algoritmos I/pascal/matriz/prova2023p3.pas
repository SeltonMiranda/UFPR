program prova;
CONST MAX = 100;
type matriz = array[1..MAX,1..MAX] of integer;
    vetor = array[1..MAX] of integer;
var m: matriz; n, i, elemento: integer;

function temrepetido(var v: vetor; n, num: integer): boolean;
var i: integer;
begin
  temrepetido:= false;
  for i:= 1 to n do
    if (v[i] = num) then
	temrepetido:= true;
end;

function achar(var m: matriz; n: integer; var elemento: integer): boolean;
var i, j, cont: integer;
begin
  for j:= 1 to n do
    Begin
      cont:= 1;
      for i:= 2 to n do
	      if temrepetido(m[i], n, m[1,j]) then
	        cont:= cont + 1;

	    if cont = n then
	      begin
          achar:= true;
          elemento:= m[1,j];
        end;
	    end;
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

procedure OrdenaLinha(var v: vetor; n: integer) ;
var i , j , pos_menor: integer; aux: integer;
begin
  for i:= 1 to n-1 do
    begin
      pos_menor:= i ;
      for j:= i+1 to n do 
	if v[j] < v[pos_menor] then
	  pos_menor:= j ;
      aux:= v[pos_menor] ; 
      v[pos_menor]:= v[ i ] ;
      v[i]:= aux;
    end;
end;

procedure ler_matriz(var m: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

Begin
  read(n);
  ler_matriz(m,n);

  for i:= 1 to n do
    OrdenaLinha(m[i], n);

  writeln();
  imprimir(m, n);

  if achar(m, n, elemento) then
    writeln(elemento)
  else 
    writeln(-1);
End.
