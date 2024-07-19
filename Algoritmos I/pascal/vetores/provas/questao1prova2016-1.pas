program questao;
CONST MAX = 20; CORINI = 1; CORFIM = 30;
type cores = CORINI..CORFIM;
     vetor = array[1..MAX] of cores;
var v, w: vetor; tam, cont, lugarCerto, lugarErrado: longint;

function TemRepetido(var v: vetor; tam: longint): boolean;
var i, j: longint;
begin
  TemRepetido:= false;
  for i:= 1 to tam do
    for j:=i + 1 to tam do
      if v[i] = v[j] then
	TemRepetido:= true;
end;

procedure LeVetor(var v:vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
      read(v[i]);
end;

function PosiIguais(var v, w:vetor; tam: longint): longint;
var cont, i, j: longint;
begin
  cont:= 0;
  for i:= 1 to tam do
    begin
      for j:= 1 to tam do
	if (v[j] = w[i]) and (j = i) then
	  cont:= cont + 1;
    end;
  PosiIguais:= cont;
end;

function PosiDiferentes(var v, w:vetor; tam: longint): longint;
var cont, i, j: longint;
begin
  cont:= 0;
  for i:= 1 to tam do
    begin
      for j:= 1 to tam do
	if (v[j] = w[i]) and (j <> i) then
	  cont:= cont + 1;
    end;
  PosiDiferentes:= cont;
end;

begin
  read(tam);
  LeVetor(v, tam);
  cont:= 0;
  repeat
    LeVetor(w, tam);

    while TemRepetido(w, tam) do
      begin
	writeln('entrada inválida');
	LeVetor(w, tam);
      end;

    lugarCerto:= PosiIguais(v, w, tam);
    lugarErrado:= PosiDiferentes(v, w, tam);
    cont:= cont + 1;
    writeln('cores no lugar certo: ', lugarCerto,', cores no lugar errado: ', lugarErrado);
  until lugarCerto = tam;

  writeln('foram lidos: ', cont,' vetores');

end.
