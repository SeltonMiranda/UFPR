program arrumar;
type vetor = array[1..200] of longint;
var v: vetor; tam, i, primeira_ocorrencia: longint;

function VerificarDireita(var v: vetor; tam, index: longint): boolean;
var i: longint;
begin
  VerificarDireita:= true;
  i:= index + 1;
  while i <= tam do
    begin
      if v[i] <= v[index] then
	VerificarDireita:= false;
      i:= i + 1;
    end;
end;

function VerificarEsquerda(var v: vetor; index: longint): boolean;
var i: longint;
begin
  VerificarEsquerda:= true;
  i:= 1;
  while i <= index - 1 do
    begin
      if v[i] > v[index] then
	VerificarEsquerda:= false;
      i:= i + 1;
    end;
end;



procedure LerVetor(var v: vetor; var tam: longint);
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
  LerVetor(v, tam);
  primeira_ocorrencia:=0;
  for i:= 2 to tam - 1 do
    begin
      if (primeira_ocorrencia = 0) and VerificarEsquerda(v, i) and VerificarDireita(v, tam, i) then
	begin
	  primeira_ocorrencia:= primeira_ocorrencia + 1;
	  writeln(i);
	end;
    end;
    writeln();
end.
