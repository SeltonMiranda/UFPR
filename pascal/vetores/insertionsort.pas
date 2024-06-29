program sort;
type vetor = array[1..200] of longint;
var n, x, i, j: longint; v: vetor;
begin
  randomize;
  for i:= 1 to 10 do
    begin
      n:= random(20);
      v[i]:= n + 1;
    end;

for i:= 1 to 10 do
  write(' ',v[i]);
writeln();

  for i:=1 to 10 do
    begin
      j:= i;
      x:= v[i];
      while (j>0) and (x < v[j-1]) do
	begin
	  v[j]:= v[j-1];
	  j:= j - 1;
	end;
      v[j]:= x;	
    end;

  for i:= 1 to 10 do
    write(' ',v[i]);
writeln();
end.
