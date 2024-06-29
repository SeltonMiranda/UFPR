Program vetores001;
CONST MIN = 0;
      MAX = 200;
type
    vetor = array[MIN..MAX] of real;
var
  divisao, soma_positivos, soma_negativos: real;
  n: longint;
  v: vetor;

procedure ler_tamanho(var tam: longint);
  begin
      repeat
	  read(tam);
      until (tam >= 0) and (tam <= 200);
  end;

procedure ler_vetor(var v: vetor; tam: longint);
  var i: longint;
  begin
      for i:= 1 to tam do
	  read(v[i]);
  end;



  if soma_negativos = 0 then
      writeln('divisao por zero')
  else if n = 0 then
	  writeln('vetor vazio')
       else 
	  writeln(divisao:0:2);
  

function soma_par(var v: vetor; tam: longint): real;
  var i: longint;
      s: real;
  begin
      s:= 0;
      for i:= 1 to tam do
	  if (i mod 2 = 0) and (v[i] > 0) then
	      s:= s + v[i];

      soma_par:= s;	  
  end;

function soma_impar(var v: vetor; tam: longint): real;
  var i: longint;
      s: real;
  begin
      s:= 0;
      for i:= 1 to tam do
	  if (i mod 2 <> 0) and (v[i] < 0) then
	      s:= s + v[i];

      soma_impar:= s;	  
  end;

begin
  ler_tamanho(n);
  if n <> 0 then
    begin
	ler_vetor(v, n);
	soma_positivos:= soma_par(v, n);
	soma_negativos:= soma_impar(v, n);
	  if soma_negativos <> 0 then
	    begin
	      divisao:= soma_positivos/soma_negativos;
	      writeln(divisao:1:2);
	    end
	  else
	      writeln('divisao por zero');
    end
  else
      writeln('vetor vazio');

end.

