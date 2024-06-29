program p3;
type matriz = array[1..100,1..100] of integer;
var n, i, j, tam: integer; m: matriz;

procedure imprimir_matriz(var m: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to n do
	write(m[i,j],' ');
      writeln();
    end;
end;

procedure remover_cor(var m: matriz; n, num: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      if num = m[i,j] then
	m[i,j]:= 0;
end;

function achar_borda_quadrada(var m: matriz; n, linIni, colIni, tam: integer): boolean;
var i, j: integer;
begin
  achar_borda_quadrada:= true;

  for i:= linIni to linIni+tam-1 do
    if m[i,colIni] <> m[linIni, colIni] then
      achar_borda_quadrada:= false;

  for i:= linIni to linIni+tam-1 do
    if m[i,colIni+tam-1] <> m[linIni, colIni] then
      achar_borda_quadrada:= false;

  for j:= colIni to colIni+tam-1 do
    if m[linIni,j] <> m[linIni, colIni] then
      achar_borda_quadrada:= false;

  for j:=colIni to colIni+tam-1 do
    if m[linIni+tam-1,j] <> m[linIni,colIni] then
      achar_borda_quadrada:= false;
end;

procedure ler_matriz(var m: matriz; n: integer);
var i,j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

begin
  read(n);
  ler_matriz(m, n);
  
  for tam:= 2 to n do
    for i:= 1 to n do
      for j:= 1 to n do
	if achar_borda_quadrada(m, n, i, j, tam) then
	  if (i = 1) and (j = 1) then
	    remover_cor(m, n, m[i,j])
	  else if tam = 3 then
	    remover_cor(m, n, m[i+1,j+1]);

  writeln();
  imprimir_matriz(m, n);

end.
