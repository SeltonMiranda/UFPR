program balanco;
type
	vetor=array[1..200] of longint;

procedure ler_numeros(var a: longint;var k: vetor);
  var
   i: longint;	 
  begin
      read(a);
      i:= 1;
      while k[i] <> 0 do
	begin
	    read(k[i]);
            i:= i + 1;	    
	end;	
  end;

function eh_balanceada(var a: longint; var k: vetor): boolean;
	var
		i:longint;
	begin
		i:= 1;
		while i <= a do
		 begin
	     		if k[i] + k[a] = k[i+1] + k[a-1] then
				eh_balanceada:= true
		        else
				eh_balanceada:= false;
		 i:= i + 1;
		 a:= a - 1;
		 end;
	end;

var
   n: longint;
   v: vetor;   
begin
	ler_numeros(n, v);

	if eh_balanceada(n, v) then
		writeln('SIM')
	else
		writeln('NAO');
	
		
end.
