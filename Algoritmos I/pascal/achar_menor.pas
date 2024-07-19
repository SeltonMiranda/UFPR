program achar_menor;

const MAX = 200;
type vetor = array[1..MAX] of longint;

var v: vetor;
    tam: longint;

procedure ler_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
      for i:= 1 to tam do
	  read(v[i]);
  end;

procedure imprimir_vetor (var v: vetor; tam: longint);
  var i: longint;
  begin
      i:= 1;
      while i<= tam -1 do
	begin
	  write(', ',v[i]);
	  i:= i+1;
	end;
      write(',  ',v[tam]);
      writeln();
  end;

function acha_menor(var v: vetor; tam:longint):longint;
  var
    menor, i: longint;
  begin
      menor:= v[1];
      for i:= 2 to tam do
	if v[i] < menor then
	  menor:= v[i];
      acha_menor:= menor;
  end;

function acha_pos_menor(var v: vetor; tam:longint):longint;
  var
    pos_menor, i: longint;
  begin
      pos_menor:= 1;
      for i:= 2 to tam do
	if v[i] < v[pos_menor] then
	  pos_menor:= i;
      acha_pos_menor:= pos_menor;
  end;

begin
  read(tam);
  ler_vetor(v, tam);
  imprimir_vetor(v, tam);
  writeln('O menor elemento do vetor eh ', acha_menor(v, tam));
  writeln('O menor elemento esta na posicao ', acha_pos_menor(v, tam));
end.
