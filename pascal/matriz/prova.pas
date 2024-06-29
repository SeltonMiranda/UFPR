program prova;
type matriz = array[1..100,1..100] of integer;
var L, C, lat, long, i, j: integer; m: matriz;

function calcula(var m: matriz; L, C, inicioL, inicioC: integer): integer;
var soma, i, j: integer;
begin
  soma:= 0;
  for i:= inicioL to L do
    for j:= inicioC to C do
      if m[i,j] <> 0 then
	soma:= soma + m[i,j];
  calcula:= soma;
end;

function EncontrarCidade(var m: matriz; L, C: integer; var lat, long: integer): boolean;
var i, j, nw, ne, se, sw: integer;
begin
  for i:= 1 to L do
    for j:= 1 to C do
      begin
	if m[i,j] <> 0 then
	  begin
	    EncontrarCidade:= true;
	    nw:= calcula(m, i-1, C, 1, j-1);
	    ne:= calcula(m, i-1, C, 1, j+1);
	    se:= calcula(m, L, C, i+1,j+1);
	    sw:= calcula(m, L, C, i+1, 1);
	    if (nw <> ne) and (ne <> se) and (se <> sw) then
	      EncontrarCidade:= false
	    else
	      begin
		lat:= i;
		long:= j;
	      end;
	  end;
      end;
end;

procedure inicializar_mapa(var m: matriz; L, C: integer);
var i, j: integer;
begin
  for i:= 1 to L do
    for j:= 1 to C do
      m[i,j]:= 0;
end;

begin
  read(L, C);
  inicializar_mapa(m, L, C);

  read(i, j);
  read(m[i,j]);
  while (i <> 0) and (j <> 0) and (m[i,j]<>0) do
    begin
      read(i, j);
      read(m[i,j]);
    end;

  if EncontrarCidade(m, L, C, lat, long) then
    writeln(lat,' ', long)
  else
    writeln('Nenhuma cidade atende a restricao');
end.
