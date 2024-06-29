program questao1;
type vetor = array[1..200] of longint;
var v: vetor; tam, indice: longint;

function VerificaEsquerda(var v: vetor; ind: longint): boolean;
var i: longint;
begin
  VerificaEsquerda:= true;
  i:= 1;
  while i < ind do
    begin
      if v[i]>v[ind] then
	VerificaEsquerda:= false;
      i:= i + 1;
    end;
end;

function VerificaDireita(var v: vetor; ind, tam: longint): boolean;
var i: longint;
begin
  VerificaDireita:= true;
  i:= ind+1;
  while i<=tam do
    begin
      if v[i]<=v[ind] then
	VerificaDireita:= false;
      i:= i + 1;
    end;
end;


function ChecaEstaArrumado(var v:vetor; tam: longint): longint;
var primeiroIndex, index, i: longint;
begin
  ChecaEstaArrumado:= 0;
  primeiroIndex:= 0;
  for i:= 1 to tam do
    begin
      if VerificaEsquerda(v, i) and VerificaDireita(v, i, tam) and (primeiroIndex= 0) then
	begin
	  primeiroIndex:= primeiroIndex + 1;
	  index:= i;
	end;
    end;
  ChecaEstaArrumado:= index;
end;

procedure levetor(var v:vetor; var tam: longint);
var i, n: longint;
begin
  i:= 0;
  read(n);
  while n <> 0 do
    begin
      i:= i + 1;
      v[i]:= n;
      read(n);
    end;
  tam:= i;
end;

begin
  levetor(v, tam);
  indice:= ChecaEstaArrumado(v, tam);
  if indice = 0 then
    writeln('o vetor nao esta arrumado')
  else
    writeln(indice);
end.
