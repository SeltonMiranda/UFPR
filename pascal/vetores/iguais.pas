program seq;
type vetor = array[1..100] of longint;
var v, k:vetor; num: longint;

function saoiguais(var v, k:vetor; tam: longint): boolean;
var i:longint;
begin
  saoiguais:= true;
  for i:= 1 to tam do
    begin
      if v[i] <> k[i] then
	saoiguais:= false;
    end;
end;

procedure LerVetor(var m: vetor; t: longint);
var i: longint;
begin
  for i:= 1 to t do
    read(m[i]);
end;

begin
  read(num);
  LerVetor(v,num);
  LerVetor(k,num);
  if saoiguais(v, k, num) then
    writeln('sim')
  else
    writeln('nao');

end.
