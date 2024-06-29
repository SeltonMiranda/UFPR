program matriz;
type matrix = array[1..100,1..100] of longint;
var
    m: matrix; n: longint;

function EhMatrizSuperior(var m: matrix; n: longint): boolean;
var i, j: longint;
begin
  EhMatrizSuperior:= true;
  for i:= 1 to n do
    for j:= 1 to n do
      if (j>i) and (m[i,j]<> 0) then
	EhMatrizSuperior:= false;
end;

function EhMatrizInferior(var m: matrix; n: longint): boolean;
var i, j: longint;
begin
  EhMatrizInferior:= true;
  for i:= 1 to n do
    for j:= 1 to n do
      if (i>j) and (m[i,j]<> 0) then
	EhMatrizInferior:= false;
end;

procedure LerMatriz(var m: matrix; n: longint);
var i, j: longint;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to n do
	read(m[i,j]);
    end;
end;

begin
  read(n);
  LerMatriz(m, n);
  if EhMatrizInferior(m, n) or EhMatrizSuperior(m, n) then
    writeln('sim')
  else
    writeln('nao');
end.
