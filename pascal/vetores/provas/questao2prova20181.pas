program questao2;
type vetor=array[1..200] of longint;
var v, vnum, vcont: vetor; tam, tamsemrepeticao, tamfrequencia: longint;

procedure imprimirOcorrencias(var vnum, vcont: vetor; tamvnum, tamvcont: longint);
var i: longint;
begin
  for i:= 1 to tamvnum do
    writeln(vnum[i],': ',vcont[i],' vezes');
end;

function vetorfrequencia(var v, vnum, vcont: vetor; tamv, tamvnum: longint): longint;
var i, j, tamvcont, cont: longint;
begin
  tamvcont:= 0;
  i:= 1;
  while i <= tamvnum do
    begin
      cont:= 0;
      j:= 1;
      while j <= tamv do
	begin
	  if vnum[i] = v[j] then
	    cont:= cont + 1;
	  j:= j + 1;
	end;
      tamvcont:= tamvcont + 1;
      vcont[tamvcont]:= cont;
      i:= i + 1;
    end;
  vetorfrequencia:= tamvcont;
end;

function estanovetor(var v: vetor; tam, x: longint): boolean;
var i: longint;
begin
  estanovetor:= false;
  for i:= 1 to tam do
    begin
      if v[i] = x then
	estanovetor:= true;
    end;
end;

function vetorsemrepeticao(var v, vnum: vetor; tamv: longint): longint;
var i, tamvnum: longint;
begin
  i:= 1;
  tamvnum:= 0;
  while i <= tamv do
    begin
      if not estanovetor(vnum, tamvnum, v[i]) then
	begin
	  tamvnum:= tamvnum + 1;
	  vnum[tamvnum]:= v[i];
	end;
      i:= i + 1;
    end;

  vetorsemrepeticao:= tamvnum;
end;

procedure lervetor(var v: vetor; var tam: longint);
var i, n: longint;
begin
  i:= 0;
  read(n);
  while n <> 0 do
    begin
      i:= i + 1;
      v[i]:= n;
      read(n);
    end;
  tam:= i;
end;

begin
  lervetor(v, tam);
  tamsemrepeticao:= vetorsemrepeticao(v, vnum, tam);
  tamfrequencia:= vetorfrequencia(v, vnum, vcont, tam, tamsemrepeticao);
  imprimirOcorrencias(vnum, vcont, tamsemrepeticao, tamfrequencia);
end.
