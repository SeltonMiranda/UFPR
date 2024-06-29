program questao3;
var
    n_anterior, n_atual, planalto: longint;
begin
    read(n_anterior, n_atual);
    planalto:= 0;

    while n_atual <> 0 do
	begin
	    if (n_atual = n_anterior) then
		begin
		  planalto:= planalto + 1;
		  while n_atual = n_anterior do
		      begin
			  n_anterior:= n_atual;
			  read(n_atual);
		      end;
		end
	    else
		begin
		    n_anterior:= n_atual;
		    read(n_atual);
		end;
	end;

    writeln(planalto);	
end.
