program inserir;

CONST MIN = 1;
      MAX = 200;
type 
    vetor = array[MIN-1..MAX+1] of real; //principal mundanca
var
  tam: integer;
  x: real;
  v: vetor;

procedure ler_tam(var n: integer);
  begin
      repeat
	  read(n);
      until (n>0) and (n <= 200);
  end;

procedure ler_valor(var x: real);
  begin
      writeln('qual valor deseja inserir?: ');
      repeat
	  read(x);
      until (x>0) and (x <= 200);
  end;

procedure insere(x: real; var v: vetor; var n: integer);
  var i: integer;
  begin
      v[0]:= x; //insere o sentinela aqui
      i:= n;
      while x < v[i] do
	  begin
	      v[i+1]:= v[i];
	      i:= i - 1;
	  end;
      v[i+1]:= x;
      n:= n + 1;
  end;

procedure ler_vetor(var v: vetor;var n: integer);
  var i: integer;
  begin
      writeln('escreva os elementos do vetor: ');
      for i:= 1 to n do
	  read(v[i]);
  end;

procedure imprimir_vetor(var v: vetor; n: integer);
  var i: integer;
  begin
      writeln('aqui esta o vetor');
      for i:= 1 to n do
	  write(v[i]:0:0,' ');
      writeln();
  end;

procedure imprimir_novo_vetor(var v: vetor; n: integer);
  var i: integer;
  begin
      writeln('este é o novo vetor: ');
      for i:= 1 to n do
	write(v[i]:0:0,' ');
      writeln();
  end;

begin
ler_tam(tam);
ler_vetor(v, tam);
imprimir_vetor(v, tam);
ler_valor(x);
insere(x, v, tam);
imprimir_novo_vetor(v, tam);

end.
