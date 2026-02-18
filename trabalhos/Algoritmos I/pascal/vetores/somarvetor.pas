program somar;
type vetor = array[1..200] of longint;
var v, w: vetor; tam_v, tam_w, k: longint;

procedure ImprimirVetor(var v: vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    write(v[i], ' ');
end;

function NovoVetor(var v, w: vetor; tamv, k: longint): longint;
var tamw, i, soma: longint;
begin
  soma:= 0; tamw:= 0;
  for i:= 1 to tamv do
    begin
      soma:= soma + v[i];
      if soma > k then
	begin
	  tamw:= tamw + 1;
	  w[tamw]:= v[i];
	  soma:= 0;
	end;
    end;

  NovoVetor:= tamw;
end;

procedure LerVetor(var v: vetor; var tamv: longint);
var i, n: longint;
begin
  i:= 0;
  read(n);
  while n <> 0 do
    begin
      i:= i +1;
      v[i]:= n;
      read(n);
    end;
  tamv:= i;
end;

begin
  lerVetor(v, tam_v);
  read(k);
  tam_w:= NovoVetor(v, w, tam_v, k);
  ImprimirVetor(w, tam_w);
end.
