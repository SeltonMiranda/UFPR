program questao2;
type vetor = array[1..200] of longint;
var v: vetor; n: longint;

procedure imprimirvetor(var v: vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    write(v[i],' ');
end;

procedure mover(var v: vetor; tam: longint);
var pos_menor, aux, i, j, k, cont: longint;
begin
  cont:= 0;
  for i:= 1 to tam do
    begin
      j:= i +1;
      
      while (j<= tam) and (v[j]<> v[i]) do
	j:= j + 1;
    
      if v[j] = v[i] then
	begin
	  aux:= v[j];
	  cont:= cont + 1;
	  
	  for k:= j to tam-1 do
	    v[k]:= v[k+1];
	  
	  v[k+1]:= aux;
	end;
    end;

  for i:= tam-cont+1 to tam-1 do
    begin
      pos_menor:= i;
      for j:= i+1 to n do
	begin
	  if v[j] < v[pos_menor] then
	    pos_menor:= j;

	  aux:= v[pos_menor];
	  v[pos_menor]:= v[i];
	  v[i]:= aux;
	end;
    end;    
end;
      
procedure lervetor(var v: vetor; var tam: longint);
var i, n: longint;
begin
  i:= 0;
  read(n);
  while n <> 0 do
    begin
      i:= i +1;
      v[i]:= n;
      read(n);
    end;
  tam:= i;
end;

begin
  lervetor(v, n);
  mover(v, n);
  imprimirvetor(v, n);
end.
