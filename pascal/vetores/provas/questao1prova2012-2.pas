program questao1;
type vetor = array[1..200] of longint;
var v, w: vetor; n, m: longint;

function intersecao(var v, w: vetor; n, m: longint): longint;
var i, j, cont: longint;
begin
  cont:= 0;
  for i:= 1 to n do
    begin
      for j:= 1 to m do
	if v[i] = w[j] then
	  cont:= cont + 1;
    end;
  intersecao:= cont;
end;

procedure lervetor(var v:vetor; var tam: longint);
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

Begin
  lervetor(v, n);
  lervetor(w, m);
  if intersecao(v, w, n, m) = 0 then
    writeln('sim')
  else
    writeln('nao');
End.
