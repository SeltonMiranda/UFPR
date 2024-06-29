program VerificaVetorArrumado;
type  vetor = array[1..200] of real;
var v: Vetor; n, p: longint;


function VerificaEsquerda(var v: vetor; indice: longint): boolean;
var i: longint;
begin
  VerificaEsquerda:= true;
  for i := 1 to indice - 1 do
     if (v[i] > v[indice]) then
	VerificaEsquerda := false;
end;

function VerificaDireita(var v: vetor; tam, indice: longint): boolean;
var i: longint;
begin
  VerificaDireita:= true;
  for i := indice + 1 to tam do
     if (v[i] <= v[indice]) then
	VerificaDireita := false;
end;



function estaarrumado(var v: vetor; var index: longint; n: longint): boolean;
var j, i, primeira_vez: longint; arrumado: boolean;
begin
  primeira_vez:= 0;
  estaarrumado:= false;
  for j := 1 to n do
    begin
     if VerificaEsquerda(v, j) and VerificaDireita(v, n, j) and (primeira_vez=0) then
	begin
	  primeira_vez:= primeira_vez + 1;
	  index:= j;
	  estaarrumado:= true;
	end;
    end;
end;
  
procedure lervetor(var v: vetor; tam: longint);
var i: longint;
begin
  for i := 1 to n do
    begin
      read(v[i]);
    end;
end;

begin
  readln(n);
  lervetor(v, n);

  if estaarrumado(v, p, n) then
    writeln(p)
  else
    writeln('o vetor nao esta arrumado');
end.

