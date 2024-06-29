program lll;
type matriz = array[1..100,1..100] of integer;
var m: matriz; n: integer;

procedure imprimir(var m: matriz; n, p: integer);
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
var i, aux, aux2, aux3: integer;
begin
  for i:= 1 to n-1 do
    begin
      if m[i,2] = m[i+1,2] then
	begin
	  if m[i,1] > m[i+1,1] then
	    begin
	      aux:= m[i,1];
	      m[i,1]:= m[i+1,1];
	      m[i+1,1]:= aux;

	      aux2:= m[i,3];
	      m[i,3]:= m[i+1,3];
	      m[i+1,3]:= aux2;

	      aux3:= m[i,2];
	      m[i,2]:= m[i+1,2];
	      m[i+1,2]:= aux3;
	    end;
	end;
    end;
end;


procedure OrdenaMes(var m: matriz; n: integer);
var i, aux, aux2, aux3: integer;
begin
  for i:= 1 to n-1 do
    begin
      if m[i,3] = m[i+1,3] then
	begin
	  if m[i,2] > m[i+1,2] then
	    begin
	      aux:= m[i,2];
	      m[i,2]:= m[i+1,2];
	      m[i+1,2]:= aux;

	      aux2:= m[i,3];
	      m[i,3]:= m[i+1,3];
	      m[i+1,3]:= aux2;

	      aux3:= m[i,1];
	      m[i,1]:= m[i+1,1];
	      m[i+1,1]:= aux3;
	    end;
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

procedure ler_matriz(var m: matriz; n, p: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to p do
      read(m[i,j]);
end;

begin
  read(n);
  ler_matriz(m,n, 3);
  OrdenaAnos(m, n);
  OrdenaMes(m, n);
  OrdenaDias(m, n);
  writeln(); 
  imprimir(m, n, 3);
end.
