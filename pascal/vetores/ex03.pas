program ex03;
CONST MAX = 200;
type vetor = array[1..MAX] of longint;
var v: vetor; tam, n, m: longint;

function inserir(n, tam: longint): vetor;
  var vet: vetor;
  begin
    vet[tam]:= n;
    inserir:= vet;
  end;

function presente(var v: vetor; tam, x: longint): boolean;
  var i: longint; achou: boolean;
  begin
    achou:= false;
    v[tam + 1]:= x;
    i:= 1;
    while (v[i]<>x) and (not achou) do
      begin
	if v[i] = x then
	  achou:= true;
	i:= i + 1;
      end;

    if i > tam then
      presente:= false
    else
      presente:= true;
  end;

begin
  read(n);
  tam:= 1;
  while n <> 0 do
    begin
      v:= inserir(n, tam);
      read(n);
      tam:= tam + 1;
    end;
   read(m);
   while m <> 0 do
     begin
       if presente(v, tam, m) then
	 writeln('pertence')
      else
	  writeln('nao pertence');
      read(m);
     end;
end.
