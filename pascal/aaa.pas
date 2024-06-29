program aaa;
CONST MIN = 1; MAX = 100;
type
    vetor = array[MIN..MAX] of longint;
var
  v, k: vetor;
  i, d_v, tam_k, tam_v, j: longint;

procedure ler_num(var v:vetor; var tam: longint);
  var i, num: longint;
  begin
    i:=	1;
    read(num);
    while num <> 0 do
      begin
	v[i]:= num;
	i:= i + 1;
      end;
    tam:= i;
  end;

function inserir(var k:vetor; i: longint): longint;
  var tam, j: longint;
  begin
    tam:= 0;
    for j:=i to i + 10 do
      begin
	k[i]:= v[i];
	tam:= tam + 1;
      end;
      inserir:= tam;  
  end;

function digito(var k: vetor; tam: longint):longint;
  var i, s, resto: longint;
  begin
    s:=0;
    for i:= tam downto 2 do
      s:= s + v[i]*i;
    resto:= s mod 11;
    if resto >= 2 then
      digito:= 11 - resto
    else
      digito:= 0;
  end;

Begin
  ler_num(v, tam_v);
  i:= 1;
  while i<= tam_v do
    begin
      tam_k:= inserir(k, i);
      d_v:= digito(k, tam_k-2);
      if d_v <> k[tam_k-1] then
	begin
	  for j:= 1 to tam_k do
	      write(k[j]);
	  write(' invalido');
	end
      else
	d_v:= digito(k, tam_k-1);
	if d_v <> k[tam_k] then
	  begin
	    for j:= 1 to tam_k do
	      write(k[j]);
	    write(' invalido');
	  end
	else
	  begin
	    for j:= 1 to tam_k do
	      write(k[j]);
	    write(' valido');
	  end;
      i:= i + 11;	  
    end;
End.
