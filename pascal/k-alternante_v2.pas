program k_alternante;
var
    n, seq_par, seq_impar, maiorseq:  longint;
    eh_alternante: boolean;
begin
    read(n);
    seq_par:= 0;
    seq_impar:= 0;
    maiorseq:= 0;
    eh_alternante:= true;


    while n <> 0 do
      begin
	  if n mod 2 = 0 then
	    begin  
	      seq_impar:= 0;
	      seq_par:= seq_par + 1;
	      if seq_par > maiorseq then
		begin
		  maiorseq:= seq_par;
		  eh_alternante:= true;
		end
	      else
		  eh_alternante:= false;
	    end
	  else
	      begin
		  seq_par:= 0;
		  seq_impar:= seq_impar + 1;
		  if seq_impar > maiorseq then
		      begin
		      maiorseq:= seq_impar;
		      eh_alternante:= true;
		      end
		  else
		      eh_alternante:= false;
	      end;
	  read(n);  
      end;
      if eh_alternante then
	  writeln('SIM, é ', maiorseq,'-alternante')
      else
	writeln('NAO');
end.
