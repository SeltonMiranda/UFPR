program bbb;
type
  vetor = array[1..200] of longint;
var
  v: vetor;
  tam_v: longint;

procedure ler(var v: vetor; var tam: longint);
  var i, n: longint;
  begin
    read(n);
    i:= 1;
    while n<>0 do
      begin
	v[i]:= n;
	i:= i + 1;
	read(n);
      end;
    tam:= i;
  end;

procedure ordenar(var v: vetor; tam: longint);
 var
   i, j, min, temp: longint;
 begin
    for i:= 1 to tam - 1 do
      begin
	min:= i;
	for j:= i + 1 to tam do
	  begin
	    if v[j] < v[min] then
	      min:= j;
	  end;
       temp:= v[i];
       v[i]:= v[min];
       v[min]:= temp;
      end;
 end;

function balanceada(var v: vetor; tam: longint): boolean;
    var i, j: longint;
  begin
    balanceada:= true;
    for i:= 1 to tam div 2 do
      begin
	j:= tam - i + 1;
	if ((v[i] + v[j]) <> (v[i+1] + v[j-1])) then
	  balanceada:= false;
      end;
  end;

begin
  ler(v, tam_v);
  ordenar(v, tam_v);
  if balanceada(v, tam_v) then
    writeln('sim')
  else
    writeln('nao');
end.
