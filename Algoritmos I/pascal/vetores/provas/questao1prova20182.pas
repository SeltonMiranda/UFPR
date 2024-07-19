program questao1;
type vetor = array[1..200] of longint;
var v: vetor; n: longint;

function ehbalanceado(var v: vetor; tam: longint): boolean;
var j, i: longint;
begin
  i:= 1;
  j:= tam;
  ehbalanceado:= true;
  
  while i <= tam div 2 do
    begin
      if v[i] + v[j] <> v[i+1] + v[j-1] then
	ehbalanceado:= false;
      i:= i + 1;
      j:= j - 1;
    end;
end;

procedure OrdenaVetor(var v: vetor; tam: longint);
var i, j, pos_menor, aux: longint;
begin
  for i:= 1 to tam-1 do
    begin
      pos_menor:= i;
      for j:= i + 1 to tam do
	if v[j] < v[pos_menor] then
	  pos_menor:= j;

	aux:=v[pos_menor];
	v[pos_menor]:= v[i];
	v[i]:= aux;
    end;
end;

procedure LerVetor(var v: vetor; var tam: longint);
var i, n: longint;
begin
  i:= 0;
  read(n);
  while n<> 0 do
    begin
      i:= i + 1;
      v[i]:= n;
      read(n);
    end;
  tam:= i;
end;

begin
  LerVetor(v, n);
  OrdenaVetor(v, n);
  if ehbalanceado(v, n) then
    writeln('sim, eh balancedo')
  else
    writeln('nao eh balanceado');

end.
