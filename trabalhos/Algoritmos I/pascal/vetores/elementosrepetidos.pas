program repetidos;
type tipo_vetor = array[1..10] of longint;
var v, k: tipo_vetor;
    tam_k, i: longint;

function VerificarRepetido(var v2: tipo_vetor; t, x: longint): boolean;
  var i: longint;
  begin
    i:= 1;
    while (v2[i] <> x) and (i <= t) do
	i:= i + 1;
    if i > t then
      VerificarRepetido:= true
    else
      VerificarRepetido:= false;
  end;
    
function AcharRepetidos(var Vetor1, Vetor2: tipo_vetor): longint;
  var i, j, tam: longint; achou: boolean;
  begin
    tam:= 0;
    for i:= 1 to 9 do
      begin
	achou:= false;
	j:= i + 1;
	while (j <= 10) and not achou do
	  begin
	    if v[i] = v[j] then
	      achou:= true;
	    j:= j + 1;
	  end;

	if achou then
	  begin
	    if VerificarRepetido(vetor2, tam, v[i]) then
	      begin
		tam:= tam + 1;
		k[tam]:= v[i];
	      end;
	  end;	  
      end;
  AcharRepetidos:= tam;
  end;

procedure LerVetor(var v: tipo_vetor);
  var i: longint;
  begin
    for i:= 1 to 10 do
      read(v[i]);
  end;

begin
  LerVetor(v);
  tam_k:= AcharRepetidos(v, k);
  for i:= 1 to tam_k do
    write(k[i],' ');
  writeln();
end.
