program vetores4;

CONST MIN=1; MAX=200;

type
    vetor = array[MIN..MAX] of longint;
var
  v, k: vetor;
  i, o, n, tamanho_k: longint;

procedure ler_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
      for i:= 1 to tam do
	  read(v[i]);
  end;

function tamanho_vetor(var v, k: vetor; tam_v: longint): longint;
  var
      tam_k, i, j: longint;
  begin
    tam_k:= 0;
    for i:= 1 to tam_v do
      begin
	  j:= 1;
	  while (j <= tam_k) and (v[i] <> k[j]) do
	      j:= j + 1;

	  if j > tam_k then
	      begin
		  tam_k:= tam_k + 1;
		  k[tam_k]:= v[i];
	      end;
      end;
      tamanho_vetor:= tam_k;  
  end;

procedure imprimir_distintos(var k: vetor; tamanho_k: longint);
  var i: longint;
  begin
    write('A sequencia tem ', tamanho_k,' numeros distintos: ');
    for i:= 1 to tamanho_k do
      write(k[i],' ');
    writeln();
  end;

function ocorrencias(tam1: longint; p: longint): longint;
  var 
     j, ocorre: longint;
  begin
	    j:= 1;
	    ocorre:= 0;
	    while j <= tam1 do
		begin
		    if k[p]=v[j] then
			ocorre:= ocorre + 1;
		    j:= j + 1;
		end;
	    ocorrencias:= ocorre;	
  end;

Begin
    read(n);
    ler_vetor(v, n);
    tamanho_k:= tamanho_vetor(v, k, n);
    imprimir_distintos(k, tamanho_k);

    for i:= 1 to tamanho_k do
      begin
	o:= ocorrencias(n, i);
	if o > 1 then
	    writeln(k[i], ' ocorre ', o, ' vezes')
	  else
	      writeln(k[i], ' ocorre ', o, ' vez');
      end;
End.
