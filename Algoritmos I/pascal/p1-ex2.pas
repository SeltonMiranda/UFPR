program p1;
var n, maior, i: longint;
begin
	read(n);
	maior:= 0;
	if n <> 0 then
	begin
	 while n <> 0 do
	 begin
	    i:=1;
	    while i < n do
	      i:=i*3;
	    if ((i = n) And (maior < n)) then
	      maior:=n;
	    read(n);
	 end;
 	end;
	writeln(maior);
end.

