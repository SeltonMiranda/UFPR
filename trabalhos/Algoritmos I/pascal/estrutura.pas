program estrutura;
CONST MIN=1; MAX=200;
type vetor = array[MIN..MAX] of longint;
var
  tam: longint;
  v: vetor;

procedure ler_tamanho(var tam: longint);
  begin
      repeat
	  read(tam);
      until (tam > 0) and (tam <= 200);
  end;
  
procedure ler_vetor(var v: vetor; tam: longint);
  var
    i: longint;
  begin
      for i:=1 to tam do
	  read(v[i]);
  end;

procedure imprimir_vetor(var v: vetor; tam: longint);
  var
    i: longint;
  begin
      for i:=1 to tam do
	  write('  ',v[i]);
      writeln()
  end;

procedure diminuir_vetor(var v: vetor; var tam: longint);
  begin
      v[MIN]:= v[tam];
      tam:= tam - 1;
  end;

procedure imprimir_vetor_menor(var v: vetor; tam: longint);
 var i: longint;
 begin
    for i:= 1 to tam do
	write('  ',v[i]);
    writeln();
 end;

begin
  ler_tamanho(tam);
  ler_vetor(v, tam);
  imprimir_vetor(v, tam);
  diminuir_vetor(v, tam);
  imprimir_vetor_menor(v, tam);
end.
