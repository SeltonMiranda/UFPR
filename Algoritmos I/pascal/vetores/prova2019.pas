program prova;
type tipo_vetor = array[1..100] of longint; tipo_cpf = array[1..11] of longint;
var dv1, dv2, n, tam: longint; v: tipo_vetor; k: tipo_cpf;

procedure ImprimirCpf(var vetor: tipo_cpf; tam: longint);
  var i: longint;
  begin
    for i:= 1 to tam do
      write(vetor[i]);
  end;

Function VerificarDigito(var vetor: tipo_cpf; x: longint): longint;  
  var s, j, i, resto: longint;
  begin 
    s:= 0;
    i:= 1;
    j:= 10;
    while i <= x do
      begin
	s:= s + vetor[1]*j;
	i:= i + 1;
	j:= j - 1;
      end;
    resto:= s mod 11;
    if resto >= 2 then
      VerificarDigito:= 11 - resto
    else
      VerificarDigito:= 0;
  end;

function GerarCpf(var vetor1: tipo_cpf;var vetor2: tipo_vetor;var x: longint): longint;
  var t: longint;
  begin
    t:= 1;
    vetor1[t]:= vetor2[x];
    while t < 11 do
      begin
	x:= x - 1;
	t:= t + 1;
	vetor1[t]:= vetor2[x];
      end;
    GerarCpf:= t; 
  end;

procedure LerVetor(var vetor: tipo_vetor;var t: longint);
  var num: longint;
  begin
    read(num);
    t:= 1;
    while num <> 0 do
      begin
	vetor[t]:= num;
	t:= t + 1;
      end;
    t:= t - 1;  
  end;

begin
  LerVetor(v, n);
  while n > 0 do
    begin
      tam:= GerarCpf(k, v, n);
      
      dv1:= VerificarDigito(k, tam-2);
      dv2:= VerificarDigito(k, tam-1);

      if (dv1=k[tam-1]) and (dv2=k[tam]) then
	begin
	  ImprimirCpf(k, tam);
	  write(' válido');
	end
      else
	  begin
	    ImprimirCpf(k, tam);
	    write(' inválido');
	  end;
    n:= n - 1;
    end;

end.
