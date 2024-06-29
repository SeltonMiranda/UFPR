program escolha_um_nome_bom;

const MAX = 100;

type vetor = array [1..MAX] of longint;

var
    v : vetor;
    n, pos, tamanho_subsequencia: longint;

procedure ler_vetor (var v: vetor; n: longint);
var i: longint;
begin
  for i:= 1 to n do
    read(v[i]);
end;

function tem_subsequencia_iguais (var v: vetor; n, tam_seg: longint): longint;
var k, j, i, primeira_repeticao: longint;
begin
  primeira_repeticao:= 0;
  tem_subsequencia_iguais:= 0;
  for i:= 1 to n do
    begin
      for j:= i + 1 to n do
	begin
	  if v[j] = v[i] then
	    begin
	      k:= 1;
	      while (v[i+k] = v[j+k]) and (i+k < j) do
		k:= k + 1;
	    end;
	  if (k = tam_seg) and (primeira_repeticao = 0) then
	    begin
	      tem_subsequencia_iguais:= i;
	      primeira_repeticao:= primeira_repeticao + 1;
	    end;
	end;
      
    end;
end;

(* programa principal *)
begin
    read (n);  
      
    // tamanho da subsequencia a ser lido
    ler_vetor (v,n); 
    pos:= 0;
    tamanho_subsequencia:= n div 2; // inicia com maior valor possivel
    while (pos = 0) and (tamanho_subsequencia >= 2) do
    begin
         pos:= tem_subsequencia_iguais (v,n,tamanho_subsequencia);
         tamanho_subsequencia:= tamanho_subsequencia - 1;
    end;
    if pos > 0 then
        writeln (pos,' ',tamanho_subsequencia+1)
    else
        writeln ('nenhuma');
end.

