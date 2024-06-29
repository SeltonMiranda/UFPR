program busca;
type vetor = array[1..200] of longint;
var v: vetor; tam: longint;

function AcharMenorPos(var v:vetor; m: longint): longint;
  var i: longint;
  begin
    i:= 1;
    while (v[i] <> v[m]) do
      i:= i + 1;
    AcharMenorPos:= i;
  end;

function BuscaBinaria(var v:vetor; tam, x: longint): longint;
  var ini, fim, meio: longint;
  begin
    ini:= 1;
    fim:= tam;
    meio:= (fim + ini) div 2;
    while (fim >= ini) and (v[meio] <> x) do
      begin
	if v[meio] > x then
	  fim:= meio - 1
	else
	  ini:= meio + 1;
	meio:= (fim + ini) div 2;
      end;
    if ini <= fim then
      	BuscaBinaria:= AcharMenorPos(v, meio)
    else
      BuscaBinaria:= 0;
  end;

procedure AcharPos(var v:vetor; t: longint);
  var x, busca:longint;
  begin
    read(x);
    busca:= BuscaBinaria(v, t, x);
    if busca = 0 then
      writeln('nao esta presente')
    else
      writeln(busca);
  end;

procedure OrdenarVetor(var v: vetor; t: longint);
  var aux, i, j: longint;
  begin
    for i:= 1 to t do
      begin
	aux:= v[i];
	j:= i - 1;
	while (j >= 1) and (v[j] > aux) do
	  begin
	    v[j+1]:= v[j];
	    j:= j - 1;
	  end;
	v[j+1]:= aux;  
      end;
  end;

function GerarVetor(var tam: longint): vetor;
  var num: longint; k: vetor;
  begin
    tam:= 0;
    read(num);
    while num <> 0 do
      begin
	tam:= tam + 1;
	k[tam]:= num;
	read(num);
      end;
    GerarVetor:= k;
  end;

procedure InicializarVetor(var v:vetor);
  var i: longint;
  begin
    for i:= 1 to 200 do
      v[i]:= 0;
  end;

Begin
  InicializarVetor(v);
  v:= GerarVetor(tam);
  OrdenarVetor(v, tam);
  AcharPos(v, tam);
End.
