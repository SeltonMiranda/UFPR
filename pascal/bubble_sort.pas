Program bubble_sort;
// faca para o exemplo: 4, 8, 2, 3, 7
type
   VETor = array[1..5] of integer;
var
  :i, j, aux: integer;
  v: vetor;
begin
    for i:= 1 to 5 do
	read(v[i]);
    
    for i:= 0 to 4 do
      begin
	for j:= 5 downto 1 do
	    begin
		if v[j-1] > v[j] then
		  begin
		      aux:= v[j-1];
		      v[j-1]:= v[j];
		      v[j]:= aux;
		  end;
	    end;
	
      end;
  
      for i:= 1 to 5 do
	  write(v[i],' ');
end.
