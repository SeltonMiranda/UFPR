program vetores006;

CONST MIN = 0; MAX = 199;
type
    vetor = array[MIN..MAX+1] of real;
var
  tam, n: longint;
  num: real;
  v: vetor;

procedure inserir_num(var v: vetor; var tam: longint; x: real);
  var i: longint;
  begin
	  v[0]:= x;
	  i:= tam;
	    while x < v[i] do
		begin
	          v[i+1]:= v[i];
		  i:= i - 1;
		end;
	  v[i+1]:= x;
	  tam:= tam + 1;
  end;

procedure remover_num(var v: vetor; var tam: longint; x: real);
  var i, pos: longint;
  begin
      i:= 1;
      while (v[i] <> x) and (i <= tam) do 
	    i:= i + 1;
      
     for pos:= i to tam-1 do
	  v[pos]:= v[pos + 1];
     tam:= tam - 1;
  end;

procedure mostrar_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
    if tam > 0 then
      for i:= 1 to tam do
	  write(v[i]:0:1,'  ')
    else
	writeln('vazio');
  end;

function pertence(var v: vetor; tam: longint; x: real): boolean;
  var i: longint;
  begin
      i:= 1;
      while (i <= tam) and (v[i] <> x) do
	  i:= i + 1;

      if i > tam then
	    pertence:= false
      else
	  pertence:= true;
  end;

begin
  tam:= 0;

  repeat
      readln(n);
      if n = 1 then
	begin
	    read(num);
	    if tam = 200 then
	      writeln('erro')
	    else
	      begin
		  inserir_num(v, tam, num);
		  mostrar_vetor(v, tam);
		  writeln();
	      end;
	      	
	end
      else if n = 2 then
	      begin
		  read(num);
		  if pertence(v, tam, num) = false then
			writeln('erro');
		  else
		    begin
		      remover_num(v, tam, num);
		      mostrar_vetor(v, tam);
		      writeln();
		    end
	      end; 
  until n = 0;

  mostrar_vetor(v, tam);
end.

