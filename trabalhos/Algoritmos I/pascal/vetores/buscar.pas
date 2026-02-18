program buscarstring;
type vetor = array[1..100] of longint;
var n1, n2, posicao: longint; v, k: vetor;

function encontrar(var v, k: vetor; tam_v, tam_k: longint): longint;
var encontrou: boolean; i, j: longint;
begin
  (*maneira de fazer pelo while*)
  i:= 1;
  while i <= tam_v do
    begin
      encontrou:= true;
      j:= 1;
      while j <= tam_k do
	begin
	  if v[i + j - 1] <> k[j] then
	    encontrou:= false;
	  j:= j + 1;
	end;
      if encontrou then
	encontrar:= i;
      i:= i + 1;	
    end;

    (* outra maneira de fazer pelo for-to*)
    (*for i:= 1 to tam_v do
      begin
	encontrou:= true;
	for j:= 1 to tam_k do
	  begin
	    if v[i + j - 1] <> k[j] then
	      encontrou:= false;
	  end;

	if encontrou then
	  begin
	    encontrar:= i;
	  end;
      end;*)
    end;

procedure lervetor(var vet: vetor; tam: longint);
  var i: longint;
  begin
    for i:=1 to tam do
      read(vet[i]);
  end;

begin
  read(n1, n2);
  lervetor(v, n1);
  lervetor(k, n2);
  posicao:= encontrar(v, k, n1, n2);

  if posicao = 0 then
    writeln('nao encontrou')
  else
    writeln('encontrou na posicao: ', posicao);
end.
