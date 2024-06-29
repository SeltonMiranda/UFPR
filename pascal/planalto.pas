program questao3;
var
    n_anterior, n_atual, planalto: longint;
    dentro_do_planalto: boolean;
begin
    read(n_anterior, n_atual);
    planalto:= 0;
    dentro_do_planalto:= false;

    while n_atual <> 0 do
	begin
	    if (n_atual = n_anterior) and (not dentro) then
		begin
		  planalto:= planalto + 1;
		  dentro_do_planalto:= true;
		  n_anterior:= n_atual;
		  read(n_atual);
		end
	    else
		begin
		    if n_anterior <> n_atual then
		      dentro_do_planalto:= false;

		    n_anterior:= n_atual;
		    read(n_atual);
		end;
	end;

    writeln(planalto);	
end.
