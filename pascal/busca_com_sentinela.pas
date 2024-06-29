program busca_com_sentinela;
type vetor = array[1..200] of real;

function busca(x: real; var v: vetor; n: integer): integer;
  var i: integer;
  begin
      v[n+1]:= x;
      i:=1;
      while v[i] <> x do
	  i:= i + 1;
      
      if i <= n then
	  busca:= i
      else
	  busca:= 0;
  end;

procedure ler_vetor(var v: vetor; tam: integer);
  var i: integer;
  begin
      for i:=1 to tam do
	  read(v[i]);
  end;
  
var
  x: real;
  n, index: integer;
  v: vetor;

begin
    writeln('qual o tamanho do vetor?');
    read(n);
    ler_vetor(v, n);

    writeln('qual numero quer procurar?');
    read(x);
    index:= busca(x, v, n);

    writeln('o elemento que procura está no indice: ', index);
end.
