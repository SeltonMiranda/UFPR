program nulo;
type matriz = array[1..100,1..100] of longint;
var v: matriz; m,n, LinhasNulas, ColunasNulas: longint;

function ContarColunasNulas(var v: matriz; m, n: longint): longint;
var cont, i, j: longint; ehnulo: boolean;
begin
  cont:= 0;
  for j:= 1 to n do
    begin
      ehnulo:= true;
      for i:= 1 to m do
	if v[i,j] <> 0 then
	  ehnulo:= false;

      if ehnulo then
	cont:= cont + 1;
    end;
  ContarColunasNulas:= cont;
end;

function ContarLinhasNulas(var v: matriz; m, n: longint): longint;
var cont, i, j: longint; ehnulo: boolean;
begin
  cont:= 0;
  for i:= 1 to m do
    begin
      ehnulo:= true;
      for j:= 1 to n do
	if v[i,j] <> 0 then
	  ehnulo:= false;

      if ehnulo then
	cont:= cont + 1;
    end;
  ContarLinhasNulas:= cont;
end;

procedure LerMatriz(var v: matriz; m,n: longint);
var i, j: longint;
begin
  for i:= 1 to m do
    for j:= 1 to n do
      read(v[i,j]);
end;

begin
  read(m, n);
  LerMatriz(v, m, n);
  LinhasNulas:= ContarLinhasNulas(v, m, n);
  ColunasNulas:= ContarColunasNulas(v, m, n);

  writeln('linhas:',LinhasNulas);
  writeln('colunas:', ColunasNulas);
end.
