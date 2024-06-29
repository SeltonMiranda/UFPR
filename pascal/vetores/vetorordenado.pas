program vetorordenado;
type vetor = array[1..200] of longint;
var tam: longint; v: vetor;

procedure ler_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
    for i:= 1 to tam do
      read(v[i]);
  end;

function ehordenado(var v: vetor; tam: longint): boolean;
  var i: longint;
  begin
    ehordenado:= true;
    i:= 1;
    while (i < tam) do
      begin
	if v[i] > v[i+1] then
	  ehordenado:= false;
	i:= i + 1;
      end;
  end;

Begin
  read(tam);
  if tam = 0 then
    writeln('vetor vazio')
  else
    begin
      ler_vetor(v, tam);
      if ehordenado(v, tam) then
	writeln('sim')
      else
	writeln('NAO');
    end;
End.
