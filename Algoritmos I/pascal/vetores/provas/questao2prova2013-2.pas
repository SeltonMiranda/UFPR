program questao2;
type vetor=array[1..200] of longint;
var tamv, tamw, k: longint; v, w: vetor;

procedure imprimir(var v:vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    write(v[i],' ');
end;

procedure copiavetor(var v,w:vetor; tamw, k:longint);
var i, j: longint;
begin
  i:= k;
  j:= 1;
  while i < k+tamw do
    begin
      v[i]:= w[j];
      i:= i +1;
      j:= j +1;
    end;
end;

procedure abreespaco(var v:vetor; var tamv: longint; tamw, k: longint);
var t,n: longint;
begin
  t:= tamv+tamw;
  n:= tamv;
  while k <= tamv do
    begin
      v[t]:= v[n];
      t:= t-1;
      n:= n -1;
      k:= k + 1;
    end;
  tamv:= tamv+tamw;
end;


procedure levetor(var v:vetor; tam: longint);
var i: longint;
begin
  for i:=1 to tam do
    read(v[i]);
end;

begin
  read(tamv, tamw);
  if tamv+tamw > 200 then
    writeln('nao ha espaco no vetor v')
  else
    begin
      levetor(v, tamv);
      levetor(w, tamw);
      read(k);
      abreespaco(v, tamv, tamw, k);
      copiavetor(v, w, tamw, k);
      imprimir(v, tamv);
    end;
end.
