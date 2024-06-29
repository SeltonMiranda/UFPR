program posicao;
type tipo_vetor = array[1..200] of longint;
var num, tam, posi: longint; v: tipo_vetor;

function AcharPosicao(var v: tipo_vetor; t, n: longint): longint;
var i: longint;
begin
  i:= 1;
  while (i <= t) and (v[i] <> num) do
      i:= i + 1;

  if i <= t then
    AcharPosicao:= i
  else
    AcharPosicao:= 0;
end;

function lerVetor(var v: tipo_vetor): longint;
var tamanho, n: longint;
begin
 tamanho:= 0;
 read(n);
 while n <> 0 do
   begin
     tamanho:= tamanho + 1;
     v[tamanho]:= n;
     read(n);
   end;
 lerVetor:= tamanho;
end;

begin
  tam:= lerVetor(v);
  read(num);
  while num <> 0 do
    begin
      posi:= AcharPosicao(v, tam, num);
      writeln(posi);
      read(num);
    end;
end.

