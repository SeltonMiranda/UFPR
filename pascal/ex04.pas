program ex04;
CONST MAX = 200;
type vetor = array[1..MAX] of longint;
var v: vetor; tam: longint;

procedure gerar_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
    for i:= 1 to tam do
      begin
	if i mod 2 = 1 then
	  v[i]:= 3*i
	else
	  v[i]:=2*i;
      end;
  end;

procedure imprimir_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
    for i:= 1 to tam do
      write(v[i], ' ');
  end;

Begin
  read(tam);
  gerar_vetor(v, tam);
  imprimir_vetor(v, tam);
End.
