program eh_par;
CONST MAX = 200;
type
    vetor = array[1..MAX] of longint;
var
   tam: longint;
   v: vetor;

procedure ler_tamanho(var tam: longint);
  begin
      writeln('qual o tamanho do vetor?');
      repeat
	  read(tam);
      until (tam > 0) and (tam <= 200);
  end;

procedure ler_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
      for i:= 1 to tam do
	read(v[i]);
  end;

function eh_par(n: longint): boolean;
  begin
      if n mod 2 = 0 then
	  eh_par:= true
	else eh_par:= false;
  end;

procedure imprimir_pares(var v: vetor; tam: longint);
  var
    i: longint;
  begin
      writeln('aqui esta os pares dentro do vetor:');
      for i:= 1 to tam do
	  if eh_par(v[i]) then
	    write(v[i],' ');
      writeln();
  end;

procedure imprimir_pos_pares(var v: vetor; tam: longint);
  var i: longint;
  begin
      writeln('Aqui esta os valores com indices pares no vetor: ');
      for i:= 1 to tam do
	if eh_par(i) then
	    write(v[i],' ');
      writeln();
  end;
begin
  ler_tamanho(tam);
  ler_vetor(v, tam);
  imprimir_pares(v, tam);
  imprimir_pos_pares(v, tam);
end.
