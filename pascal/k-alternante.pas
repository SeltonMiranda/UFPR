program k_alternante;
var
    n, val_pares, val_impares, maior_p, maior_i: longint;
begin
    read(n);
    val_pares:= 0;
    val_impares:= 0;
    maior_p:= 0;
    maior_i:= 0;

    while n <> 0 do
      begin
	  if n mod 2 = 0 then
	    begin  
	    val_impares:= 0;
	    val_pares:= val_pares + 1;
	    if val_pares > maior_p then
		maior_p:= val_pares;
	    end
	  else
	      begin
	      val_pares:= 0;
	      val_impares:= val_impares + 1;
	      if val_impares > maior_i then
		maior_i:= val_impares;
	      end;
	  read(n);  
      end;

    if (maior_p <> 0) and (maior_i = 0) then
	writeln('SIM, a sequencia é ', maior_p,'-alternante')
    else if (maior_p = 0) and (maior_i <> 0) then
	    writeln('SIM, a sequencia é ', maior_i,'-alternante')
	 else if maior_p = maior_i then
	      	writeln('SIM, a sequencia é ', maior_p,'-alternante')
	      else
		  writeln('NAO, a sequencia nao é alternante');

end.
