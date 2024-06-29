program questao1;
type Tpvetor = array[1..100] of longint;
var v: Tpvetor; n, posi, num: longint;

procedure imprimir(var v: Tpvetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    write(v[i],' ');
end;

procedure remove(var v: Tpvetor; var n: longint; posi, num: longint);
var i, j: longint;
begin
  if posi + num <= n then
    begin
      i:= posi;
      j:= num + posi;
      while i <= j do
	begin
	  v[i]:= v[i+num];
	  i:= i + 1;
	end;
      n:= n - num;	
    end;
end;

procedure lervetor(var v:Tpvetor; var n: longint);
var i, p: longint;
begin
  i:=0;
  read(p);
  while p <> 0 do
    begin
      i:= i +1;
      v[i]:= p;
      read(p);
    end;
  n:= i;
end;
  
begin
  lervetor(v, n);
  read(posi, num);
  remove(v, n, posi, num);
  imprimir(v, n);
end.
