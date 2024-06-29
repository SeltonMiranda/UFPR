program cruz;
type matriz = array[1..100,1..100] of longint;
var n, m: longint; v: matriz;

procedure imprimir(var v: matriz; n, m: longint);
var i, j: longint;
begin
  for i:= 1 to n do
    begin
      for j:= 1 to m do
	write(v[i,j],' ');
      writeln();
    end;
end;

procedure verifica(var v: matriz; n, m: longint);
var i, j, c: longint;
begin
  c:= 0;
  for i:= 1 to n do
    begin
      for j:= 1 to m do
	begin
	  if (v[i,j]=0) then
	    begin
	      if (v[i+1,j]= 0) and (i < n) then 
		begin
		  if i = 1 then
		    begin
		      c:= c + 1;
		      v[i,j]:= c;
		    end
		  else if (v[i-1,j] = -1) then
		    begin
		      c:= c + 1;
		      v[i,j]:= c;
		    end
		  else if (v[i,j+1] = 0) and (j < m) then
		    begin
		      if j = 1 then
			begin
			  c:= c + 1;
			  v[i,j]:= c;
			end
		      else if v[i,j-1]= -1 then
			begin
			  c:= c+ 1;
			  v[i,j]:= c;
			end;
		    end;
		end
	      else if (v[i,j+1] = 0) and (j < m) then 
		begin
		  if j = 1 then
		    begin
		      c:= c + 1;
		      v[i,j]:= c;
		    end
		  else if v[i,j-1] = -1 then
		    begin
		      c:= c + 1;
		      v[i,j]:= c;
		    end;
		end;
    	    end;
	end;
    end;
end;


procedure lerMatriz(var v: matriz; n, m: longint);
var i, j: longint;
begin
  for i:= 1 to n do
    for j:= 1 to m do
      read(v[i,j]);
end;

begin
  read(n, m);
  lerMatriz(v, n, m);
  verifica(v, n, m);
  imprimir(v, n, m);
end.
