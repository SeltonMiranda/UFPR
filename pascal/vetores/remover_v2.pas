program remover_v2;
type vetor = array[1..200] of longint;
var n: longint; v: vetor;

procedure imprimir(var v:vetor; n: longint);
  var i: longint;
  begin
    for i:= 1 to n do
      write(v[i], ' ');
  end;

function busca(var v: vetor; n, p: longint): longint;
  var i: longint; achou: boolean;
  begin
    i:= 1;
    achou:= false;
    while (i <= n) and not achou do
      begin
	if v[i] = p then
	  achou:= true;
	i:= i + 1;
      end;
    busca:= i - 1;
  end;

procedure remove(var v: vetor; var n: longint);
  var p, posi, i: longint;
  begin
    read(p);
    posi:= busca(v, n, p);
    for i:= posi to n-1 do
      v[i]:= v[i+1];
    n:= n - 1;
  end;

procedure ordenar(var v:vetor; n: longint);
  var i, j, aux: longint;
  begin
    for i:= 1 to n do
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

procedure ler_vetor(var v: vetor; n: longint);
  var i: longint;
  begin
    for i:= 1 to n do
      read(v[i]);
  end;

Begin
  read(n);
  ler_vetor(v, n);
  ordenar(v, n);
  remove(v, n);
  imprimir(v, n);
  writeln();
End. 
