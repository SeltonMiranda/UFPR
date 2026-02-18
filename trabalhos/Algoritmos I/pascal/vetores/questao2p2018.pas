program questao2;
type vetor = array[1..200] of longint;
var v: vetor; n:longint;

procedure Imprimir(var v:vetor; tam: longint);
  var i: longint;
  begin
    for i:=1 to tam do
      write(v[i], ' ');
    writeln();
  end;

procedure Reorganizar(var v:vetor; tam: longint);
  var  i, j, aux, k: longint;
  begin
    for i:= tam downto 2 do
      begin
	j:= i - 1;
	while (j >= 1) and (v[j]<>v[i]) do
	  j:= j - 1;

	if j >= 1 then
	  begin
	    if i <> tam then
	      begin 
		aux:= v[i];
		for k:= i to tam-1 do
		  v[k]:= v[k+1];
		v[tam]:= aux;
	      end;	      
	  end;	
      end;
  end;

procedure LerVetor(var v:vetor; tam: longint);
 var i: longint;
 begin
   for i:= 1 to tam do
     read(v[i]);
 end;

begin
  read(n);
  LerVetor(v, n);
  Reorganizar(v, n);
  Imprimir(v, n);
end.
