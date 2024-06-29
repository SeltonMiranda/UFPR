program quest;
type matriz = array[1..10,1..10] of integer;
var m, k, r: matriz; tam_r, n: integer;

procedure ler_matriz(var m: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

procedure ordena(var m: matriz; n: integer);
var i, j, menor, k, z, q, w, aux: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to n do
	begin
	  menor:= m[i,j];
	  z:= i;
	  q:= j;
	  w:= j;
	  for k:= i to n do
	    begin
	      while w <= n do
		begin
		  if m[k,w] < menor then
		    begin
		      menor:= m[k,w];
		      z:= k;
		      q:= w;
		    end;
		  w:= w + 1;
		end;
	      w:= 1;
	    end;

	  aux:= m[i,j];
	  m[i,j]:= m[z,q];
	  m[z,q]:= aux;
	end;
    end;
end;

procedure merge (var m, k, r: matriz; n: integer; var tam: integer);
var c, l, i, j, linha_m, linha_k, coluna_m, coluna_k, cont_m, cont_k: integer;
begin
  linha_m:= 1;
  linha_k:= 1;
  coluna_m:= 1;
  coluna_k:= 1;
  cont_m:= 1;
  cont_k:= 1;
  i:= 1;
  j:= 1;
  while (cont_m <= n*n) and (cont_k <= n*n) do
    begin
      if m[linha_m, coluna_m] <= k[linha_k, coluna_k] then
	begin
	  r[i,j]:= m[linha_m, coluna_m];
	  coluna_m:= coluna_m + 1;
	  cont_m:= cont_m + 1;
	  if coluna_m > n then
	    begin
	      coluna_m:= 1;
	      linha_m:= linha_m + 1;
	    end;
	end
      else
	begin
	  r[i,j]:= k[linha_k, coluna_k];
	  coluna_k:= coluna_k + 1;
	  cont_k:= cont_k + 1;
	  if coluna_k > n then
	    begin
	      coluna_k:= 1;
	      linha_k:= linha_k + 1;
	    end;
	end;
      j:= j + 1;
      if j > 2*n then
	begin
	  j:= 1;
	  i:= i + 1;
	end;
    end;
  for l:= linha_m to n do
    begin
      for c:= coluna_m to n do
	begin
	  r[i,j]:= m[l, c];
	  j:= j + 1;
	  if j > 2*n then
	    begin
	      j:= 1;
	      i:= i + 1;
	    end;
	end;
    end;
  for l:= linha_k to n do
    begin
      for c:= coluna_k to n do
	begin
	  r[i,j]:= k[l,c];
	  j:= j + 1;
	  if j > 2*n then
	    begin
	      j:= 1;
	      i:= i + 1;
	    end;
	end;
    end;
  tam:= 2*n;
end;

procedure imprime(var m: matriz; n: integer);
var i,j : integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to n do
	write(m[i,j],'  ');
      writeln();
    end;
end;

procedure imprime_resultado(var m: matriz; n, p: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to p do
	write(m[i,j],'  ');
      writeln();
    end;
end;

begin
  read(n);
  ler_matriz(m, n);
  ler_matriz(k, n);
  ordena(m, n);
  ordena(k, n);
  merge(m, k, r, n, tam_r);
  imprime(m, n);
  writeln();
  imprime(k, n);
  writeln();
  imprime_resultado(r, n, tam_r);
end.
