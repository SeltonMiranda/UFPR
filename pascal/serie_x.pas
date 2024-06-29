program serie;
var
  n, i, sinal, j: integer;
  s, x, num, den: real;
begin
    read(n, x);
	      
    i:= 1;
    s:= 0;
    num:= 1;
    den:= 1;
    sinal:= 1;
    j:= 1;

    while i <= n do
      begin
	  s:= s + sinal*(num/den);
	  i:= i + 1;
	  j:= j + 1;
	  num:= num*x*x*x*x;
	  den:= den*real(j);

	  if i mod 3 = 0 then
		sinal:= -sinal
	    else if (i mod 3 = 1) then
		    begin	    
			sinal:= -sinal;
			den:= 1;
			j:= 1;
		    end;
	      
      end;

writeln(s:0:2);
end.
