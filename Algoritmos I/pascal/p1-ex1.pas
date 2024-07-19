program p1ex1facil;
var lnn: real;
    i, n: longint;
begin
	read(n);
	lnn := 0; 
	i := 1;
	while i <= n do
	begin
		lnn := lnn + 1/i;
		i := i + 1;
	end;
	writeln(lnn:0:4,' ', ln(n):0:4,' ',lnn-ln(n):0:4);
end.
