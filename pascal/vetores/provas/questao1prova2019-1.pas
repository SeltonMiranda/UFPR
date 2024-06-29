program VerificarCPF;
type tipo_vetor = array[1..100] of int64; tipo_cpf = array[1..11] of longint;
var tam_v, tam_cpf, dv1, dv2: longint; v: tipo_vetor; vetorcpf: tipo_cpf;

procedure ImprimirCPF(var vet: tipo_cpf; tam: longint);
  var i: longint;
  begin
    for i:=1 to tam do
      write(vet[i]);
  end;

function Validar(var vetor: tipo_cpf; tam: longint): longint;
  var soma, j, i, resto: longint;
  begin
    soma:= 0;
    j:= 2;
    for i:=tam downto 1 do
      begin
	soma:= soma + vetor[i]*j;
	j:= j + 1;
      end;
    resto:= soma mod 11;
    if resto < 2 then
      Validar:= 0
    else
      Validar:= 11 - resto;
  end;

procedure reordenarCpf(var vetor: tipo_cpf; tam: longint);
  var i, temp, t: longint;
  begin
    t:= tam;
    for i:= 1 to (tam div 2) do
      begin
	temp:= vetor[i];
	vetor[i]:=vetor[t];
	vetor[t]:= temp;
	t:= t - 1;
      end;
  end;

function GerarCpf(x: int64; var vetor: tipo_cpf): longint;
  var i: longint;
  begin
    i:= 0;
    while x > 0 do
      begin
	i:= i + 1;
	vetor[i]:= x mod 10;
	x:= x div 10;
      end;
    GerarCpf:= i;  
  end;

procedure LerEntrada(var vetor:tipo_vetor; var tam: longint);
  var num: int64; i: longint;
  begin 
    read(num);
    i:= 0;
    while num <> 0 do
      begin
	i:= i + 1;
	vetor[i]:= num;
	read(num);
      end;
      tam:= i;
  end;   
  
begin
  LerEntrada(v, tam_v);
    while tam_v > 0 do
      begin
	tam_cpf:= GerarCpf(v[tam_v], vetorcpf);
	reordenarCpf(vetorcpf, tam_cpf);

	dv1:= Validar(vetorcpf, tam_cpf-2);
	dv2:= Validar(vetorcpf, tam_cpf-1);

	if (dv1 = vetorcpf[tam_cpf-1]) and (dv2 = vetorcpf[tam_cpf]) then
	  begin
	    ImprimirCPF(vetorcpf, tam_cpf);
	    write(' válido');
	  end
	else
	  begin
	    ImprimirCPF(vetorcpf, tam_cpf);
	    write(' inválido');
	  end;
	writeln();	

	tam_cpf:= 0;
	tam_v:= tam_v - 1;
      end;
end.
