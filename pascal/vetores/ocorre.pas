program occur;
type tipo_vetor = array[1..200] of longint;
var v, k: tipo_vetor; i, n, oc, tam_k: longint;

function ocorrencias(var v: tipo_vetor; x, tam: longint): longint;
  var i, cont: longint;
  begin
    cont:= 0;
    for i:= 1 to tam do
      begin
	if x = v[i] then
	  cont:= cont + 1;
      end;
    ocorrencias:= cont;
  end;

function VetorDigitos(var v, k: tipo_vetor; tam: longint): longint; (*Constrói um vetor de digitos diferentes *)
  var i, j, tam2: longint; repetido: boolean;
  begin
    tam2:= 0;
    for i:= 1 to tam do
      begin
	repetido:= false;
	j:= 1;
	while (j < i) and not repetido do
	  begin
	    if v[i] = k[j] then
	      repetido:= true;
	    j:= j + 1;
	  end;
	if (j > tam2) and not repetido then
	  begin
	    tam2:= tam2 + 1;
	    k[tam2]:= v[i];
	  end;
      end;
  VetorDigitos:= tam2;
  end;

procedure LerVetor(var v: tipo_vetor; tam: longint);
  var i: longint;
  begin
    for i:= 1 to tam do
      read(v[i]);
  end;

begin
  read(n);
  LerVetor(v, n);
  tam_k:= VetorDigitos(v, k, n);
  for i:= 1 to tam_k do
    begin
      oc:= ocorrencias(v, k[i], n);
      if oc = 1 then
	writeln(k[i], ' ocorre ', oc,' vez')
      else
	writeln(k[i], ' ocorre ', oc,' vezes');
    end;
end.
