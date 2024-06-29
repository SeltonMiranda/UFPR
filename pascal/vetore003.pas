Program vetores003;

CONST MIN=1; MAX=200;

type 
  vetor=array[MIN-1..MAX] of longint;
var
  tam: longint;
  v: vetor;

procedure ler_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
      for i:= 1 to tam do
	  read(v[i]);
  end;
  
procedure vetor_ordem_inversa(var v: vetor; tam: longint);
  var i: longint;
  begin
      for i:= tam downto 1 do
	write(v[i],' ');
  end;
  
function esta_ordenado(var v: vetor; tam: longint): boolean;
  var i: longint;
  begin
      i:= 1;
      while (v[i] <= v[i+1]) and (i <= tam-1) do
	  i:= i + 1;

      if i = tam then
	  esta_ordenado:= true
	else
	  esta_ordenado:= false;
  end;

Begin
    read(tam);
    if tam > 0 then
      begin
	ler_vetor(v, tam);

	if esta_ordenado(v, tam) then
	  begin
	    writeln('sim');
	    vetor_ordem_inversa(v, tam);
	  end
	else
	    begin
	      writeln('nao');	
	      vetor_ordem_inversa(v, tam);
	    end;
      end
    else
	writeln('vetor vazio');
End.
