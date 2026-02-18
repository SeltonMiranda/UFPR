program vetores4;

CONST MIN=1; MAX=200;

type
    vetor = array[MIN..MAX] of longint;
    vetor_digitos = array[MIN..MAX] of longint;
var
  v, k: vetor;
  n, tamanho_k: longint;

procedure ler_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
      for i:= 1 to tam do
	  read(v[i]);
  end;

function digitos_distintos(var v, k: vetor; tam: longint): longint;
  var
      quantidade, i, j: longint;
  begin
      quantidade:= 0;
      for i:= 1 to tam do
	begin
	  j:= 1;
	  while (v[i] <> k[j]) and (j <= quantidade) do
	      begin
		  j:= j + 1; 
	      end;
	  
	  if j > quantidade then
	      begin
		  quantidade:= quantidade + 1;
		  k[quantidade]:= v[i];
	      end;
	end;
  digitos_distintos:= quantidade;
  end;

procedure imprimir_distintos(var k: vetor; tamanho_k: longint);
  var i: longint;
  begin
    write('A sequencia tem ', tamanho_k,' numeros distintos: ');
    for i:= 1 to tamanho_k do
      write(k[i],' ');
    writeln();
  end;

procedure imprimir_ocorrencias(var v, k: vetor; tam1, tam2: longint);
  var 
    i, j, ocorre: longint;
  begin
      for i:= 1 to tam2 do
	begin
	    j:= 1;
	    ocorre:= 0;
	    while j <= tam1 do
		begin
		    if k[i]=v[j] then
			ocorre:= ocorre + 1;
		    j:= j + 1;
		end;
	writeln(k[i], ' ocorre ', ocorre, ' vezes');	
	end;
  end;

Begin
    read(n);
    ler_vetor(v, n);
    tamanho_k:= digitos_distintos(v, k, n);
    imprimir_distintos(k, tamanho_k);
    imprimir_ocorrencias(v, k, n, tamanho_k);
End.
