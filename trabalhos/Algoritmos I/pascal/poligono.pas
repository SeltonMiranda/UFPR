program poligono;
var
   n_atual, n_anterior, cont: longint;
   ehregular: boolean;
begin
    read(n_anterior, n_atual);

    cont:= 1;
    ehregular:= true;

    while (n_atual<> 0) and ehregular do
	begin
	    if n_atual <> n_anterior then
		ehregular:= false
	      else
		  begin
		      cont:= cont + 1;
		      n_anterior:= n_atual;
		      read(n_atual);
		  end;
	end;

    if (cont >= 3) and ehregular then
	writeln('SIM')
      else 
	writeln('NAO');
end.
