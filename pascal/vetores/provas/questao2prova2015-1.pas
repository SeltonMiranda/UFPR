program questao2;
type vetor = array[1..100] of longint;
var v: vetor; tam: longint;

procedure Imprimir(var v:vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    write(v[i],' ');
end;

procedure OrdenaRepetidos(var v:vetor; tam, c: longint);
var i, j, posmenor, aux: longint;
begin
  for i:= tam-c+1 to tam-1 do
    begin
      posmenor:= i;
      for j:= i + 1 to tam do
	  if v[j] < v[posmenor] then
	    posmenor:= j;

	  aux:= v[posmenor];
	  v[posmenor]:= v[i];
	  v[i]:= aux;
    end;
end;

procedure Mover(var v:vetor; tam: longint);
var i, j, k, cont, aux: longint;
begin
  cont:=0;
  i:= 1;
  while i<= tam do
    begin
      j:= i + 1;
      while (j<=tam) and (v[j]<>v[i]) do
	j:= j + 1;
      if v[j] = v[i] then
	begin
	  cont:= cont + 1;
	  aux:= v[j];
	  for k:= j to tam-1 do
	    v[k]:= v[k+1];
	  v[k+1]:= aux;
	end;
      i:= i + 1;
    end;
  OrdenaRepetidos(v, tam, cont);
end;

procedure LerVetor(var v:vetor; var tam: longint);
var i, n: longint;
begin
  i:=0;
  read(n);
  while n <> 0 do
    begin
      i:= i +1;
      v[i]:= n;
      read(n);
    end;
  tam:= i;
end;

Begin
  LerVetor(v, tam);
  Mover(v, tam);
  Imprimir(v, tam);
End.
