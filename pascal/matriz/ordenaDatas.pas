program lll;
type matriz = array[1..20000,1..3] of integer;
var m: matriz; n: integer;

procedure imprimir(var m: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to 3 do
	write(m[i,j],' ');
      writeln();
    end;
end;

procedure OrdenaDias(var m: matriz; n: integer);
var i, aux, j: integer;
begin
  for i:= n downto 2 do
    begin
      j:= i;
      while (m[j,2] = m[j-1,2]) and (m[j,3] = m[j-1,3]) do
	begin
	  if m[j,1] < m[j-1,1] then
	    begin
	      aux:= m[j-1,1];
	      m[j-1,1]:= m[j,1];
	      m[j,1]:= aux;
	    end;
	  j:= j - 1;
	end;
    end;
end;


procedure OrdenaMes(var m: matriz; n: integer);
var i, aux, aux2, j: integer;
begin
  for i:= n downto 2 do
    begin
      j:= i;
      while m[j,3] = m[j-1,3] do
	begin
	  if m[j,2] < m[j-1,2] then
	    begin
	      aux:= m[j-1,2];
	      m[j-1,2]:= m[j,2];
	      m[j,2]:= aux;
	      
	      aux2:= m[j-1,1];
	      m[j-1,1]:= m[j,1];
	      m[j,1]:= aux2;
	    end;
	  j:= j - 1;
	end;
    end;
end;


procedure OrdenaAnos(var m: matriz; n: integer);
var i, j, menor_pos, aux, aux2, aux3: integer;
begin
  for i:= 1 to n-1 do
    begin
      menor_pos:= i;
      for j:=i+1 to n do
	if m[j,3] < m[menor_pos,3] then
	  menor_pos:= j;

      aux:= m[menor_pos, 3];
      m[menor_pos, 3]:= m[i,3];
      m[i,3]:= aux;

      aux2:= m[menor_pos, 2];
      m[menor_pos,2]:= m[i,2];
      m[i,2]:= aux2;

      aux3:= m[menor_pos, 1];
      m[menor_pos,1]:= m[i,1];
      m[i,1]:= aux3;
    end;
end;

procedure ler_matriz(var m: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to 3 do
      read(m[i,j]);
end;

begin
  read(n);
  ler_matriz(m,n);
  OrdenaAnos(m, n);
  OrdenaMes(m, n);
  OrdenaDias(m, n);
  writeln(); 
  imprimir(m, n);
end.
