program questao2;
type vetor = array[1..200] of longint;
var x, y: vetor; n, m, total: longint;

function Aparece(var x, y: vetor; n, m: longint): longint;
var i, j, cont: longint; 
begin
  cont:= 0;
  i:= 1;
  while i <= m do
    begin
      j:= 1;
      while (j<=n) and (x[j]=y[i+j-1]) do
	  j:= j + 1;

      if j-1=n then
	cont:= cont + 1;

      i:= i + 1;
    end;
  Aparece:= cont;
end;

procedure levetor(var v:vetor; var tam: longint);
var i, n: longint;
begin
  i:= 0;
  read(n);
  while n<>0 do
    begin
      i:= i + 1;
      v[i]:= n;
      read(n);
    end;
  tam:= i;
end;


begin
  levetor(x, n);
  levetor(y, m);
  total:= Aparece(x, y, n, m);
  writeln(total);
end.
