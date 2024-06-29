program questao2;
type vetor = array[1..200] of longint;
var n, m, k: longint; v, w: vetor;

procedure ImprimirVetor(var v: vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    write(v[i],' ');
end;

procedure CopiaVetorW(var v, w: vetor; m, k: longint);
var i: longint;
begin
  i:= 1;
  while i <= m do
    begin
      v[k]:= w[i];
      k:= k + 1;
      i:= i +1;
    end;
end;

procedure AbreEspaco(var v: vetor; var tamv: longint; tamw, k: longint);
var o, t, j, p: longint;
begin
    p:= tamv;
    o:= tamw;
    t:= p + o;
    while p >= k do
      begin
	v[t]:= v[p]; 
	t:= t - 1;
	p:= p - 1;
      end;
    tamv:= tamv + tamw;
end;

procedure LerVetor(var v: vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    read(v[i]);
end;

begin
  read(n, m);
  LerVetor(v, n);
  LerVetor(w, m);
  read(k);

  AbreEspaco(v, n, m, k);
  CopiaVetorW(v, w, m, k);

  ImprimirVetor(v, n);
end.
