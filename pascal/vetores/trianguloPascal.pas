program pascal;
type vetor = array[1..20] of longint;
var v, w: vetor; n, m: longint;

procedure substituirvetor(var v, w: vetor; var tamv: longint; tamw: longint);
var i: longint;
begin
  for i:= 1 to tamw do
    v[i]:= w[i];
  tamv:= tamw;
end;

procedure novalinha(var v, w: vetor; tamv: longint; var tamw: longint);
var i: longint;
begin
  w[1]:= 1;
  for i:= 2 to tamv+1 do
    w[i]:= v[i-1] + v[i];
  tamw:= tamv+1;
end;

procedure imprimir(var v: vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    write(v[i],' ');
end;

procedure InicializarVetor(var v:vetor; var tam: longint);
var i: longint;
begin
  v[1]:= 1;
  n:= 1;
  for i:= 2 to 20 do
    v[i]:= 0;
end;

begin
  InicializarVetor(v, n);
  imprimir(v, n);
  writeln();
  while n <> 10 do
    begin
      novalinha(v, w, n, m);
      substituirvetor(v,w, n, m);
      imprimir(w, m);
      writeln();
    end;
end.
