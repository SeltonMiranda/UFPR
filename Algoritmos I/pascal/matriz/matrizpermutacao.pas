program permuta;
type matriz = array[1..100,1..100] of longint;
var v: matriz; n: longint;

function VerificaLinhas(var v: matriz; n: longint): boolean;
var i, j, cont: longint;
begin
  VerificaLinhas:= true;
  for i:= 1 to n do
    begin
      cont:= 0;
      for j:= 1 to n do
	begin
	  if (v[i,j]<>1) and (v[i,j]<> 0) then
	    VerificaLinhas:= false
	  else if (v[i,j] = 1) then
	    cont:= cont + 1;
	end;
      if cont > 1 then
	VerificaLinhas:= false;
    end;

  end;

function VerificaColunas(var v: matriz; n: longint): boolean;
var i, j, cont: longint;
begin
  VerificaColunas:= true;
  for j:= 1 to n do
    begin
      cont:= 0;
      for i:= 1 to n do
	begin
	  if (v[i,j]<>1) and (v[i,j]<>0) then
	    VerificaColunas:= false
	  else if v[i,j]=1 then
	    cont:= cont + 1;
	end;
      if cont > 1 then
	VerificaColunas:= false;
    end;
end;

procedure LerMatriz(var v: matriz; n: longint);
var i, j: longint;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(v[i,j]);
end;

begin
  read(n);
  LerMatriz(v, n);
  if VerificaLinhas(v, n) and VerificaColunas(v, n) then
    writeln('sim')
  else
    writeln('nao');
end.
