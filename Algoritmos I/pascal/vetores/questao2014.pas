program VerificaVetorArrumado;
type  vetor = array[1..200] of real;
var v: Vetor; n, p: longint;

function estaarrumado(var v: vetor; var index: longint; n: longint): boolean;
var j, i, primeira_vez: longint; arrumado: boolean;
begin
  primeira_vez:= 0;
  estaarrumado:= false;
  for j := 1 to n do
    begin
      arrumado := true;
      
      for i := 1 to j - 1 do
	  if (v[i] > v[j]) then
	    arrumado := false;

      if arrumado then
	for i := j + 1 to n do
	    if (v[j] >= v[i]) then
		arrumado := false;

      if arrumado and (primeira_vez=0) then
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

