Program AcharMaisFrequente;
type vetor = array[1..200] of longint;
var
  v: vetor;    num_anterior, num_atual, MaiorVb: longint;

function valorbase(var v:vetor): longint;
var i, maior: longint;
begin
  maior:= 1;
  for i:= 2 to 9 do
    if v[i] > v[maior] then
      maior:= i;
    valorbase:= maior;
end;

procedure inicializarVetor(var v: vetor);
var i: longint;
begin
  for i:= 1 to 9 do
    v[i]:= 0;
end;

Begin
   read(num_atual);
   inicializarVetor(v);

   while num_atual <> 0 do
       begin
        num_anterior:= num_atual;
        read(num_atual);

        if num_atual = num_anterior then  
          begin
	    while num_atual = num_anterior do
	      begin
		num_anterior:= num_atual;
		read(num_atual);
	      end;
	    v[num_anterior]:= v[num_anterior] + 1; 
          end;
       end;
MaiorVb:= valorbase(v);
writeln(MaiorVb);
End.
