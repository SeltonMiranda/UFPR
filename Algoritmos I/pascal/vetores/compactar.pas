program compactacao;
type vetor = array[1..100] of longint;
var SequenciaOriginal, SequenciaCompactada: vetor; n, tamanho_sem_repeticao: longint;


function EstaNoVetor(var k: vetor; x, tam_compactado: longint): boolean;
var i: longint;
begin
  EstaNoVetor:= false;
  for i:=1 to tam_compactado do
    begin
      if k[i] = x then
	EstaNoVetor:= true
    end;
end;

function NovoVetor(var v, k: vetor; tam: longint): longint;
var i, tam_compactado: longint; 
begin
  tam_compactado:=0;
  for i:= 1 to tam do
    begin
      if not EstaNoVetor(k, v[i], tam_compactado) then
	begin
	  tam_compactado:= tam_compactado + 1;
	  k[tam_compactado]:= v[i];
	end;
    end;
  NovoVetor:= tam_compactado;
end;

procedure ImprimirVetor(var v: vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    write(v[i],' ');
end;

procedure LerVetor(var v: vetor; tam: longint);
var i: longint;
begin
  for i:= 1 to tam do
    read(v[i]);
end;

begin
  read(n);
  while n <> 0 do
    begin
      LerVetor(SequenciaOriginal, n);
      write('O: ');
      ImprimirVetor(SequenciaOriginal, n);
      tamanho_sem_repeticao:= NovoVetor(SequenciaOriginal, SequenciaCompactada, n);
      
      writeln();

      write('C: ');
      ImprimirVetor(SequenciaCompactada, tamanho_sem_repeticao);
      
      writeln();
      
      read(n);
      tamanho_sem_repeticao:=0;
    end;
end.
