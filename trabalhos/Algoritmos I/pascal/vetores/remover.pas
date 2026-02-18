program remover;
type vetor = array[1..200] of longint;
var n: longint; v: vetor;

procedure imprimir(var v: vetor; n: longint);
  var i: longint;
  begin
    for i:= 1 to n do
      write(v[i],' ');
  end;

function busca(var v: vetor; n, p: longint): longint;
var inicio, fim, meio: longint;
begin
  inicio:= 1;
  fim:= n;
  meio:= (inicio+fim) div 2;
  
  while (p <> v[meio]) and (fim >= inicio) do
    begin
      if p > v[meio] then
	inicio:= meio + 1
      else
	fim:= meio - 1;

      meio:= (inicio+fim) div 2;
    end;

  if fim < inicio then
    busca:= 0
  else
    busca:= meio;
end;

procedure remove(var v: vetor; var n: longint);
  var posi, i, p: longint;
  begin
    read(p);
    posi:= busca(v, n, p);
    for i:= posi to n-1 do
      v[i]:= v[i+1];
    n:= n - 1;
  end;

procedure OrdenaVetor(var v:vetor; tam: longint);
var i, j, pos_menor, aux: longint;
begin
  for i:= 1 to tam-1 do
    begin
      pos_menor:= i;
      for j:= i+1 to tam do
	if v[j] < v[pos_menor] then
	  pos_menor:= j;

      aux:= v[pos_menor];
      v[pos_menor]:= v[i];
      v[i]:= aux;
    end;
end;

procedure ler_vetor(var v: vetor; n: longint);
  var i: longint;
  begin
      for i:= 1 to n do
	read(v[i]);
  end;

Begin
  read(n);
  ler_vetor(v, n);
  OrdenaVetor(v, n);
  remove(v, n);
  imprimir(v, n);
  writeln();
End.
