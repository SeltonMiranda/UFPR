program exemplo;
CONST MAX = 200;
type vetor = array[1..MAX] of integer;
var
   v: vetor;
   tam: integer;

function inicializar_vetor(tam: integer):vetor;
  var i: integer; v: vetor;
  begin
    for i:= 1 to tam do
      begin
	if i mod 2 = 0 then
	  v[i]:= 7
	else
	  v[i]:= -2;
      end;
      inicializar_vetor:= v;  
  end;

procedure imprimir(var v: vetor; tam: integer);
  var i: integer;
  begin
    for i:= 1 to tam do
      write(v[i], ' ');
  end;

begin
  read(tam);
  v:= inicializar_vetor(tam);
  imprimir(v, tam);
end.
