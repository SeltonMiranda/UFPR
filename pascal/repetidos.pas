program repete;
type tipo_vetor = array[1..200] of longint;
var k, v: tipo_vetor; n, i, tam_novovetor: longint;

procedure mostrarocorrencias(var v1, v2: tipo_vetor; tamv2, x: longint);
var cont, i: longint;
begin
  cont:= 0;
  for i:= 1 to tamv2 do
    begin
	  if v1[x] = v2[i] then
	    cont:= cont + 1;
    end;

  if cont > 1 then
    writeln(v1[x],' ocorre ', cont,' vezes')
  else
    writeln(v1[x],' ocorre ', cont,' vez');
end;
  
function estanovetor(var k: tipo_vetor; tam, x: longint): boolean;
var i: longint;
begin
  estanovetor:= false;
  for i:= 1 to tam do
    begin
      if x = v[i] then
	estanovetor:= true;
    end;
end;

function criarvetor(var v, k: tipo_vetor; tam_v: longint): longint;
var i, tam_k: longint;
begin
  tam_k:= 0;
  for i:= 1 to tam_v do
    begin
      if not estanovetor(k, tam_k, v[i]) then
	begin
	  tam_k:= tam_k + 1;
	  k[tam_k]:= v[i];
	end;
    end;
  criarvetor:= tam_k;
end;

procedure lervetor(var v: tipo_vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    read(v[i]);
end;

begin
  read(n);
  lervetor(v, n);
  tam_novovetor:= criarvetor(v, k, n);

  writeln('a sequencia tem ', tam_novovetor,' numeros distintos:');
  for i:= 1 to tam_novovetor do
    write(k[i],' ');
  writeln();
  for i:= 1 to tam_novovetor do
      mostrarocorrencias(k, v, n, i);
  writeln();
end.
