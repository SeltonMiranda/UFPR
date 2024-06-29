program cont;
type vetordigitos = array[0..9] of longint;
var i, num: Longint; contagem: vetordigitos;

function contar(n: longint): vetordigitos;
  var frequencia: vetordigitos; i: longint;
  begin
    for i:= 0 to 9 do
      frequencia[i]:= 0;

    while n <> 0 do
      begin
	frequencia[n mod 10]:= frequencia[n mod 10] + 1;
	n:= n div 10;
      end;

      contar:= frequencia;   
  end;

begin
  read(num);

  contagem:= contar(num);

  for i:= 0 to 9 do
    begin
      if contagem[i] <> 0 then
	if contagem[i] = 1 then
	  writeln(i, ' ocorre ', contagem[i], ' vez')
	else
	   writeln(i, ' ocorre ', contagem[i], ' vezes');
    end;
end.
