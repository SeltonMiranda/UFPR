program soma;
type tipo_vetor = array[1..100] of longint;
var
  n, SomaFinal: Integer;
  v: tipo_vetor;

function AcharValorMax(var vetor: tipo_vetor; tam:longint): longint;
  var i, SomaMax, SomaAtual: longint;
  begin
    SomaMax:= vetor[1];
    SomaAtual:= vetor[1];
    for i := 2 to n do
      begin
	if SomaAtual < 0 then
	  SomaAtual := vetor[i]
	else
	  SomaAtual := SomaAtual + vetor[i];

	if SomaAtual > SomaMax then
	  SomaMax := SomaAtual;
      end;
      AcharValorMax:= SomaMax;

  end;


procedure LerVetor(var vetor: tipo_vetor; tam:longint);
  var i: longint;
  begin
    for i := 1 to n do
      read(vetor[i]);
  end;
  
begin
  read(n);
  LerVetor(v, n);
  
  SomaFinal := AcharValorMax(v, n);
  
  Writeln(SomaFinal);
end.

