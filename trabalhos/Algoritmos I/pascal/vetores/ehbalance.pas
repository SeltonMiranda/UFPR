program balanceado;
type tipo_vetor = array[1..200] of longint;
var v: tipo_vetor; tam: longint;

function EhBalanceado(var vetor: tipo_vetor; n: longint): boolean;
  var i, j: longint;
  begin 
    EhBalanceado:= true;
    i:= 1;
    j:= n;
    while i <= n div 2 do
      begin
	if v[i] + v[j] <> v[i+1] + v[j-1] then
	  EhBalanceado:= false;
	i:= i + 1;
	j:= j - 1;
      end;
  end;

procedure OrdenarVetor(var vetor:tipo_vetor; n: longint);
  var i, j, PosMenor, aux: longint;
  begin
    for i:= 1 to n - 1 do
      begin
	PosMenor:= i;
	for j:= i + 1 to n do
	  if v[j] < v[PosMenor] then
	    PosMenor:= j;

	aux:=v[PosMenor];
	v[PosMenor]:= v[i];
	v[i]:= aux;
      end;
  end;

function GerarVetor(var vetor:tipo_vetor): longint;
  var i, n: longint;
  begin
    read(n);
    i:= 1;

    while n <> 0 do
      begin
	v[i]:= n;
	i:= i + 1;
	read(n);
      end;
    GerarVetor:= i-1;  
  end;
  
begin
  tam:= GerarVetor(v);
  OrdenarVetor(v, tam);

  if EhBalanceado(v, tam) then
    writeln('Sim, eh balanceado')
  else
    writeln('Nao eh balanceado');
end.
