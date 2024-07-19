program buscar;
type vetor = array[1..100] of longint;
var n, m, vezes_repetidas: longint; vetor_n, vetor_m: vetor;

function repeticoes(var v, k: vetor; tam_v, tam_k: longint): longint;
var cont, i, j: longint; achou: boolean;
begin
  cont:= 0;
  i:= 1;
  while i <= tam_v do
    begin
      achou:= true;
      j:= 1;
      while j <= tam_k do
	begin
	  if v[i + j -1] <> k[j] then
	    achou:= false;
	  j:= j + 1;
	end;
      if achou then
	cont:= cont + 1;
      i:= i + 1;
    end;
  repeticoes:= cont;  
end;

procedure LerVetor(var v: vetor; tam: longint);
var i: longint;
begin
  for i:=1 to tam do
    read(v[i]);
end;

Begin
  read(n);
  read(m);

  if (n = 0) or (m = 0) then
    writeln(0)
  else
    begin
      LerVetor(vetor_n, n);
      LerVetor(vetor_m, m);
      vezes_repetidas:= repeticoes(vetor_n, vetor_m, n, m);
      writeln(vezes_repetidas);
    end;


End.
