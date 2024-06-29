program ex02;
CONST MAX = 200;
type vetor = array[1..MAX] of real;
var v: vetor; n, i: longint; a, val_positivos, val_negativos: real;

function inserir(a: real; i: longint): vetor;
  var vet_num: vetor;
  begin
      vet_num[i]:= a;
      inserir:= vet_num;
  end;

function soma_positivos(var v: vetor; tam: longint): real;
  var s: real ; i: longint;
  begin
    s:=0;
    for i:= 1 to tam do
      begin
	if v[i] > 0 then
	  s:= s+ v[i];
      end;

    if s <> 0 then
      soma_positivos:= s
    else
      soma_positivos:= 0;
  end;

function soma_negativos(var v: vetor; tam: longint): real;
  var s: real; i: longint;
  begin
    s:=0;
    for i:= 1 to tam do
      begin
	if v[i] < 0 then
	  s:= s+ v[i];
      end;

    if s <> 0 then
      soma_negativos:= s
    else
      soma_negativos:= 0;
  end;

procedure saida(n1, n2: real);
begin
  if n2 = 0 then
    writeln('divisao por zero!')
  else
     writeln(n1/n2:0:2);
end;

procedure imprimir(var v: vetor; n: longint);
  var i: longint;
  begin
    for i:= 1 to n do
      write(v[i], ' ');
  end;

begin
  repeat
    read(n);
  until (n >= 0) and (n <= 200);
if n = 0 then
  writeln('vetor vazio')
else
  begin
    for i:= 1 to n do
      begin
	read(a);
	v:= inserir(a, i);
      end;
      imprimir(v, n);
    (*val_positivos:= soma_positivos(v, n);  
    val_negativos:= soma_negativos(v, n);
    saida(val_positivos, val_negativos);*)
  end;
end.
