Program fundir;
CONST MIN = 1;
      MAX = 200;
type vetor = array[MIN-1..MAX + 1] of integer;

var
  n_v, n_w, n_r: integer;
  r, v, w: vetor;

procedure ler_tam(var n1, n2: integer);
  begin
      writeln('tamanho dos vetores v e w, respectivamente');
      read(n1, n2);
  end;

procedure ler_vetores(var v, w: vetor; n1, n2: integer);
  var i: integer;
  begin
      writeln('elementos vetor v: ');
      for i:= 1 to n1 do
	  read(v[i]);
      writeln();
      writeln('elementos vetor w: ');
      for i:= 1 to n2 do
	  read(w[i]);
  end;

procedure imprimir_vetores(var v, w: vetor; n1, n2: integer);
var i: integer;
  begin
      writeln(' vetor v: ');
      for i:= 1 to n1 do
	  write(v[i],' ');
      writeln();
      writeln(' vetor w: ');
      for i:= 1 to n2 do
	  write(w[i],' ');
  end;

procedure merge(var r, v, w: vetor; var n3: integer; n1, n2:integer );
  var i_r, i_v, i_w: integer;
  begin
      i_r:= 1; 
      i_v:= 1; 
      i_w:= 1;
      while (i_v <= n1) and (i_w <= n2) do
	begin
	    if v[i_v] < w[i_w] then
	      begin
		  r[i_r]:= v[i_v];
		  i_v:= i_v + 1;
	      end
	      else
		begin
		    r[i_r]:= w[i_w];
		    i_w:= i_w + 1;
		end;
		i_r:= i_r + 1;
	end;

	if i_v <= n1 then
	    for i_v:= i_v to n1 do
		begin
		    r[i_r]:=v[i_v];
		    i_r:= i_r + 1;
		end
	else
	  for i_w:= i_w to n2 do
	      begin
		  r[i_r]:= w[i_w];
		  i_r:= i_r + 1;
	      end;
	n3:= n1 + n2;     
  end;

procedure imprimir_vetor_mergeado(var r: vetor; tam: integer);
  var i: integer;
  begin
      writeln('aqui esta o vetor mergeado(r)');
      for i:= 1 to tam do
	write(r[i],' ');
      writeln();
  end;

begin
  ler_tam(n_v, n_w);
  ler_vetores(v, w, n_v, n_w);
  imprimir_vetores(v, w, n_v, n_w);
  merge(r, v, w, n_r, n_v, n_w);
  imprimir_vetor_mergeado(r, n_r);
end.
