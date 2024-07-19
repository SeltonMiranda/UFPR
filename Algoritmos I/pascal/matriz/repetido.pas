program repete;
type matriz = array[1..100,1..100] of longint;
var v: matriz; m, n: longint;


function TemReptido(var v:matriz; m,n: longint): boolean;
var repetido: boolean; i, j, k, t: longint;
begin
  i:= 1;
  repetido:= false;
  while (i <= m) and not repetido do
    begin
      j:= 1;
      while (j <= n) and not repetido do
	begin 
	  k:= 1;
	  while (k <= m) and not repetido do
	    begin
	      t:= 1;
	      while (t <= n) and not repetido do
		begin
		  if (v[i,j] = v[k,t]) and ((i<>k) and(j<>t)) then
		    repetido:= true;
		  t:= t + 1;
		end;
	      k:= k + 1;
	    end;
	  j:= j + 1;
	end;
      i:= i+ 1;
    end;
  if repetido then
    TemReptido:= true
  else
    TemReptido:= false;
end;

procedure LerMatriz(var v:matriz; m,n: longint);
var i,j: longint;
begin
  for i:= 1 to m do
    for j:= 1 to n do
      read(v[i,j]);
end;

begin
  read(m, n);
  LerMatriz(v, m, n);
  if TemReptido(v, m, n) then
    writeln('sim')
  else
    writeln('nao');
end.
