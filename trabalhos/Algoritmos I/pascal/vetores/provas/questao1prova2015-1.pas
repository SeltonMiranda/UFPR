program questao1;
type vetor = array[1..200] of longint;
var v: vetor; tam: longint;

procedure lerentrada(var v: vetor; var tam: longint);
var i, n, p: longint;
begin
  i:= 0;
  read(n);
  while n<> 0 do
    begin
      i:= i +1;
      v[i]:= n;
      if n < 0 then
	begin
	  randomize;
	  p:= random(i)+1;
	  while v[p] < 0 do
	    p:= random(i)+1;
	  write(v[p],' ');
	end;
      read(n);
    end;
end;

begin
  lerentrada(v, tam);
end.
